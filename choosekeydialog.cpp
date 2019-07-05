#include "choosekeydialog.h"
#include "ui_choosekeydialog.h"
QString ChooseKeyDialog::KEYNAMEFORCHOOSEDLL = HAITAI;
ChooseKeyDialog::ChooseKeyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseKeyDialog)
{
    ui->setupUi(this);

}

ChooseKeyDialog::~ChooseKeyDialog()
{
    qDebug()<<"chooseKey 析构::"<<KEYNAMEFORCHOOSEDLL;
    delete ui;
}



void ChooseKeyDialog::on_HAITAICHOOSE_toggled(bool checked)
{
    if(checked)
        KEYNAMEFORCHOOSEDLL = HAITAI;
    qDebug()<<"this is haitai has be choosed ："<<KEYNAMEFORCHOOSEDLL;
}

void ChooseKeyDialog::on_LONGMAICHOOSE_toggled(bool checked)
{
    if(checked)
        KEYNAMEFORCHOOSEDLL = LONGMAI;
    qDebug()<<"this is longmai has be choosed ："<<KEYNAMEFORCHOOSEDLL;
}

void ChooseKeyDialog::on_FEITIANCHOOSE_toggled(bool checked)
{
    if (checked)
        KEYNAMEFORCHOOSEDLL = FEITIAN;
    qDebug() << "this is feitian has be choosed ：" << KEYNAMEFORCHOOSEDLL;
}
