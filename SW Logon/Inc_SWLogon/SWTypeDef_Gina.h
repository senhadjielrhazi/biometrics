/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003. 									 //
//																			 //
//	File:		SWTypeDef_Gina.h											 //
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
//	SAGEM SA Logon Module													 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#ifndef SWTYPEDEF_GINA_H
#define SWTYPEDEF_GINA_H

typedef struct _Globals {
	PWLX_DISPATCH_VERSION_1_0	m_p_WlxFuncs;
	HINSTANCE					m_h_DllInstance;
	HANDLE						m_h_GlobalWlx;
	HANDLE						m_h_LogonMutex;
	TLogonField					m_T_LogonData;
	WCHAR						m_pwc_UserPassW[VI_USERPASSW_MAX];
    HANDLE						m_h_UserToken;
	DWORD						m_dw_Options;
	WCHAR						m_pwc_Title[256];
	WCHAR						m_pwc_Message[256];
	HWND						m_h_HwndDlgMsg;
	HWND						m_h_HwndDlgLog;
	SYSTEMTIME					m_T_LogonTime;
	C_Registry					m_x_Registry;
	HFONT						m_h_Font_1;
	HFONT						m_h_Font_2;
	INT							m_i_Progress;
	TModuleRet					m_T_Result;
	INT							m_i_UserTypeLogon;
	BOOL						m_b_ScreenSaver;
} Globals, * PGlobals;

//_MiniMemory
typedef struct {
	HINSTANCE					m_h_DllInstance;
	TSWState					m_T_SWState;
	BOOL						m_b_Progress;
} MiniMemory, *PMiniMemory;

#endif//SWTYPEDEF_GINA_H
