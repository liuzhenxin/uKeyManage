#ifndef VERIFYPIN_H
#define VERIFYPIN_H

#include <QDialog>
#include <QDebug>
#include <typedefine.h>
#include <choosekeydialog.h>
#include <utilfunction.h>
#include <iostream>
#include <QMessageBox>
namespace Ui {
class VerifyPin;
}

class VerifyPin : public QDialog
{
    Q_OBJECT
signals:

public:
    explicit VerifyPin(QWidget *parent = nullptr);
    ~VerifyPin();

private:
    int verifyPIN(HAPPLICATION phApp);

private slots:
    void on_inputPin_textChanged(const QString &arg1);

    void on_okButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::VerifyPin *ui;

public:
    QString dllName = nullptr;
    QString pinCode = nullptr;
    bool isExit = false;
    bool islocked = false;
    HAPPLICATION phApp = nullptr;
    typeDefApi *vpDapi = nullptr;
};

#endif // VERIFYPIN_H
