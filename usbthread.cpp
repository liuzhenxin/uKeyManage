#include "usbthread.h"
usbThread::usbThread(QString mKeyName)
{
    qDebug()<<"usbthread create";

    keyName = mKeyName;
    if(keyName == "" || keyName == nullptr)
        keyName = HAITAI;
    qDebug()<<"选中的dll为::"<<keyName;
    utDapi = new typeDefApi(keyName);
}

//void usbThread::apiTypeChoose(typeDefApi *apiType)
//{
//    utDapi = apiType;
//    qDebug()<<"apiTypeChoose is over::"<<utDapi;
//}
usbThread::~usbThread()
{
    qDebug()<<"usbthread delete";
    if(!utDapi)
        delete utDapi;
}
void usbThread::run()
{
    qDebug()<<"run";
    while(1){

        if(utDapi == nullptr)
            continue;
        utDapi->SKF_WaitForDevEvent(szDevName,&pulDevNameLen, &pulEvent);
        if(pulEvent == 1)
        {
            emit usbMsg(1);
            qDebug()<<"1";
        }
        if(pulEvent == 2)
        {
            emit usbMsg(2);
            qDebug()<<"2";
        }
        sleep(5);
    }

}

