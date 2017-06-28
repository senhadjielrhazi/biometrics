/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWTypeDef_Dsp.h 											 //
//																			 //
//	Contents:																 //
//																			 //
//	Classes:																 //
//																			 //
//	Functions:																 //
//																			 //
//	History:	01-01-2003	 O. Senhadji El Rhazi   Created					 //
//				01-07-2003	 O. Senhadji El Rhazi   1 ere Release			     //
///////////////////////////////////////////////////////////////////////////////
//																			 //
//	Secure Workstation Suite Product										 //
//	SAGEM SA Data Service Provider Module									 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#ifndef SWTYPEDEF_DSP_H
#define SWTYPEDEF_DSP_H

typedef struct{
	TSWState			m_T_SWState;
	BOOL				m_b_LogonIdent;
	BOOL				m_b_AccessIdent;
	BOOL				m_b_DataIdent;
	BOOL				m_b_AdminIdent;
	BOOL				m_b_AdminEnroll;
	TModuleRet			m_T_ResultLogonId;
	TModuleRet			m_T_ResultAccessId;
	TModuleRet			m_T_ResultDataId;
	TModuleRet			m_T_ResultAdminEn;
	TModuleRet			m_T_ResultAdminId;
	TModuleRet			m_T_ResultAccessUp;
	TModuleRet			m_T_ResultAdminUp;
	TModuleRet			m_T_ResultAdminUser;
	INT 				m_i_DataCreateOrNo;
	BOOL				m_b_LockSW;
	TAllDataOut 		m_T_MsoData;
	TSupDataOut 		m_T_PcData; 
	TUpDataOut			m_T_UpdateData;
	BOOL				m_b_EraseDel;
	UCHAR				m_puc_UserID[VI_USERID_MAX*sizeof(WCHAR)];
} TSharedMemory, *PTSharedMemory;

typedef struct{
	HANDLE				m_h_AdminUser;
	HANDLE				m_h_SWOn;
	HANDLE				m_h_SWOff;
	HANDLE				m_h_WaitAdminUser;
	HANDLE				m_h_AdminDb;
	HANDLE				m_h_WaitAdminDb;
	HANDLE				m_h_WaitOn;
	HANDLE				m_h_WaitOff;
	HANDLE				m_h_WaitPaint;
	HANDLE				m_h_WaitUpdateAccess;
	HANDLE				m_h_WaitUpdateAdmin;
	HANDLE				m_h_WaitCancel;
	HANDLE				m_h_LogonIdent;
	HANDLE				m_h_AccessIdent;
	HANDLE				m_h_AccessUpdate;
	HANDLE				m_h_AdminUpdate;
	HANDLE				m_h_DataIdent;
	HANDLE				m_h_AdminIdent;
	HANDLE				m_h_AdminEnroll;
	HANDLE				m_h_WaitIdent;
	HANDLE				m_h_WaitEnroll;
	HANDLE				m_h_ExistSW;
	HANDLE				m_h_HostExitEvent;
	HANDLE				m_h_HostExitEventKo;
	BOOL				m_b_RebootOk;
} TLocalMemory, *PTLocalMemory;

#endif//SWTYPEDEF_DSP_H
