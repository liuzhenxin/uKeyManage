#ifndef CHOOSEKEYDIALOG_H
#define CHOOSEKEYDIALOG_H

#include <QDialog>
#include <QDebug>

#define HAITAI  "SKFAPI20509.dll"
#define LONGMAI "mtoken_gm3000"
#define FEITIAN "HNCA3000GM.dll"
#define YALUETE "SMSKF.dll"

namespace Ui {
class ChooseKeyDialog;
}

class ChooseKeyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseKeyDialog(QWidget *parent = nullptr);
    ~ChooseKeyDialog();
public:
    static QString KEYNAMEFORCHOOSEDLL;
    static std::string PIN;
    static QString CREATEFILENAME;
//    static int CREATFILESIZE;
private slots:


    void on_HAITAICHOOSE_toggled(bool checked);

    void on_LONGMAICHOOSE_toggled(bool checked);

    void on_FEITIANCHOOSE_toggled(bool checked);

    void on_YALUETECHOOSE_toggled(bool checked);

private:
    Ui::ChooseKeyDialog *ui;
};

#endif // CHOOSEKEYDIALOG_H
