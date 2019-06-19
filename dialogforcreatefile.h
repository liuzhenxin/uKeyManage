#ifndef DIALOGFORCREATEFILE_H
#define DIALOGFORCREATEFILE_H

#include <QDialog>
#include <choosekeydialog.h>
namespace Ui {
class DialogForCreateFile;
}

class DialogForCreateFile : public QDialog
{
    Q_OBJECT

public:
    explicit DialogForCreateFile(QWidget *parent = nullptr);
    ~DialogForCreateFile();

private slots:
    void on_CreateFileWithName_clicked();

    void on_ExitCreateDialog_clicked();

    void on_FileNameInput_textChanged(const QString &arg1);

//    void on_spinBox_valueChanged(int arg1);

private:
    Ui::DialogForCreateFile *ui;
    QString filename;
//    int filesize;
};

#endif // DIALOGFORCREATEFILE_H
