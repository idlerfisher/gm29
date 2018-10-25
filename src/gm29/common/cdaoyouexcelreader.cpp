#include "cdaoyouexcelreader.h"

CDaoyouExcelReader::CDaoyouExcelReader(const QString &strFileName, QObject *parent) :
    QObject(parent)
{
    m_strFileName = strFileName;
    m_pXls = xlCreateBook();
    if (!m_pXls) {
        return;
    }
}

bool CDaoyouExcelReader::load()
{
    if (!m_pXls) {
        return false;
    }

    QTextCodec* codec = QTextCodec::codecForName("gb2312");

    m_pXls->load(m_strFileName.toLatin1().data());
    int nSheetCount = m_pXls->sheetCount();
    for (int i = 0; i < nSheetCount; i++) {
        libxl::Sheet* pSheet = m_pXls->getSheet(i);
        if (!pSheet) {
            return false;
        }
        qDebug() << codec->toUnicode(pSheet->name());
    }

    return true;
}
