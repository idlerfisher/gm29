#ifndef CEXCELREADER_H
#define CEXCELREADER_H

#include <QtSql>
#include <QtCore>
#include <iostream>
#include <string>
#include <functional>

class CExcelReader : QObject
{
    Q_OBJECT
public:
    CExcelReader(QObject *parent = 0);
    CExcelReader(const QString& strFile, QObject *parent = 0);

    //打开ODBC读取excel文件
    bool open();

    //关闭ODBC
    void close();

    //遍历所有行并调用回调
    void foreachRow(const std::function<void(int, std::vector<QString>&)>& func);

    //获取excel文件的所有子表格名称
    QStringList getExcelSheets();

    //利用com接口操作excel的例子
    void testExcelFromCom();

private:
    QString m_strFile;
    QSqlDatabase m_db;
};

#endif // CEXCELREADER_H
