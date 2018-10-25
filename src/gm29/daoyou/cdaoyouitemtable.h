#ifndef CDAOYOUITEMTABLE_H
#define CDAOYOUITEMTABLE_H

#include <QObject>
#include <QtCore>
//#include <map>

class CDaoYouItemTable : public QObject
{
    Q_OBJECT
protected:
    explicit CDaoYouItemTable(QObject *parent = 0);

public:
    static CDaoYouItemTable& getInstance();
    void loadFile();
    void getItemList(QList<QString>& strList);
    void getItemTidList(QList<QString>& tidList);
    QString getGMAddItem(const QString& strItemName, int count = 1);
    QString getTid(const QString& strItemName);
    QStringList getNameByTid(int tid);

private:
    int getTidByItemName(const QString& strItemName);

private:
//    std::map<QString, int> m_mapCache;
    QMap<QString, int> m_mapCache;
};

#endif // CDAOYOUITEMTABLE_H
