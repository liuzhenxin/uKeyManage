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
    static std::string GbkToUtf8(const char *src_str);
    static std::string Utf8ToGbk(const char *src_str);
};

#endif // UTILFUNCTION_H
