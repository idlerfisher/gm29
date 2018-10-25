#include "cexcelreader.h"
#include <QAxObject>
#include <QAxWidget>

CExcelReader::CExcelReader(QObject *parent) :
    QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QODBC");
}

CExcelReader::CExcelReader(const QString &strFile, QObject *parent) :
    QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QODBC");
    m_strFile = strFile;
}

bool CExcelReader::open()
{
    if (m_strFile.isEmpty()) {
        qDebug() << "CExcelReader::open 文件名为空";
        return false;
    }

    if (m_db.isOpen()) {
        m_db.close();
    }

    QString strDbName = "Driver={Microsoft Excel Driver (*.xls)};Dbq=" + m_strFile + ";";
    m_db.setDatabaseName(strDbName);
    if (!m_db.open()) {
        qDebug() << tr("open %1 failed: %2").arg(m_strFile).arg(m_db.lastError().text());
        return false;
    }

    qDebug() << tr("open %1 success").arg(m_strFile);

    return true;
}

void CExcelReader::close()
{
    m_db.close();
}

void CExcelReader::foreachRow(const std::function<void(int, std::vector<QString>&)>& func)
{
    int count = 0;
    std::vector<QString> vec;

    QString strCmd = tr("select * from [%1$]").arg("Sheet1");
    QSqlQuery query(strCmd);
    qDebug() << strCmd;
//    QSqlQuery query("select * from [" + QString("Sheet1") + "$]");
    // Select range, place A1:B5 after $
    while (query.next()) {
        vec.clear();
        count = query.record().count();
        vec.resize(count);

        for (int i = 0; i < count; i++) {
            vec[i] = query.value(i).toString();
//            qDebug() << i << " -> " << record.fieldName(i);
        }
        if (func) {
            func(count, vec);
        }
    }
}

QStringList CExcelReader::getExcelSheets()
{
    QStringList strList;

    do {
        QAxWidget excel("Excel.Application");
        excel.setProperty("Visible", false);
        QAxObject* workbooks = excel.querySubObject("WorkBooks");
        if (!workbooks) {
            break;
        }
        workbooks->dynamicCall("Open (const QString&)", m_strFile);
        QAxObject* workbook = excel.querySubObject("ActiveWorkBook");
        if (!workbook) {
            break;
        }
        QAxObject* worksheets = workbook->querySubObject("WorkSheets");
        int count = worksheets->property("Count").toInt();
        for (int i = 1; i <= count; i++)
        {
            QAxObject* worksheet = workbook->querySubObject("Worksheets(int)", i);
            if (!worksheet) {
                break;
            }
            strList.append(worksheet->property("Name").toString());
        }
        excel.dynamicCall("Quit (void)");
    } while(0);

    return strList;
}

void CExcelReader::testExcelFromCom()
{
    //This example is from "http://www.cnblogs.com/findumars/p/5290132.html"

    QAxWidget excel("Excel.Application");
    excel.setProperty("Visible", true);
    QAxObject * workbooks = excel.querySubObject("WorkBooks");
    workbooks->dynamicCall("Open (const QString&)", QString("c:/test.xls"));
    QAxObject * workbook = excel.querySubObject("ActiveWorkBook");
    QAxObject * worksheets = workbook->querySubObject("WorkSheets");
    int intCount = worksheets->property("Count").toInt();
    for (int i = 1; i <= intCount; i++)
    {
        int intVal;
        QAxObject * worksheet = workbook->querySubObject("Worksheets(int)", i);
        qDebug() << i << worksheet->property("Name").toString();
        QAxObject * range = worksheet->querySubObject("Cells(1,1)");
        intVal = range->property("Value").toInt();
        range->setProperty("Value", QVariant(intVal+1));
        QAxObject * range2 = worksheet->querySubObject("Range(C1)");
        intVal = range2->property("Value").toInt();
        range2->setProperty("Value", QVariant(intVal+1));
    }
    QAxObject * worksheet = workbook->querySubObject("Worksheets(int)", 1);
    QAxObject * usedrange = worksheet->querySubObject("UsedRange");
    QAxObject * rows = usedrange->querySubObject("Rows");
    QAxObject * columns = usedrange->querySubObject("Columns");
    int intRowStart = usedrange->property("Row").toInt();
    int intColStart = usedrange->property("Column").toInt();
    int intCols = columns->property("Count").toInt();
    int intRows = rows->property("Count").toInt();
    for (int i = intRowStart; i < intRowStart + intRows; i++)
    {
        for (int j = intColStart; j <= intColStart + intCols; j++)
        {
            QAxObject * range = worksheet->querySubObject("Cells(int,int)", i, j );
            qDebug() << i << j << range->property("Value");
        }
    }
    excel.setProperty("DisplayAlerts", 0);
    workbook->dynamicCall("SaveAs (const QString&)", QString("c:/xlsbyqt.xls"));
    excel.setProperty("DisplayAlerts", 1);
    workbook->dynamicCall("Close (Boolean)", false);
    excel.dynamicCall("Quit (void)");
}
