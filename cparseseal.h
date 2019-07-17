#ifndef CPARSESEAL_H
#define CPARSESEAL_H

#include "QtDebug"
#include <QTextCodec>
#include "utilfunction.h"
#include "QMessageBox"

#include "OFD_SESealASN1.h"
#include "OFD_ZWFWSESealASN1.h"
#include "SESealASN1.h"

class CParseSeal
{
public:

    CParseSeal(unsigned char* ucSealData,unsigned long ulSealSize);

    ~CParseSeal();

    void setSealData(unsigned char* ucSealData,unsigned long ulSealSize);

    QString getFormateSealInfo();
private:

    void getSealInfo();

public:
    QString ES_ESPictrueInfo_Data = "";
    QString SES_ESPictrueInfo_Type = "";
    QString SES_SignInfo_Cert = "";
    QString SES_SignInfo_SignatureAlgorithm = "";
    QString SES_SignInfo_SignData = "";
    QString SES_ESPropertyInfo_Type = "";
    QString SES_ESPropertyInfo_Name = "";
    QString SES_ESPropertyInfo_Cert = "";
    QString SES_ESPropertyInfo_CreateDate = "";
    QString SES_ESPropertyInfo_ValidStart = "";
    QString SES_ESPropertyInfo_ValidEnd = "";
    QString SES_SealInfo_EsID = "";
private:
    unsigned char* ucSealData = nullptr;
    unsigned long ulSealSize = 0;

};

#endif // CPARSESEAL_H
