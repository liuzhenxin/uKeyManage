#include "verifypin.h"
#include "ui_verifypin.h"
std::string ChooseKeyDialog::PIN = "";
VerifyPin::VerifyPin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerifyPin)
{
    ui->setupUi(this);
    this->setWindowTitle("PIN码验证");

}

VerifyPin::~VerifyPin()
{
    qDebug()<<"析构pin码对话框";
    if(vpDapi)
    {
        delete vpDapi;
        vpDapi = nullptr;
    }
    if(phApp)
    {
        phApp = nullptr;
    }

    delete ui;
    qDebug()<<"析构pin码对话框结束";
}

void VerifyPin::on_inputPin_textChanged(const QString &arg1)
{
   pinCode = arg1;
}

void VerifyPin::on_okButton_clicked()
{
    dllName = ChooseKeyDialog::KEYNAMEFORCHOOSEDLL;
    if(dllName == "" || dllName == nullptr)
        dllName = HAITAI;
    qDebug()<<"选中的dll为::"<<dllName;
    vpDapi = new typeDefApi(dllName);

    if(!phApp || !vpDapi)
    {
        this->setWindowTitle("函数或应用句柄为空");
    }

    ChooseKeyDialog::PIN = UtilFunction::QString2CharPoint(pinCode);
    if(ChooseKeyDialog::PIN != "")
    {
        if(verifyPIN(phApp)){
            isExit = false;
            this->~VerifyPin();
        }
    }
    else {
        this->ui->inputPin->clear();
    }
}

int VerifyPin::verifyPIN(HAPPLICATION phApp)
{
    ULONG pulRetryCount = 4;
    int midRet;
    qDebug()<<"缓存pin::"<<QString::fromStdString(ChooseKeyDialog::PIN);
    midRet = vpDapi->SKF_VerifyPIN (phApp, 1, (char*)(ChooseKeyDialog::PIN).c_str(), &pulRetryCount);

    if(midRet == 0x0A000025)
    {
        qDebug()<<"pin码锁死，请解锁";
        this->setWindowTitle("pin码锁死，请解锁");
        this->ui->okButton->setEnabled(false);
        return 0;
    }
    if(midRet == 0x0A000024)
    {
        qDebug()<<"验证pin码失败::"<<QString::number(midRet,16);
        qDebug()<<"剩余输入次数::"<<pulRetryCount;
        qDebug()<<"pin错误"<<QString::fromStdString(ChooseKeyDialog::PIN);
        this->setWindowTitle("pin码错误，剩余"+QString::number(pulRetryCount)+"次");
        if(pulRetryCount == 0)
        {
            this->ui->okButton->setEnabled(false);
            return 0;
        }
    }
    if(midRet)
    {
        qDebug()<<"SKF_VerifyPIN错误"<<QString::number(midRet,16);
        return 0;
    }
    qDebug()<<"pin码正确"<<QString::number(midRet,16);
    return 1;
}

void VerifyPin::on_exitButton_clicked()
{
    isExit = true;
    this->~VerifyPin();
}
