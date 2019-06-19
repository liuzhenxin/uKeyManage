#ifndef TYPEDEFINE_H
#define TYPEDEFINE_H
#include <windows.h>
#include <QLibrary>

#define EPST_SKEY_IDX_AMK			0xA2			//应用维护对称秘钥
#define EPST_SKEY_IDX_EDK			0xA6			//数据加解密对称秘钥

#define SGD_SM4_ECB					0x00000401		//SM4ECB模式
#define SGD_SM4_CBC					0x00000402		//SM4CBC模式

#define SECURE_ANYONE_ACCOUNT       0x000000FF      //文件权限 任何人
#define SECURE_USER_ACCOUNT         0x00000010      //文件权限 用户权限
#define SECURE_ADM_ACCOUNT          0x00000001      //文件权限 管理员权限
#define SECURE_NEVER_ACCOUNT        0x00000000      //文件权限 不允许

typedef void* DEVHANDLE;
typedef void* HAPPLICATION;
typedef void* HCONTAINER;


typedef struct Struct_Version{
    BYTE major;
    BYTE minor;
}VERSION;

typedef struct Struct_DEVINFO{
    VERSION		Version;
    CHAR		Manufacturer[64];
    CHAR		Issuer[64];
    CHAR		Label[32];
    CHAR		SerialNumber[32];
    VERSION		HWVersion;
    VERSION		FirmwareVersion;
    ULONG		AlgSymCap;
    ULONG		AlgAsymCap;
    ULONG		AlgHashCap;
    ULONG		DevAuthAlgId;
    ULONG		TotalSpace;
    ULONG		FreeSpace;
    ULONG		MaxECCBufferSize;
    ULONG		MaxBufferSize;
    BYTE  		Reserved[64];
}DEVINFO,*PDEVINFO;

#define MAX_RSA_MODULUS_LEN 256
#define MAX_RSA_EXPONENT_LEN 4
typedef struct Struct_RSAPUBLICKEYBLOB{
    ULONG	AlgID;
    ULONG	BitLen;
    BYTE	Modulus[MAX_RSA_MODULUS_LEN];
    BYTE	PublicExponent[MAX_RSA_EXPONENT_LEN];
}RSAPUBLICKEYBLOB, *PRSAPUBLICKEYBLOB;

#define ECC_MAX_MODULUS_BITS_LEN 512
typedef struct Struct_ECCPRIVATEKEYBLOB{
    ULONG	BitLen;
    BYTE	PrivateKey[ECC_MAX_MODULUS_BITS_LEN/8];
}ECCPRIVATEKEYBLOB, *PECCPRIVATEKEYBLOB;

#define ECC_MAX_XCOORDINATE_BITS_LEN 512
#define ECC_MAX_YCOORDINATE_BITS_LEN 512
typedef struct Struct_ECCPUBLICKEYBLOB{
    ULONG	BitLen;
    BYTE	XCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8];
    BYTE	YCoordinate[ECC_MAX_YCOORDINATE_BITS_LEN/8];
}ECCPUBLICKEYBLOB, *PECCPUBLICKEYBLOB;

typedef struct Struct_ECCCIPHERBLOB{
    BYTE  XCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8];
    BYTE  YCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8];
    BYTE  HASH[32];
    ULONG CipherLen;
    BYTE  Cipher[1];
} ECCCIPHERBLOB, *PECCCIPHERBLOB;
//
typedef struct SKF_ENVELOPEDKEYBLOB{
    ULONG Version;
    ULONG ulSymmAlgID;
    ULONG ulBits;
    BYTE cbEncryptedPriKey[64];
    ECCPUBLICKEYBLOB PubKey;
    ECCCIPHERBLOB ECCCipherBlob;
}ENVELOPEDKEYBLOB, *PENVELOPEDKEYBLOB;

typedef struct Struct_ECCSIGNATUREBLOB{
    BYTE r[ECC_MAX_XCOORDINATE_BITS_LEN/8];
    BYTE s[ECC_MAX_XCOORDINATE_BITS_LEN/8];
} ECCSIGNATUREBLOB, *PECCSIGNATUREBLOB;

typedef struct Struct_BLOCKCIPHERPARAM{
    BYTE	IV[4096];
    ULONG	IVLen;
    ULONG	PaddingType;
    ULONG	FeedBitLen;
} BLOCKCIPHERPARAM, *PBLOCKCIPHERPARAM;

typedef struct Struct_FILEATTRIBUTE{
    CHAR	FileName[32];
    ULONG	FileSize;
    ULONG	ReadRights;
    ULONG	WriteRights;
} FILEATTRIBUTE, *PFILEATTRIBUTE;
typedef ULONG(WINAPI *PFN_SKF_WaitForDevEvent)(LPSTR szDevName,ULONG *pulDevNameLen, ULONG *pulEvent);
typedef ULONG(WINAPI *PFN_SKF_FormatDevice)();
typedef ULONG(WINAPI *PFN_SKF_EnumDev)(BOOL bPresent, LPSTR szNameList, ULONG *pulSize);
typedef ULONG(WINAPI *PFN_SKF_ConnectDev)(LPSTR szName, DEVHANDLE *phDev);
typedef ULONG(WINAPI *PFN_SKF_UnblockPIN)(HAPPLICATION hApplication, LPSTR szAdminPIN, LPSTR szNewUserPIN,  ULONG *pulRetryCount);
typedef ULONG(WINAPI *PFN_SKF_GetDevState )(LPSTR szDevName, ULONG *pulDevState);
typedef ULONG(WINAPI *PFN_SKF_DisConnectDev)(DEVHANDLE hDev);
typedef ULONG(WINAPI *PFN_SKF_GetDevInfo)(DEVHANDLE hDev, DEVINFO *pDevInfo);
typedef ULONG(WINAPI *PFN_SKF_GetPINInfo)(HAPPLICATION hApplication, ULONG ulPINType, ULONG *pulMaxRetryCount, ULONG *pulRemainRetryCount, BOOL *pbDefaultPin);
typedef ULONG(WINAPI *PFN_SKF_VerifyPIN)(HAPPLICATION hApplication, ULONG ulPINType, LPSTR szPIN, ULONG *pulRetryCount);
typedef ULONG(WINAPI *PFN_SKF_ChangePIN)(HAPPLICATION hApplication, ULONG ulPINType, LPSTR szOldPin, LPSTR szNewPin, ULONG *pulRetryCount);
typedef ULONG(WINAPI *PFN_SKF_EnumApplication)(DEVHANDLE hDev, LPSTR szAppName,ULONG *pulSize);
typedef ULONG(WINAPI *PFN_SKF_CreateApplication)(DEVHANDLE hDev, LPSTR szAppName, LPSTR szAdminPin, DWORD dwAdminPinRetryCount,LPSTR szUserPin, DWORD dwUserPinRetryCount,DWORD dwCreateFileRights, HAPPLICATION *phApplication);
typedef ULONG(WINAPI *PFN_SKF_DeleteApplication)(DEVHANDLE hDev, LPSTR szAppName);
typedef ULONG(WINAPI *PFN_SKF_OpenApplication)(DEVHANDLE hDev, LPSTR szAppName, HAPPLICATION *phApplication);
typedef ULONG(WINAPI *PFN_SKF_CloseApplication)(HAPPLICATION hApplication);
typedef ULONG(WINAPI *PFN_SKF_CreateContainer)(HAPPLICATION hApplication, LPSTR szContainerName, HCONTAINER *phContainer);
typedef ULONG(WINAPI *PFN_SKF_DeleteContainer)(HAPPLICATION hApplication, LPSTR szContainerName);
typedef ULONG(WINAPI *PFN_SKF_OpenContainer)(HAPPLICATION hApplication,LPSTR szContainerName,HCONTAINER *phContainer);
typedef ULONG(WINAPI *PFN_SKF_CloseContainer)(HCONTAINER hContainer);
typedef ULONG(WINAPI *PFN_SKF_EnumContainer)(HAPPLICATION hApplication, LPSTR szContainerName, ULONG *pulSize);
typedef ULONG(WINAPI *PFN_SKF_GetContainerType)(HCONTAINER hContainer, ULONG *pulContainerType);
typedef ULONG(WINAPI *PFN_SKF_ImportCertificate)(HCONTAINER hContainer, BOOL bSignFlag,  BYTE* pbCert, ULONG ulCertLen);
typedef ULONG(WINAPI *PFN_SKF_ExportCertificate)(HCONTAINER hContainer, BOOL bSignFlag,  BYTE* pbCert, ULONG *pulCertLen);
typedef ULONG(WINAPI *PFN_SKF_GenRandom)(DEVHANDLE hDev, BYTE *pbRandom, ULONG ulRandomLen);
typedef ULONG(WINAPI *PFN_SKF_GenRSAKeyPair)(HCONTAINER hContainer, ULONG ulBitsLen, RSAPUBLICKEYBLOB *pBlob);
typedef ULONG(WINAPI *PFN_SKF_ImportRSAKeyPair)(HCONTAINER hContainer, ULONG ulSymAlgId, BYTE *pbWrappedKey, ULONG ulWrappedKeyLen, BYTE *pbEncryptedData, ULONG ulEncryptedDataLen);
typedef ULONG(WINAPI *PFN_SKF_RSASignData)(HCONTAINER hContainer, BYTE *pbData, ULONG  ulDataLen, BYTE *pbSignature, ULONG *pulSignLen);
typedef ULONG(WINAPI *PFN_SKF_RSAVerify)(DEVHANDLE hDev , RSAPUBLICKEYBLOB* pRSAPubKeyBlob, BYTE *pbData, ULONG  ulDataLen, BYTE *pbSignature, ULONG ulSignLen);
typedef ULONG(WINAPI *PFN_SKF_RSAExportSessionKey)(HCONTAINER hContainer, ULONG ulAlgId, RSAPUBLICKEYBLOB *pPubKey, BYTE *pbData, ULONG  *pulDataLen, HANDLE *phSessionKey);
typedef ULONG(WINAPI *PFN_SKF_GenECCKeyPair)(HCONTAINER hContainer, ULONG ulAlgId, ECCPUBLICKEYBLOB *pBlob);
typedef ULONG(WINAPI *PFN_SKF_ImportECCKeyPair)(HCONTAINER hContainer, PENVELOPEDKEYBLOB pEnvelopedKeyBlob);
typedef ULONG(WINAPI *PFN_SKF_ECCSignData)(HCONTAINER hContainer, BYTE *pbData, ULONG  ulDataLen, PECCSIGNATUREBLOB pSignature);
typedef ULONG(WINAPI *PFN_SKF_ECCVerify)(DEVHANDLE hDev , ECCPUBLICKEYBLOB* pECCPubKeyBlob, BYTE *pbData, ULONG  ulDataLen, PECCSIGNATUREBLOB pSignature);
typedef ULONG(WINAPI *PFN_SKF_ExtECCEncrypt)(DEVHANDLE hDev, ECCPUBLICKEYBLOB *pECCPubKeyBlob,BYTE* pbPlainText, ULONG ulPlainTextLen, PECCCIPHERBLOB pCipherText);
typedef ULONG(WINAPI *PFN_SKF_ExtECCSign)(DEVHANDLE hDev, ECCPRIVATEKEYBLOB*  pECCPriKeyBlob, BYTE* pbData, ULONG ulDataLen, PECCSIGNATUREBLOB pSignature);
typedef ULONG(WINAPI *PFN_SKF_ExtECCVerify)(DEVHANDLE hDev, ECCPUBLICKEYBLOB*  pECCPubKeyBlob,BYTE* pbData, ULONG ulDataLen, PECCSIGNATUREBLOB pSignature);
typedef ULONG(WINAPI *PFN_SKF_ECCExportSessionKey)(HCONTAINER hContainer, ULONG ulAlgId, ECCPUBLICKEYBLOB *pPubKey, PECCCIPHERBLOB pData, HANDLE *phSessionKey);
typedef ULONG(WINAPI *PFN_SKF_ExportPublicKey)(HCONTAINER hContainer, BOOL bSignFlag, BYTE* pbBlob, ULONG* pulBlobLen);
typedef ULONG(WINAPI *PFN_SKF_ImportSessionKey)(HCONTAINER hContainer, ULONG ulAlgId,BYTE *pbWrapedData,ULONG ulWrapedLen,HANDLE *phKey);
typedef ULONG(WINAPI *PFN_SKF_SetSymmKey)(DEVHANDLE hDev, BYTE* pbKey, ULONG ulAlgID, HANDLE* phKey);
typedef ULONG(WINAPI *PFN_SKF_EncryptInit)(HANDLE hKey, BLOCKCIPHERPARAM EncryptParam);
typedef ULONG(WINAPI *PFN_SKF_Encrypt)(HANDLE hKey, BYTE * pbData, ULONG ulDataLen, BYTE *pbEncryptedData, ULONG *pulEncryptedLen);
typedef ULONG(WINAPI *PFN_SKF_EncryptUpdate)(HANDLE hKey, BYTE * pbData, ULONG ulDataLen, BYTE *pbEncryptedData, ULONG *pulEncryptedLen);
typedef ULONG(WINAPI *PFN_SKF_EncryptFinal)(HANDLE hKey, BYTE *pbEncryptedData, ULONG *ulEncryptedDataLen );
typedef ULONG(WINAPI *PFN_SKF_DecryptInit)(HANDLE hKey, BLOCKCIPHERPARAM DecryptParam);
typedef ULONG(WINAPI *PFN_SKF_Decrypt)(HANDLE hKey, BYTE *pbEncryptedData, ULONG ulEncryptedLen, BYTE * pbData, ULONG * pulDataLen);
typedef ULONG(WINAPI *PFN_SKF_DecryptUpdate)(HANDLE hKey, BYTE *pbEncryptedData, ULONG ulEncryptedLen, BYTE * pbData, ULONG * pulDataLen);
typedef ULONG(WINAPI *PFN_SKF_DecryptFinal)(HANDLE hKey, BYTE *pbPlainText, ULONG *pulPlainTextLen);
typedef ULONG(WINAPI *PFN_SKF_DigestInit)(DEVHANDLE hDev, ULONG ulAlgID, ECCPUBLICKEYBLOB *pPubKey, unsigned char *pucID, ULONG ulIDLen, HANDLE *phHash);
typedef ULONG(WINAPI *PFN_SKF_Digest)(HANDLE hHash, BYTE *pbData, ULONG ulDataLen, BYTE *pbHashData, ULONG *pulHashLen);
typedef ULONG(WINAPI *PFN_SKF_DigestUpdate)(HANDLE hHash, BYTE *pbData, ULONG  ulDataLen);
typedef ULONG(WINAPI *PFN_SKF_DigestFinal)(HANDLE hHash, BYTE *pHashData, ULONG  *pulHashLen);
typedef ULONG(WINAPI *PFN_SKF_CloseHandle)(HANDLE hHandle);

typedef ULONG(WINAPI *PFN_SKF_CreateFile)(HAPPLICATION hApplication, LPSTR szFileName, ULONG ulFileSize, ULONG ulReadRights, ULONG ulWriteRights);
typedef ULONG(WINAPI *PFN_SKF_DeleteFile)(HAPPLICATION hApplication, LPSTR szFileName);
typedef ULONG(WINAPI *PFN_SKF_EnumFiles)(HAPPLICATION hApplication, LPSTR szFileList, ULONG *pulSize);
typedef ULONG(WINAPI *PFN_SKF_GetFileInfo)(HAPPLICATION hApplication, LPSTR szFileName, FILEATTRIBUTE *pFileInfo);
typedef ULONG(WINAPI *PFN_SKF_ReadFile)(HAPPLICATION hApplication, LPSTR szFileName, ULONG ulOffset, ULONG ulSize, BYTE * pbOutData, ULONG *pulOutLen);
typedef ULONG(WINAPI *PFN_SKF_WriteFile)(HAPPLICATION hApplication, LPSTR szFileName, ULONG  ulOffset, BYTE *pbData, ULONG ulSize);
typedef ULONG(WINAPI *PFN_SKF_DevAuth)(DEVHANDLE hDev, BYTE *pbAuthData,ULONG ulLen);
typedef ULONG(WINAPI *PFN_SKF_CheckLicense)(BYTE * pcAppId);

typedef ULONG(WINAPI *PFN_EPS_ImportSymmKey)(CONST HANDLE hContainer, ULONG ulKeyIndex, CONST BYTE* pbEncData,ULONG ulEncDataLen, ULONG ulFlags);
typedef ULONG(WINAPI *PFN_EPS_WriteESealData)(CONST HANDLE hApplication, CONST BYTE* pbData,ULONG ulDataSize, ULONG ulFlags);
typedef ULONG(WINAPI *PFN_EPS_ReadESealData)(CONST HANDLE hApplication, ULONG ulKeyIndex, ULONG ulKeyAlgId,BYTE* pbData, ULONG* ulDataSize, ULONG ulFlags);
typedef ULONG(WINAPI *PFN_EPS_Encrypt)(CONST HANDLE hApplication, ULONG ulKeyIndex, ULONG ulAlgId,
                                   CONST BYTE* pbIVData, ULONG ulIVLen, ULONG DivCount, CONST BYTE* pbDivComponent,
                                         ULONG ulDivComponentLen, CONST BYTE* pbInputData, ULONG ulInputLen,
                                         BYTE* pbOutputData, ULONG* pulOutputDataLen, ULONG ulFlags);
typedef ULONG(WINAPI *PFN_EPS_Decrypt)(CONST HANDLE hApplication, ULONG ulKeyIndex, ULONG ulAlgId,
                                   CONST BYTE* pbIVData, ULONG ulIVLen, ULONG DivCount, CONST BYTE* pbDivComponent,
                                         ULONG ulDivComponentLen, CONST BYTE* pbInputData, ULONG ulInputLen,
                                         BYTE* pbOutputData, ULONG* pulOutputDataLen, ULONG ulFlags);
typedef ULONG(WINAPI *PFN_EPS_Mac)(CONST HANDLE hApplication, ULONG ulKeyIndex, ULONG ulAlgId,
                               CONST BYTE* pbIVData, ULONG ulIVLen, ULONG DivCount, CONST BYTE* pbDivComponent,
                                     ULONG ulDivComponentLen, CONST BYTE* pbInputData, ULONG ulInputLen,
                                     BYTE* pbOutputData, ULONG* pulOutputDataLen, ULONG ulFlags);
class typeDefApi{
public:
    typeDefApi(QString);
    ~typeDefApi();
public:
    PFN_SKF_WaitForDevEvent SKF_WaitForDevEvent;
    PFN_SKF_GetDevState SKF_GetDevState;
    PFN_SKF_FormatDevice SKF_FormatDevice;
    PFN_SKF_EnumDev SKF_EnumDev;
    PFN_SKF_ConnectDev SKF_ConnectDev;
    PFN_SKF_UnblockPIN SKF_UnblockPIN;
    PFN_SKF_DisConnectDev SKF_DisConnectDev;
    PFN_SKF_GetDevInfo SKF_GetDevInfo;

    PFN_SKF_EnumApplication SKF_EnumApplication;
    PFN_SKF_CreateApplication SKF_CreateApplication;
    PFN_SKF_DeleteApplication SKF_DeleteApplication;
    PFN_SKF_OpenApplication SKF_OpenApplication;
    PFN_SKF_CloseApplication SKF_CloseApplication;

    PFN_SKF_GetPINInfo SKF_GetPINInfo;
    PFN_SKF_VerifyPIN SKF_VerifyPIN;
    PFN_SKF_ChangePIN SKF_ChangePIN;

    PFN_SKF_CreateContainer SKF_CreateContainer;
    PFN_SKF_DeleteContainer SKF_DeleteContainer;
    PFN_SKF_OpenContainer SKF_OpenContainer;
    PFN_SKF_CloseContainer SKF_CloseContainer;
    PFN_SKF_EnumContainer SKF_EnumContainer;
    PFN_SKF_GetContainerType SKF_GetContainerType;
    PFN_SKF_ImportCertificate SKF_ImportCertificate;
    PFN_SKF_ExportCertificate SKF_ExportCertificate;

    PFN_SKF_GenRandom SKF_GenRandom;
    PFN_SKF_GenRSAKeyPair SKF_GenRSAKeyPair;
    PFN_SKF_ImportRSAKeyPair SKF_ImportRSAKeyPair;
    PFN_SKF_RSASignData SKF_RSASignData;
    PFN_SKF_RSAVerify SKF_RSAVerify;
    PFN_SKF_RSAExportSessionKey SKF_RSAExportSessionKey;
    PFN_SKF_GenECCKeyPair SKF_GenECCKeyPair;
    PFN_SKF_ImportECCKeyPair SKF_ImportECCKeyPair;
    PFN_SKF_ECCSignData SKF_ECCSignData;
    PFN_SKF_ECCVerify SKF_ECCVerify;
    PFN_SKF_ECCExportSessionKey SKF_ECCExportSessionKey;
    PFN_SKF_ExtECCEncrypt SKF_ExtECCEncrypt;
    PFN_SKF_ExtECCSign SKF_ExtECCSign;
    PFN_SKF_ExtECCVerify SKF_ExtECCVerify;

    PFN_SKF_ExportPublicKey SKF_ExportPublicKey;
    PFN_SKF_ImportSessionKey SKF_ImportSessionKey;
    PFN_SKF_SetSymmKey SKF_SetSymmKey;
    PFN_SKF_EncryptInit SKF_EncryptInit;
    PFN_SKF_Encrypt SKF_Encrypt;
    PFN_SKF_EncryptUpdate SKF_EncryptUpdate;
    PFN_SKF_EncryptFinal SKF_EncryptFinal;
    PFN_SKF_DecryptInit SKF_DecryptInit;
    PFN_SKF_Decrypt SKF_Decrypt;
    PFN_SKF_DecryptUpdate SKF_DecryptUpdate;
    PFN_SKF_DecryptFinal SKF_DecryptFinal;
    PFN_SKF_DigestInit SKF_DigestInit;
    PFN_SKF_Digest SKF_Digest;
    PFN_SKF_DigestUpdate SKF_DigestUpdate;
    PFN_SKF_DigestFinal SKF_DigestFinal;
    PFN_SKF_CloseHandle SKF_CloseHandle;


    PFN_SKF_CreateFile SKF_CreateFile;
    PFN_SKF_DeleteFile SKF_DeleteFile;
    PFN_SKF_EnumFiles SKF_EnumFiles;
    PFN_SKF_GetFileInfo SKF_GetFileInfo;
    PFN_SKF_ReadFile SKF_ReadFile;
    PFN_SKF_WriteFile SKF_WriteFile;

    PFN_SKF_DevAuth SKF_DevAuth;

    PFN_EPS_ImportSymmKey EPS_ImportSymmKey;
    PFN_EPS_WriteESealData EPS_WriteESealData;
    PFN_EPS_ReadESealData EPS_ReadESealData;
    PFN_EPS_Encrypt EPS_Encrypt;
    PFN_EPS_Decrypt EPS_Decrypt;
    PFN_EPS_Mac EPS_Mac;
};
#endif // TYPEDEFINE_H
