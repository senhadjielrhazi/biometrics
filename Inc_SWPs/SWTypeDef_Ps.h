/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003. 									 //
//																			 //
//	File:		SWTypeDef_Ps.h												 //
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
//	SAGEM SA Suite Product Type Definition									 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#ifndef SWTYPEDEF_PS_H
#define SWTYPEDEF_PS_H

#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS                  ((NTSTATUS)0x00000000L)
#define STATUS_MORE_ENTRIES             ((NTSTATUS)0x00000105L)
#define STATUS_NO_MORE_ENTRIES          ((NTSTATUS)0x8000001AL)
#endif

//Terminal Com State.
typedef enum { 
	MSO_COM_OK								= 1,
	MSO_COM_ERR								= 2
} TComState;

//Terminal Database State.
typedef enum { 
	MSO_DB_OK								= 1,
	MSO_DB_INVALIDE							= 2,
	MSO_DB_NOBASE							= 3,
	MSO_DB_ERR								= 4,
	MSO_DB_FULL								= 5,
	MSO_DB_EMPTY							= 6
} TDbState;

typedef struct
{
	TComState	m_T_ComState;
	TDbState	m_T_DbState;
} TSWState,*PTSWState;

typedef enum { 
	SW_OKHIT_MD								= 1,
	SW_NOHIT_MD								= 2,
	SW_ABORT_MD								= 3,
	SW_ERRSTG_MD							= 4,
	SW_ERRACT_MD							= 5
} TModuleRet;

typedef struct
{
	WCHAR				m_pwc_UserId[VI_USERID_MAX];
	WCHAR				m_pwc_UserKey[VI_DBFIELD_MAX];
	WCHAR				m_pwc_UserLogon[VI_DBFIELD_MAX];
} TSpeDataOut, *PTSpeDataOut;

typedef struct
{
	WCHAR				m_pwc_UserId[VI_USERID_MAX];
	WCHAR				m_pwc_UserKey[VI_DBFIELD_MAX];
	WCHAR				m_pwc_UserLogon[VI_DBFIELD_MAX];
	WCHAR				m_pwc_UserBase[VI_NBAPPLI_MAX][VI_DBFIELD_MAX];
} TAllDataOut, *PTAllDataOut;

typedef struct
{
	INT					m_i_FieldIndex;
	WCHAR				m_pwc_UserId[VI_USERID_MAX];
	WCHAR				m_pwc_Field[VI_DBFIELD_MAX];
} TUpDataOut, *PTUpDataOut;

typedef struct
{
	WCHAR				m_pwc_UserKey[VI_DBFIELD_MAX];
	WCHAR				m_pwc_UserLogon[VI_DBFIELD_MAX];
	WCHAR				m_pwc_Field[VI_DBFIELD_MAX];
	HWND				m_h_hwndImage_1;
	HWND				m_h_hwndImage_2;
	HWND				m_h_hwndImage_3;
	HWND				m_h_hwndImage_4;
	HWND				m_h_hwndText_1;
	HWND				m_h_hwndText_2;
	INT					m_i_CurrentImage;
} TSupDataOut, *PTSupDataOut;

//fields
typedef struct
{
	WCHAR m_pwc_UserKeyBase[VI_BASEKEY_MAX];
	WCHAR m_pwc_UserKeyData[VI_DATAKEY_MAX];
} TKeyField, *PTKeyField;

typedef struct
{
	WCHAR m_pwc_UserLogin[VI_USERLOGON_MAX];
	WCHAR m_pwc_UserPassW[VI_USERPASSW_MAX];
	WCHAR m_pwc_UserDomain[VI_USERDOMAIN_MAX];
} TLogonField, *PTLogonField;

typedef struct
{
	INT	  m_i_AppOption;//0:nothing,1:hide,2:enter,3:hide&enter
	WCHAR m_pwc_AppClassN[VI_APPCLASS_MAX];
	WCHAR m_pwc_AppClassNP[VI_APPCLASSP_MAX];
	WCHAR m_pwc_AppTitleB[VI_APPTITLE_MAX];
	WCHAR m_pwc_AppName[VI_APPNAME_MAX];
	WCHAR m_pwc_AppPassW[VI_APPPASSW_MAX];
} TAccessField, *PTAccessField;

#endif//SWTYPEDEF_PS_H