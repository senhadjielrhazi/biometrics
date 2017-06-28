/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWGlobals.cpp												 //
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




#include "stdafx.h"

extern MiniMemory g_T_MiniMemory;

/*****************************BioLogonDlgProc********************************/
//DLL HWND Callback, this fuction Handle Messages for BioLogon Page.
/****************************************************************************/
INT CALLBACK BioLogonDlgProc
(
 HWND		 hDlg,
 UINT		 Message,
 WPARAM 	 wParam,
 LPARAM 	 lParam
 )
{
	PGlobals	l_p_Globals = NULL;
	
	__try
	{
		switch (Message)
		{
		case WM_INITDIALOG: 
			{
				return BioLogonDlgInit(hDlg,lParam,TRUE);
			}
		case WM_TIMER :
			return BioLogonProgress(hDlg,wParam);
		default:
			return(FALSE);
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		return FALSE;
	}
}

/*****************************BioLogonProgress*******************************/
//DLL HWND Handler, this fuction Handle Progress of the BioAthentication.
/****************************************************************************/
BOOL BioLogonProgress
(
 HWND hDlg,
 WPARAM wParam
 )
{
	PGlobals	l_p_Globals = NULL;
	
	__try
	{
		l_p_Globals = (PGlobals)GetWindowLong(hDlg,GWL_USERDATA);
		
		if(wParam == 0)
		{
			switch(l_p_Globals->m_i_Progress)
			{
			case 0:
				{		
					::SendDlgItemMessage
						(
						hDlg,IDC_TEXT_LOG_1,
						WM_SETFONT,
						(WPARAM)l_p_Globals->m_h_Font_1, 
						(LPARAM)TRUE
						);
					::SetDlgItemText(hDlg,IDC_TEXT_LOG_1,_T(VC_LOGON_WAITOK));
					::KillTimer(hDlg,0);
					l_p_Globals->m_i_Progress++;
					::SetWindowLong(hDlg,GWL_USERDATA,(LONG)l_p_Globals);
					break;
				}
			case 1:
				{
					::SendDlgItemMessage
						(
						hDlg,IDC_TEXT_LOG_1,
						WM_SETFONT,
						(WPARAM)l_p_Globals->m_h_Font_2, 
						(LPARAM)TRUE
						);
					Animate_Stop((HWND)GetDlgItem(hDlg,IDC_STATIC_BIOAVI));
					Animate_Close((HWND)GetDlgItem(hDlg,IDC_STATIC_BIOAVI));
					switch(l_p_Globals->m_T_Result)
					{
					case SW_OKHIT_MD:
						{
							::SetDlgItemText(hDlg,IDC_TEXT_LOG_1,_T(VC_LOGON_AUTH_OK));
							Animate_Open( (HWND)GetDlgItem(hDlg,IDC_STATIC_BIOAVI), MAKEINTRESOURCE(IDR_SW_OK));
							Animate_Play( (HWND)GetDlgItem(hDlg,IDC_STATIC_BIOAVI), 0, -1, 1);	
							break;
						}
					case SW_NOHIT_MD:
						{
							::SetDlgItemText(hDlg,IDC_TEXT_LOG_1,_T(VC_LOGON_AUTH_OK));
							Animate_Open( (HWND)GetDlgItem(hDlg,IDC_STATIC_BIOAVI), MAKEINTRESOURCE(IDR_SW_ERR));
							Animate_Play( (HWND)GetDlgItem(hDlg,IDC_STATIC_BIOAVI), 0, -1, 1);
							break;
						}
					default:
						{
							::SetDlgItemText(hDlg,IDC_TEXT_LOG_1,_T(VC_LOGON_AUTH_ERR));
							Animate_Open( (HWND)GetDlgItem(hDlg,IDC_STATIC_BIOAVI), MAKEINTRESOURCE(IDR_SW_ERR));
							Animate_Play( (HWND)GetDlgItem(hDlg,IDC_STATIC_BIOAVI), 0, -1, 1);
							break;
						}
					}
					::SendDlgItemMessage
						(
						hDlg,IDC_TEXT_LOG_2,
						WM_SETFONT,
						(WPARAM)l_p_Globals->m_h_Font_1, 
						(LPARAM)TRUE
						);
					::SetDlgItemText(hDlg,IDC_TEXT_LOG_2,_T(VC_LOGON_PROCESSOK));
					l_p_Globals->m_i_Progress++;
					::SetWindowLong(hDlg,GWL_USERDATA,(LONG)l_p_Globals);
					break;
				}
			case 2:
				{
					::SendDlgItemMessage
						(
						hDlg,IDC_TEXT_LOG_2,
						WM_SETFONT,
						(WPARAM)l_p_Globals->m_h_Font_2, 
						(LPARAM)TRUE
						);
					switch(l_p_Globals->m_T_Result)
					{
					case SW_OKHIT_MD:
						{
							::SetDlgItemText(hDlg,IDC_TEXT_LOG_2,_T(VC_LOGON_USER_OK));
							break;
						}
					case SW_NOHIT_MD:
						{
							::SetDlgItemText(hDlg,IDC_TEXT_LOG_2,_T(VC_LOGON_USER_NO));
							break;
						}
					case SW_ABORT_MD:
						{
							::SetDlgItemText(hDlg,IDC_TEXT_LOG_2,_T(VC_LOGON_USER_ABORT));
							break;
						}
					default:
						{
							::SetDlgItemText(hDlg,IDC_TEXT_LOG_2,_T(VC_LOGON_USER_ERR));
							break;
						}
					}
					::SendDlgItemMessage
						(
						hDlg,IDC_TEXT_LOG_3,
						WM_SETFONT,
						(WPARAM)l_p_Globals->m_h_Font_1, 
						(LPARAM)TRUE
						);
					::SetDlgItemText(hDlg,IDC_TEXT_LOG_3,_T(VC_LOGON_WAITKO));
					l_p_Globals->m_i_Progress++;
					::SetWindowLong(hDlg,GWL_USERDATA,(LONG)l_p_Globals);
					break;
				}
			case 3:
				{
					l_p_Globals->m_i_Progress++;
					::SetWindowLong(hDlg,GWL_USERDATA,(LONG)l_p_Globals);
					break;
				}
			case 4:
				{
					::SendDlgItemMessage
						(
						hDlg,IDC_TEXT_LOG_1,
						WM_SETFONT,
						(WPARAM)l_p_Globals->m_h_Font_2, 
						(LPARAM)TRUE
						);
					::KillTimer(hDlg,0);
					l_p_Globals->m_i_Progress = 0;
					::SetWindowLong(hDlg,GWL_USERDATA,(LONG)l_p_Globals);
					Animate_Stop((HWND)GetDlgItem(hDlg,IDC_STATIC_BIOAVI));
					Animate_Close((HWND)GetDlgItem(hDlg,IDC_STATIC_BIOAVI));
					BioLogonDlgRet(hDlg,l_p_Globals->m_T_Result);
					break;
				}
			}
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
	return(TRUE);
}

/*****************************BioLogonProgress*******************************/
//DLL HWND Handler, this fuction Handle Progress of the BioAthen Result.
/****************************************************************************/
INT BioLogonDlgRet
(
 HWND hDlg,
 TModuleRet wParam
 )
{
	PGlobals	l_p_Globals = NULL;
	
	__try
	{
		l_p_Globals = (PGlobals)GetWindowLong(hDlg,GWL_USERDATA);
		
		switch(wParam)
		{
		case SW_OKHIT_MD :
			{
				l_p_Globals->m_i_UserTypeLogon = WLX_SAS_TYPE_BIO_HITOK;
				::EndDialog(hDlg,WLX_SAS_TYPE_BIO_HITOK);
				break;
			}
		case SW_NOHIT_MD :
			{
				l_p_Globals->m_i_UserTypeLogon = WLX_SAS_TYPE_BIO_HITNO;
				::EndDialog(hDlg,WLX_SAS_TYPE_BIO_HITNO);
				break;
			}
		default :
				break;
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
	return(TRUE);
}

/*****************************BioLogonDlgInit********************************/
//DLL HWND Handler, this fuction Handle the initialization. 
/****************************************************************************/
INT BioLogonDlgInit
(
 HWND hDlg, 
 LPARAM lParam,
 BOOL	l_Font
 )
{	
	PGlobals	l_p_Globals = NULL;
	LONG		*l_l_Adress = NULL;
	
	__try
	{
		l_p_Globals = (PGlobals) lParam;	
		
		CenterWindow(hDlg);
		
		g_T_MiniMemory.m_b_Progress	= FALSE;
		
		l_p_Globals->m_i_UserTypeLogon = WLX_SAS_TYPE_CTRL_ALT_DEL;
		
		l_p_Globals->m_i_Progress	= 0;
		l_p_Globals->m_h_HwndDlgLog = hDlg;
		l_p_Globals->m_h_Font_1 = ::CreateFont(15, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 
			PROOF_QUALITY,VARIABLE_PITCH | FF_SWISS, L""); 
		
		if(l_Font)
		{
			l_p_Globals->m_h_Font_2 = NULL;
			
			l_p_Globals->m_h_Font_2 = (HFONT)SendDlgItemMessage
				(
				hDlg,IDC_TEXT_LOG_1,
				WM_GETFONT, (WPARAM)0, 
				(LPARAM)0
				);
			
			::SetDlgItemText(hDlg,IDC_TEXT_LOG_1,_T(""));
			::SetDlgItemText(hDlg,IDC_TEXT_LOG_2,_T(""));
			::SetDlgItemText(hDlg,IDC_TEXT_LOG_3,_T(""));
		}

		l_l_Adress = (LONG *)malloc(sizeof(*l_p_Globals));
		memset(l_l_Adress,0,sizeof(Globals));
		memcpy(l_l_Adress,l_p_Globals,sizeof(*l_p_Globals));
		::SetWindowLong(hDlg,GWL_USERDATA,(LONG)l_p_Globals);
		free(l_l_Adress);
		
		Animate_Open( (HWND)GetDlgItem(hDlg,IDC_STATIC_BIOAVI), MAKEINTRESOURCE(IDR_SW_WAIT));
		Animate_Play( (HWND)GetDlgItem(hDlg,IDC_STATIC_BIOAVI), 0, -1, -1);
		
		CreateThread
			(
			NULL,
			0,
			(LPTHREAD_START_ROUTINE)LogonIdentThreadProc,
			hDlg,
			0,
			0
			);
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}	
	return(TRUE);
}

/****************************LogonIdentThreadProc*****************************/
//DLL Thread Proc, this fuction Handle the Authentification. 
/****************************************************************************/
DWORD WINAPI LogonIdentThreadProc
(
 LPVOID lpvParam
 )
{
	TSWState		l_T_SWState;
	C_Crypto_AES	l_x_oRijndael;
	PGlobals		l_p_Globals 		= NULL;
	TSpeDataOut 	l_T_in_Data 		= {0};
	TKeyField		l_T_Keys			= {0};
	UCHAR			*l_puc_Key			= NULL;
	UCHAR			*l_puc_szDataOut	= NULL;
	UCHAR			*l_puc_szDataIn 	= NULL;
	INT 			l_i_size_out		= 0;
	INT 			l_i_size_in 		= 0;
	HWND			l_h_hwnd			= NULL; 
	
	__try
	{
		l_h_hwnd	=(HWND)lpvParam;
		l_p_Globals = (PGlobals)GetWindowLong(l_h_hwnd,GWL_USERDATA);
		g_T_MiniMemory.m_b_Progress	= FALSE;
		l_p_Globals->m_i_Progress = 0;
		::SetWindowLong(l_p_Globals->m_h_HwndDlgLog,GWL_USERDATA,(LONG)l_p_Globals);
		::SetTimer(l_p_Globals->m_h_HwndDlgLog, 0, 50, (TIMERPROC) NULL);
		
		if(!WlxIsSWValid())
		{
			if(WlxIsSWLock())
				Sleep(100);
			else
				WlxSWReboot(l_T_SWState);
		}

		l_p_Globals->m_T_Result = WlxLogonIdentOn(l_T_in_Data);
		
		if(l_p_Globals->m_T_Result == SW_ERRSTG_MD || l_p_Globals->m_T_Result == SW_ERRACT_MD)
		{
			::SetDlgItemText(l_p_Globals->m_h_HwndDlgLog,IDC_TEXT_LOG_1,_T(VC_LOGON_WAITOKERR));
			if(!WlxIsSWLock())
				WlxSWReboot(l_T_SWState);
			
			if(WlxIsSWValid())
			{
				::KillTimer(l_p_Globals->m_h_HwndDlgLog,0);
				l_p_Globals->m_i_Progress = 1;
				BioLogonDlgInit(l_p_Globals->m_h_HwndDlgLog,(WPARAM)l_p_Globals,FALSE);
				return FALSE;
			}
		}

		if(l_p_Globals->m_T_Result == SW_OKHIT_MD)
		{
			//encrypt data for logon.
			memset(&l_T_Keys,0,sizeof(TKeyField));
			memcpy(&l_T_Keys,l_T_in_Data.m_pwc_UserKey,sizeof(l_T_in_Data.m_pwc_UserKey));
			
			l_puc_Key =(UCHAR *)malloc(VI_BASEKEY_MAX*sizeof(WCHAR));
			memset(l_puc_Key,0,VI_BASEKEY_MAX*sizeof(WCHAR));
			memcpy(l_puc_Key,l_T_Keys.m_pwc_UserKeyBase,sizeof(l_T_Keys.m_pwc_UserKeyBase));
			
			l_x_oRijndael.C_Crypto_MakeKey(l_puc_Key,C_Crypto_AES::Key32Bytes);
			
			l_i_size_in 	= sizeof(l_T_in_Data.m_pwc_UserLogon);
			l_i_size_out	= l_x_oRijndael.C_Crypto_Length(l_i_size_in);
			
			l_puc_szDataIn	= (UCHAR *)malloc(l_i_size_in+1);
			l_puc_szDataOut = (UCHAR *)malloc(l_i_size_out+1);
			
			memset(l_puc_szDataIn,0,l_i_size_in+1);
			memset(l_puc_szDataOut,0,l_i_size_out+1);
			
			memcpy(l_puc_szDataIn,l_T_in_Data.m_pwc_UserLogon,sizeof(l_T_in_Data.m_pwc_UserLogon));
			
			l_x_oRijndael.C_Crypto_Decrypt(l_puc_szDataIn,l_i_size_in,l_puc_szDataOut);
			
			memset(&l_p_Globals->m_T_LogonData,0,sizeof(TLogonField));
			memcpy(&l_p_Globals->m_T_LogonData,l_puc_szDataOut,sizeof(TLogonField));
			
			free(l_puc_szDataOut);
			free(l_puc_szDataIn);
			free(l_puc_Key);
		}
		if(l_p_Globals->m_i_Progress == 0)
		{
			::SendDlgItemMessage
				(
				l_p_Globals->m_h_HwndDlgLog,IDC_TEXT_LOG_1,
				WM_SETFONT,
				(WPARAM)l_p_Globals->m_h_Font_1, 
				(LPARAM)TRUE
				);
			::SetDlgItemText(l_p_Globals->m_h_HwndDlgLog,IDC_TEXT_LOG_1,_T(VC_LOGON_WAITOK));
			l_p_Globals->m_i_Progress = 1;
			::KillTimer(l_p_Globals->m_h_HwndDlgLog,0);
		}
		Sleep(10);
		g_T_MiniMemory.m_b_Progress	= TRUE;
		::SetWindowLong(l_p_Globals->m_h_HwndDlgLog,GWL_USERDATA,(LONG)l_p_Globals);
		::SetTimer(l_p_Globals->m_h_HwndDlgLog, 0, 1000, (TIMERPROC) NULL);
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	
	{
		g_T_MiniMemory.m_b_Progress	= TRUE;
	}
	return 0;
}

/*****************************WinLogonDlgProc********************************/
//DLL HWND Callback, this fuction Handle the Messages for WinLogon.
/****************************************************************************/
INT CALLBACK WinLogonDlgProc
(
 HWND		 hDlg,
 UINT		 Message,
 WPARAM 	 wParam,
 LPARAM 	 lParam
 )
{
	__try
	{
		switch (Message)
		{
		case WM_INITDIALOG:
			return WinLogonDlgInit(hDlg,lParam);
			
		case WM_COMMAND:
			{
				if (LOWORD(wParam) == IDC_OK)
					return WinLogonDlgRet(hDlg);
				if (LOWORD(wParam) == IDC_CANCEL)
					::EndDialog(hDlg, WLX_SAS_ACTION_NONE);
				if (LOWORD(wParam) == IDC_SHUTDOWN)
					::EndDialog(hDlg, WLX_SAS_ACTION_SHUTDOWN);
				return(TRUE);
			}
		default:
			return(FALSE);
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		return(FALSE);
	}
}

/******************************WinLogonDlgInit*******************************/
//DLL HWND Callback, this fuction Handle the Initialisalisation.
/****************************************************************************/
INT WinLogonDlgInit
(
 HWND hDlg,
 LPARAM lParam
 )
{	
	LPWSTR		*l_puc_TrustList	= NULL;  
	DWORD		l_dw_TrustCount 	= 0;	
	PGlobals	l_p_Globals 		= NULL;
	INT 		l_i_Selection		= 0;
	
	__try
	{
		l_p_Globals = (PGlobals) lParam;
		
		CenterWindow(hDlg);
		
		::SetWindowLong(hDlg,GWL_USERDATA,(LONG)lParam);
		
		::SendMessage(GetDlgItem(hDlg, IDC_PASSWORD), EM_SETPASSWORDCHAR,'*', 0);
		
		::SendMessage(GetDlgItem(hDlg, IDC_USERNAME), EM_LIMITTEXT, VI_USERLOGON_MAX-1, 0);
		::SendMessage(GetDlgItem(hDlg, IDC_PASSWORD), EM_LIMITTEXT, VI_USERPASSW_MAX-1, 0);
		::SendMessage(GetDlgItem(hDlg, IDC_DOMAINNAME), EM_LIMITTEXT, VI_USERDOMAIN_MAX-1, 0);
		
		::SetDlgItemText(hDlg,IDC_USERNAME,_T(""));
		::SetDlgItemText(hDlg,IDC_PASSWORD,_T(""));
		::SetDlgItemText(hDlg,IDC_DOMAINNAME,_T(""));
		
		::SetDlgItemText(hDlg,IDC_USERNAME,l_p_Globals->m_T_LogonData.m_pwc_UserLogin);
		
		l_dw_TrustCount = 0;
		l_puc_TrustList = (LPWSTR *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY ,DOMAIN_MAX_COUNT * sizeof(LPWSTR));
		
		if(BuildTrustList(&l_puc_TrustList, &l_dw_TrustCount))
		{
			if (l_dw_TrustCount)
			{
				for(INT i = 0 ; i < (INT)l_dw_TrustCount ; i++)
				{
					if (memcmp(l_puc_TrustList[i], l_p_Globals->m_T_LogonData.m_pwc_UserDomain,wcslen(l_puc_TrustList[i])*sizeof(WCHAR)) != 0)
						::SendMessage(GetDlgItem(hDlg, IDC_DOMAINNAME), CB_INSERTSTRING, -1, (LPARAM) l_puc_TrustList[i]);	
				}
			}
		}
		
		::SendMessage(GetDlgItem(hDlg, IDC_DOMAINNAME), CB_INSERTSTRING, -1, (LPARAM) l_p_Globals->m_T_LogonData.m_pwc_UserDomain);  
		l_i_Selection = ::SendMessage(GetDlgItem(hDlg, IDC_DOMAINNAME), CB_GETCOUNT, 0, 0);  
		::SendMessage(GetDlgItem(hDlg, IDC_DOMAINNAME), CB_SETCURSEL,l_i_Selection-1,0);  
		
		for(INT i = 0; i < (INT)l_dw_TrustCount; i++) 
		{
			if(l_puc_TrustList[i] != NULL)
				HeapFree(GetProcessHeap(), 0, l_puc_TrustList[i]);
		}
		
		HeapFree(GetProcessHeap(), 0, l_puc_TrustList); 	
		
		::SetFocus(GetDlgItem(hDlg, IDC_PASSWORD)); 
		
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
	return(TRUE);
}

/******************************WinLogonDlgRet********************************/
//DLL HWND Callback, this fuction Handle the Logon Processing.
/****************************************************************************/
INT WinLogonDlgRet
(
 HWND hDlg
 )
{
	PGlobals	l_p_Globals = NULL;
	
	__try
	{
		l_p_Globals = (PGlobals)GetWindowLong(hDlg,GWL_USERDATA);
		memset(&l_p_Globals->m_T_LogonData,0,sizeof(TLogonField));
		
		::GetDlgItemText(hDlg,IDC_DOMAINNAME,l_p_Globals->m_T_LogonData.m_pwc_UserDomain,sizeof(l_p_Globals->m_T_LogonData.m_pwc_UserDomain));
		::GetDlgItemText(hDlg,IDC_USERNAME,l_p_Globals->m_T_LogonData.m_pwc_UserLogin,sizeof(l_p_Globals->m_T_LogonData.m_pwc_UserLogin));
		::GetDlgItemText(hDlg,IDC_PASSWORD,l_p_Globals->m_T_LogonData.m_pwc_UserPassW,sizeof(l_p_Globals->m_T_LogonData.m_pwc_UserPassW));
		
		::EndDialog(hDlg, WLX_SAS_ACTION_LOGON);
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
	return(TRUE);
}

/******************************BioLockDlgProc*********************************/
//DLL HWND Callback, this fuction Handle the BioLock.
/****************************************************************************/
INT CALLBACK BioLockDlgProc
(
 HWND		 hDlg,
 UINT		 Message,
 WPARAM 	 wParam,
 LPARAM 	 lParam
 )
{
	PGlobals	l_p_Globals = NULL;
	
	__try
	{
		switch (Message)
		{
		case WM_INITDIALOG:
			return BioLockDlgInit(hDlg,lParam,TRUE);
		case WM_TIMER :
			return BioLockProgress(hDlg,wParam);
		default:
			return(FALSE);
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		return(FALSE);
	}
	
}

/******************************BioLockProgress********************************/
//DLL HWND Callback, this fuction Handle the BioLock Processing
/****************************************************************************/
BOOL BioLockProgress
(
 HWND hDlg,
 WPARAM wParam
 )
{
	PGlobals	l_p_Globals = NULL;
	
	__try
	{
		l_p_Globals = (PGlobals)GetWindowLong(hDlg,GWL_USERDATA);
		
		if(wParam == 0)
		{
			switch(l_p_Globals->m_i_Progress)
			{
			case 0:
				{	
					::SendDlgItemMessage
						(
						hDlg,IDC_TEXT_LOCK_1,
						WM_SETFONT,
						(WPARAM)l_p_Globals->m_h_Font_1, 
						(LPARAM)TRUE
						);
					::SetDlgItemText(hDlg,IDC_TEXT_LOCK_1,_T(VC_LOGON_WAITOK));
					::KillTimer(hDlg,0);
					l_p_Globals->m_i_Progress++;
					::SetWindowLong(hDlg,GWL_USERDATA,(LONG)l_p_Globals);
					break;
				}
			case 1:
				{
					::SendDlgItemMessage
						(
						hDlg,IDC_TEXT_LOCK_1,
						WM_SETFONT,
						(WPARAM)l_p_Globals->m_h_Font_2, 
						(LPARAM)TRUE
						);
					Animate_Stop((HWND)GetDlgItem(hDlg,IDC_STATIC_BIOAVI));
					Animate_Close((HWND)GetDlgItem(hDlg,IDC_STATIC_BIOAVI));
					switch(l_p_Globals->m_T_Result)
					{
					case SW_OKHIT_MD:
						{
							::SetDlgItemText(hDlg,IDC_TEXT_LOCK_1,_T(VC_LOGON_AUTH_OK));
							Animate_Open( (HWND)GetDlgItem(hDlg,IDC_STATIC_BIOAVI), MAKEINTRESOURCE(IDR_SW_OK));
							Animate_Play( (HWND)GetDlgItem(hDlg,IDC_STATIC_BIOAVI), 0, -1, 1);	
							break;
						}
					case SW_NOHIT_MD:
						{
							::SetDlgItemText(hDlg,IDC_TEXT_LOCK_1,_T(VC_LOGON_AUTH_OK));
							Animate_Open( (HWND)GetDlgItem(hDlg,IDC_STATIC_BIOAVI), MAKEINTRESOURCE(IDR_SW_ERR));
							Animate_Play( (HWND)GetDlgItem(hDlg,IDC_STATIC_BIOAVI), 0, -1, 1);
							break;
						}
					default:
						{
							::SetDlgItemText(hDlg,IDC_TEXT_LOCK_1,_T(VC_LOGON_AUTH_ERR));
							Animate_Open( (HWND)GetDlgItem(hDlg,IDC_STATIC_BIOAVI), MAKEINTRESOURCE(IDR_SW_ERR));
							Animate_Play( (HWND)GetDlgItem(hDlg,IDC_STATIC_BIOAVI), 0, -1, 1);
							break;
						}
					}
					::SendDlgItemMessage
						(
						hDlg,IDC_TEXT_LOCK_2,
						WM_SETFONT,
						(WPARAM)l_p_Globals->m_h_Font_1, 
						(LPARAM)TRUE
						);
					::SetDlgItemText(hDlg,IDC_TEXT_LOCK_2,_T(VC_LOGON_PROCESSOK));
					l_p_Globals->m_i_Progress++;
					::SetWindowLong(hDlg,GWL_USERDATA,(LONG)l_p_Globals);
					break;
				}
			case 2:
				{
					::SendDlgItemMessage
						(
						hDlg,IDC_TEXT_LOCK_2,
						WM_SETFONT,
						(WPARAM)l_p_Globals->m_h_Font_2, 
						(LPARAM)TRUE
						);
					switch(l_p_Globals->m_T_Result)
					{
					case SW_OKHIT_MD:
						{
							::SetDlgItemText(hDlg,IDC_TEXT_LOCK_2,_T(VC_LOGON_USER_OK));
							break;
						}
					case SW_NOHIT_MD:
						{
							::SetDlgItemText(hDlg,IDC_TEXT_LOCK_2,_T(VC_LOGON_USER_NO));
							break;
						}
					case SW_ABORT_MD:
						{
							::SetDlgItemText(hDlg,IDC_TEXT_LOCK_2,_T(VC_LOGON_USER_ABORT));
							break;
						}
					default:
						{
							::SetDlgItemText(hDlg,IDC_TEXT_LOCK_2,_T(VC_LOGON_USER_ERR));
							break;
						}
					}
					::SendDlgItemMessage
						(
						hDlg,IDC_TEXT_LOCK_3,
						WM_SETFONT,
						(WPARAM)l_p_Globals->m_h_Font_1, 
						(LPARAM)TRUE
						);
					::SetDlgItemText(hDlg,IDC_TEXT_LOCK_3,_T(VC_LOGON_WAITKO));
					l_p_Globals->m_i_Progress++;
					::SetWindowLong(hDlg,GWL_USERDATA,(LONG)l_p_Globals);
					break;
				}
			case 3:
				{
					l_p_Globals->m_i_Progress++;
					::SetWindowLong(hDlg,GWL_USERDATA,(LONG)l_p_Globals);
					break;
				}
			case 4:
				{
					l_p_Globals->m_h_Font_2 = (HFONT)SendDlgItemMessage
						(
						hDlg,IDC_TEXT_LOCK_2,
						WM_GETFONT, (WPARAM)0, 
						(LPARAM)0
						);
					::KillTimer(hDlg,0);
					l_p_Globals->m_i_Progress = 0;
					::SetWindowLong(hDlg,GWL_USERDATA,(LONG)l_p_Globals);
					Animate_Stop((HWND)GetDlgItem(hDlg,IDC_STATIC_BIOAVI));
					Animate_Close((HWND)GetDlgItem(hDlg,IDC_STATIC_BIOAVI));
					BioLogonDlgRet(hDlg,l_p_Globals->m_T_Result);
					break;
				}
			}
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
	return(TRUE);
}

/******************************BioLockDlgRet********************************/
//DLL HWND Callback, this fuction Handle the BioLock Result.
/****************************************************************************/
INT BioLockDlgRet
(
 HWND hDlg,
 TModuleRet wParam
 )
{
	PGlobals	l_p_Globals = NULL;
	
	__try
	{
		l_p_Globals = (PGlobals)GetWindowLong(hDlg,GWL_USERDATA);
		
		switch(wParam)
		{
		case SW_OKHIT_MD :
			{
				l_p_Globals->m_i_UserTypeLogon = WLX_SAS_TYPE_BIO_HITOK;
				::EndDialog(hDlg,WLX_SAS_TYPE_BIO_HITOK);
				break;
			}
		case SW_NOHIT_MD :
			{
				l_p_Globals->m_i_UserTypeLogon = WLX_SAS_TYPE_BIO_HITNO;
				::EndDialog(hDlg,WLX_SAS_TYPE_BIO_HITNO);
				break;
			}
		default :
			break;
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
	return(TRUE);
}

/******************************BioLockDlgInit********************************/
//DLL HWND Callback, this fuction Handle the BioLock initialization.
/****************************************************************************/
INT BioLockDlgInit
(
 HWND hDlg, 
 LPARAM lParam,
 BOOL l_Font
 )
{
	WCHAR		l_pwcTmp_1[256] = {0};
	PGlobals	l_p_Globals 	= NULL;
	LONG		*l_l_Adress		= NULL;
	
	__try
	{
		CenterWindow(hDlg);
		
		l_p_Globals = (PGlobals) lParam;	
		
		g_T_MiniMemory.m_b_Progress	= FALSE;
		
		l_p_Globals->m_i_UserTypeLogon = WLX_SAS_TYPE_CTRL_ALT_DEL;
		
		memset(l_pwcTmp_1,0,sizeof(l_pwcTmp_1));
		wsprintf(l_pwcTmp_1,_T(VC_LOCK_USERSHOW),l_p_Globals->m_T_LogonData.m_pwc_UserLogin,l_p_Globals->m_T_LogonData.m_pwc_UserDomain);
		::SetDlgItemText(hDlg, IDC_STATIC_USERINFO, l_pwcTmp_1);
		l_p_Globals->m_i_Progress	= 0;
		l_p_Globals->m_h_HwndDlgLog = hDlg;
		l_p_Globals->m_h_Font_1 = ::CreateFont(15, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 
			PROOF_QUALITY,VARIABLE_PITCH | FF_SWISS, L""); 
		
		if(l_Font)
		{
			l_p_Globals->m_h_Font_2 = NULL;
			
			l_p_Globals->m_h_Font_2 = (HFONT)SendDlgItemMessage
				(
				hDlg,IDC_TEXT_LOCK_1,
				WM_GETFONT, (WPARAM)0, 
				(LPARAM)0
				);
			
			::SetDlgItemText(hDlg,IDC_TEXT_LOCK_1,_T(""));
			::SetDlgItemText(hDlg,IDC_TEXT_LOCK_2,_T(""));
			::SetDlgItemText(hDlg,IDC_TEXT_LOCK_3,_T(""));
		}
		
		l_l_Adress = (LONG *)malloc(sizeof(*l_p_Globals));
		memset(l_l_Adress,0,sizeof(Globals));
		memcpy(l_l_Adress,l_p_Globals,sizeof(*l_p_Globals));
		::SetWindowLong(hDlg,GWL_USERDATA,(LONG)l_p_Globals);
		free(l_l_Adress);
		
		Animate_Open( (HWND)GetDlgItem(hDlg,IDC_STATIC_BIOAVI), MAKEINTRESOURCE(IDR_SW_WAIT));
		Animate_Play( (HWND)GetDlgItem(hDlg,IDC_STATIC_BIOAVI), 0, -1, -1);
		
		CreateThread
			(
			NULL,
			0,
			(LPTHREAD_START_ROUTINE)LockIdentThreadProc,
			hDlg,
			0,
			0
			);
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}	
	return(TRUE);
}

/******************************LockIdentThreadProc****************************/
//DLL Thread Proc, this fuction Handle the BioLock Authentication.
/****************************************************************************/
DWORD WINAPI LockIdentThreadProc
(
 LPVOID lpvParam
 )
{
	C_Crypto_AES	l_x_oRijndael;
	TSWState		l_T_SWState;
	PGlobals		l_p_Globals 		= NULL;
	TSpeDataOut 	l_T_in_Data 		= {0};
	TKeyField		l_T_Keys			= {0};
	UCHAR			*l_puc_Key			= NULL;
	UCHAR			*l_puc_szDataOut	= NULL;
	UCHAR			*l_puc_szDataIn 	= NULL;
	INT 			l_i_size_out		= 0;
	INT 			l_i_size_in 		= 0;
	HWND			l_h_hwnd			= NULL; 
	TLogonField 	l_T_LogonData		= {0};
	
	__try
	{
		l_h_hwnd		= (HWND)lpvParam;
		l_p_Globals		= (PGlobals)GetWindowLong(l_h_hwnd,GWL_USERDATA);
		g_T_MiniMemory.m_b_Progress	= FALSE;
		l_p_Globals->m_i_Progress = 0;
		::SetWindowLong(l_p_Globals->m_h_HwndDlgLog,GWL_USERDATA,(LONG)l_p_Globals);
		::SetTimer(l_p_Globals->m_h_HwndDlgLog, 0, 50, (TIMERPROC) NULL);
		
		if(!WlxIsSWValid())
		{
			if(WlxIsSWLock())
				Sleep(100);
			else
				WlxSWReboot(l_T_SWState);
		}
		
		l_p_Globals->m_T_Result = WlxLogonIdentOn(l_T_in_Data);

		if(l_p_Globals->m_T_Result == SW_ERRSTG_MD || l_p_Globals->m_T_Result == SW_ERRACT_MD)
		{
			::SetDlgItemText(l_p_Globals->m_h_HwndDlgLog,IDC_TEXT_LOCK_1,_T(VC_LOGON_WAITOKERR));
			if(!WlxIsSWLock())
				WlxSWReboot(l_T_SWState);
			
			if(WlxIsSWValid())
			{
				::KillTimer(l_p_Globals->m_h_HwndDlgLog,0);
				l_p_Globals->m_i_Progress = 1;
				BioLogonDlgInit(l_p_Globals->m_h_HwndDlgLog,(WPARAM)l_p_Globals,FALSE);
				return FALSE;
			}
		}

		if(l_p_Globals->m_T_Result == SW_OKHIT_MD)
		{
			//encrypt data for logon.
			memset(&l_T_Keys,0,sizeof(TKeyField));
			memcpy(&l_T_Keys,l_T_in_Data.m_pwc_UserKey,sizeof(l_T_in_Data.m_pwc_UserKey));
			
			l_puc_Key =(UCHAR *)malloc(VI_BASEKEY_MAX*sizeof(WCHAR));
			memset(l_puc_Key,0,VI_BASEKEY_MAX*sizeof(WCHAR));
			memcpy(l_puc_Key,l_T_Keys.m_pwc_UserKeyBase,sizeof(l_T_Keys.m_pwc_UserKeyBase));
			
			l_x_oRijndael.C_Crypto_MakeKey(l_puc_Key,C_Crypto_AES::Key32Bytes);
			
			l_i_size_in 	= sizeof(l_T_in_Data.m_pwc_UserLogon);
			l_i_size_out	= l_x_oRijndael.C_Crypto_Length(l_i_size_in);
			
			l_puc_szDataIn	= (UCHAR *)malloc(l_i_size_in+1);
			l_puc_szDataOut = (UCHAR *)malloc(l_i_size_out+1);
			
			memset(l_puc_szDataIn,0,l_i_size_in+1);
			memset(l_puc_szDataOut,0,l_i_size_out+1);
			
			memcpy(l_puc_szDataIn,l_T_in_Data.m_pwc_UserLogon,sizeof(l_T_in_Data.m_pwc_UserLogon));
			
			l_x_oRijndael.C_Crypto_Decrypt(l_puc_szDataIn,l_i_size_in,l_puc_szDataOut);
			
			memset(l_p_Globals->m_pwc_UserPassW,0,sizeof(l_p_Globals->m_pwc_UserPassW));
			memset(&l_T_LogonData,0,sizeof(TLogonField));
			memcpy(&l_T_LogonData,l_puc_szDataOut,sizeof(TLogonField));
			memcpy(l_p_Globals->m_pwc_UserPassW,l_T_LogonData.m_pwc_UserPassW,sizeof(l_T_LogonData.m_pwc_UserPassW));
			
			free(l_puc_szDataOut);
			free(l_puc_szDataIn);
			free(l_puc_Key);
		}
		if(l_p_Globals->m_i_Progress == 0)
		{
			::SendDlgItemMessage
				(
				l_p_Globals->m_h_HwndDlgLog,IDC_TEXT_LOCK_1,
				WM_SETFONT,
				(WPARAM)l_p_Globals->m_h_Font_1, 
				(LPARAM)TRUE
				);
			::SetDlgItemText(l_p_Globals->m_h_HwndDlgLog,IDC_TEXT_LOCK_1,_T(VC_LOGON_WAITOK));
			l_p_Globals->m_i_Progress = 1;
			::KillTimer(l_p_Globals->m_h_HwndDlgLog,0);
		}
		Sleep(10);
		g_T_MiniMemory.m_b_Progress	= TRUE;
		::SetWindowLong(l_p_Globals->m_h_HwndDlgLog,GWL_USERDATA,(LONG)l_p_Globals);
		::SetTimer(l_p_Globals->m_h_HwndDlgLog, 0, 1000, (TIMERPROC) NULL);
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		g_T_MiniMemory.m_b_Progress	= TRUE;
	}
	return 0;
}

/******************************WinLockDlgProc*********************************/
//DLL HWND Callback, this fuction 
/****************************************************************************/
INT CALLBACK WinLockDlgProc
(
 HWND		 hDlg,
 UINT		 Message,
 WPARAM 	 wParam,
 LPARAM 	 lParam
 )
{
	__try
	{
		switch (Message)
		{
		case WM_INITDIALOG:
			return WinLockDlgInit(hDlg,lParam); 
			
		case WM_COMMAND:
			{
				if (LOWORD(wParam) == IDC_OK)
					return WinLockDlgRet(hDlg);
				if (LOWORD(wParam) == IDC_CANCEL)
					::EndDialog(hDlg, WLX_SAS_ACTION_NONE);
				if (LOWORD(wParam) == IDC_SHUTDOWN)
					::EndDialog(hDlg, WLX_SAS_ACTION_FORCE_LOGOFF);
				return(TRUE);
			}
		default:
			return(FALSE);
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		return FALSE;
	}
}

/******************************WinLockDlgInit********************************/
//DLL HWND Handler, this fuction Handle the WinLock initialization.
/****************************************************************************/
INT WinLockDlgInit
(
 HWND hDlg,
 LPARAM lParam
 )
{
	PGlobals	l_p_Globals 	= NULL; 
	WCHAR		l_pwcTmp_1[256] = {0};
	
	__try
	{
		l_p_Globals = (PGlobals) lParam;
		CenterWindow(hDlg);
		
		::SetWindowLong(hDlg,GWL_USERDATA,(LONG)lParam);
		
		::SendMessage(GetDlgItem(hDlg, IDC_PASSWORD), EM_SETPASSWORDCHAR,'*', 0);
		
		memset(l_pwcTmp_1,0,sizeof(l_pwcTmp_1));
		wsprintf(l_pwcTmp_1,_T(VC_LOCK_USERSHOW),l_p_Globals->m_T_LogonData.m_pwc_UserLogin,l_p_Globals->m_T_LogonData.m_pwc_UserDomain);
		::SetDlgItemText(hDlg, IDC_STATIC_USERINFO, l_pwcTmp_1);
		
		::SendMessage(GetDlgItem(hDlg, IDC_PASSWORD), EM_LIMITTEXT, VI_USERPASSW_MAX-1, 0);
		
		::SetFocus(GetDlgItem(hDlg, IDC_PASSWORD));

		::SetDlgItemText(hDlg,IDC_PASSWORD,_T(""));
		
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
	return(TRUE);
}

/******************************INT WinLockDlgRet********************************/
//DLL HWND Handler, this fuction Handle the WinLock Processing
/****************************************************************************/
INT WinLockDlgRet
(
 HWND hDlg
 )
{
	PGlobals	l_p_Globals = NULL;
	
	__try
	{
		l_p_Globals = (PGlobals)GetWindowLong(hDlg,GWL_USERDATA);
		
		memset(l_p_Globals->m_pwc_UserPassW,0,sizeof(l_p_Globals->m_pwc_UserPassW));
		
		::GetDlgItemText(hDlg,IDC_PASSWORD,l_p_Globals->m_pwc_UserPassW,sizeof(l_p_Globals->m_pwc_UserPassW));
		
		::SetWindowLong(hDlg,GWL_USERDATA,(LONG)l_p_Globals);

		::EndDialog(hDlg, WLX_SAS_ACTION_UNLOCK_WKSTA);
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
	return(TRUE);
}



/******************************OptionsDlgProc*********************************/
//DLL HWND Callback, this fuction Ctrl+Alt+Suppr Options.
/****************************************************************************/
INT CALLBACK OptionsDlgProc
(
 HWND		 hDlg,
 UINT		 Message,
 WPARAM 	 wParam,
 LPARAM 	 lParam
 )
{
	__try
	{
		switch (Message)
		{
		case WM_INITDIALOG:
			return OptionsDlgInit(hDlg,lParam); 
		case WM_COMMAND:
			{
				switch (LOWORD(wParam))
				{
				case IDC_CANCEL :
					{
						::EndDialog(hDlg, WLX_SAS_ACTION_NONE);
						return(TRUE);
					}
				case IDC_LOCK :
					{
						::EndDialog(hDlg, WLX_SAS_ACTION_LOCK_WKSTA);
						return(TRUE);
					}
				case IDC_SHUTDOWN :
					return OptionsDlgShutdown(hDlg);
				case IDC_PASSWORD : 
					return OptionsDlgChangePassword(hDlg);
					
				case IDC_TASKLIST :
					{
						::EndDialog(hDlg, WLX_SAS_ACTION_TASKLIST);
						return(TRUE);
					}
				case IDC_LOGOFF :
					{
						::EndDialog(hDlg, WLX_SAS_ACTION_LOGOFF);
						return (TRUE);
					}
				}
			}
			
		default:
			return(FALSE);
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		return FALSE;
	}
}

/******************************OptionsDlgInit*********************************/
//DLL HWND Handler, this fuction Ctrl+Alt+Suppr Options Initialization.
/****************************************************************************/
INT OptionsDlgInit
(
 HWND hDlg,
 LPARAM lParam
 )
{
	WCHAR		l_pwcTmp_1[256] = {0};
	WCHAR		l_pwcTmp_2[256] = {0};
	PGlobals	l_p_Globals 	= NULL;
	
	__try
	{
		l_p_Globals = (PGlobals) lParam;
		
		CenterWindow(hDlg);
		
		::SetWindowLong(hDlg,GWL_USERDATA,(LONG)lParam);
		
		memset(l_pwcTmp_1,0,sizeof(l_pwcTmp_1));
		memset(l_pwcTmp_2,0,sizeof(l_pwcTmp_2));
		::GetDlgItemText(hDlg, IDC_STATIC_USERDOMAINE, l_pwcTmp_2,sizeof(l_pwcTmp_2));
		
		wsprintf(l_pwcTmp_1,l_pwcTmp_2,l_p_Globals->m_T_LogonData.m_pwc_UserLogin,l_p_Globals->m_T_LogonData.m_pwc_UserDomain,l_p_Globals->m_T_LogonData.m_pwc_UserLogin);
		::SetDlgItemText(hDlg, IDC_STATIC_USERDOMAINE, l_pwcTmp_1);
		
		memset(l_pwcTmp_1,0,sizeof(l_pwcTmp_1));
		memset(l_pwcTmp_2,0,sizeof(l_pwcTmp_2));
		::GetDlgItemText(hDlg, IDC_STATIC_TIME, l_pwcTmp_2,sizeof(l_pwcTmp_2));
		
		wsprintf(l_pwcTmp_1,l_pwcTmp_2,l_p_Globals->m_T_LogonTime.wDay,l_p_Globals->m_T_LogonTime.wMonth,l_p_Globals->m_T_LogonTime.wYear,l_p_Globals->m_T_LogonTime.wHour,l_p_Globals->m_T_LogonTime.wMinute,l_p_Globals->m_T_LogonTime.wSecond);
		::SetDlgItemText(hDlg, IDC_STATIC_TIME, l_pwcTmp_1);
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
	
	return TRUE;
}

/****************************OptionsDlgShutdown*******************************/
//DLL HWND Handler, this fuction Ctrl+Alt+Suppr ShtDown Options.
/****************************************************************************/
INT OptionsDlgShutdown
(
 HWND hDlg
 )
{
	PGlobals	l_p_Globals = NULL;
	INT 		l_i_Result	= 0;
	
	__try
	{
		::ShowWindow(hDlg,SW_HIDE);
		
		l_p_Globals = (PGlobals)GetWindowLong(hDlg,GWL_USERDATA);
		
		l_i_Result = l_p_Globals->m_p_WlxFuncs->WlxDialogBoxParam
			( 
			l_p_Globals->m_h_GlobalWlx,
			l_p_Globals->m_h_DllInstance,
			(LPTSTR) MAKEINTRESOURCE(IDD_SHUTDOWN_DLG),
			NULL,
			ShutdownDlgProc,
			NULL
			);
		
		if(l_i_Result == WLX_SAS_ACTION_NONE)
		{
			::ShowWindow(hDlg,SW_SHOWNORMAL);
			::CenterWindow(hDlg);
		}
		else
			::EndDialog(hDlg, l_i_Result);
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
	
	return(TRUE);
}

/*****************************ShutdownDlgProc********************************/
//DLL HWND Callback, this fuction Handle the ShutDown Options.
/****************************************************************************/
INT CALLBACK ShutdownDlgProc
(
 HWND		 hDlg,
 UINT		 Message,
 WPARAM 	 wParam,
 LPARAM 	 lParam
 )
{
	__try
	{
		switch (Message)
		{
		case WM_INITDIALOG:
			{
				CenterWindow(hDlg);
				::CheckDlgButton(hDlg,IDC_CONFIRM_LOGOFF, BST_CHECKED);
				return(TRUE);
			}
			
		case WM_COMMAND:
			{
				if (LOWORD(wParam) == IDC_OK)
				{
					if(::IsDlgButtonChecked(hDlg,IDC_CONFIRM_LOGOFF) == BST_CHECKED)
						::EndDialog(hDlg, WLX_SAS_ACTION_LOGOFF);
					else if(::IsDlgButtonChecked(hDlg,IDC_CONFIRM_SHUTDOWN) == BST_CHECKED)
						::EndDialog(hDlg, WLX_SAS_ACTION_SHUTDOWN);
					else
						::EndDialog(hDlg, WLX_SAS_ACTION_SHUTDOWN_REBOOT);	
				}
				else if(LOWORD(wParam) == IDC_CANCEL)
					::EndDialog(hDlg, WLX_SAS_ACTION_NONE);
				else{}
				return(TRUE);
			}
			
		default:
			return(FALSE);
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		return FALSE;
	}
}

/*************************OptionsDlgChangePassword***************************/
//DLL HWND Dialog, this fuction Create the dialof for ChangePassWord.
/****************************************************************************/
INT OptionsDlgChangePassword
(
 HWND hDlg
 )
{
	PGlobals	l_p_Globals = NULL;
	INT 		l_i_Result	= 0;
	
	__try
	{
		::ShowWindow(hDlg,SW_HIDE);
		
		l_p_Globals = (PGlobals)GetWindowLong(hDlg,GWL_USERDATA);
		
		l_i_Result = l_p_Globals->m_p_WlxFuncs->WlxDialogBoxParam
			( 
			l_p_Globals->m_h_GlobalWlx,
			l_p_Globals->m_h_DllInstance,
			(LPTSTR) MAKEINTRESOURCE(IDD_CHANGEPWD_DLG),
			NULL,
			ChangePasswordDlgProc,
			(LPARAM)l_p_Globals
			);
		
		::ShowWindow(hDlg,SW_SHOWNORMAL);
		
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
	return(TRUE);
}

/****************************ChangePasswordProc******************************/
//DLL HWND Callback, this fuction Handle the Change PassWord. 
/****************************************************************************/
INT CALLBACK ChangePasswordDlgProc
(
 HWND		 hDlg,
 UINT		 Message,
 WPARAM 	 wParam,
 LPARAM 	 lParam
 )
{
	__try
	{
		switch (Message)
		{
		case WM_INITDIALOG:
			return ChangePasswordDlgInit(hDlg,lParam);
		case WM_COMMAND:
			{
				if (LOWORD(wParam) == IDC_OK)
				{
					if(TryToChangePassword(hDlg))
						::EndDialog(hDlg, 0);
				}
				else if(LOWORD(wParam) == IDC_CANCEL)
					::EndDialog(hDlg, 0);
				else{}
				return(TRUE);
			}
		default:
			return(FALSE);
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		return FALSE;
	}
}

/*************************ChangePasswordDlgInit******************************/
//DLL HWND Callback, this fuction Handle the Initialization. 
/****************************************************************************/
INT ChangePasswordDlgInit
(
 HWND hDlg,
 LPARAM lParam
 )
{
	
	LPWSTR		*l_puc_TrustList	= NULL;  
	DWORD		l_dw_TrustCount 	= 0;	
	PGlobals	l_p_Globals 		= NULL;
	INT 		l_i_Selection		= 0;
	
	__try
	{
		l_p_Globals = (PGlobals) lParam;
		
		CenterWindow(hDlg);
		
		::SetWindowLong(hDlg,GWL_USERDATA,(LONG)lParam);
		
		::SendMessage(GetDlgItem(hDlg, IDC_OLDPASSWORD), EM_SETPASSWORDCHAR,'*', 0);
		::SendMessage(GetDlgItem(hDlg, IDC_NEWPASSWORD), EM_SETPASSWORDCHAR,'*', 0);

		::SendMessage(GetDlgItem(hDlg, IDC_USERNAME), EM_LIMITTEXT, VI_USERLOGON_MAX-1, 0);
		::SendMessage(GetDlgItem(hDlg, IDC_OLDPASSWORD), EM_LIMITTEXT, VI_USERPASSW_MAX-1, 0);
		::SendMessage(GetDlgItem(hDlg, IDC_NEWPASSWORD), EM_LIMITTEXT, VI_USERPASSW_MAX-1, 0);
		::SendMessage(GetDlgItem(hDlg, IDC_DOMAINNAME), EM_LIMITTEXT, VI_USERDOMAIN_MAX-1, 0);
		
		::SetDlgItemText(hDlg,IDC_USERNAME,l_p_Globals->m_T_LogonData.m_pwc_UserLogin);
		
		l_dw_TrustCount = 0;
		l_puc_TrustList = (LPWSTR *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY ,DOMAIN_MAX_COUNT * sizeof(LPWSTR));
		
		if(BuildTrustList(&l_puc_TrustList, &l_dw_TrustCount))
		{
			if (l_dw_TrustCount)
			{
				for(INT i = 0 ; i < (INT)l_dw_TrustCount ; i++)
				{
					if (memcmp(l_puc_TrustList[i], l_p_Globals->m_T_LogonData.m_pwc_UserDomain,wcslen(l_puc_TrustList[i])*sizeof(WCHAR)) != 0)
						::SendMessage(GetDlgItem(hDlg, IDC_DOMAINNAME), CB_INSERTSTRING, -1, (LPARAM) l_puc_TrustList[i]);	
				}
			}
		}
		
		::SendMessage(GetDlgItem(hDlg, IDC_DOMAINNAME), CB_INSERTSTRING, -1, (LPARAM) l_p_Globals->m_T_LogonData.m_pwc_UserDomain);  
		l_i_Selection = ::SendMessage(GetDlgItem(hDlg, IDC_DOMAINNAME), CB_GETCOUNT, 0, 0);  
		::SendMessage(GetDlgItem(hDlg, IDC_DOMAINNAME), CB_SETCURSEL,l_i_Selection-1,0);  
		
		for(INT i = 0; i < (INT)l_dw_TrustCount; i++) 
		{
			if(l_puc_TrustList[i] != NULL)
				HeapFree(GetProcessHeap(), 0, l_puc_TrustList[i]);
		}
		
		HeapFree(GetProcessHeap(), 0, l_puc_TrustList); 	
		
		::SetFocus(GetDlgItem(hDlg, IDC_OLDPASSWORD));	
		
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
	
	return(TRUE);
}

/*************************TryToChangePassword********************************/
//DLL HWND Callback, this fuction Handle Changing the PassWord. 
/****************************************************************************/
BOOL TryToChangePassword
(
 HWND hDlg
 )
{
	PTSTR			l_puc_Username			= NULL;
	PTSTR			l_puc_Domain			= NULL;
	PTSTR			l_puc_OldPass			= NULL;
	PTSTR			l_puc_NewPass			= NULL;
	NET_API_STATUS	NetStatus				= 0;	
	PGlobals		l_p_Globals 			= NULL;
	
	__try
	{
		l_p_Globals = (PGlobals)GetWindowLong(hDlg,GWL_USERDATA);
		
		l_puc_Username = AllocAndCaptureText(hDlg, IDC_USERNAME);
		l_puc_Domain = AllocAndCaptureText(hDlg, IDC_DOMAINNAME);
		l_puc_OldPass = AllocAndCaptureText(hDlg, IDC_OLDPASSWORD);
		l_puc_NewPass = AllocAndCaptureText(hDlg, IDC_NEWPASSWORD);
		
		if (!l_puc_Username || !l_puc_Domain || !l_puc_OldPass || !l_puc_NewPass)
			goto clean_exit;
		
		NetStatus = NetUserChangePassword(l_puc_Domain, l_puc_Username, l_puc_OldPass, l_puc_NewPass);
		
		if(NetStatus == NERR_Success)
		{
			if(memcmp(l_puc_Username,l_p_Globals->m_T_LogonData.m_pwc_UserLogin,wcslen(l_puc_Username)*sizeof(WCHAR)) == 0 &&\
				memcmp(l_puc_Domain,l_p_Globals->m_T_LogonData.m_pwc_UserDomain,wcslen(l_puc_Domain)*sizeof(WCHAR)) == 0)
			{
				memset(l_p_Globals->m_T_LogonData.m_pwc_UserPassW,0,sizeof(l_p_Globals->m_T_LogonData.m_pwc_UserPassW));
				memcpy(l_p_Globals->m_T_LogonData.m_pwc_UserPassW,l_puc_NewPass,wcslen(l_puc_NewPass)*sizeof(WCHAR));
				::SetWindowLong(hDlg,GWL_USERDATA,(LONG)l_p_Globals);
			}
			::MessageBox(hDlg, _T(VC_CHANGPASS_OK),\
				_T(VC_CHANGPASS_TITLE), MB_ICONINFORMATION | MB_OK);
		}
		else
		{
			if (NetStatus == ERROR_ACCESS_DENIED)
			{
				::MessageBox(hDlg, _T(VC_CHANGPASS_ACCESS),
					_T(VC_CHANGPASS_TITLE), MB_ICONSTOP | MB_OK);
			}
			else if(NetStatus == ERROR_INVALID_PASSWORD)
			{
				::MessageBox(hDlg, _T(VC_CHANGPASS_INVALIDPASS),
					_T(VC_CHANGPASS_TITLE), MB_ICONSTOP | MB_OK);
			}
			else if(NetStatus == NERR_InvalidComputer)
			{
				::MessageBox(hDlg, _T(VC_CHANGPASS_INVALIDDOMAIN),
					_T(VC_CHANGPASS_TITLE), MB_ICONSTOP | MB_OK);
			}
			else if(NetStatus == NERR_NotPrimary)
			{
				::MessageBox(hDlg, _T(VC_CHANGPASS_NOUSER),
					_T(VC_CHANGPASS_TITLE), MB_ICONSTOP | MB_OK);
			}
			else if(NetStatus == NERR_UserNotFound)
			{
				MessageBox(hDlg, _T(VC_CHANGPASS_NOUSER),
					_T(VC_CHANGPASS_TITLE), MB_ICONSTOP | MB_OK);
			}
			else if(NetStatus == NERR_PasswordTooShort )
			{
				::MessageBox(hDlg, _T(VC_CHANGPASS_PASSSHORT),
					_T(VC_CHANGPASS_TITLE), MB_ICONSTOP | MB_OK);
			}
			else
			{
				::MessageBox(hDlg, _T(VC_CHANGPASS_ERR),
					_T(VC_CHANGPASS_TITLE), MB_ICONINFORMATION | MB_OK);		
			}
		}
		
clean_exit:
		if (l_puc_Username)
			LocalFree(l_puc_Username);
		if (l_puc_Domain)
			LocalFree(l_puc_Domain);
		if (l_puc_OldPass)
			LocalFree(l_puc_OldPass);
		if (l_puc_NewPass)
			LocalFree(l_puc_NewPass);
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
	
	return(NetStatus == NERR_Success);
}
