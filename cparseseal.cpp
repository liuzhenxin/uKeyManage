#include "cparseseal.h"


ASN1_SEQUENCE(SHS_Header) =
    {
        ASN1_SIMPLE(SHS_Header, SHS_Header_ID, ASN1_IA5STRING),
        ASN1_SIMPLE(SHS_Header, SHS_Header_Version, ASN1_INTEGER),
        ASN1_SIMPLE(SHS_Header, SHS_Header_VID, ASN1_IA5STRING),
        ASN1_SIMPLE(SHS_Header, SHS_Header_Length, ASN1_INTEGER)
}
ASN1_SEQUENCE_END(SHS_Header)
    IMPLEMENT_ASN1_FUNCTIONS(SHS_Header)

    ASN1_SEQUENCE(SES_ESPictrueInfo) =
        {
            ASN1_SIMPLE(SES_ESPictrueInfo, SES_ESPictrueInfo_Type, ASN1_IA5STRING),
            ASN1_SIMPLE(SES_ESPictrueInfo, ES_ESPictrueInfo_Data, ASN1_OCTET_STRING)
}
ASN1_SEQUENCE_END(SES_ESPictrueInfo)
    IMPLEMENT_ASN1_FUNCTIONS(SES_ESPictrueInfo)

    ASN1_SEQUENCE(SES_ESPropertyInfo) =
        {
            ASN1_SIMPLE(SES_ESPropertyInfo, SES_ESPropertyInfo_Type, ASN1_INTEGER),
            ASN1_SIMPLE(SES_ESPropertyInfo, SES_ESPropertyInfo_Name, ASN1_UTF8STRING),
            ASN1_SIMPLE(SES_ESPropertyInfo, SES_ESPropertyInfo_Cert, ASN1_OCTET_STRING),
            ASN1_SIMPLE(SES_ESPropertyInfo, SES_ESPropertyInfo_CreateDate, ASN1_UTCTIME),
            ASN1_SIMPLE(SES_ESPropertyInfo, SES_ESPropertyInfo_ValidStart, ASN1_UTCTIME),
            ASN1_SIMPLE(SES_ESPropertyInfo, SES_ESPropertyInfo_ValidEnd, ASN1_UTCTIME),
            //	ASN1_SIMPLE(SES_ESPropertyInfo, SES_ESPropertyInfo_UserRight, ASN1_INTEGER),
            }
    ASN1_SEQUENCE_END(SES_ESPropertyInfo)
        IMPLEMENT_ASN1_FUNCTIONS(SES_ESPropertyInfo)

    ASN1_SEQUENCE(SES_SealInfo) =
        {
            ASN1_SIMPLE(SES_SealInfo, SES_SealInfo_EsID, ASN1_IA5STRING),
            ASN1_SIMPLE(SES_SealInfo, SES_SealInfo_Property, SES_ESPropertyInfo),
            ASN1_SIMPLE(SES_SealInfo, SES_SealInfo_Picture, SES_ESPictrueInfo),
            ASN1_SIMPLE(SES_SealInfo, SES_SealInfo_Data, ASN1_OCTET_STRING),
            }
    ASN1_SEQUENCE_END(SES_SealInfo)
        IMPLEMENT_ASN1_FUNCTIONS(SES_SealInfo)


    ASN1_SEQUENCE(SES_SignInfo) =
        {
            ASN1_SIMPLE(SES_SignInfo, SES_SignInfo_Cert, ASN1_OCTET_STRING),
            ASN1_SIMPLE(SES_SignInfo, SES_SignInfo_SignatureAlgorithm, ASN1_OBJECT),
            ASN1_SIMPLE(SES_SignInfo, SES_SignInfo_SignData, ASN1_BIT_STRING),

            /*ASN1_SIMPLE(SES_SignInfo, temp1, ASN1_INTEGER),
    ASN1_SIMPLE(SES_SignInfo, temp2, ASN1_ENUMERATED),
    ASN1_SIMPLE(SES_SignInfo, temp3, ASN1_BIT_STRING),
    ASN1_SIMPLE(SES_SignInfo, temp4, ASN1_OCTET_STRING),
    ASN1_SIMPLE(SES_SignInfo, temp5, ASN1_PRINTABLESTRING),
    ASN1_SIMPLE(SES_SignInfo, temp6, ASN1_T61STRING),
    ASN1_SIMPLE(SES_SignInfo, temp7, ASN1_IA5STRING),
    ASN1_SIMPLE(SES_SignInfo, temp8, ASN1_GENERALSTRING),
    ASN1_SIMPLE(SES_SignInfo, temp9, ASN1_UNIVERSALSTRING),
    ASN1_SIMPLE(SES_SignInfo, temp10, ASN1_BMPSTRING),
    ASN1_SIMPLE(SES_SignInfo, temp11, ASN1_UTCTIME),
    ASN1_SIMPLE(SES_SignInfo, temp12, ASN1_TIME),
    ASN1_SIMPLE(SES_SignInfo, temp13, ASN1_GENERALIZEDTIME),
    ASN1_SIMPLE(SES_SignInfo, temp14, ASN1_VISIBLESTRING),
    ASN1_SIMPLE(SES_SignInfo, temp15, ASN1_UTF8STRING),*/
}
    ASN1_SEQUENCE_END(SES_SignInfo)
        IMPLEMENT_ASN1_FUNCTIONS(SES_SignInfo)

    ASN1_SEQUENCE(SESeal) =
        {
            ASN1_SIMPLE(SESeal, SHS_Header, SHS_Header),
            ASN1_SIMPLE(SESeal, SES_SealInfo, SES_SealInfo),
            ASN1_SIMPLE(SESeal, SES_SignInfo, SES_SignInfo)
}
    ASN1_SEQUENCE_END(SESeal)
        IMPLEMENT_ASN1_FUNCTIONS(SESeal)

    ASN1_SEQUENCE(SEIndata) =
        {
            ASN1_SIMPLE(SEIndata, SHS_Header, SHS_Header),
            ASN1_SIMPLE(SEIndata, SES_SealInfo, SES_SealInfo),
            }
    ASN1_SEQUENCE_END(SEIndata)
        IMPLEMENT_ASN1_FUNCTIONS(SEIndata)

    ASN1_SEQUENCE(SES_Signature) =
        {
            ASN1_SIMPLE(SES_Signature, SES_Signature_Version, ASN1_INTEGER),
            ASN1_SIMPLE(SES_Signature, SES_Signature_SESeal, SESeal),
            ASN1_SIMPLE(SES_Signature, SES_Signature_TimeInfo, ASN1_BIT_STRING),
            ASN1_SIMPLE(SES_Signature, SES_Signature_DataHash, ASN1_BIT_STRING),
            ASN1_SIMPLE(SES_Signature, SES_Signature_PropertyInfo, ASN1_IA5STRING),
            ASN1_SIMPLE(SES_Signature, SES_Signature_Certid, ASN1_IA5STRING),
            ASN1_SIMPLE(SES_Signature, SES_Signature_SignatureAlgorithm, ASN1_OBJECT),
            ASN1_SIMPLE(SES_Signature, SES_Signature_Signature, ASN1_BIT_STRING)
}
    ASN1_SEQUENCE_END(SES_Signature)
        IMPLEMENT_ASN1_FUNCTIONS(SES_Signature)


    //-----------新标准
    ASN1_SEQUENCE(OFD_SES_Header) =
        {
            ASN1_SIMPLE(OFD_SES_Header, SES_Header_ID, ASN1_IA5STRING),
            ASN1_SIMPLE(OFD_SES_Header, SES_Header_Version, ASN1_INTEGER),
            ASN1_SIMPLE(OFD_SES_Header, SES_Header_VID, ASN1_IA5STRING)
}
    ASN1_SEQUENCE_END(OFD_SES_Header)
        IMPLEMENT_ASN1_FUNCTIONS(OFD_SES_Header)

    ASN1_SEQUENCE(OFD_SES_ESPictrueInfo) =
        {
            ASN1_SIMPLE(OFD_SES_ESPictrueInfo, SES_ESPictrueInfo_Type, ASN1_IA5STRING),
            ASN1_SIMPLE(OFD_SES_ESPictrueInfo, SES_ESPictrueInfo_Data, ASN1_OCTET_STRING),
            ASN1_SIMPLE(OFD_SES_ESPictrueInfo, SES_ESPictrueInfo_Width, ASN1_INTEGER),
            ASN1_SIMPLE(OFD_SES_ESPictrueInfo, SES_ESPictrueInfo_Height, ASN1_INTEGER)
}
    ASN1_SEQUENCE_END(OFD_SES_ESPictrueInfo)
        IMPLEMENT_ASN1_FUNCTIONS(OFD_SES_ESPictrueInfo)

    ASN1_SEQUENCE(OFD_SES_ESPropertyInfo) =
        {
            ASN1_SIMPLE(OFD_SES_ESPropertyInfo, SES_ESPropertyInfo_Type, ASN1_INTEGER),
            ASN1_SIMPLE(OFD_SES_ESPropertyInfo, SES_ESPropertyInfo_Name, ASN1_UTF8STRING),
            ASN1_SEQUENCE_OF(OFD_SES_ESPropertyInfo, SES_ESPropertyInfo_certList, ASN1_OCTET_STRING),
            ASN1_SIMPLE(OFD_SES_ESPropertyInfo, SES_ESPropertyInfo_CreateDate, ASN1_UTCTIME),
            ASN1_SIMPLE(OFD_SES_ESPropertyInfo, SES_ESPropertyInfo_ValidStart, ASN1_UTCTIME),
            ASN1_SIMPLE(OFD_SES_ESPropertyInfo, SES_ESPropertyInfo_ValidEnd, ASN1_UTCTIME)
}
    ASN1_SEQUENCE_END(OFD_SES_ESPropertyInfo)
        IMPLEMENT_ASN1_FUNCTIONS(OFD_SES_ESPropertyInfo)

    ASN1_SEQUENCE(ExtData) =
        {
            ASN1_SIMPLE(ExtData, SES_SealInfo_extnID, ASN1_OBJECT),
            ASN1_SIMPLE(ExtData, SES_SealInfo_critical, ASN1_BOOLEAN),
            ASN1_SIMPLE(ExtData, SES_SealInfo_extnValue, ASN1_OCTET_STRING)
}
    ASN1_SEQUENCE_END(ExtData)
        IMPLEMENT_ASN1_FUNCTIONS(ExtData)

    ASN1_SEQUENCE(OFD_SES_SealInfo) =
        {
            ASN1_SIMPLE(OFD_SES_SealInfo, SES_SealInfo_Header, OFD_SES_Header),
            ASN1_SIMPLE(OFD_SES_SealInfo, SES_SealInfo_EsID, ASN1_IA5STRING),
            ASN1_SIMPLE(OFD_SES_SealInfo, SES_SealInfo_Property, OFD_SES_ESPropertyInfo),
            ASN1_SIMPLE(OFD_SES_SealInfo, SES_SealInfo_Picture, OFD_SES_ESPictrueInfo),
            //ASN1_EXP_OPT(OFD_SES_SealInfo, SES_SealInfo_ExtDatas, ExtData, ASN1_TFLG_OPTIONAL)
            ASN1_SEQUENCE_OF(OFD_SES_SealInfo, SES_SealInfo_ExtDatas, ExtData)
}
    ASN1_SEQUENCE_END(OFD_SES_SealInfo)
        IMPLEMENT_ASN1_FUNCTIONS(OFD_SES_SealInfo)

    ASN1_SEQUENCE(OFD_SES_SignInfo) =
        {
            ASN1_SIMPLE(OFD_SES_SignInfo, SES_SignInfo_Cert, ASN1_OCTET_STRING),
            ASN1_SIMPLE(OFD_SES_SignInfo, SES_SignInfo_SignatureAlgorithm, ASN1_OBJECT),
            ASN1_SIMPLE(OFD_SES_SignInfo, SES_SignInfo_SignData, ASN1_BIT_STRING)
}
    ASN1_SEQUENCE_END(OFD_SES_SignInfo)
        IMPLEMENT_ASN1_FUNCTIONS(OFD_SES_SignInfo)

    ASN1_SEQUENCE(OFD_SESeal) =
        {
            ASN1_SIMPLE(OFD_SESeal, SES_SealInfo, OFD_SES_SealInfo),
            ASN1_SIMPLE(OFD_SESeal, SES_SignInfo, OFD_SES_SignInfo)
}
    ASN1_SEQUENCE_END(OFD_SESeal)
        IMPLEMENT_ASN1_FUNCTIONS(OFD_SESeal)

    ASN1_SEQUENCE(OFD_TBS_Sign) =
        {
            ASN1_SIMPLE(OFD_TBS_Sign, SES_Signature_Version, ASN1_INTEGER),
            ASN1_SIMPLE(OFD_TBS_Sign, SES_Signature_SESeal, OFD_SESeal),
            ASN1_SIMPLE(OFD_TBS_Sign, SES_Signature_TimeInfo, ASN1_BIT_STRING),
            ASN1_SIMPLE(OFD_TBS_Sign, SES_Signature_DataHash, ASN1_BIT_STRING),
            ASN1_SIMPLE(OFD_TBS_Sign, SES_Signature_PropertyInfo, ASN1_IA5STRING),
            ASN1_SIMPLE(OFD_TBS_Sign, SES_Signature_Cert, ASN1_IA5STRING),
            ASN1_SIMPLE(OFD_TBS_Sign, SES_Signature_SignatureAlgorithm, ASN1_OBJECT)
}
    ASN1_SEQUENCE_END(OFD_TBS_Sign)
        IMPLEMENT_ASN1_FUNCTIONS(OFD_TBS_Sign)

    ASN1_SEQUENCE(OFD_SES_Signature) =
        {
            ASN1_SIMPLE(OFD_SES_Signature, SES_TBS_Sign, OFD_TBS_Sign),
            ASN1_SIMPLE(OFD_SES_Signature, SES_Signature_Signature, ASN1_BIT_STRING)
}
    ASN1_SEQUENCE_END(OFD_SES_Signature)
        IMPLEMENT_ASN1_FUNCTIONS(OFD_SES_Signature)


    ASN1_SEQUENCE(OFD_SESeal_Indata) =
        {
            ASN1_SIMPLE(OFD_SESeal_Indata, SES_SealInfo, OFD_SES_SealInfo),
            ASN1_SIMPLE(OFD_SESeal_Indata, SES_SignInfo_Cert, ASN1_OCTET_STRING),
            ASN1_SIMPLE(OFD_SESeal_Indata, SES_SignInfo_SignatureAlgorithm, ASN1_OBJECT)
}
    ASN1_SEQUENCE_END(OFD_SESeal_Indata)
        IMPLEMENT_ASN1_FUNCTIONS(OFD_SESeal_Indata)


    // ----------国办新标准ZWFW政务服务平台

    ASN1_SEQUENCE(OFD_ZWFW_SES_Header) =
        {
            ASN1_SIMPLE(OFD_ZWFW_SES_Header, SES_Header_ID, ASN1_IA5STRING),
            ASN1_SIMPLE(OFD_ZWFW_SES_Header, SES_Header_Version, ASN1_INTEGER),
            ASN1_SIMPLE(OFD_ZWFW_SES_Header, SES_Header_VID, ASN1_IA5STRING)
}
    ASN1_SEQUENCE_END(OFD_ZWFW_SES_Header)
        IMPLEMENT_ASN1_FUNCTIONS(OFD_ZWFW_SES_Header)

    ASN1_SEQUENCE(OFD_ZWFW_SES_ESPictrueInfo) =
        {
            ASN1_SIMPLE(OFD_ZWFW_SES_ESPictrueInfo, SES_ESPictrueInfo_Type, ASN1_IA5STRING),
            ASN1_SIMPLE(OFD_ZWFW_SES_ESPictrueInfo, SES_ESPictrueInfo_Data, ASN1_OCTET_STRING),
            ASN1_SIMPLE(OFD_ZWFW_SES_ESPictrueInfo, SES_ESPictrueInfo_Width, ASN1_INTEGER),
            ASN1_SIMPLE(OFD_ZWFW_SES_ESPictrueInfo, SES_ESPictrueInfo_Height, ASN1_INTEGER)
}
    ASN1_SEQUENCE_END(OFD_ZWFW_SES_ESPictrueInfo)
        IMPLEMENT_ASN1_FUNCTIONS(OFD_ZWFW_SES_ESPictrueInfo)

    ASN1_SEQUENCE(OFD_ZWFW_SES_ESPropertyInfo) =
        {
            ASN1_SIMPLE(OFD_ZWFW_SES_ESPropertyInfo, SES_ESPropertyInfo_Type, ASN1_INTEGER),
            ASN1_SIMPLE(OFD_ZWFW_SES_ESPropertyInfo, SES_ESPropertyInfo_Name, ASN1_UTF8STRING),
            ASN1_SIMPLE(OFD_ZWFW_SES_ESPropertyInfo, SES_ESPropertyInfo_CertListType, ASN1_INTEGER),
            ASN1_SIMPLE(OFD_ZWFW_SES_ESPropertyInfo, SES_ESPropertyInfo_certList, OFD_ZWFW_SES_CertList),
            ASN1_SIMPLE(OFD_ZWFW_SES_ESPropertyInfo, SES_ESPropertyInfo_CreateDate, ASN1_UTCTIME),
            ASN1_SIMPLE(OFD_ZWFW_SES_ESPropertyInfo, SES_ESPropertyInfo_ValidStart, ASN1_UTCTIME),
            ASN1_SIMPLE(OFD_ZWFW_SES_ESPropertyInfo, SES_ESPropertyInfo_ValidEnd, ASN1_UTCTIME)
}
    ASN1_SEQUENCE_END(OFD_ZWFW_SES_ESPropertyInfo)
        IMPLEMENT_ASN1_FUNCTIONS(OFD_ZWFW_SES_ESPropertyInfo)

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    ASN1_CHOICE(OFD_ZWFW_SES_CertList) =
        {
            ASN1_SEQUENCE_OF(OFD_ZWFW_SES_CertList, CertLists.SES_CertList_Certs, ASN1_OCTET_STRING),
            ASN1_SEQUENCE_OF(OFD_ZWFW_SES_CertList, CertLists.SES_CertList_CertDigestList, OFD_ZWFW_CertDigestObj)
}
    ASN1_CHOICE_END(OFD_ZWFW_SES_CertList)
        IMPLEMENT_ASN1_FUNCTIONS(OFD_ZWFW_SES_CertList)

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    ASN1_SEQUENCE(OFD_ZWFW_CertDigestObj) =
        {
            ASN1_SIMPLE(OFD_ZWFW_CertDigestObj, SES_CertDigestObj_type, ASN1_PRINTABLESTRING),
            ASN1_SIMPLE(OFD_ZWFW_CertDigestObj, SES_CertDigestObj_value, ASN1_OCTET_STRING)
}
    ASN1_SEQUENCE_END(OFD_ZWFW_CertDigestObj)
        IMPLEMENT_ASN1_FUNCTIONS(OFD_ZWFW_CertDigestObj)

    //-------------------------------------------------------------------
    ASN1_SEQUENCE(OFD_ZWFW_ExtData) =
        {
            ASN1_SIMPLE(OFD_ZWFW_ExtData, SES_SealInfo_extnID, ASN1_OBJECT),
            ASN1_SIMPLE(OFD_ZWFW_ExtData, SES_SealInfo_critical, ASN1_BOOLEAN),
            ASN1_SIMPLE(OFD_ZWFW_ExtData, SES_SealInfo_extnValue, ASN1_OCTET_STRING)
}
    ASN1_SEQUENCE_END(OFD_ZWFW_ExtData)
        IMPLEMENT_ASN1_FUNCTIONS(OFD_ZWFW_ExtData)


    ASN1_SEQUENCE(OFD_ZWFW_SES_SealInfo) =
        {
            ASN1_SIMPLE(OFD_ZWFW_SES_SealInfo, SES_SealInfo_Header, OFD_ZWFW_SES_Header),
            ASN1_SIMPLE(OFD_ZWFW_SES_SealInfo, SES_SealInfo_EsID, ASN1_IA5STRING),
            ASN1_SIMPLE(OFD_ZWFW_SES_SealInfo, SES_SealInfo_Property, OFD_ZWFW_SES_ESPropertyInfo),
            ASN1_SIMPLE(OFD_ZWFW_SES_SealInfo, SES_SealInfo_Picture, OFD_ZWFW_SES_ESPictrueInfo),
            ASN1_SEQUENCE_OF(OFD_ZWFW_SES_SealInfo, SES_SealInfo_ExtDatas, OFD_ZWFW_ExtData)
}
    ASN1_SEQUENCE_END(OFD_ZWFW_SES_SealInfo)
        IMPLEMENT_ASN1_FUNCTIONS(OFD_ZWFW_SES_SealInfo)

    // 自定义结构?
    ASN1_SEQUENCE(OFD_ZWFW_SESeal) =
        {
            ASN1_SIMPLE(OFD_ZWFW_SESeal, SES_Seal_SealInfo, OFD_ZWFW_SES_SealInfo),
            ASN1_SIMPLE(OFD_ZWFW_SESeal, SES_Seal_Cert, ASN1_OCTET_STRING),
            ASN1_SIMPLE(OFD_ZWFW_SESeal, SES_Seal_SignAlgID, ASN1_OBJECT),
            ASN1_SIMPLE(OFD_ZWFW_SESeal, SES_Seal_SignedValue, ASN1_BIT_STRING)
}
    ASN1_SEQUENCE_END(OFD_ZWFW_SESeal)
        IMPLEMENT_ASN1_FUNCTIONS(OFD_ZWFW_SESeal)


    ASN1_SEQUENCE(OFD_ZWFW_TBS_Sign) =
        {
            ASN1_SIMPLE(OFD_ZWFW_TBS_Sign, SES_Signature_Version, ASN1_INTEGER),
            ASN1_SIMPLE(OFD_ZWFW_TBS_Sign, SES_Signature_SESeal, OFD_ZWFW_SESeal),
            ASN1_SIMPLE(OFD_ZWFW_TBS_Sign, SES_Signature_TimeInfo, ASN1_BIT_STRING),
            ASN1_SIMPLE(OFD_ZWFW_TBS_Sign, SES_Signature_DataHash, ASN1_BIT_STRING),
            ASN1_SIMPLE(OFD_ZWFW_TBS_Sign, SES_Signature_PropertyInfo, ASN1_IA5STRING),
            ASN1_SIMPLE(OFD_ZWFW_TBS_Sign, SES_Signature_Cert, ASN1_IA5STRING),
            ASN1_SIMPLE(OFD_ZWFW_TBS_Sign, SES_Signature_SignatureAlgorithm, ASN1_OBJECT)
}
    ASN1_SEQUENCE_END(OFD_ZWFW_TBS_Sign)
        IMPLEMENT_ASN1_FUNCTIONS(OFD_ZWFW_TBS_Sign)

    ASN1_SEQUENCE(OFD_ZWFW_SES_Signature) =
        {
            ASN1_SIMPLE(OFD_ZWFW_SES_Signature, SES_Signature_TBS_Sign, OFD_ZWFW_TBS_Sign),
            ASN1_SIMPLE(OFD_ZWFW_SES_Signature, SES_Signature_Signature, ASN1_BIT_STRING)
}
    ASN1_SEQUENCE_END(OFD_ZWFW_SES_Signature)
        IMPLEMENT_ASN1_FUNCTIONS(OFD_ZWFW_SES_Signature)

CParseSeal::CParseSeal(unsigned char* ucSealData,unsigned long ulSealSize)
{
    this->ucSealData = ucSealData;
    this->ulSealSize = ulSealSize;
    getSealInfo();
}

CParseSeal::~CParseSeal()
{

}

void CParseSeal::setSealData(unsigned char* ucSealData, unsigned long ulSealSize)
{
    this->ucSealData = ucSealData;
    this->ulSealSize = ulSealSize;
}

void CParseSeal::getSealInfo()
{
    SESeal *temp = nullptr;
    temp = SESeal_new();
    if(temp == nullptr){
        qDebug()<<"SESeal_new Err";
        return;
    }
    const unsigned char *p = ucSealData;
    temp = d2i_SESeal(&temp,&p,(long)ulSealSize);
    if(temp == nullptr){
        qDebug()<<"d2i_SESeal Err";
        QMessageBox::warning(nullptr,"解析印章","印章解析失败，格式错误或数据损坏",nullptr,nullptr);
        return;
    }
    //签章图片
    ES_ESPictrueInfo_Data = QString((char*)temp->SES_SealInfo->SES_SealInfo_Picture->ES_ESPictrueInfo_Data->data);
    //签章图片类型
    SES_ESPictrueInfo_Type = QString((char*)temp->SES_SealInfo->SES_SealInfo_Picture->SES_ESPictrueInfo_Type->data);
    //制章人签名证书
    SES_SignInfo_Cert = QString((char*)temp->SES_SignInfo->SES_SignInfo_Cert->data);
    //制章人签名证书签名算法标示
    char cBuf[128] = "\0";
    i2t_ASN1_OBJECT(cBuf,128,temp->SES_SignInfo->SES_SignInfo_SignatureAlgorithm);
    SES_SignInfo_SignatureAlgorithm = cBuf;
//    memcpy(bstrSealInfo,cBuf,strlen(cBuf));
    //制章人签名值
    SES_SignInfo_SignData = QString((char*)temp->SES_SignInfo->SES_SignInfo_SignData->data);
    //印章类型
    int iType = ASN1_INTEGER_get(temp->SES_SealInfo->SES_SealInfo_Property->SES_ESPropertyInfo_Type);
    char chType[65];
    _itoa( iType, chType, 10);
    SES_ESPropertyInfo_Type = chType;
//    memcpy(bstrSealInfo,chType,strlen(chType));
    //印章名称
//    QTextCodec* utf8 = QTextCodec::codecForName("UTF-8");
//    QTextCodec* gbk = QTextCodec::codecForName("gbk");
//    QString qstrSealName = QString::fromLatin1((char*)temp->SES_SealInfo->SES_SealInfo_Property->SES_ESPropertyInfo_Name->data);
//    QString utf8SealName = utf8->toUnicode(qstrSealName.toLocal8Bit().data());
//    QString gbkSealName = QString::fromLatin1((char*)temp->SES_SealInfo->SES_SealInfo_Property->SES_ESPropertyInfo_Name->data);
//    SES_ESPropertyInfo_Name = utf8->fromUnicode(gbk->toUnicode(gbkSealName.toLocal8Bit().data())).data();
    char tempSealName[256] = { 0 };
    memcpy(tempSealName, temp->SES_SealInfo->SES_SealInfo_Property->SES_ESPropertyInfo_Name->data,
           (size_t)temp->SES_SealInfo->SES_SealInfo_Property->SES_ESPropertyInfo_Name->length);
    std::string stdTempSealNameForUTF = UtilFunction::GbkToUtf8(tempSealName);
    SES_ESPropertyInfo_Name = QString::fromStdString(stdTempSealNameForUTF);
    //签章人证书列表
    SES_ESPropertyInfo_Cert = QString((char*)temp->SES_SealInfo->SES_SealInfo_Property->SES_ESPropertyInfo_Cert->data);
    //印章制作日期
    SES_ESPropertyInfo_CreateDate = QString((char*)temp->SES_SealInfo->SES_SealInfo_Property->SES_ESPropertyInfo_CreateDate->data);
    //印章有效起始日期
    SES_ESPropertyInfo_ValidStart = QString((char*)temp->SES_SealInfo->SES_SealInfo_Property->SES_ESPropertyInfo_ValidStart->data);
    //印章有效终止日期
    SES_ESPropertyInfo_ValidEnd = QString((char*)temp->SES_SealInfo->SES_SealInfo_Property->SES_ESPropertyInfo_ValidEnd->data);
    //电子印章数据标识
    SES_SealInfo_EsID = QString((char*)temp->SES_SealInfo->SES_SealInfo_EsID->data);

    if(temp != nullptr)
    {
        SESeal_free(temp);
    }

    if(ucSealData != nullptr)
    {
        free(ucSealData);
    }
}

QString CParseSeal::getFormateSealInfo()
{
    QString qstrSealInfo = ".>>>>印章信息<<<<<\n\n";
    qstrSealInfo += "..印章名称:\t"+ SES_ESPropertyInfo_Name +"\n\n";
    qstrSealInfo += "..印章类型:\t"+ SES_ESPropertyInfo_Type +"\n\n";
    qstrSealInfo += "..制作日期:\t"+ SES_ESPropertyInfo_CreateDate +"\n\n";
    qstrSealInfo += "..起始日期:\t"+ SES_ESPropertyInfo_ValidStart +"\n\n";
    qstrSealInfo += "..终止日期:\t"+ SES_ESPropertyInfo_ValidEnd +"\n\n";
    qstrSealInfo += "..数据标识:\t"+ SES_SealInfo_EsID +"\n\n";
    qstrSealInfo += "..图片类型:\t"+ SES_ESPictrueInfo_Type +"\n\n";

    return qstrSealInfo;
}
