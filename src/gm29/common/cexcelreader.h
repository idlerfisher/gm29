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

    //��ODBC��ȡexcel�ļ�
    bool open();

    //�ر�ODBC
    void close();

    //���������в����ûص�
    void foreachRow(const std::function<void(int, std::vector<QString>&)>& func);

    //��ȡexcel�ļ��������ӱ������
    QStringList getExcelSheets();

    //����com�ӿڲ���excel������
    void testExcelFromCom();

private:
    QString m_strFile;
    QSqlDatabase m_db;
};

#endif // CEXCELREADER_H
