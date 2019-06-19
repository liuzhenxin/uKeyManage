#include "utilfunction.h"

UtilFunction::UtilFunction()
{

}

char* UtilFunction::QString2CharPoint(QString qstring)
{
    QByteArray qByteArray = qstring.toLatin1();
    return qByteArray.data();
}

char* UtilFunction::QString2CharPoint1(QString qstring)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QByteArray qByteArray = qstring.toLocal8Bit();
    return qByteArray.data();
}

const char* UtilFunction::QString2ConstCharPoint(QString qstring)
{
    std::string cString = qstring.toStdString();
    return cString.c_str();
}

QString UtilFunction::ReadFileRights(ULONG hex)
{
    switch (hex) {
    case SECURE_ANYONE_ACCOUNT:return QString("0x000000FF  任何人");
    case SECURE_USER_ACCOUNT:return QString("0x00000010  用户权限");
    case SECURE_ADM_ACCOUNT:return QString("0x00000001  管理员权限");
    case SECURE_NEVER_ACCOUNT:return QString("0x00000000  不允许");
    default:return QString("UNKNOWRIGHTS");
    }
}
