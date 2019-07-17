#ifndef SESEALASN1_H_H_
#define SESEALASN1_H_H_

#include <openssl/ecdsa.h>
#include <openssl/asn1.h>
#include <openssl/asn1t.h>
#include <openssl/objects.h>

//头信息的ASN.1定义
typedef struct SHS_Header_st1
{
	ASN1_IA5STRING *SHS_Header_ID;
	ASN1_INTEGER *SHS_Header_Version;
	ASN1_IA5STRING *SHS_Header_VID;
	ASN1_INTEGER *SHS_Header_Length;
} SHS_Header;
DECLARE_ASN1_FUNCTIONS(SHS_Header);



	//印章图片信息的ASN.1定义
	typedef struct SES_ESPictrueInfo_st1
{
	ASN1_IA5STRING *SES_ESPictrueInfo_Type;
	ASN1_OCTET_STRING *ES_ESPictrueInfo_Data;
} SES_ESPictrueInfo;
DECLARE_ASN1_FUNCTIONS(SES_ESPictrueInfo);

	//印章属性信息的ASN.1定义
	typedef struct SES_ESPropertyInfo_st1
{
	ASN1_INTEGER *SES_ESPropertyInfo_Type;
	ASN1_UTF8STRING *SES_ESPropertyInfo_Name;
	ASN1_OCTET_STRING *SES_ESPropertyInfo_Cert;
	ASN1_UTCTIME *SES_ESPropertyInfo_CreateDate;
	ASN1_UTCTIME *SES_ESPropertyInfo_ValidStart;
	ASN1_UTCTIME *SES_ESPropertyInfo_ValidEnd;
//	ASN1_INTEGER *SES_ESPropertyInfo_UserRight;
} SES_ESPropertyInfo;
DECLARE_ASN1_FUNCTIONS(SES_ESPropertyInfo);

	//印章信息的ASN.1定义
	typedef struct SES_SealInfo_st
{
	ASN1_IA5STRING *SES_SealInfo_EsID;
	SES_ESPropertyInfo *SES_SealInfo_Property;
	SES_ESPictrueInfo *SES_SealInfo_Picture;
	ASN1_OCTET_STRING *SES_SealInfo_Data;
} SES_SealInfo;
DECLARE_ASN1_FUNCTIONS(SES_SealInfo);


	//印章签名信息的ASN.1定义
	typedef struct SES_SignInfo_st1
{
	ASN1_OCTET_STRING *SES_SignInfo_Cert;
	ASN1_OBJECT *SES_SignInfo_SignatureAlgorithm;
	ASN1_BIT_STRING *SES_SignInfo_SignData;

	/*ASN1_INTEGER *temp1;
	ASN1_ENUMERATED *temp2;
	ASN1_BIT_STRING *temp3;
	ASN1_OCTET_STRING *temp4;
	ASN1_PRINTABLESTRING *temp5;
	ASN1_T61STRING *temp6;
	ASN1_IA5STRING *temp7;
	ASN1_GENERALSTRING *temp8;
	ASN1_UNIVERSALSTRING *temp9;
	ASN1_BMPSTRING *temp10;
	ASN1_UTCTIME *temp11;
	ASN1_TIME *temp12;
	ASN1_GENERALIZEDTIME *temp13;
	ASN1_VISIBLESTRING *temp14;
	ASN1_UTF8STRING *temp15;
	ASN1_STRING *temp16;*/

} SES_SignInfo;
DECLARE_ASN1_FUNCTIONS(SES_SignInfo);


	typedef struct SESeal_st
{
	SHS_Header *SHS_Header;
	SES_SealInfo *SES_SealInfo;
	SES_SignInfo *SES_SignInfo;
} SESeal;
DECLARE_ASN1_FUNCTIONS(SESeal);


	typedef struct SESeal_st1
{
	SHS_Header *SHS_Header;
	SES_SealInfo *SES_SealInfo;
} SEIndata;
DECLARE_ASN1_FUNCTIONS(SEIndata);


	//电子签章数据的ASN.1定义
	typedef struct SES_Signature_st1
{
	ASN1_INTEGER *SES_Signature_Version;
	SESeal *SES_Signature_SESeal;
	ASN1_BIT_STRING *SES_Signature_TimeInfo;
	ASN1_BIT_STRING *SES_Signature_DataHash;
	ASN1_IA5STRING *SES_Signature_PropertyInfo;
	ASN1_IA5STRING *SES_Signature_Certid;
	ASN1_OBJECT *SES_Signature_SignatureAlgorithm;
	ASN1_BIT_STRING *SES_Signature_Signature;
} SES_Signature;
DECLARE_ASN1_FUNCTIONS(SES_Signature);


#endif