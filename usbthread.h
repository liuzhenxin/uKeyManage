#ifndef USBTHREAD_H
#define USBTHREAD_H
#include <QThread>
#include "typedefine.h"
#include <QDebug>
#include <choosekeydialog.h>
#include <setupapi.h>
#include <vector>
class usbThread : public QThread
{
Q_OBJECT
signals:
    void usbMsg(int type);
private slots:
//    void apiTypeChoose(typeDefApi*);
public:
    usbThread(QString);
    ~usbThread();
    void run();
private:

    void EnumUsbInfo(std::vector<std::string> &device);

public:
    typeDefApi *utDapi;
    char szDevName[1024] = {0};
    ULONG pulDevNameLen = 1024;
    ULONG pulEvent;
private:
    QString keyName = nullptr;
};

#endif // USBTHREAD_H
