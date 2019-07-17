#pragma once
#include <openssl/asn1.h>
#include <openssl/asn1t.h>
#include<list>


//头信息的ASN.1定义
typedef struct OFD_ZWFW_SES_Header_st1
{
	~OFD_ZWFW_SES_Header_st1()
	{
		if (SES_Header_ID != NULL) delete SES_Header_ID;
		if (SES_Header_VID != NULL) delete SES_Header_VID;
	}
	ASN1_IA5STRING *SES_Header_ID;
	ASN1_INTEGER *SES_Header_Version;
	ASN1_IA5STRING *SES_Header_VID;
} OFD_ZWFW_SES_Header;


//印章图片信息的ASN.1定义
typedef struct OFD_ZWFW_SES_ESPictrueInfo_st1
{
	~OFD_ZWFW_SES_ESPictrueInfo_st1()
	{
		if (SES_ESPictrueInfo_Type != NULL) delete SES_ESPictrueInfo_Type;
		if (SES_ESPictrueInfo_Data != NULL) delete SES_ESPictrueInfo_Data;
	}
	ASN1_IA5STRING *SES_ESPictrueInfo_Type;
	ASN1_OCTET_STRING *SES_ESPictrueInfo_Data;
	ASN1_INTEGER *SES_ESPictrueInfo_Width;
	ASN1_INTEGER *SES_ESPictrueInfo_Height;
} OFD_ZWFW_SES_ESPictrueInfo;
DECLARE_ASN1_FUNCTIONS(OFD_ZWFW_SES_ESPictrueInfo)


//印章属性信息的ASN.1定义
typedef struct OFD_ZWFW_SES_ESPropertyInfo_st1
{
	~OFD_ZWFW_SES_ESPropertyInfo_st1()
	{
		if (SES_ESPropertyInfo_Name != NULL) delete SES_ESPropertyInfo_Name;
		if (SES_ESPropertyInfo_certList != NULL) delete SES_ESPropertyInfo_certList;
		if (SES_ESPropertyInfo_CreateDate != NULL) delete SES_ESPropertyInfo_CreateDate;
		if (SES_ESPropertyInfo_ValidStart != NULL) delete SES_ESPropertyInfo_ValidStart;
		if (SES_ESPropertyInfo_ValidEnd != NULL) delete SES_ESPropertyInfo_ValidEnd;
	}
	ASN1_INTEGER *SES_ESPropertyInfo_Type;
	ASN1_UTF8STRING *SES_ESPropertyInfo_Name;
	ASN1_INTEGER *SES_ESPropertyInfo_CertListType;
	STACK_OF(OFD_ZWFW_SES_CertList*) *SES_ESPropertyInfo_certList;
	ASN1_UTCTIME *SES_ESPropertyInfo_CreateDate;
	ASN1_UTCTIME *SES_ESPropertyInfo_ValidStart;
	ASN1_UTCTIME *SES_ESPropertyInfo_ValidEnd;
} OFD_ZWFW_SES_ESPropertyInfo;
DECLARE_ASN1_FUNCTIONS(OFD_ZWFW_SES_ESPropertyInfo)


typedef struct OFD_ZWFW_SES_CertList_st1 {
	~OFD_ZWFW_SES_CertList_st1()
	{
		if (NULL != CertLists.SES_CertList_CertDigestList) delete CertLists.SES_CertList_CertDigestList;
		if (NULL != CertLists.SES_CertList_Certs) delete CertLists.SES_CertList_Certs;
	}
	int type;
	union CertLists_st1{
		STACK_OF(ASN1_OCTET_STRING*) *SES_CertList_Certs;
		STACK_OF(OFD_ZWFW_CertDigestObj*) *SES_CertList_CertDigestList;
	}CertLists;
}OFD_ZWFW_SES_CertList;
DECLARE_ASN1_FUNCTIONS(OFD_ZWFW_SES_CertList)


typedef struct OFD_ZWFW_CertDigestObj_st1 {
	~OFD_ZWFW_CertDigestObj_st1()
	{
		if (SES_CertDigestObj_type != NULL) delete SES_CertDigestObj_type;
		if (SES_CertDigestObj_value != NULL) delete SES_CertDigestObj_value;
	}

	ASN1_PRINTABLESTRING *SES_CertDigestObj_type;
	ASN1_OCTET_STRING *SES_CertDigestObj_value;
}OFD_ZWFW_CertDigestObj;
DECLARE_ASN1_FUNCTIONS(OFD_ZWFW_CertDigestObj)


typedef struct OFD_ZWFW_ExtData_st1 {
	~OFD_ZWFW_ExtData_st1()
	{
		if (SES_SealInfo_extnValue != NULL) delete SES_SealInfo_extnValue;
	}

	ASN1_OBJECT* SES_SealInfo_extnID;
	ASN1_BOOLEAN SES_SealInfo_critical /*= false*/;
	ASN1_OCTET_STRING* SES_SealInfo_extnValue;
}OFD_ZWFW_ExtData;
DECLARE_ASN1_FUNCTIONS(OFD_ZWFW_ExtData)
//印章信息的ASN.1定义
typedef struct OFD_ZWFW_SES_SealInfo_st
{
	~OFD_ZWFW_SES_SealInfo_st()
	{
		if (SES_SealInfo_Header != NULL) delete SES_SealInfo_Header;
		if (SES_SealInfo_EsID != NULL) delete SES_SealInfo_EsID;
		if (SES_SealInfo_Property != NULL) delete SES_SealInfo_Property;
		if (SES_SealInfo_Picture != NULL) delete SES_SealInfo_Picture;
		if (SES_SealInfo_ExtDatas != NULL) delete SES_SealInfo_ExtDatas;
	}

	OFD_ZWFW_SES_Header *SES_SealInfo_Header;
	ASN1_IA5STRING *SES_SealInfo_EsID;
	OFD_ZWFW_SES_ESPropertyInfo *SES_SealInfo_Property;
	OFD_ZWFW_SES_ESPictrueInfo *SES_SealInfo_Picture;
	STACK_OF(OFD_ZWFW_ExtData*)* SES_SealInfo_ExtDatas;
} OFD_ZWFW_SES_SealInfo;
DECLARE_ASN1_FUNCTIONS(OFD_ZWFW_SES_SealInfo)

// 国办印章结构定义
typedef struct OFD_ZWFW_SESeal_st
{
	~OFD_ZWFW_SESeal_st(){
		if (SES_Seal_SealInfo != NULL) delete SES_Seal_SealInfo;
		if (SES_Seal_Cert != NULL) delete SES_Seal_Cert;
		if (SES_Seal_SignAlgID != NULL) delete SES_Seal_SignAlgID;
		if (SES_Seal_SignedValue != NULL) delete SES_Seal_SignedValue;
	}
	OFD_ZWFW_SES_SealInfo *SES_Seal_SealInfo;
	ASN1_OCTET_STRING *SES_Seal_Cert;
	ASN1_OBJECT *SES_Seal_SignAlgID;		//=============
	ASN1_BIT_STRING *SES_Seal_SignedValue;	//=============
} OFD_ZWFW_SESeal;
DECLARE_ASN1_FUNCTIONS(OFD_ZWFW_SESeal);



//电子签章数据的ASN.1定义
typedef struct OFD_ZWFW_TBS_Sign_st1
{
	~OFD_ZWFW_TBS_Sign_st1()
	{
		if(SES_Signature_SESeal !=NULL) delete SES_Signature_SESeal;
		if(SES_Signature_TimeInfo !=NULL) delete SES_Signature_TimeInfo;
		if(SES_Signature_DataHash !=NULL) delete SES_Signature_DataHash;
		if(SES_Signature_PropertyInfo !=NULL) delete SES_Signature_PropertyInfo;
		if(SES_Signature_Cert !=NULL) delete SES_Signature_Cert;
	}
	ASN1_INTEGER *SES_Signature_Version;
	OFD_ZWFW_SESeal *SES_Signature_SESeal;
	ASN1_BIT_STRING *SES_Signature_TimeInfo;
	ASN1_BIT_STRING *SES_Signature_DataHash;
	ASN1_IA5STRING *SES_Signature_PropertyInfo;
	ASN1_OCTET_STRING *SES_Signature_Cert;
	ASN1_OBJECT *SES_Signature_SignatureAlgorithm;
} OFD_ZWFW_TBS_Sign;
DECLARE_ASN1_FUNCTIONS(OFD_ZWFW_TBS_Sign)

typedef struct OFD_ZWFW_SES_Signature_st1
{
	~OFD_ZWFW_SES_Signature_st1()
	{
		if(SES_Signature_TBS_Sign !=NULL) delete SES_Signature_TBS_Sign;
		if(SES_Signature_Signature !=NULL) delete SES_Signature_Signature;
	}
	OFD_ZWFW_TBS_Sign *SES_Signature_TBS_Sign;
	ASN1_BIT_STRING *SES_Signature_Signature;
} OFD_ZWFW_SES_Signature;
DECLARE_ASN1_FUNCTIONS(OFD_ZWFW_SES_Signature)
