#include "cdaoyougmui.h"
#include "ui_cdaoyougmui.h"
#include "cdaoyouitemtable.h"

CDaoYouGmUi::CDaoYouGmUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CDaoYouGmUi)
{
    ui->setupUi(this);

    CDaoYouItemTable::getInstance().loadFile();

    QList<QString> strItemList;
    CDaoYouItemTable::getInstance().getItemList(strItemList);

    m_pCompleter = new QCompleter(strItemList, this);
    m_pCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    m_pCompleter->setMaxVisibleItems(30);
    ui->lineItemName->setCompleter(m_pCompleter);
//    qDebug() << strItemList;


    QList<QString> tidList;
    CDaoYouItemTable::getInstance().getItemTidList(tidList);
//    qDebug() << tidList;

    m_pCompleterTid = new QCompleter(tidList, this);
    m_pCompleterTid->setCaseSensitivity(Qt::CaseInsensitive);
    m_pCompleterTid->setMaxVisibleItems(30);
    ui->lineItemTid->setCompleter(m_pCompleterTid);
}

CDaoYouGmUi::~CDaoYouGmUi()
{
    delete ui;
}

void CDaoYouGmUi::on_lineItemName_returnPressed()
{
    QString strCmd = CDaoYouItemTable::getInstance().getTid(ui->lineItemName->text());
    qApp->clipboard()->setText(strCmd);
    ui->textGm->setText(strCmd);
}


void CDaoYouGmUi::on_btnCopy_clicked()
{
    qApp->clipboard()->setText(ui->textGm->toPlainText());
}

void CDaoYouGmUi::on_lineItemTid_returnPressed()
{
    QStringList nameList = CDaoYouItemTable::getInstance().getNameByTid(ui->lineItemTid->text().toInt());
    ui->textItemName->setText(nameList.join("\n"));
}

void CDaoYouGmUi::on_btnCopyName_clicked()
{
    qApp->clipboard()->setText(ui->textItemName->toPlainText());
}
