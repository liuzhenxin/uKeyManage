#ifndef CERTPARSE_H
#define CERTPARSE_H

#include <openssl/pem.h>
#include <openssl/conf.h>
#include <openssl/x509v3.h>
#include <openssl/x509.h>
#include <iostream>
#include <QString>
#include <QDebug>
#include <time.h>
#include <stdlib.h>
class CertParse
{
private:
//    void *vCertInfo;
    X509* vCertInfo;

public:

private:
//    long getVersion();
    int mypint( const char ** s, int n, int min, int max, int * e);
    time_t ASN1_TIME_get ( ASN1_TIME * a, int *err);
    void FormatTime(time_t time1, char *szTime);

    QString getIssuer(int);
    QString getSubject(int);
public:
    CertParse(char*,unsigned long);
    ~CertParse();
//    QString GetCertDNInfo(DN_Type dnType, DN_Detail dnDetail);
    QString getVersion();
    QString getSerialNumber();
    QString getPublicKey();


    QString getIssuer_C();
    QString getIssuer_O();
    QString getIssuer_OU();
    QString getIssuer_S();
    QString getIssuer_CN();
    QString getIssuer_L();
    QString getIssuer_E();


    QString getSubject_C();
    QString getSubject_O();
    QString getSubject_OU();
    QString getSubject_S();
    QString getSubject_CN();
    QString getSubject_L();
    QString getSubject_E();

    QString getCertValidDate();
};

#endif // CERTPARSE_H
