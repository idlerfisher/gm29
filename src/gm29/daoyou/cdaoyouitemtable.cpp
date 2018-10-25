#include "cdaoyouitemtable.h"

#define ITEM_TABLE_FILE "itemtable.txt"

CDaoYouItemTable::CDaoYouItemTable(QObject *parent) :
    QObject(parent)
{
}

CDaoYouItemTable &CDaoYouItemTable::getInstance()
{
    static CDaoYouItemTable obj;
    return obj;
}

void CDaoYouItemTable::loadFile()
{
    QFile file(ITEM_TABLE_FILE);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "open failed";
        return;
    }

    QTextStream stream(&file);
    QString strLine;
    QStringList strList;
    while (!stream.atEnd()) {
        strLine = stream.readLine();
        strList = strLine.split("\t");
        if (!strList.empty() && strList.size() >= 2) {
            m_mapCache.insert(strList.at(1), strList.at(0).toInt());
//            qDebug() << strList;
        } else {
            qDebug() << "split error:" + strLine;
        }
    }

    file.close();
}

void CDaoYouItemTable::getItemList(QList<QString> &strList)
{
    strList = m_mapCache.keys();
}

void CDaoYouItemTable::getItemTidList(QList<QString>& tidList)
{
    QMap<QString,int> tmpMap;
    QList<int> intList = m_mapCache.values();

    for (int i = 0; i < intList.size(); i++)
    {
        tmpMap[tr("%1").arg(intList.at(i))] = tmpMap[tr("%1").arg(intList.at(i))] + 1;
    }
    tidList = tmpMap.keys();
}

QString CDaoYouItemTable::getGMAddItem(const QString &strItemName, int count)
{
    int nTid = getTidByItemName(strItemName);
    QString strCmd = tr("me.gm.addItem(%1,%2)").arg(nTid).arg(count);
    return strCmd;
}

QString CDaoYouItemTable::getTid(const QString& strItemName)
{
    int nTid = getTidByItemName(strItemName);
    return tr("%1").arg(nTid);
}

int CDaoYouItemTable::getTidByItemName(const QString &strItemName)
{
    return m_mapCache.value(strItemName);
}

QStringList CDaoYouItemTable::getNameByTid(int tid)
{
    QStringList strList;
    QMapIterator<QString, int> i(m_mapCache);
    while (i.hasNext()) {
        i.next();
        if (i.value() == tid) {
            strList.append(i.key());
        }
    }
    return strList;
}
