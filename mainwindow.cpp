#include "mainwindow.h"
#include "ui_mainwindow.h"
QTextCodec *tc =QTextCodec::codecForName("UTF-8");
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setTabEnabled(1,false);
    ui->tabWidget->setTabEnabled(2,false);
    ui->unlockPinButton->setEnabled(false);
    // 起始key类型选择窗口
    chooseKeyD = new ChooseKeyDialog(this);
    chooseKeyD->exec();
    // 开启usb插拔判断线程
//    QSharedPointer<usbThread> HaiTaiUsb = QSharedPointer<usbThread>(new usbThread(HAITAI));     // 海泰插拔key提示线程
    HaiTaiUsb = new usbThread(HAITAI);    // 龙脉插拔key提示线程
    HaiTaiUsb->start();
//    QSharedPointer<usbThread> LongMaiUsb = QSharedPointer<usbThread>(new usbThread(LONGMAI));   // 龙脉插拔key提示线程
    LongMaiUsb = new usbThread(LONGMAI);    // 龙脉插拔key提示线程
    LongMaiUsb->start();
    // 切换到当前选择的dll
    changeDll();
    // 槽函数
//    connect(this, SIGNAL(apiTypeChooseMsg(typeDefApi*)),usb ,SLOT(apiTypeChoose(typeDefApi*)));
//    connect(HaiTaiUsb.data(),SIGNAL(usbMsg(int)),this,SLOT(usbMsgS(int)));
//    connect(LongMaiUsb.data(),SIGNAL(usbMsg(int)),this,SLOT(usbMsgS(int)));
    connect(HaiTaiUsb,SIGNAL(usbMsg(int)),this,SLOT(usbMsgS(int)));
    connect(LongMaiUsb,SIGNAL(usbMsg(int)),this,SLOT(usbMsgS(int)));
    connect(this,SIGNAL(deletefile(HAPPLICATION,QString)),this,SLOT(deleteButton(HAPPLICATION,QString)));
    connect(this->ui->FileTree, SIGNAL(customContextMenuRequested(const QPoint& )), this, SLOT(ShowContextMenu(const QPoint&)));
//    connect(pinDailog,SIGNAL(pinMsg(QString)),this,SLOT(pinRecvS(QString)));

    // 初始化comboBox
    if(ChooseKeyDialog::KEYNAMEFORCHOOSEDLL == HAITAI)
        ui->comboBox->setCurrentIndex(1);
    if(ChooseKeyDialog::KEYNAMEFORCHOOSEDLL == LONGMAI)
        ui->comboBox->setCurrentIndex(2);
}

MainWindow::~MainWindow()
{
    qDebug()<<"MainWindow 析构";
    //断开与设备连接
    if(phDev)
        Dapi->SKF_DisConnectDev(phDev);

    if(chooseKeyD)
    {
        delete chooseKeyD;
        chooseKeyD = nullptr;
    }
    if(Dapi)
    {
        delete Dapi;
        Dapi = nullptr;
    }
    if(HaiTaiUsb)
    {
        HaiTaiUsb = nullptr;
    }

    if(LongMaiUsb)
    {
        LongMaiUsb = nullptr;
    }
    delete ui;
}

void MainWindow::on_FileTree_clicked(const QModelIndex &index)
{
    // 关闭应用
    if(phApp)
        Dapi->SKF_CloseApplication(phApp);
    // 关闭设备
    if(phDev)
        Dapi->SKF_DisConnectDev(phDev);
    phDev = nullptr;
    phApp = nullptr;
    ui->deleteButton->setEnabled(false);
    ui->ImportSymmKeyButton->setEnabled(false);
    ui->WriteESealDataButton->setEnabled(false);
    ULONG uRet;
    ui->TBItemInfo->clear();
    qDebug()<<index<<"&"<<index.row()<<"&"<<index.parent().data().toString();

    if(index.parent().data().toString() == ""){

        std::string sTmpStr = index.data().toString().toStdString();
        char *cTmpStr = (char*)sTmpStr.c_str();
        connectDev(cTmpStr);
        //char pDevInfo[1024] = { 0 };
        DEVINFO pDevInfo;
        uRet = Dapi->SKF_GetDevInfo(phDev, &pDevInfo);
        if(uRet)
        {
            qDebug()<<"获取设备信息出错::"<<QString::number(uRet,16);
            return;
        }

        //    qDebug()<<((DEVINFO*)pDevInfo)->SerialNumber;
        QString TBItemMsg = "";
        TBItemMsg += "\nLable:\t";
        TBItemMsg += pDevInfo.Label;
        TBItemMsg += "\nIssuer:\t";
        TBItemMsg += pDevInfo.Issuer;
        TBItemMsg += "\nAlgSymCap:\t";
        TBItemMsg += QString::number(pDevInfo.AlgSymCap);
        TBItemMsg += "\nSerialNumber:\t";
        TBItemMsg += pDevInfo.SerialNumber;
        TBItemMsg += "\nTotalSpace:\t";
        TBItemMsg += QString::number(pDevInfo.TotalSpace);
        TBItemMsg += "\nFreeSpace:\t";
        TBItemMsg += QString::number(pDevInfo.FreeSpace);
        ui->TBItemInfo->setText(QString(TBItemMsg));
        //        TBItemMsg.clear();

    }
    else
    {
        //应用
        if(index.parent().parent().data().toString() == "")
        {
            std::string sTmpStr = index.parent().data().toString().toStdString();
            char *cTmpStr = (char*)sTmpStr.c_str();
            connectDev(cTmpStr);
            std::string sTmpStrSub = index.data().toString().toStdString();
            uRet = Dapi->SKF_OpenApplication(phDev, (char*)sTmpStrSub.c_str(), &phApp);
            if(uRet)
            {
                qDebug()<<"打开应用出错::"<<QString::number(uRet,16);
                return;
            }

            qDebug()<<"应用名::"<<index.data().toString();

            QString TBItemMsg = "";
            TBItemMsg = "\n应用名:\t" + index.data().toString();
            ui->TBItemInfo->setText(QString(TBItemMsg));

        }
        else
        {
            if(index.parent().parent().parent().data().toString() == "")
            {
                //
                std::string sTmpStr = index.parent().parent().data().toString().toStdString();
                char *cTmpStr = (char*)sTmpStr.c_str();
                connectDev(cTmpStr);
                char *cTmpStrSub = (char*)index.parent().data().toString().toStdString().c_str();
                qDebug()<<"应用名::"<<index.parent().data().toString();

                uRet = Dapi->SKF_OpenApplication(phDev, cTmpStrSub, &phApp);
                if(uRet)
                {
                    qDebug()<<"打开应用出错::"<<QString::number(uRet,16);
                    return;
                }
                verifyPIN(phApp);
                qDebug()<<"文件名::"<<index.data().toString();
                FILEATTRIBUTE pFileInfo;
                ZeroMemory(&pFileInfo, sizeof(pFileInfo));

                QString qString = index.data().toString();
                std::string cString = qString.toStdString();
                uRet = Dapi->SKF_GetFileInfo(phApp, (char*)cString.c_str(), &pFileInfo);
                if(uRet){
                    //获取文件属性失败
                    qDebug()<<"获取文件属性错误::"<<QString::number(uRet,16);
                }
                BYTE fileBuf[4096*20];
                memset(fileBuf,0,4096*20);
                ULONG iReadLen = 4096*20;
                uRet = Dapi->SKF_ReadFile (phApp,(char*)cString.c_str(), 0, pFileInfo.FileSize, fileBuf, &iReadLen);
                if(uRet){
                    //读失败
                    qDebug()<<"读取文件错误::"<<QString::number(uRet,16);
                }
                ui->TBItemInfo->setText((char*)fileBuf);
                //                qDebug()<<fileBuf;
                ui->deleteButton->setEnabled(true);
                curItemName = qString;

            }

        }
    }
    if(phApp == nullptr)
    {
        ui->tabWidget->setTabEnabled(1,false);
        ui->tabWidget->setTabEnabled(2,false);
    }
    else
    {
        ui->tabWidget->setTabEnabled(1,true);
        ui->tabWidget->setTabEnabled(2,true);
    }
}

void MainWindow::connectDev(char* cConDevTmpStr)
{
    qDebug()<<"设备名::"<<cConDevTmpStr;

    ULONG pulDevStateT=128,uConDevRet=128;
    uConDevRet = Dapi->SKF_GetDevState(cConDevTmpStr, &pulDevStateT);

    qDebug()<<"连接状态::"<<pulDevStateT<<"::"<<(pulDevStateT == 0x00000001)<<"::"<<(phDev == nullptr);

    if(pulDevStateT == 0x00000001/* && phDev == nullptr*/)
    {

        qDebug()<<"检测设备是否连接";
        //连接到设备
        uConDevRet = Dapi->SKF_ConnectDev(cConDevTmpStr, &phDev);
        if(uConDevRet)
        {
            qDebug()<<"连接设备出错::"<<QString::number(uConDevRet,16);
            return;
        }
    }

}

void MainWindow::deleteButton(HAPPLICATION phApp,QString curItemName)
{
    // emit deletefile(phApp,index.data().toString());
    ui->TBItemInfo->clear();
    ui->TBItemInfo->setText(curItemName);

    verifyPIN(phApp);
    // 验PIN end

    int idRet = Dapi->SKF_DeleteFile(phApp , (char*)curItemName.toStdString().c_str());
    if(idRet)
    {
        qDebug()<<"删除失败::"<<QString::number(idRet,16);
        curItemName = "删除失败"+QString::number(idRet,16);
        ui->TBItemInfo->setText(curItemName);
        return;
    }
    else
    {
        curItemName += "删除成功";
        ui->TBItemInfo->setText(curItemName);
        treeView_model();
    }

}

void MainWindow::on_deleteButton_clicked()
{
    emit deletefile(phApp,curItemName);
}

void MainWindow::on_reflashButton_clicked()
{
    ui->TBItemInfo->clear();
    treeView_model();
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1 == "海泰")
    {
        ChooseKeyDialog::KEYNAMEFORCHOOSEDLL = HAITAI;
    }
    if(arg1 == "龙脉")
    {
        ChooseKeyDialog::KEYNAMEFORCHOOSEDLL = LONGMAI;
    }
    changeDll();
}

void MainWindow::changeDll()
{
    ui->resultBrowser->clear();
    ui->textInput->clear();
    ui->tabWidget->setTabEnabled(1,false);
    ui->tabWidget->setTabEnabled(2,false);
    ui->ContainerList->clear();
    ui->ContainerBrowser->clear();
    ui->deleteButton->setEnabled(false);
    ui->ImportSymmKeyButton->setEnabled(false);

    if(phDev)
    {
        Dapi->SKF_DisConnectDev(phDev);
        phDev = nullptr;
    }
    if(chooseKeyD)
    {
        delete chooseKeyD;
        chooseKeyD = nullptr;
    }

    if(Dapi)
    {
        delete Dapi;
        Dapi = nullptr;
    }
//    chooseKeyD = new ChooseKeyDialog(this);
//    chooseKeyD->exec();
    QString mwQDllName = ChooseKeyDialog::KEYNAMEFORCHOOSEDLL;
    qDebug()<<mwQDllName;

    // 获取dll入口指针
    Dapi = new typeDefApi(mwQDllName);
    // 通过信号向usb线程传递dll入口指针
//    emit apiTypeChooseMsg(Dapi);
    // 实例化树状图内置模型
    model = new QStandardItemModel(ui->FileTree);
    // 树状图模型定义
    treeView_model();

//    usb = new usbThread(mwQDllName);
//    usb->start();
}

void MainWindow::treeView_model()
{
    ui->resultBrowser->clear();
    ui->textInput->clear();
    ui->deleteButton->setEnabled(false);
    ui->tabWidget->setTabEnabled(1,false);
    ui->tabWidget->setTabEnabled(2,false);
    ui->ContainerList->clear();
    ui->ContainerBrowser->clear();
    ui->ImportSymmKeyButton->setEnabled(false);
    ui->WriteESealDataButton->setEnabled(false);
    // 关闭应用
    if(phApp)
        Dapi->SKF_CloseApplication(phApp);
    // 关闭设备
    if(phDev)
       Dapi->SKF_DisConnectDev(phDev);
    phDev = nullptr;
    ui->deleteButton->setEnabled(false);
    // fileItem *model = new fileItem();
    qDebug()<<"treeView_model in";
    model->clear();

    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("Usb Key Info")/*<<QStringLiteral("信息")*/);
    // 枚举设备 SKF_EnumDev(BOOL bPresent, LPSTR szNameList, ULONG *pulSize)
    char DevList[512] = {0};
    ULONG DevCount = 512;
    qDebug()<<"枚举设备开始";
    ULONG iRet = Dapi->SKF_EnumDev(true,DevList,&DevCount);
    if(iRet)
    {
        QMessageBox::information(this,"设备","无可用设备",nullptr,nullptr);
        return;
    }
    QStandardItem *itemIndex1;
    for(int i = 0;DevList[i] != 0x00; i = i + (int)strlen(&DevList[i]) + 1)
    {
        QString tmpDev = DevList+i;
        /*QStandardItem */itemIndex1 = new QStandardItem(tmpDev);/*设备名或ID*/
        model->appendRow(itemIndex1);
        std::string m_tmp = tmpDev.toStdString();
        char *m_TmpStr = (char*)m_tmp.c_str();
        connectDev(m_TmpStr);
        // 枚举应用
        char szAppName[512] = {0};
        ULONG pulSize = 512;
        qDebug()<<"枚举应用开始"<<phDev;
        iRet = Dapi->SKF_EnumApplication(phDev,szAppName,&pulSize);
        if(iRet || pulSize <1)
        {
            qDebug()<<"枚举应用出错:: "<<QString::number(iRet,16);
            return;
        }
        for(int j = 0 ; szAppName[j] != 0x00 ; j = j + (int)strlen(&szAppName[j]) + 1)
        {
            phApp = nullptr;
            iRet = Dapi->SKF_OpenApplication(phDev, &szAppName[j], &phApp);
            if(iRet)
            {
                qDebug()<<"打开应用出错::"<<QString::number(iRet,16);
                return;
            }
            QString tmpApp = szAppName+j;
            qDebug()<<tmpApp;
            QStandardItem *itemIndex2 = new QStandardItem(tmpApp);
            itemIndex1->appendRow(itemIndex2);
            // 枚举文件 加入model 显示在treeview中
            char cTmpBuf[512] = {0};
            ULONG iTmpBufLen = 512;

            iRet = Dapi->SKF_EnumFiles(phApp,cTmpBuf,&iTmpBufLen);
            if(iRet || iTmpBufLen == 0){
                // 枚举失败
                qDebug()<<"枚举文件失败"<<QString::number(iRet,16);
                return;
            }
            unsigned int k = 0;
            while(cTmpBuf[k] != 0x00){
                QString tmpFile = cTmpBuf+k;
                qDebug()<<tmpFile;
                QStandardItem *itemIndex3 = new QStandardItem(tmpFile);
                itemIndex2->appendRow(itemIndex3);
                k = k + strlen(&cTmpBuf[k]) +1;
            }

            // 枚举容器加入list，在容器选项卡中显示
            char cTmpBufCon[512] = {0};
            ULONG uTmpBufConLen = 512;

            iRet = Dapi->SKF_EnumContainer(phApp , cTmpBufCon , &uTmpBufConLen);
            if(iRet || uTmpBufConLen == 0){
                // 枚举失败
                qDebug()<<"枚举容器失败"<<QString::number(iRet,16);
                return;
            }
            k = 0;
            while(cTmpBufCon[k] != 0x00){
                QString tmpCon = cTmpBufCon+k;
                qDebug()<<tmpCon;
                // 写入listview
                ui->ContainerList->addItem(tmpCon);
                k = k + strlen(&cTmpBufCon[k]) +1;
            }

            // 所有项目加入容器 关闭应用
            if(phApp)
                Dapi->SKF_CloseApplication(phApp);
        }
         qDebug()<<"枚举应用结束";
         // 关闭设备
         if(phDev)
            Dapi->SKF_DisConnectDev(phDev);
    }
    ui->FileTree->setModel(model);
    qDebug()<<"treeView_model out";
}

void MainWindow::usbMsgS(int type)
{
    if(1 == type)
    {
        QMessageBox::information(this,"usb","USBKey已插入",nullptr,nullptr);

    }
    if(2 == type)
    {
        QMessageBox::information(this,"usb","USBKey已拔出",nullptr,nullptr);
    }
    treeView_model();
}

int MainWindow::verifyPIN(HAPPLICATION phApp)
{

    if(ChooseKeyDialog::PIN == ""/* || QString(ChooseKeyDialog::PIN).indexOf("\d{6,6}") == -1*/)
    {
        qDebug()<<"无缓存";
        // PIN码不合法或为空
        pinDailog = new VerifyPin(this);
        pinDailog->phApp = phApp;
        pinDailog->exec();
        if(pinDailog->isExit)
        {
            treeView_model();
            pinDailog = nullptr;
            return 0;
        }
        qDebug()<<"PIN码验证成功";
        pinDailog = nullptr;
        return 1;
    }
    qDebug()<<"有缓存::"<<QString::fromStdString(ChooseKeyDialog::PIN)<<"::phapp::"<<phApp;
    // PIN码合法
    ULONG pulRetryCount = 4;
    int  midRet = Dapi->SKF_VerifyPIN (phApp, 1, (char*)(ChooseKeyDialog::PIN).c_str(), &pulRetryCount);
    if(midRet == 0x0A000025)
    {
        qDebug()<<"pin码锁死，请解锁";
        this->setWindowTitle("pin码锁死，请解锁");
        return 0;
    }
    if(midRet == 0x0A000024)
    {
        ChooseKeyDialog::PIN = "";
        qDebug()<<"验证pin码失败::"<<QString::number(midRet,16);
        qDebug()<<"剩余输入次数::"<<pulRetryCount;
        qDebug()<<"pin错误"<<QString::fromStdString(ChooseKeyDialog::PIN);
        this->setWindowTitle("pin码错误，剩余"+QString::number(pulRetryCount)+"次");
        if(pulRetryCount == 0)
        {
            return 0;
        }
    }
    return 1;
//    ULONG pulRetryCount = 4;
//    int midRet;
//    char* pin = UtilFunction::QString2CharPoint(pinCode);
//    qDebug()<<"缓存pin::"<<pin;
////    while(1)
////    {
//        if(pin)
//        {
//            pinDailog = new VerifyPin(this);

//            pinDailog->exec();

//            if(pinDailog->isExit)
//            {
//                treeView_model();
//                pinDailog = nullptr;
//                return 0;
//            }
//            pin =  UtilFunction::QString2CharPoint(pinDailog->pinCode);
//            pinCode = pinDailog->pinCode;
//        }
//        if(!pin)
//             return 0;
//        qDebug()<<QString(pin);
//        midRet = Dapi->SKF_VerifyPIN (phApp, 1, pin, &pulRetryCount);
//        if(midRet == 0x0A000025)
//        {
//            qDebug()<<"pin码锁死，请解锁";
//            ui->unlockPinButton->setEnabled(true);
//        }
//        if(midRet == 0x0A000024)
//        {
//            qDebug()<<"验证pin码失败::"<<QString::number(midRet,16);
//            curItemName = "验证pin码失败"+QString::number(midRet,16);
//            ui->TBItemInfo->setText(curItemName);
//            qDebug()<<"剩余输入次数::"<<pulRetryCount;
//            qDebug()<<"pin错误"<<QString(pin);
//            pinDailog = nullptr;
//            if(pulRetryCount == 0)
//                return 0;
////            continue;
//        }
//        pinDailog = nullptr;
//        return 1;
////    }
}

void MainWindow::on_ContainerList_itemClicked(QListWidgetItem *item)
{
    qDebug()<<item->text()<<"|"<<phApp<<"|"<<phDev;
    if(!phApp)
    {
        qDebug()<<"空应用句柄";
        return;
    }
//    if(!verifyPIN(phApp))
//    {
//        return;
//    }
    mhContainer = nullptr;
    ULONG ilRet = Dapi->SKF_OpenContainer(phApp,(char*)(item->text()).toStdString().c_str(),&mhContainer);
    if(ilRet)
    {
        qDebug()<<"打开容器出错"<<QString::number(ilRet,16);
        ui->ContainerBrowser->setText("打开容器出错"+QString::number(ilRet,16));
        return;
    }
    ContainerName = item->text();
    if(ContainerName != nullptr)
    {
        ui->ImportSymmKeyButton->setEnabled(true);
        ui->WriteESealDataButton->setEnabled(true);
    }else{
        ui->ImportSymmKeyButton->setEnabled(false);
        ui->WriteESealDataButton->setEnabled(false);
    }
    char ucCertS[4096] = {0};
    ULONG ulCertLen = 4096;
    ilRet = Dapi->SKF_ExportCertificate(mhContainer, true,  (BYTE*)ucCertS, &ulCertLen);
    if(ilRet)
    {
        qDebug()<<"导出签名证书出错"<<QString::number(ilRet,16);
        ui->ContainerBrowser->setText("导出签名证书出错"+QString::number(ilRet,16));
        return;
    }
//    qDebug()<<QString(ucCert);
//    ui->ContainerBrowser->setText(tc->toUnicode(QString(ucCert).toLocal8Bit()));
    QString certInfo = "";
    certInfo += "++++++++++++++++++++++ \\\\ \n";
    certInfo += "++++++++++++++签名证书  \\\\\n";
    certInfo += "++++++++++++++++++++++  // \n";
    certInfo += getFormatCertText(ucCertS,ulCertLen);
    char ucCertE[4096*2] = {0};
    ulCertLen = 4096*2;
    ilRet = Dapi->SKF_ExportCertificate(mhContainer, false,  (BYTE*)ucCertE, &ulCertLen);
    if(ilRet)
    {
        qDebug()<<"导出加密证书出错"<<QString::number(ilRet,16);
        certInfo += "\n\n      加密证书导出错误";
        ui->ContainerBrowser->setText(certInfo);
//        ui->ContainerBrowser->setText("导出加密证书出错"+QString::number(ilRet,16));
        return;
    }
    certInfo += "++++++++++++++++++++++ \\\\ \n";
    certInfo += "++++++++++++++加密证书  \\\\ \n";
    certInfo += "++++++++++++++++++++++  // \n";
    certInfo += getFormatCertText(ucCertE,ulCertLen);

    ui->ContainerBrowser->setText(certInfo);
}

QString MainWindow::getFormatCertText(char* ucCert, ULONG ulCertLen)
{
     CertParse certParse((char*)ucCert,ulCertLen);
     QString FormatCert = "";
     FormatCert += "\n证书版本：\t";
     FormatCert += certParse.getVersion();
     FormatCert += "\n\n证书序列号：\t";
     FormatCert += certParse.getSerialNumber();

     FormatCert += "\n\n颁发者信息：\t";
     FormatCert += "\n\n     C：";
     FormatCert += certParse.getIssuer_C();
     FormatCert += "\tL：";
     FormatCert += certParse.getIssuer_L();
     FormatCert += "\n     E：";
     FormatCert += certParse.getIssuer_E();
     FormatCert += "\n     O：";
     FormatCert += certParse.getIssuer_O();
     FormatCert += "\n     S：";
     FormatCert += certParse.getIssuer_S();
     FormatCert += "\n     CN：";
     FormatCert += certParse.getIssuer_CN();
     FormatCert += "\n     OU：";
     FormatCert += certParse.getIssuer_OU();

     FormatCert += "\n\n使用者信息：\t";
     FormatCert += "\n\n     C：";
     FormatCert += certParse.getSubject_C();
     FormatCert += "\tL：";
     FormatCert += certParse.getSubject_L();
     FormatCert += "\n     E：";
     FormatCert += certParse.getSubject_E();
     FormatCert += "\n     O：";
     FormatCert += certParse.getSubject_O();
     FormatCert += "\n     S：";
     FormatCert += certParse.getSubject_S();
     FormatCert += "\n     CN：";
     FormatCert += certParse.getSubject_CN();
     FormatCert += "\n     OU：";
     FormatCert += certParse.getSubject_OU();

     FormatCert += "\n\n证书期限：";
     FormatCert += "\n\n     ";
     FormatCert += certParse.getCertValidDate();
     FormatCert += "\n\n\n\n";
     return FormatCert;
}

void MainWindow::on_unlockPinButton_clicked()
{
    ULONG count = 4;
    int ret = Dapi->SKF_UnblockPIN(phApp,"admin","111111",&count);
    qDebug()<<QString::number(ret,16)<<"||"<<count;

    if(!ret)
    {
        ui->unlockPinButton->setEnabled(false);
    }
}

void MainWindow::on_ImportSymmKeyButton_clicked()
{
    ULONG iISRet;
    if(!phApp)
    {
        qDebug()<<"空应用句柄";
        return;
    }
    if(!verifyPIN(phApp))
    {
        return;
    }
    if(ContainerName == nullptr)
    {
        qDebug()<<"容器名为空";
        return;
    }
    mhContainer = nullptr;
    iISRet = Dapi->SKF_OpenContainer(phApp,(char*)ContainerName.toStdString().c_str(),&mhContainer);
    if(iISRet)
    {
        qDebug()<<"打开容器出错"<<QString::number(iISRet,16);
        ui->resultBrowser->setText("打开容器出错"+QString::number(iISRet,16));
        return;
    }
    char* mSymmKey = nullptr;
    // 是否解base64（ 由复选框返回值决定 ）
    if(ui->isBase64->isChecked() == true)
    {
        QByteArray baseEncodeData = QByteArray::fromBase64(ui->textInput->toPlainText().toLocal8Bit());
        mSymmKey = (char*)baseEncodeData.toStdString().c_str();
    }
    else
    {
        mSymmKey = (char*)(ui->textInput->toPlainText()).toStdString().c_str();
    }

    // 导出加密公钥
    ECCPUBLICKEYBLOB eccPubBlob = {0};
    DWORD dwEccPubBlobLen = sizeof(ECCPUBLICKEYBLOB);
    iISRet = Dapi->SKF_ExportPublicKey(mhContainer, FALSE, (BYTE *)&eccPubBlob, &dwEccPubBlobLen);
    if (iISRet != 0)
    {
        qDebug()<<"导出加密公钥失败";
        return;
    }

    // 使用加密公钥加密会话密钥
    ECCCIPHERBLOB eccCipherBlob = {0};
    iISRet = Dapi->SKF_ExtECCEncrypt(phDev, &eccPubBlob, (byte*)mSymmKey, strlen(mSymmKey), &eccCipherBlob);
    if (iISRet != 0)
    {
        qDebug()<<"使用加密公钥加密会话密钥失败";
        return;
    }

//    qDebug()<<QByteArray(mSymmKey).toBase64();
    // 导入秘钥
    iISRet = Dapi->EPS_ImportSymmKey(mhContainer, EPST_SKEY_IDX_AMK,eccCipherBlob.Cipher, /*eccCipherBlob.CipherLen*/sizeof (eccPubBlob), 0);
    if(iISRet)
    {
        qDebug()<<"导入秘钥出错"<<QString::number(iISRet,16);
        qDebug()<<eccCipherBlob.Cipher<<endl<<eccCipherBlob.CipherLen;
        ui->resultBrowser->setText("导入秘钥出错"+QString::number(iISRet,16));
        return;
    }
    ui->resultBrowser->setText("导入秘钥成功");
    qDebug()<<eccCipherBlob.Cipher<<endl<<eccCipherBlob.CipherLen;
}

void MainWindow::on_WriteESealDataButton_clicked()
{
    int iWERet;
    if(!phApp)
    {
        qDebug()<<"空应用句柄";
        return;
    }
    if(!verifyPIN(phApp))
    {
        return;
    }
    if(ContainerName == nullptr)
    {
        qDebug()<<"容器名为空";
        return;
    }
    mhContainer = nullptr;
    iWERet = Dapi->SKF_OpenContainer(phApp,(char*)ContainerName.toStdString().c_str(),&mhContainer);
    if(iWERet)
    {
        qDebug()<<"打开容器出错"<<QString::number(iWERet,16);
        ui->resultBrowser->setText("打开容器出错"+QString::number(iWERet,16));
        return;
    }
    char* sealData = nullptr;
    QString qsInputText = nullptr;

    // 处理 从文件 复选框选择
    if(ui->isUseFile->isChecked() == true)
    {
        // 从文件获取印章数据
        QString inputFileName = QFileDialog::getOpenFileName(this,tr(""),"",tr("文本(*.txt)"));  // 选择路径
        qDebug()<<"选择文件路径为:"<<inputFileName;
        QFile inputFile(inputFileName);     // 打开文件
        if(!inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
           QMessageBox::warning(this,"Warnning","打开失败!",QMessageBox::Yes);
        }
        QTextStream inData(&inputFile);
        // 若读取的数据有乱码可尝试改变缓冲区编码
        inData.setCodec("GBK");
        qsInputText = inData.readAll();
        inputFile.close();
    }
    else
    {
        // 获取输入框输入
        qsInputText = ui->textInput->toPlainText();
    }
    qDebug()<<"获取输入框或文件印章数据：\n"<<qsInputText;

     std::string stInputText;
    // 处理 base64编码 复选框选择
    if(ui->isBase64->isChecked() == true)
    {
        QByteArray baseEncodeData = QByteArray::fromBase64(qsInputText.toLocal8Bit());
        qDebug()<<"QByteArray数据 "<<tc->toUnicode(baseEncodeData);
        /*std::string */stInputText = (tc->toUnicode(baseEncodeData)).toStdString();
        qDebug()<<"String数据 "<<tc->toUnicode(baseEncodeData);
        sealData = (char*)stInputText.c_str();
    }
    else
    {
        qsInputText = qsInputText.toLocal8Bit();
        /*std::string*/ stInputText = qsInputText.toStdString();
        sealData = (char*)stInputText.c_str();
    }
    qDebug()<<"base64编码或直接转char*的印章数据：\n"<<(QString::fromStdString(stInputText))<<"\n长度 "<<QString::fromStdString(stInputText).length();
    if(!strlen(sealData))  // 若印章长度有问题则退出本次操作并弹出警告对话框
    {
        QMessageBox::warning(this,"Warnning","印章信息无效!",QMessageBox::Yes);
        return;
    }

//    // 对印章明文数据（ 若为base64编码状态则先解编码 ）加密
//    unsigned char ucPubKey[4096] = { 0 };
//    unsigned long uiPubKeyLen = 4096;
//    Dapi->SKF_ExportPublicKey(mhContainer, FALSE, (BYTE*)ucPubKey, &uiPubKeyLen);
////    std::string pbEncData = sealData;
////    ULONG uiInDataLen = pbEncData.length();
//    unsigned char pucEncData[4096*20] = { 0 };
//    unsigned int puiEncDataLen = 4096*20;
//    sm4_cipher_ctx ctx;
//    uint32_t mode = SM4_CBC;
//    memset(&ctx, 0, sizeof(sm4_cipher_ctx));

//    BYTE iv[32];
//    BLOCKCIPHERPARAM EncryptParam = { 0 };
//    if (!EncryptParam.IVLen)
//        mode = SM4_ECB;
//    else
//    {
//        ((EncryptParam.IVLen >= 16) && (EncryptParam.IVLen <= 32));
//        memcpy(iv, EncryptParam.IV, EncryptParam.IVLen);
//    }
//    ULONG tmpLen = 0;
//    SM4_encrypt_init(&ctx, ucPubKey, (const unsigned char*)sealData, mode);
//    SM4_encrypt_update(&ctx, pucEncData, &puiEncDataLen , (const unsigned char*)sealData, strlen(sealData));
//    tmpLen += puiEncDataLen;
//    SM4_encrypt_final(&ctx, pucEncData + tmpLen, &puiEncDataLen);
//    tmpLen += puiEncDataLen;
//    // 导入印章
//    iWERet = Dapi->EPS_WriteESealData(phApp,pucEncData,tmpLen, 0);
//    if(iWERet)
//    {
//        qDebug()<<"导入印章出错"<<QString::number(iWERet,16);
//        ui->resultBrowser->setText("导入印章出错"+QString::number(iWERet,16));
//        return;
//    }
//    ui->resultBrowser->setText(QString("导入印章成功,印章大小:")+QString::number(tmpLen));
    BYTE bEncData[4096*20] = {0};
    DWORD dwEncDataLen = sizeof(bEncData);
    BYTE bKey[4096] = "1234567812345678";
    // 使用SM4算法对初始数据加密
    HANDLE hKey = nullptr;
    BLOCKCIPHERPARAM cipherParam = {0};
    Dapi->SKF_SetSymmKey(phDev, bKey, SGD_SM4_ECB, &hKey);
    Dapi->SKF_EncryptInit(hKey, cipherParam);
    Dapi->SKF_Encrypt(hKey, (byte*)sealData, 4096, bEncData, &dwEncDataLen);
    qDebug()<<"加密后长度："<<dwEncDataLen<<"||||"<<sizeof(bEncData);
    iWERet = Dapi->EPS_WriteESealData(phApp,(BYTE*)bEncData, strlen((char*)bEncData), 0);
    if(iWERet)
    {
        qDebug()<<"导入印章出错"<<QString::number(iWERet,16);
        ui->resultBrowser->setText("导入印章出错"+QString::number(iWERet,16));
        return;
    }
    ui->resultBrowser->setText(QString("导入印章成功,印章大小:")+QString::number(dwEncDataLen));
}

void MainWindow::on_exitUKey_clicked()
{
    ui->resultBrowser->clear();
    ui->textInput->clear();
    ui->tabWidget->setTabEnabled(1,false);
    ui->tabWidget->setTabEnabled(2,false);
    ui->ContainerList->clear();
    ui->ContainerBrowser->clear();
    ui->deleteButton->setEnabled(false);
    ui->ImportSymmKeyButton->setEnabled(false);
    model->clear();
    // 关闭容器
    if(ContainerName != nullptr)
        ContainerName = nullptr;
    if(mhContainer)
        Dapi->SKF_CloseContainer(mhContainer);
    // 关闭应用
    if(phApp)
        Dapi->SKF_CloseApplication(phApp);
    // 关闭设备
    if(phDev)
       Dapi->SKF_DisConnectDev(phDev);
    mhContainer = nullptr;
    phDev = nullptr;
    phApp = nullptr;

}

void MainWindow::on_ReadESealDataButton_clicked()
{
    int iRERet;
    if(!phApp)
    {
        qDebug()<<"空应用句柄";
        return;
    }
    if(!verifyPIN(phApp))
    {
        return;
    }
    char sealData[4096*10] = {0};
    ULONG sealDataLen = 4096*10;

    iRERet = Dapi->EPS_ReadESealData(phApp, EPST_SKEY_IDX_AMK, SGD_SM4_ECB, (BYTE*)sealData, &sealDataLen, 0);
    qDebug()<<"读取印章:"<<tc->toUnicode(sealData);
    if(iRERet)
    {
        qDebug()<<"导出印章出错"<<QString::number(iRERet,16);
        ui->resultBrowser->setText("导出印章出错"+QString::number(iRERet,16));
        return;
    }
    if(ui->isBase64->isChecked() == true)
    {
//       ui->resultBrowser->setText(tc->toUnicode(QString(sealData).toLocal8Bit().toBase64()));
        ui->resultBrowser->setText(tc->toUnicode(QString::fromStdString(sealData).toLocal8Bit().toBase64()));
    }
    else
    {
//        ui->resultBrowser->setText(tc->toUnicode(QString(sealData).toLocal8Bit()));
        ui->resultBrowser->setText(QString::fromStdString(sealData));
    }
    qDebug()<<"印章大小为:"<<sealDataLen;
}

void MainWindow::on_EncryptButton_clicked()
{
    int iERet;
    if(!phApp)
    {
        qDebug()<<"空应用句柄";
        return;
    }
    if(!verifyPIN(phApp))
    {
        return;
    }
    char IV[16] = { '1','2','3','4','5','6','7','8','1','2','3','4','5','6','7','8' };
    ULONG IVLen = 16;
    char *EncryptBuf = nullptr;

    if(ui->isBase64->isChecked() == true)
    {
        QByteArray baseEncodeData = QByteArray::fromBase64(ui->textInput->toPlainText().toLocal8Bit());
        EncryptBuf = (char*)baseEncodeData.toStdString().c_str();
    }
    else
    {
        EncryptBuf = (char*)(ui->textInput->toPlainText()).toStdString().c_str();
    }
    char pbEncData[4096] = {0};
    ULONG ulEncDataLen = 4096;
    iERet = Dapi->EPS_Encrypt(phApp, EPST_SKEY_IDX_AMK, SGD_SM4_ECB,
                              (BYTE*)IV, IVLen, 0, (BYTE*)pbEncData,
                              ulEncDataLen, (BYTE*)EncryptBuf, strlen(EncryptBuf),
                              (BYTE*)pbEncData, &ulEncDataLen, 0);
    if(iERet)
    {
        qDebug()<<"数据加密出错"<<QString::number(iERet,16);
        ui->resultBrowser->setText("数据加密出错"+QString::number(iERet,16));
        return;
    }
    ui->resultBrowser->setText(QByteArray(pbEncData).toBase64());


}

void MainWindow::on_DecryptButton_clicked()
{
    int iDRet;
    if(!phApp)
    {
        qDebug()<<"空应用句柄";
        return;
    }
    if(!verifyPIN(phApp))
    {
        return;
    }
    char IV[16] = { '1','2','3','4','5','6','7','8','1','2','3','4','5','6','7','8' };
    ULONG IVLen = 16;
    char *DecryptBuf = nullptr;
    if(ui->isBase64->isChecked() == true)
    {
        QByteArray baseEncodeData = QByteArray::fromBase64(ui->textInput->toPlainText().toLocal8Bit());
        DecryptBuf = (char*)baseEncodeData.toStdString().c_str();
    }
    else
    {
        DecryptBuf = (char*)(ui->textInput->toPlainText()).toStdString().c_str();
    }
    char pbEncData[4096] = {0};
    ULONG ulEncDataLen = 4096;
    iDRet = Dapi->EPS_Decrypt(phApp, EPST_SKEY_IDX_AMK, SGD_SM4_ECB,
                              (BYTE*)IV, IVLen, 0, (BYTE*)pbEncData,
                              ulEncDataLen, (BYTE*)DecryptBuf, strlen(DecryptBuf),
                              (BYTE*)pbEncData, &ulEncDataLen, 0);
    if(iDRet)
    {
        qDebug()<<"数据解密出错"<<QString::number(iDRet,16);
        ui->resultBrowser->setText("数据解密出错"+QString::number(iDRet,16));
        return;
    }

    ui->resultBrowser->setText(QString(pbEncData).toLocal8Bit());

}

void MainWindow::on_MacButton_clicked()
{
    int iMRet;
    if(!phApp)
    {
        qDebug()<<"空应用句柄";
        return;
    }
    if(!verifyPIN(phApp))
    {
        return;
    }
    char IV[16] = { '1','2','3','4','5','6','7','8','1','2','3','4','5','6','7','8' };
    ULONG IVLen = 16;
    char *EncryptBuf = nullptr;
    if(ui->isBase64->isChecked() == true)
    {
        QByteArray baseEncodeData = QByteArray::fromBase64(ui->textInput->toPlainText().toLocal8Bit());
        EncryptBuf = (char*)baseEncodeData.toStdString().c_str();
    }
    else
    {
        EncryptBuf = (char*)(ui->textInput->toPlainText()).toStdString().c_str();
    }
    char pbEncData[16] = { '1','2','3','4','5','6','7','8','1','2','3','4','5','6','7','8' };
    ULONG ulEncDataLen = 16;
    char EncData[64] = { '1','2','3','4','5','6','7','8','1','2','3','4','5','6','7','8','1','2','3','4','5','6','7','8','1','2','3','4','5','6','7','8', '1','2','3','4','5','6','7','8','1','2','3','4','5','6','7','8','1','2','3','4','5','6','7','8','1','2','3','4','5','6','7','8' };
    char cdeData[4096] = {0};
    ULONG cdeDataLen = 4096;
    iMRet = Dapi->EPS_Mac(phApp, EPST_SKEY_IDX_AMK, SGD_SM4_CBC,
                    (BYTE*)pbEncData, ulEncDataLen, 0, (BYTE*)pbEncData,
                    ulEncDataLen, (BYTE*)EncData, 64,
                    (BYTE*)cdeData, &cdeDataLen, 0);
    if(iMRet)
    {
        qDebug()<<"生成鉴别码出错"<<QString::number(iMRet,16);
        ui->resultBrowser->setText("生成鉴别码出错"+QString::number(iMRet,16));
        return;
    }
    if(ui->isBase64->isChecked() == true)
    {
       ui->resultBrowser->setText(QString(cdeData).toLocal8Bit().toBase64());
    }
    else
    {
        ui->resultBrowser->setText(QString(cdeData).toLocal8Bit());
    }
}

void MainWindow::ShowContextMenu(const QPoint& pos)
{
    // 创建右键菜单
    QMenu menu;
    // 添加右键菜单中的action
    QModelIndex curIndex = ui->FileTree->indexAt(pos);      //当前点击的元素的index
    QModelIndex index = curIndex.sibling(curIndex.row(),0); //该行的第1列元素的index

//    // 对文件项进行操作
//    if (index.parent().data().toString() == "" && index.isValid())
//    {
//        menu.addAction(QStringLiteral("关闭设备"), this, [=](){

//            // 关闭应用
//            if(phApp)
//            {
//                Dapi->SKF_CloseApplication(phApp);
//                phApp = nullptr;
//            }
//            // 关闭设备
//            if(phDev)
//            {
//                Dapi->SKF_DisConnectDev(phDev);
//                phDev = nullptr;
//            }
//            ui->deleteButton->setEnabled(false);
//            ui->ImportSymmKeyButton->setEnabled(false);
//            ui->WriteESealDataButton->setEnabled(false);

//            if(phApp == nullptr)
//            {
//                ui->tabWidget->setTabEnabled(1,false);
//                ui->tabWidget->setTabEnabled(2,false);
//            }
//            else
//            {
//                ui->tabWidget->setTabEnabled(1,true);
//                ui->tabWidget->setTabEnabled(2,true);
//            }
//        });
//    }

    // 对文件项进行操作
    if (index.parent().data().toString() != "" && index.parent().parent().data().toString() == "")
    {
        menu.addAction(QStringLiteral("关闭应用"), this, [=](){
            // 关闭应用
            if(phApp)
            {
                Dapi->SKF_CloseApplication(phApp);
                phApp = nullptr;
            }

            ui->deleteButton->setEnabled(false);
            ui->ImportSymmKeyButton->setEnabled(false);
            ui->WriteESealDataButton->setEnabled(false);

            if(phApp == nullptr)
            {
                ui->tabWidget->setTabEnabled(1,false);
                ui->tabWidget->setTabEnabled(2,false);
            }
            else
            {
                ui->tabWidget->setTabEnabled(1,true);
                ui->tabWidget->setTabEnabled(2,true);
            }
        });
        menu.addSeparator();    //添加一个分隔线
        menu.addAction(QStringLiteral("创建文件"), this, [=](){
            // 创建文件
            ULONG uRet = 0;

            std::string sTmpStr = index.parent().data().toString().toStdString();
            char *cTmpStr = (char*)sTmpStr.c_str();
            connectDev(cTmpStr);
            std::string sTmpStrSub = index.data().toString().toStdString();
            uRet = Dapi->SKF_OpenApplication(phDev, (char*)sTmpStrSub.c_str(), &phApp);
            if(uRet)
            {
                qDebug()<<"打开应用出错::"<<QString::number(uRet,16);
                return;
            }

            qDebug()<<"应用名::"<<index.data().toString()<<phApp;
            DialogForCreateFile *inputFilename = new DialogForCreateFile;
            inputFilename->exec();
            inputFilename = nullptr;

            QString fileName = ChooseKeyDialog::CREATEFILENAME;

            if(fileName == "")
            {
                qDebug()<<"文件名空";
                return;
            }
            // 调用skf接口创建文件
            uRet  = Dapi->SKF_CreateFile(phApp,(char*)fileName.toStdString().c_str(),1,SECURE_ANYONE_ACCOUNT,SECURE_ANYONE_ACCOUNT);
            if(uRet)
            {
                if(uRet == 0xa00002f)
                {
                    ui->TBItemInfo->setText(QString("文件已存在!"));
                }
                qDebug()<<"创建文件失败::"<<QString::number(uRet,16);
                return;
            }
            ui->TBItemInfo->setText(QString("文件创建成功!"));
            treeView_model();
        });
    }

    // 对文件项进行操作
    if (index.parent().parent().data().toString() != "")
    {
        menu.addAction(QStringLiteral("保存到文件"), this, [=](){
            // 写文件
            ULONG uRet = 0;
            QString qsText = ui->TBItemInfo->toPlainText();
            // 为兼容海泰 先删除文件 然后重新创建新的容量的文件
            QString qsFileName = index.data().toString();
            ULONG ulFileSize = strlen(qsText.toStdString().c_str());
            if(ulFileSize == 0)
                ulFileSize = 1;
            uRet = Dapi->SKF_DeleteFile(phApp,(char*)qsFileName.toStdString().c_str());
            uRet  = Dapi->SKF_CreateFile(phApp,(char*)qsFileName.toStdString().c_str(),ulFileSize,SECURE_ANYONE_ACCOUNT,SECURE_ANYONE_ACCOUNT);
            uRet = Dapi->SKF_WriteFile(phApp, (char*)qsFileName.toStdString().c_str(), 0 , (byte*)qsText.toStdString().c_str(),ulFileSize);
            if(uRet)
            {
                qDebug()<<"保存文件失败"<<QString::number(uRet,16);
                ui->TBItemInfo->setText(QString("保存文件失败：")+QString::number(uRet,16));
                return;
            }
             QMessageBox::information(this,tr("文件操作"),tr("文件保存成功"),QMessageBox::Yes);
        });
        menu.addSeparator();    //添加一个分隔线
        menu.addAction(QStringLiteral("获取文件属性"), this, [=](){
            // 获取文件属性
            FILEATTRIBUTE pFileInfo={0};
            ULONG uRet = Dapi->SKF_GetFileInfo (phApp, (char*)index.data().toString().toStdString().c_str(), &pFileInfo);
            if(uRet)
            {
                qDebug()<<"获取文件信息失败"<<QString::number(uRet,16);
                ui->TBItemInfo->setText(QString("获取文件信息失败：")+QString::number(uRet,16));
                return;
            }
            QString qsFileInfo = "文件名:\t";
            qsFileInfo += pFileInfo.FileName;
            qsFileInfo += "\n文件大小:\t";
            qsFileInfo += QString::number(pFileInfo.FileSize);
            qsFileInfo += "\n读权限:\t";
            qsFileInfo += UtilFunction::ReadFileRights(pFileInfo.ReadRights);
            qsFileInfo += "\n写权限:\t";
            qsFileInfo += UtilFunction::ReadFileRights(pFileInfo.WriteRights);
            ui->TBItemInfo->setText(qsFileInfo);
        });
    }
    // 显示该菜单，进入消息循环
    menu.exec(this->ui->FileTree->mapToGlobal(pos)/*全局位置*/);

}

void MainWindow::on_base64Decode_clicked()
{
    QString base64Text = ui->base64TextEdit->toPlainText();
    QByteArray decodeText = QByteArray::fromBase64(base64Text.toLocal8Bit());
    ui->plainTextEdit->setPlainText(tc->toUnicode(decodeText));

//    QFile out("C:/Users/Administrator.SC-201902270233/Desktop/testTextFileforBase64Decode.txt");
//    out.open(QIODevice::ReadWrite | QIODevice::Text);
//    out.write(decodeText);
//    out.close();
}

void MainWindow::on_base64Encode_clicked()
{
    QString base64Text = ui->plainTextEdit->toPlainText();

//    QFile out("C:/Users/Administrator.SC-201902270233/Desktop/testTextFileforBase64Encode.txt");
//    out.open(QIODevice::ReadWrite | QIODevice::Text);
//    out.write((base64Text.toLocal8Bit()).toBase64());
//    out.close();

    ui->base64TextEdit->setText((base64Text.toLocal8Bit()).toBase64());
}
