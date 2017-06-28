/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		C_Access.cpp												 //
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




#include "stdafx.h"

C_Access theApp;

BEGIN_MESSAGE_MAP(C_Access, CWinApp)
//{{AFX_MSG_MAP(C_Access)
//}}AFX_MSG
ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

C_Access::C_Access
(
 )
{
	m_i_TimeOut = 100;
	m_b_ShowErr = TRUE;
}

C_Access::~C_Access
(
 )
{
}

VOID C_Access::C_Access_CipherToUser
(
 TAllDataOut i_T_Data
 )
{
	C_Crypto_AES	l_x_oRijndael;
	UCHAR			*l_puc_Key			= NULL; 
	UCHAR			*l_puc_szDataOut	= NULL;
	UCHAR			*l_puc_szDataIn 	= NULL;
	INT 			l_i_size_out		= 0;
	INT 			l_i_size_in 		= 0;
	
	__try
	{
		//Get User ID
		memset(m_pwc_UserId,0,sizeof(m_pwc_UserId));
		memcpy(m_pwc_UserId,i_T_Data.m_pwc_UserId,sizeof(m_pwc_UserId));
		
		//Get CryptoKeys
		memset(&m_T_Keys,0,sizeof(TKeyField));
		memcpy(&m_T_Keys,i_T_Data.m_pwc_UserKey,sizeof(TKeyField));
		
		l_puc_Key =(UCHAR *)malloc(VI_BASEKEY_MAX*sizeof(WCHAR));
		memset(l_puc_Key,0,VI_BASEKEY_MAX*sizeof(WCHAR));
		memcpy(l_puc_Key,m_T_Keys.m_pwc_UserKeyBase,VI_BASEKEY_MAX*sizeof(WCHAR));
		
		l_x_oRijndael.C_Crypto_MakeKey(l_puc_Key,C_Crypto_AES::Key32Bytes);
		
		//Get Logon Fields
		l_i_size_in 	= sizeof(i_T_Data.m_pwc_UserLogon);
		l_i_size_out	= l_x_oRijndael.C_Crypto_Length(l_i_size_in);
		
		l_puc_szDataIn	= (UCHAR *)malloc(l_i_size_in+1);
		l_puc_szDataOut = (UCHAR *)malloc(l_i_size_out+1);
		
		memset(l_puc_szDataIn,0,l_i_size_in+1);
		memset(l_puc_szDataOut,0,l_i_size_out+1);
		memcpy(l_puc_szDataIn,i_T_Data.m_pwc_UserLogon,sizeof(i_T_Data.m_pwc_UserLogon));
		
		l_x_oRijndael.C_Crypto_Decrypt(l_puc_szDataIn,l_i_size_in,l_puc_szDataOut);
		
		memset(&m_T_Logon,0,sizeof(m_T_Logon));
		memcpy(&m_T_Logon,l_puc_szDataOut,sizeof(m_T_Logon));
		
		free(l_puc_szDataOut);
		free(l_puc_szDataIn);
		
		//Get App Fields
		for(INT i = 0; i<VI_NBAPPLI_MAX;i++)
		{
			l_i_size_in 	= sizeof(i_T_Data.m_pwc_UserBase[i]);
			l_i_size_out	= l_x_oRijndael.C_Crypto_Length(l_i_size_in);
			
			l_puc_szDataIn	= (UCHAR *)malloc(l_i_size_in+1);
			l_puc_szDataOut = (UCHAR *)malloc(l_i_size_out+1);
			
			memset(l_puc_szDataIn,0,l_i_size_in+1);
			memset(l_puc_szDataOut,0,l_i_size_out+1);
			
			memcpy(l_puc_szDataIn,i_T_Data.m_pwc_UserBase[i],sizeof(i_T_Data.m_pwc_UserBase[i]));
			
			l_x_oRijndael.C_Crypto_Decrypt(l_puc_szDataIn,l_i_size_in,l_puc_szDataOut);
			
			memset(&m_T_Access[i],0,sizeof(m_T_Access[i]));
			memcpy(&m_T_Access[i],l_puc_szDataOut,sizeof(m_T_Access[i]));
			free(l_puc_szDataOut);
			free(l_puc_szDataIn);
		}
		
		free(l_puc_Key);
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

VOID C_Access::C_Access_ProcessUser
(
 BOOL i_b_HitNoHit
 )
{
	TActiveWndData	l_T_ActiveWndData				= {0};
	TActiveWndData	l_T_ActiveWndNull 				= {NULL};
	INT 			l_i_NbAppEqual					= 0;
	INT 			l_pi_AppEqual[VI_NBAPPLI_MAX]	= {0};
	INT 			l_i_Response					= 0;
	
	__try
	{
		m_Info->m_b_HitNoHit = i_b_HitNoHit;
		
		if(!i_b_HitNoHit)
			m_Info->DoModal();
		else
		{
			m_Wnd->C_Wnd_GetActiveWnd(l_T_ActiveWndData);
			memset(l_pi_AppEqual,0,sizeof(l_pi_AppEqual));
			
			memset(&l_T_ActiveWndNull,0,sizeof(l_T_ActiveWndNull));
			if(memcmp(&l_T_ActiveWndData,&l_T_ActiveWndNull,sizeof(l_T_ActiveWndNull)) == 0)
			{
				m_Info->m_c_Info_UserName.Format(L"%s",m_T_Logon.m_pwc_UserLogin);
				m_Info->DoModal();
				return;
			}



			for(INT i = 0; i<VI_NBAPPLI_MAX;i++)
			{
				if(m_Wnd->C_Wnd_IsWndEqual(l_T_ActiveWndData,m_T_Access[i]))
				{
					l_pi_AppEqual[i] = 1;
					l_i_NbAppEqual++;
				}
			}
			if(l_i_NbAppEqual == 0)
			{
				m_Info->m_c_Info_UserName.Format(L"%s",m_T_Logon.m_pwc_UserLogin);
				m_Info->DoModal();
			}
			else if(l_i_NbAppEqual == 1)
			{
				for(INT j = 0; j<VI_NBAPPLI_MAX;j++)
				{
					if(l_pi_AppEqual[j] == 1)
					{
						m_Wnd->C_Wnd_SetWndData(m_T_Access[j]);
						break;
					}
				}
				if(m_Wnd->C_Wnd_IsBrowser(m_Wnd->m_h_hwndToSet))
				{
					for(INT k = 0; k<VI_NBAPPLI_MAX;k++)
					{
						if(m_Wnd->C_Wnd_IsWndInHtml(l_T_ActiveWndData,m_T_Access[k]))
						{
							m_Wnd->C_Wnd_SetWndDataInHtml(m_T_Access[k]);
						}
					}
				}
			}
			else
			{
				*(&(m_Profil->m_pi_AppEqual)) = l_pi_AppEqual;
				m_Profil->m_i_NbAppEqual	  = l_i_NbAppEqual;
				*(&(m_Profil->m_T_Access))	  = m_T_Access;
				
				l_i_Response = m_Profil->DoModal();
				if(l_i_Response == IDOK)
				{
					if(0 <= m_Profil->m_i_Index && m_Profil->m_i_Index < VI_NBAPPLI_MAX)
						m_Wnd->C_Wnd_SetWndData(m_T_Access[m_Profil->m_i_Index]);
				}
			}
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

VOID C_Access::C_Access_ProcessShow
(
 VOID
 )
{
	HPEN			l_cp_WndPen 	= NULL; 
	CClientDC		l_dc_DeskDc 	= NULL;
	CWnd			*l_h_CWndDesk	= l_dc_DeskDc.GetWindow();
	INT 			i				= 0;
	INT 			x				= 0;
	INT 			y				= 0;
	INT 			z				= 0;
	HGDIOBJ 		l_hp_PrevPen	= NULL;
	HGDIOBJ 		l_hb_PrevBrush	= NULL;
	
	m_b_SetGetState = (::GetKeyState(VK_CONTROL) < 0);
	
	l_cp_WndPen 	= ::CreatePen(PS_SOLID, 1,RGB(100,100,254));	
	l_hp_PrevPen	= l_dc_DeskDc.SelectObject(l_cp_WndPen);
	l_hb_PrevBrush	= l_dc_DeskDc.SelectObject(::GetStockObject(HOLLOW_BRUSH));
	x				= ::GetSystemMetrics(SM_CXFULLSCREEN)/2;
	y				= ::GetSystemMetrics(SM_CYFULLSCREEN)/2;
	z				= (x<y?x:y)*2/3;
	
	for(i = 1;i<10;i++)
	{	
		l_dc_DeskDc.Ellipse(x - i*z/10, 
			y - i*z/10,x + i*z/10, y + i*z/10);
	}
	l_h_CWndDesk->UpdateData(TRUE);
	l_h_CWndDesk->RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ALLCHILDREN);
	
	for(i = 10;i>1;i--)
	{	
		l_dc_DeskDc.Ellipse(x - i*z/10, 
			y - i*z/10,x + i*z/10, y + i*z/10);
	}
	l_h_CWndDesk->UpdateData(TRUE);
	l_h_CWndDesk->RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ALLCHILDREN);
	
	l_dc_DeskDc.SelectObject(l_hp_PrevPen);
	l_dc_DeskDc.SelectObject(l_hb_PrevBrush);
}

UINT C_Access::C_Access_Thread
(
 VOID
 )
{	
	TModuleRet	l_T_Ret;
	TAllDataOut l_T_Data			= {NULL};
	DWORD		l_dw_EventRet		= -1;
	HANDLE		l_ph_LoopEvents[4]	= {NULL};
	TSWState	o_T_SWState;
	
	__try
	{
		l_ph_LoopEvents[0] = m_h_AccessExit;
		l_ph_LoopEvents[1] = m_h_AccessStop;
		l_ph_LoopEvents[2] = m_h_AccessStart;
		
		do
		{	
			l_dw_EventRet = WaitForMultipleObjects(3,l_ph_LoopEvents,FALSE,INFINITE);
			switch(l_dw_EventRet)
			{
			case WAIT_OBJECT_0:
				{
					SetEvent(m_h_ExitKo);
					continue;
				}
			case WAIT_OBJECT_0+1:
				{
					ResetEvent(m_h_AccessStart);
					continue;
				}
			case WAIT_OBJECT_0+2:
				{
					SetEvent(m_h_AccessStart);
					if(WlxIsSWValid())
					{
						m_Notify->m_T_WndData.m_b_UpdateOn = 0;
						SetWindowLong(m_Notify->m_h_hwnd,GWL_USERDATA,(LONG)&m_Notify->m_T_WndData);
						m_b_ShowErr = TRUE;
						m_Notify->SetState(TRUE,FALSE,FALSE);
					}
					else
					{
						if(WlxIsSWLock())
						{
							Sleep(m_i_TimeOut);
							continue;
						}
						else
							WlxSWReboot(o_T_SWState);
					}
					if(WlxIsSWValid())
					{
						m_Notify->m_T_WndData.m_b_UpdateOn = 0;
						SetWindowLong(m_Notify->m_h_hwnd,GWL_USERDATA,(LONG)&m_Notify->m_T_WndData);
						m_b_ShowErr = TRUE;
						m_Notify->SetState(TRUE,FALSE,FALSE);
					}
					l_T_Ret = WlxAccessIdentOn(l_T_Data);
					break;	
				}
			default:
				{
					continue;
				}
			}
			
			switch(l_T_Ret)
			{
			case SW_OKHIT_MD :
				{
					m_Notify->m_T_WndData.m_b_UpdateOn = 0;
					SetWindowLong(m_Notify->m_h_hwnd,GWL_USERDATA,(LONG)&m_Notify->m_T_WndData);
					m_b_ShowErr = TRUE;
					m_Notify->SetState(TRUE,FALSE,FALSE);
					C_Access_ProcessShow();
					C_Access_CipherToUser(l_T_Data);
					if(m_b_SetGetState)
					{
						m_Notify->m_T_WndData.m_b_UpdateOn = 1;
						SetWindowLong(m_Notify->m_h_hwnd,GWL_USERDATA,(LONG)&m_Notify->m_T_WndData);
						m_AccessWizard->DoModal();
						m_Notify->m_T_WndData.m_b_UpdateOn = 0;
						SetWindowLong(m_Notify->m_h_hwnd,GWL_USERDATA,(LONG)&m_Notify->m_T_WndData);
					}
					else
						C_Access_ProcessUser(TRUE);
					break;
				}
			case SW_NOHIT_MD :
				{
					m_Notify->m_T_WndData.m_b_UpdateOn = 0;
					SetWindowLong(m_Notify->m_h_hwnd,GWL_USERDATA,(LONG)&m_Notify->m_T_WndData);
					m_b_ShowErr = TRUE;
					m_Notify->SetState(TRUE,FALSE,FALSE);
					C_Access_ProcessShow();
					C_Access_ProcessUser(FALSE);
					break;
				}
			case SW_ABORT_MD :
				{
					m_b_ShowErr = TRUE;
					m_Notify->SetState(TRUE,FALSE,FALSE);
					Sleep(m_i_TimeOut/3);
					break;
				}
			case SW_ERRSTG_MD :
				{
					m_Notify->m_T_WndData.m_b_UpdateOn = 1;
					SetWindowLong(m_Notify->m_h_hwnd,GWL_USERDATA,(LONG)&m_Notify->m_T_WndData);
					m_Notify->SetState(FALSE,TRUE,m_b_ShowErr);
					m_b_ShowErr = FALSE;
					WlxSWReboot(o_T_SWState);
					Sleep(m_i_TimeOut/4);
					break;
				}
			case SW_ERRACT_MD :
				{
					m_Notify->m_T_WndData.m_b_UpdateOn = 1;
					SetWindowLong(m_Notify->m_h_hwnd,GWL_USERDATA,(LONG)&m_Notify->m_T_WndData);
					m_Notify->SetState(FALSE,FALSE,m_b_ShowErr);
					m_b_ShowErr = FALSE;
					WlxSWReboot(o_T_SWState);
					Sleep(m_i_TimeOut/4);
					break;
				}
			}
		}while(l_dw_EventRet != WAIT_OBJECT_0);
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
	return 0;
}


UINT C_Access_Task
( 
 LPVOID pParam 
 )
{
	C_Access *C_AccessData = (C_Access*) pParam;
	return C_AccessData->C_Access_Thread();
}

BOOL C_Access::InitInstance
(
 VOID
 )
{
	DWORD					l_dw_LastError		= 0;
	DWORD					l_dw_LoopRet		= 0;
	HANDLE					l_ph_LoopEvents[4]	= {NULL};
	MSG 					l_x_msg 			= {NULL};
	UINT					l_ui_TimeOut		= 1000;
	PSECURITY_DESCRIPTOR	l_p_pSD 			= NULL;
	SECURITY_ATTRIBUTES 	l_T_sa				= {0};
	
	///SetProcessShutdownParameters(0x4FF,0x000010);
	
	l_p_pSD = (PSECURITY_DESCRIPTOR) malloc( SECURITY_DESCRIPTOR_MIN_LENGTH );
	
	if (l_p_pSD == NULL)
		return FALSE;
	
	if (!InitializeSecurityDescriptor(l_p_pSD, SECURITY_DESCRIPTOR_REVISION))
	{
		free(l_p_pSD);
		return FALSE;
	}
	
	// add a NULL disc. ACL to the security descriptor.
	if (!SetSecurityDescriptorDacl(l_p_pSD, TRUE, (PACL) NULL, FALSE))
	{
		free(l_p_pSD);
		return FALSE;
	}
	
	l_T_sa.nLength = sizeof(l_T_sa);
	l_T_sa.lpSecurityDescriptor = l_p_pSD;
	l_T_sa.bInheritHandle = FALSE;
	
	m_h_Mutex = CreateMutex
		(
		(LPSECURITY_ATTRIBUTES)&l_T_sa, 
		(BOOL)TRUE, 
		(LPCTSTR)_T(VC_ACCESSMUTEX_NAME) 
		);
	
	free(l_p_pSD);
	
	l_dw_LastError = GetLastError ();
	
	// If cannot create Mutex, exit.
	if (m_h_Mutex == NULL)
		return FALSE;
	
	// If Mutex already existed, exit.
	if (l_dw_LastError == ERROR_ALREADY_EXISTS)
	{
		ReleaseMutex(m_h_Mutex);
		CloseHandle (m_h_Mutex);
		m_h_Mutex = NULL;
		return FALSE;
	}
	
	m_h_ExitOk		= CreateEvent(NULL, FALSE, FALSE, _T(VC_ACCESSEXITOK));
	m_h_ExitKo		= CreateEvent(NULL, FALSE, FALSE, _T(VC_ACCESSEXITKO));
	m_h_Start		= CreateEvent(NULL, FALSE, FALSE, _T(VC_ACCESSSTART));
	m_h_Stop		= CreateEvent(NULL, FALSE, FALSE, _T(VC_ACCESSSTOP));
	m_h_AccessExit	= CreateEvent(NULL, FALSE, FALSE, _T(VC_ACCESSEXITTHREAD));
	m_h_AccessStart = CreateEvent(NULL, FALSE, FALSE, _T(VC_ACCESSSTARTTHREAD));
	m_h_AccessStop	= CreateEvent(NULL, FALSE, FALSE, _T(VC_ACCESSSTOPTHREAD));
	
	if(m_h_ExitOk == NULL || m_h_ExitKo == NULL ||\
		m_h_Start == NULL || m_h_Stop == NULL)
	{
		ReleaseMutex(m_h_Mutex);
		CloseHandle(m_h_Mutex);
		return FALSE;
	}
	
	m_Wnd				= new C_Wnd();
	m_Info				= new C_Info();
	m_Profil			= new C_Profil();	
	m_Notify			= new C_Notify(m_h_ExitOk,m_h_ExitKo,m_h_Start,m_h_Stop);
	m_AccessWizard		= new C_AccessWizard(m_Wnd,m_T_Access,&m_T_Keys,m_pwc_UserId);
	
	l_ph_LoopEvents[0] = m_h_ExitOk;
	l_ph_LoopEvents[1] = m_h_Start;
	l_ph_LoopEvents[2] = m_h_Stop;
	
	SetEvent(m_h_Start);
	AfxBeginThread(C_Access_Task,(LPVOID)this);
	do
	{
		l_dw_LoopRet = MsgWaitForMultipleObjects(3, l_ph_LoopEvents,FALSE, INFINITE, QS_ALLEVENTS | QS_ALLINPUT | QS_ALLPOSTMESSAGE | QS_SENDMESSAGE | QS_POSTMESSAGE | QS_MOUSE | QS_MOUSEBUTTON | QS_PAINT | QS_MOUSEMOVE | QS_INPUT |  QS_TIMER);
		switch(l_dw_LoopRet)
		{
		case WAIT_OBJECT_0 :
			{
				ResetEvent(m_h_AccessStart);
				ResetEvent(m_h_AccessStop);
				SetEvent(m_h_AccessExit);
				WlxAccessIdentOff();
				break;
			}
		case WAIT_OBJECT_0+1 :
			{
				ResetEvent(m_h_AccessStop);
				SetEvent(m_h_AccessStart);
				break;
			}
		case WAIT_OBJECT_0+2 :
			{
				ResetEvent(m_h_AccessStart);
				SetEvent(m_h_AccessStop);
				WlxAccessIdentOff();	
				break;
			}
		default :
			{
				break;
			}
		}
		
		while (PeekMessage(&l_x_msg, NULL, 0, 0, PM_REMOVE))
		{
			if(l_x_msg.message == WM_ENDSESSION || l_x_msg.message == WM_QUERYENDSESSION || l_x_msg.message == 0x003B || l_x_msg.message == WM_DESTROY || l_x_msg.message == WM_CLOSE)	
			{
				l_dw_LoopRet = WAIT_OBJECT_0;
				ResetEvent(m_h_AccessStart);
				ResetEvent(m_h_AccessStop);
				SetEvent(m_h_AccessExit);
				WlxAccessIdentOff();
				continue;
			}

			TranslateMessage(&l_x_msg);
			DispatchMessage(&l_x_msg);
		}
		
	}while(l_dw_LoopRet != WAIT_OBJECT_0);
	
	WaitForSingleObject(m_h_ExitKo,60*m_i_TimeOut);
	
	delete(m_Notify);
	delete(m_Wnd);
	delete(m_Info);
	delete(m_Profil);
	delete(m_AccessWizard);
	
	ReleaseMutex(m_h_Mutex);
	CloseHandle(m_h_Mutex);
	
	CloseHandle(m_h_ExitOk);
	CloseHandle(m_h_ExitKo);
	CloseHandle(m_h_Start);
	CloseHandle(m_h_Stop);
	CloseHandle(m_h_AccessExit);
	CloseHandle(m_h_AccessStart);
	CloseHandle(m_h_AccessStop);
	
	return FALSE;
}

