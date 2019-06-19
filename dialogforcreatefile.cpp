#include "dialogforcreatefile.h"
#include "ui_dialogforcreatefile.h"
QString ChooseKeyDialog::CREATEFILENAME = "";
DialogForCreateFile::DialogForCreateFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogForCreateFile)
{
    ui->setupUi(this);
}

DialogForCreateFile::~DialogForCreateFile()
{
    delete ui;
}

void DialogForCreateFile::on_CreateFileWithName_clicked()
{
    ChooseKeyDialog::CREATEFILENAME = filename;
//    ChooseKeyDialog::CREATFILESIZE = filesize;
    this->~DialogForCreateFile();
}

void DialogForCreateFile::on_ExitCreateDialog_clicked()
{
    ChooseKeyDialog::CREATEFILENAME = "";
//    ChooseKeyDialog::CREATFILESIZE = 0;
    this->~DialogForCreateFile();
}

void DialogForCreateFile::on_FileNameInput_textChanged(const QString &arg1)
{
    filename = arg1;
}

//void DialogForCreateFile::on_spinBox_valueChanged(int arg1)
//{
//    filesize = arg1;
//}
