/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWAccess.h													 //
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
//	SAGEM SA Access Module													 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#ifndef C_ACCESS_H
#define C_ACCESS_H

UINT C_Access_Task( LPVOID pParam );

class C_Access : public CWinApp
{
public:
	C_Access();
	~C_Access();
	
	UINT C_Access_Thread();
	VOID C_Access_CipherToUser(TAllDataOut i_in_Data);
	VOID C_Access_ProcessShow();
	VOID C_Access_ProcessUser(BOOL i_b_HitNoHit);
	
	HANDLE					m_h_ExitOk;
	HANDLE					m_h_ExitKo;
	HANDLE					m_h_Start;
	HANDLE					m_h_Stop;
	HANDLE					m_h_Admin;
	HANDLE					m_h_Mutex;
	INT 					m_i_TimeOut;
	BOOL					m_b_ShowErr;
	C_Notify				*m_Notify;
	
	BOOL					m_b_SetGetState;
	
	HANDLE					m_h_AccessExit;
	HANDLE					m_h_AccessStop;
	HANDLE					m_h_AccessStart;
	
	C_Wnd					*m_Wnd;
	C_Info					*m_Info;
	C_Profil				*m_Profil;
	C_AccessWizard			*m_AccessWizard;
	
	//Data User
	TKeyField				m_T_Keys;
	TLogonField 			m_T_Logon;
	TAccessField			m_T_Access[VI_NBAPPLI_MAX];
	WCHAR					m_pwc_UserId[VI_USERID_MAX];
	
	//{{AFX_VIRTUAL(C_Access)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	
	//{{AFX_MSG(C_Access)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif//C_Access_H