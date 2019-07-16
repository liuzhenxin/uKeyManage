#ifndef UTILFUNCTION_H
#define UTILFUNCTION_H
#include <QString>
#include <iostream>
#include <QByteArray>
#include <QTextCodec>
#include <typedefine.h>
class UtilFunction
{
public:
    UtilFunction();
    static char* QString2CharPoint(QString);
    static char* QString2CharPoint1(QString);
    static char* QString2ConstCharPoint(QString);
    static QString ReadFileRights(ULONG);
};

#endif // UTILFUNCTION_H
