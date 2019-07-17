#pragma once
#include <openssl/asn1.h>
#include <openssl/asn1t.h>
#include<list>


//头信息的ASN.1定义
typedef struct OFD_SES_Header_st1
{
	~OFD_SES_Header_st1()
	{
		if (SES_Header_ID != NULL) delete SES_Header_ID;
		if (SES_Header_VID != NULL) delete SES_Header_VID;
	}
	ASN1_IA5STRING *SES_Header_ID;
	ASN1_INTEGER *SES_Header_Version;
	ASN1_IA5STRING *SES_Header_VID;
} OFD_SES_Header;


//印章图片信息的ASN.1定义
typedef struct OFD_SES_ESPictrueInfo_st1
{
	~OFD_SES_ESPictrueInfo_st1()
	{
		if (SES_ESPictrueInfo_Type != NULL) delete SES_ESPictrueInfo_Type;
		if (SES_ESPictrueInfo_Data != NULL) delete SES_ESPictrueInfo_Data;
	}
	ASN1_IA5STRING *SES_ESPictrueInfo_Type;
	ASN1_OCTET_STRING *SES_ESPictrueInfo_Data;
	ASN1_INTEGER *SES_ESPictrueInfo_Width;
	ASN1_INTEGER *SES_ESPictrueInfo_Height;
} OFD_SES_ESPictrueInfo;
DECLARE_ASN1_FUNCTIONS(OFD_SES_ESPictrueInfo)


//印章属性信息的ASN.1定义
typedef struct OFD_SES_ESPropertyInfo_st1
{
	~OFD_SES_ESPropertyInfo_st1()
	{
		if (SES_ESPropertyInfo_Name != NULL) delete SES_ESPropertyInfo_Name;
		/*if (!SES_ESPropertyInfo_certList.empty())
		{
			for(list<ASN1_OCTET_STRING*>::iterator it = SES_ESPropertyInfo_certList.begin(); it != SES_ESPropertyInfo_certList.end(); ++it)
			{
				if (*it != NULL)
				{
					delete *it;
				}
			}
		}*/
		if (SES_ESPropertyInfo_CreateDate != NULL) delete SES_ESPropertyInfo_CreateDate;
		if (SES_ESPropertyInfo_ValidStart != NULL) delete SES_ESPropertyInfo_ValidStart;
		if (SES_ESPropertyInfo_ValidEnd != NULL) delete SES_ESPropertyInfo_ValidEnd;
	}
	ASN1_INTEGER *SES_ESPropertyInfo_Type;
	ASN1_UTF8STRING *SES_ESPropertyInfo_Name;
	//list<ASN1_OCTET_STRING*> SES_ESPropertyInfo_certList;
	STACK_OF(ASN1_OCTET_STRING*)* SES_ESPropertyInfo_certList;
	ASN1_UTCTIME *SES_ESPropertyInfo_CreateDate;
	ASN1_UTCTIME *SES_ESPropertyInfo_ValidStart;
	ASN1_UTCTIME *SES_ESPropertyInfo_ValidEnd;
} OFD_SES_ESPropertyInfo;
DECLARE_ASN1_FUNCTIONS(OFD_SES_ESPropertyInfo)


typedef struct ExtData_st1 {
	~ExtData_st1()
	{
		if (SES_SealInfo_extnValue != NULL) delete SES_SealInfo_extnValue;
	}

	ASN1_OBJECT* SES_SealInfo_extnID;
	ASN1_BOOLEAN SES_SealInfo_critical /*= false*/;
	ASN1_OCTET_STRING* SES_SealInfo_extnValue;
}ExtData;
DECLARE_ASN1_FUNCTIONS(ExtData)
//印章信息的ASN.1定义
typedef struct OFD_SES_SealInfo_st
{
	~OFD_SES_SealInfo_st()
	{
		if (SES_SealInfo_Header != NULL) delete SES_SealInfo_Header;
		if (SES_SealInfo_EsID != NULL) delete SES_SealInfo_EsID;
		if (SES_SealInfo_Property != NULL) delete SES_SealInfo_Property;
		if (SES_SealInfo_Picture != NULL) delete SES_SealInfo_Picture;
		/*if (!SES_SealInfo_ExtDatas.empty())
		{
			for( list<ExtData*>::iterator it = SES_SealInfo_ExtDatas.begin(); it != SES_SealInfo_ExtDatas.end(); ++it)
			{
				if (*it != NULL)
				{
					delete *it;
				}
			}
		}*/
	}

	OFD_SES_Header *SES_SealInfo_Header;
	ASN1_IA5STRING *SES_SealInfo_EsID;
	OFD_SES_ESPropertyInfo *SES_SealInfo_Property;
	OFD_SES_ESPictrueInfo *SES_SealInfo_Picture;
	//list<ExtData*> SES_SealInfo_ExtDatas;
	STACK_OF(ExtData*)* SES_SealInfo_ExtDatas;
} OFD_SES_SealInfo;
DECLARE_ASN1_FUNCTIONS(OFD_SES_SealInfo)


//印章签名信息的ASN.1定义
typedef struct OFD_SES_SignInfo_st1
{
	~OFD_SES_SignInfo_st1()
	{
		if (SES_SignInfo_Cert != NULL) delete SES_SignInfo_Cert;
		if (SES_SignInfo_SignData != NULL) delete SES_SignInfo_SignData;
	}
	ASN1_OCTET_STRING *SES_SignInfo_Cert;
	ASN1_OBJECT *SES_SignInfo_SignatureAlgorithm;
	ASN1_BIT_STRING *SES_SignInfo_SignData;
} OFD_SES_SignInfo;
DECLARE_ASN1_FUNCTIONS(OFD_SES_SignInfo)


typedef struct OFD_SESeal_st
{
	~OFD_SESeal_st(){
		if (SES_SealInfo != NULL) delete SES_SealInfo;
		if (SES_SignInfo != NULL) delete SES_SignInfo;
	}
	OFD_SES_SealInfo *SES_SealInfo;
	OFD_SES_SignInfo *SES_SignInfo;
} OFD_SESeal;
DECLARE_ASN1_FUNCTIONS(OFD_SESeal);

typedef struct OFD_SESeal_Indata_st
{
	~OFD_SESeal_Indata_st(){
		if (SES_SealInfo != NULL) delete SES_SealInfo;
	}
	OFD_SES_SealInfo *SES_SealInfo;
	ASN1_OCTET_STRING *SES_SignInfo_Cert;
	ASN1_OBJECT *SES_SignInfo_SignatureAlgorithm;
} OFD_SESeal_Indata;
DECLARE_ASN1_FUNCTIONS(OFD_SESeal_Indata);

//电子签章数据的ASN.1定义
typedef struct OFD_TBS_Sign_st1
{
	~OFD_TBS_Sign_st1()
	{
		if(SES_Signature_SESeal !=NULL) delete SES_Signature_SESeal;
		if(SES_Signature_TimeInfo !=NULL) delete SES_Signature_TimeInfo;
		if(SES_Signature_DataHash !=NULL) delete SES_Signature_DataHash;
		if(SES_Signature_PropertyInfo !=NULL) delete SES_Signature_PropertyInfo;
		if(SES_Signature_Cert !=NULL) delete SES_Signature_Cert;
	}
	ASN1_INTEGER *SES_Signature_Version;
	OFD_SESeal *SES_Signature_SESeal;
	ASN1_BIT_STRING *SES_Signature_TimeInfo;
	ASN1_BIT_STRING *SES_Signature_DataHash;
	ASN1_IA5STRING *SES_Signature_PropertyInfo;
	ASN1_OCTET_STRING *SES_Signature_Cert;
	ASN1_OBJECT *SES_Signature_SignatureAlgorithm;
} OFD_TBS_Sign;
DECLARE_ASN1_FUNCTIONS(OFD_TBS_Sign)

typedef struct OFD_SES_Signature_st1
{
	~OFD_SES_Signature_st1()
	{
		if(SES_TBS_Sign !=NULL) delete SES_TBS_Sign;
		if(SES_Signature_Signature !=NULL) delete SES_Signature_Signature;
	}
	OFD_TBS_Sign *SES_TBS_Sign;
	ASN1_BIT_STRING *SES_Signature_Signature;
} OFD_SES_Signature;
DECLARE_ASN1_FUNCTIONS(OFD_SES_Signature)
