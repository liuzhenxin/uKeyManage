#include <typedefine.h>
typeDefApi::typeDefApi(QString DLLNAME)
{
    QLibrary SKFAPI(/*"SKFAPI20509.dll"*/DLLNAME);
//    QLibrary SKFAPI("mtoken_gm3000");
    SKFAPI.load();
    SKF_WaitForDevEvent=(PFN_SKF_WaitForDevEvent)SKFAPI.resolve("SKF_WaitForDevEvent");
    SKF_FormatDevice=(PFN_SKF_FormatDevice)SKFAPI.resolve("SKF_FormatDevice");
    SKF_EnumDev=(PFN_SKF_EnumDev)SKFAPI.resolve("SKF_EnumDev");
    SKF_GetDevState=(PFN_SKF_GetDevState)SKFAPI.resolve("SKF_GetDevState");
    SKF_ConnectDev=(PFN_SKF_ConnectDev)SKFAPI.resolve("SKF_ConnectDev");
    SKF_UnblockPIN=(PFN_SKF_UnblockPIN)SKFAPI.resolve("SKF_UnblockPIN");
    SKF_DisConnectDev = (PFN_SKF_DisConnectDev)SKFAPI.resolve("SKF_DisConnectDev");
    SKF_GetDevInfo = (PFN_SKF_GetDevInfo)SKFAPI.resolve("SKF_GetDevInfo");

    SKF_EnumApplication = (PFN_SKF_EnumApplication)SKFAPI.resolve("SKF_EnumApplication");
    SKF_CreateApplication = (PFN_SKF_CreateApplication)SKFAPI.resolve("SKF_CreateApplication");
    SKF_DeleteApplication = (PFN_SKF_DeleteApplication)SKFAPI.resolve("SKF_DeleteApplication");
    SKF_OpenApplication = (PFN_SKF_OpenApplication)SKFAPI.resolve("SKF_OpenApplication");
    SKF_CloseApplication = (PFN_SKF_CloseApplication)SKFAPI.resolve("SKF_CloseApplication");
    SKF_GetPINInfo = (PFN_SKF_GetPINInfo)SKFAPI.resolve("SKF_GetPINInfo");
    SKF_VerifyPIN = (PFN_SKF_VerifyPIN)SKFAPI.resolve("SKF_VerifyPIN");
    SKF_ChangePIN = (PFN_SKF_ChangePIN)SKFAPI.resolve("SKF_ChangePIN");

    SKF_CreateContainer = (PFN_SKF_CreateContainer)SKFAPI.resolve("SKF_CreateContainer");
    SKF_DeleteContainer = (PFN_SKF_DeleteContainer)SKFAPI.resolve("SKF_DeleteContainer");
    SKF_OpenContainer = (PFN_SKF_OpenContainer)SKFAPI.resolve("SKF_OpenContainer");
    SKF_CloseContainer = (PFN_SKF_CloseContainer)SKFAPI.resolve("SKF_CloseContainer");
    SKF_EnumContainer = (PFN_SKF_EnumContainer)SKFAPI.resolve("SKF_EnumContainer");
    SKF_GetContainerType = (PFN_SKF_GetContainerType)SKFAPI.resolve("SKF_GetContainerType");
    SKF_ImportCertificate = (PFN_SKF_ImportCertificate)SKFAPI.resolve("SKF_ImportCertificate");
    SKF_ExportCertificate = (PFN_SKF_ExportCertificate)SKFAPI.resolve("SKF_ExportCertificate");
    SKF_GenRandom = (PFN_SKF_GenRandom)SKFAPI.resolve("SKF_GenRandom");
    SKF_GenRSAKeyPair = (PFN_SKF_GenRSAKeyPair)SKFAPI.resolve("SKF_GenRSAKeyPair");
    SKF_ImportRSAKeyPair = (PFN_SKF_ImportRSAKeyPair)SKFAPI.resolve("SKF_ImportRSAKeyPair");
    SKF_RSASignData = (PFN_SKF_RSASignData)SKFAPI.resolve("SKF_RSASignData");
    SKF_RSAVerify = (PFN_SKF_RSAVerify)SKFAPI.resolve("SKF_RSAVerify");
    SKF_RSAExportSessionKey = (PFN_SKF_RSAExportSessionKey)SKFAPI.resolve("SKF_RSAExportSessionKey");
    SKF_GenECCKeyPair = (PFN_SKF_GenECCKeyPair)SKFAPI.resolve("SKF_GenECCKeyPair");
    SKF_ImportECCKeyPair = (PFN_SKF_ImportECCKeyPair)SKFAPI.resolve("SKF_ImportECCKeyPair");
    SKF_ECCSignData = (PFN_SKF_ECCSignData)SKFAPI.resolve("SKF_ECCSignData");
    SKF_ECCVerify = (PFN_SKF_ECCVerify)SKFAPI.resolve("SKF_ECCVerify");
    SKF_ECCExportSessionKey = (PFN_SKF_ECCExportSessionKey)SKFAPI.resolve("SKF_ECCExportSessionKey");
    SKF_ExtECCEncrypt = (PFN_SKF_ExtECCEncrypt)SKFAPI.resolve("SKF_ExtECCEncrypt");
    SKF_ExtECCSign = (PFN_SKF_ExtECCSign)SKFAPI.resolve("SKF_ExtECCSign");
    SKF_ExtECCVerify = (PFN_SKF_ExtECCVerify)SKFAPI.resolve("SKF_ExtECCVerify");

    SKF_ExportPublicKey = (PFN_SKF_ExportPublicKey)SKFAPI.resolve("SKF_ExportPublicKey");
    SKF_ImportSessionKey = (PFN_SKF_ImportSessionKey)SKFAPI.resolve("SKF_ImportSessionKey");
    SKF_SetSymmKey = (PFN_SKF_SetSymmKey)SKFAPI.resolve("SKF_SetSymmKey");
    SKF_EncryptInit = (PFN_SKF_EncryptInit)SKFAPI.resolve("SKF_EncryptInit");
    SKF_Encrypt = (PFN_SKF_Encrypt)SKFAPI.resolve("SKF_Encrypt");
    SKF_EncryptUpdate = (PFN_SKF_EncryptUpdate)SKFAPI.resolve("SKF_EncryptUpdate");
    SKF_EncryptFinal = (PFN_SKF_EncryptFinal)SKFAPI.resolve("SKF_EncryptFinal");
    SKF_DecryptInit = (PFN_SKF_DecryptInit)SKFAPI.resolve("SKF_DecryptInit");
    SKF_Decrypt = (PFN_SKF_Decrypt)SKFAPI.resolve("SKF_Decrypt");
    SKF_DecryptUpdate = (PFN_SKF_DecryptUpdate)SKFAPI.resolve("SKF_DecryptUpdate");
    SKF_DecryptFinal = (PFN_SKF_DecryptFinal)SKFAPI.resolve("SKF_DecryptFinal");
    SKF_DigestInit = (PFN_SKF_DigestInit)SKFAPI.resolve("SKF_DigestInit");
    SKF_Digest = (PFN_SKF_Digest)SKFAPI.resolve("SKF_Digest");
    SKF_DigestUpdate = (PFN_SKF_DigestUpdate)SKFAPI.resolve("SKF_DigestUpdate");
    SKF_DigestFinal = (PFN_SKF_DigestFinal)SKFAPI.resolve("SKF_DigestFinal");
    SKF_CloseHandle = (PFN_SKF_CloseHandle)SKFAPI.resolve("SKF_CloseHandle");
    SKF_DevAuth = (PFN_SKF_DevAuth)SKFAPI.resolve("SKF_DevAuth");


    //文件管理
    SKF_CreateFile = (PFN_SKF_CreateFile)SKFAPI.resolve("SKF_CreateFile");
    SKF_DeleteFile = (PFN_SKF_DeleteFile)SKFAPI.resolve("SKF_DeleteFile");
    SKF_EnumFiles = (PFN_SKF_EnumFiles)SKFAPI.resolve("SKF_EnumFiles");
    SKF_GetFileInfo = (PFN_SKF_GetFileInfo)SKFAPI.resolve("SKF_GetFileInfo");
    SKF_ReadFile = (PFN_SKF_ReadFile)SKFAPI.resolve("SKF_ReadFile");
    SKF_WriteFile = (PFN_SKF_WriteFile)SKFAPI.resolve("SKF_WriteFile");

    if(DLLNAME != "HNCA3000GM.dll" && DLLNAME != "SMSKF.dll")
    {
        EPS_ImportSymmKey = (PFN_EPS_ImportSymmKey)SKFAPI.resolve("EPS_ImportSymmKey");
        EPS_WriteESealData = (PFN_EPS_WriteESealData)SKFAPI.resolve("EPS_WriteESealData");
        EPS_ReadESealData = (PFN_EPS_ReadESealData)SKFAPI.resolve("EPS_ReadESealData");
        EPS_Encrypt = (PFN_EPS_Encrypt)SKFAPI.resolve("EPS_Encrypt");
        EPS_Decrypt = (PFN_EPS_Decrypt)SKFAPI.resolve("EPS_Decrypt");
        EPS_Mac = (PFN_EPS_Mac)SKFAPI.resolve("EPS_Mac");
    }
}
typeDefApi::~typeDefApi()
{
    //
}
