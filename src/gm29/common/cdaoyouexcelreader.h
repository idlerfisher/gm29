#ifndef CDAOYOUEXCELREADER_H
#define CDAOYOUEXCELREADER_H

#include <QtCore>
#include <QObject>
#include "libxl/libxl.h"

class CDaoyouExcelReader : public QObject
{
    Q_OBJECT
public:
    explicit CDaoyouExcelReader(const QString& strFileName, QObject *parent = 0);

    //载入基本信息
    bool load();
    
private:
    libxl::Book* m_pXls;
    QString m_strFileName;
};

#endif // CDAOYOUEXCELREADER_H
