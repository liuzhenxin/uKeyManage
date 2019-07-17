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

char* UtilFunction::QString2ConstCharPoint(QString qstring)
{
    std::string cString = qstring.toStdString();
    return (char*)cString.c_str();
}

QString UtilFunction::ReadFileRights(ULONG hex)
{
//    return QString::number(hex,16);
    switch (hex) {
        case SECURE_ANYONE_ACCOUNT:return QString("0x000000FF  任何人");
        case SECURE_USER_ACCOUNT:return QString("0x00000010  用户权限");
        case SECURE_ADM_ACCOUNT:return QString("0x00000001  管理员权限");
        case SECURE_NEVER_ACCOUNT:return QString("0x00000000  不允许");
        default:return QString("UNKNOWRIGHTS");
    }
}

std::string UtilFunction::GbkToUtf8(const char *src_str)
{
    int len = MultiByteToWideChar(CP_ACP, 0, src_str, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_ACP, 0, src_str, -1, wstr, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* str = new char[len + 1];
    memset(str, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
    std::string strTemp = str;
    if (wstr) delete[] wstr;
    if (str) delete[] str;
    return strTemp;
}

std::string UtilFunction::Utf8ToGbk(const char *src_str)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, src_str, -1, NULL, 0);
    wchar_t* wszGBK = new wchar_t[len + 1];
    memset(wszGBK, 0, len * 2 + 2);
    MultiByteToWideChar(CP_UTF8, 0, src_str, -1, wszGBK, len);
    len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
    char* szGBK = new char[len + 1];
    memset(szGBK, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
    std::string strTemp(szGBK);
    if (wszGBK) delete[] wszGBK;
    if (szGBK) delete[] szGBK;
    return strTemp;
}
