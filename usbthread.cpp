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
    char DevList[512] = {0};
    ULONG DevCount = 512;
    ULONG oldDevCount = 512;
    qDebug()<<"run";
    while(1){
        sleep(1);

        if(utDapi == nullptr)
            continue;

        if(keyName == "SMSKF.dll")
        {
            oldDevCount = DevCount;
            memset(DevList,0,strlen(DevList));
            DevCount = 512;
            ULONG iRet = utDapi->SKF_EnumDev(true,DevList,&DevCount);
            if(iRet)
            {
                if(oldDevCount%512 > DevCount%512)
                    pulEvent = 2;
                else {
                    pulEvent = 0;
                }
            }else {
                if(oldDevCount%512 == DevCount%512)
                {
                    pulEvent = 0;
                    continue;
                }else {
                    if(oldDevCount&512 > DevCount%512)
                        pulEvent = 2;
                    else if(oldDevCount%512 < DevCount%512)
                    {
                         pulEvent = 1;
                    }
                }
                ChooseKeyDialog::KEYNAMEFORCHOOSEDLL = "SMSKF.dll";
            }
        }else{
            utDapi->SKF_WaitForDevEvent(szDevName,&pulDevNameLen, &pulEvent);
            ChooseKeyDialog::KEYNAMEFORCHOOSEDLL = keyName;
        }
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

    }

}

void usbThread::EnumUsbInfo(std::vector<std::string> &device)
{
    // get all device of system
    DWORD dwFlag = (DIGCF_ALLCLASSES | DIGCF_PRESENT);
    HDEVINFO hDevInfo = SetupDiGetClassDevs(nullptr, nullptr, nullptr, dwFlag);

    if( INVALID_HANDLE_VALUE == hDevInfo )
    {
        printf("Failed to get system device list");
        return;
    }

    // to enum USB device
    SP_DEVINFO_DATA sDevInfoData;
    sDevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    std::string strText;
    TCHAR szDIS[MAX_PATH] = {0};

    // Device Identification Strings,
    DWORD nSize = 0 ;

    for(int i = 0; SetupDiEnumDeviceInfo(hDevInfo,i,&sDevInfoData); i++ )
    {
        nSize = 0;

        if ( !SetupDiGetDeviceInstanceId(hDevInfo, &sDevInfoData, szDIS, sizeof(szDIS), &nSize) )
        {
            printf("get device id failed\n");
            break;
        }

        // filter : USB\VID_XXXX&PID_XXXX\00000xxxxxxx

        int iLen = WideCharToMultiByte(CP_ACP, 0,szDIS, -1, nullptr, 0, nullptr, nullptr);

        char* chRtn =new char[iLen*sizeof(char)];

        WideCharToMultiByte(CP_ACP, 0, szDIS, -1, chRtn, iLen, nullptr, nullptr);

        QString strDIS(chRtn);

        strDIS.toUpper();

        if( strDIS.left( 3 ) == ("USB"))
        {
            QString VID = strDIS.mid(strDIS.indexOf("VID_")+4,4).remove(QChar('"'), Qt::CaseInsensitive).toLower();

            qDebug()<<"device id : "<<VID<<endl;
            device.push_back(VID.toStdString());
        }
    }

    SetupDiDestroyDeviceInfoList(hDevInfo);
}


