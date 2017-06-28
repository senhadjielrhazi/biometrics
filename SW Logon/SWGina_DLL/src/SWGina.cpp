/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWGina.cpp													 //
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

#pragma hdrstop
MiniMemory					g_T_MiniMemory;

/********************************DllMain*************************************/
//DLL EntryPoint, this fuction 
//Provide the instance of resources.
/****************************************************************************/
BOOL WINAPI DllMain
(
 HINSTANCE hInstance,
 DWORD dwReason,
 LPVOID lpReserved
 )
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls ( hInstance );
		g_T_MiniMemory.m_h_DllInstance = hInstance;
	case DLL_PROCESS_DETACH:
	default:
		return(TRUE);
	}
}

/******************************WlxNegotiate**********************************/
//DLL WinLogon Entry, this fuction 
//Negotiate version of interface with Winlogon.
/****************************************************************************/
BOOL WINAPI WlxNegotiate
(
 DWORD dwWinlogonVersion,
 DWORD *pdwDllVersion
 )
{
	__try
	{
		if (dwWinlogonVersion < WLX_CURRENT_VERSION)
			return(FALSE);
		
		*pdwDllVersion = WLX_CURRENT_VERSION;
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		return FALSE;
	}	
	return(TRUE);	
}

/******************************WlxInitialize*********************************/
//DLL WinLogon Entry, this fuction 
//Initialize entrypoint from winlogon.
/****************************************************************************/
BOOL WINAPI WlxInitialize
(
 LPWSTR 				 lpWinsta,
 HANDLE 				 hWlx,
 PVOID					 pvReserved,
 PVOID					 pWinlogonFunctions,
 PVOID					 *pWlxContext
 )
{
	PGlobals				l_p_Globals 			= NULL;
	PSECURITY_DESCRIPTOR	l_p_pSD 				= NULL;
	SECURITY_ATTRIBUTES 	l_T_sa					= {0};
	
	__try
	{
		l_p_Globals  = (PGlobals)LocalAlloc(LMEM_FIXED | LMEM_ZEROINIT, sizeof(Globals));
		memset(l_p_Globals,0,sizeof(Globals));
		
		*pWlxContext = (PVOID) l_p_Globals;
		
		l_p_Globals->m_p_WlxFuncs	 = (PWLX_DISPATCH_VERSION_1_0) pWinlogonFunctions;
		l_p_Globals->m_h_GlobalWlx	 = hWlx;
		l_p_Globals->m_h_DllInstance = g_T_MiniMemory.m_h_DllInstance;
		
		l_p_Globals->m_p_WlxFuncs->WlxUseCtrlAltDel(hWlx);	
		
		g_T_MiniMemory.m_b_Progress	= FALSE;

		InitCommonControls();
		
		l_p_pSD = (PSECURITY_DESCRIPTOR) malloc( SECURITY_DESCRIPTOR_MIN_LENGTH );
		
		if (l_p_pSD == NULL)
		{
			l_p_Globals->m_h_LogonMutex = NULL;
			return FALSE;
		}
		
		if (!InitializeSecurityDescriptor(l_p_pSD, SECURITY_DESCRIPTOR_REVISION))
		{
			l_p_Globals->m_h_LogonMutex = NULL;
			free(l_p_pSD);
			return FALSE;
		}
		
		// add a NULL disc. ACL to the security descriptor.
		if (!SetSecurityDescriptorDacl(l_p_pSD, TRUE, (PACL) NULL, FALSE))
		{
			l_p_Globals->m_h_LogonMutex = NULL;
			free(l_p_pSD);
			return FALSE;
		}
		
		l_T_sa.nLength = sizeof(l_T_sa);
		l_T_sa.lpSecurityDescriptor = l_p_pSD;
		l_T_sa.bInheritHandle = FALSE;
		
		l_p_Globals->m_h_LogonMutex = CreateMutex
			(
			(LPSECURITY_ATTRIBUTES)&l_T_sa,
			(BOOL)TRUE, 
			(LPCTSTR)_T(VC_LOGONMUTEX_NAME)
			);

		l_p_Globals->m_x_Registry.C_Registry_GetLastUserDomain(l_p_Globals->m_T_LogonData.m_pwc_UserLogin,l_p_Globals->m_T_LogonData.m_pwc_UserDomain);

		free(l_p_pSD);
		if(l_p_Globals->m_h_LogonMutex	== NULL)
			return FALSE;
		
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		return FALSE;
	}
	return(TRUE);
}

/*****************************WlxDisplaySASNotice****************************/
//DLL WinLogon Entry, this fuction 
//Where we display the welcome, we're waiting dialog box.
/****************************************************************************/
VOID WINAPI WlxDisplaySASNotice
(
 PVOID pContext
 )
{
	TSWState	l_T_SWState;
	INT 		l_i_Result	= 0;
	PGlobals	l_p_Globals = NULL;
	
	__try
	{
		if(!WlxIsSWValid())
		{
			if(WlxIsSWLock())
				Sleep(100);
			else
				WlxSWReboot(l_T_SWState);
		}
		
		l_p_Globals = (PGlobals) pContext;
		l_p_Globals->m_i_UserTypeLogon = WLX_SAS_TYPE_CTRL_ALT_DEL;
		l_p_Globals->m_i_Progress = 0;
		WlxLogonIdentOff();
		
		l_i_Result = l_p_Globals->m_p_WlxFuncs->WlxDialogBoxParam
			(
			l_p_Globals->m_h_GlobalWlx,
			l_p_Globals->m_h_DllInstance,
			(LPTSTR) MAKEINTRESOURCE(IDD_BIOLOGON_DLG),
			NULL,
			BioLogonDlgProc,
			(LPARAM)l_p_Globals 
			);
		
		WlxLogonIdentOff();
		l_p_Globals->m_i_Progress = 0;
		l_p_Globals->m_p_WlxFuncs->WlxSasNotify(l_p_Globals->m_h_GlobalWlx,WLX_SAS_TYPE_CTRL_ALT_DEL);
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

/******************************WlxLoggedOutSAS********************************/
//DLL WinLogon Entry, this fuction 
//Called when no one logged on.
/****************************************************************************/
INT WINAPI WlxLoggedOutSAS
(
 PVOID					 pWlxContext,
 DWORD					 dwSasType,
 PLUID					 pAuthenticationId,
 PSID					 pLogonSid,
 PDWORD 				 pdwOptions,
 PHANDLE				 phToken,
 PWLX_MPR_NOTIFY_INFO	 pMprNotifyInfo,
 PVOID *				 pProfile
 )
{ 
	INT 		l_i_Result			= 0;
	PGlobals	l_p_Globals			= NULL;
	INT			l_i_LoopProgress	= 0;
	
	__try
	{
		l_p_Globals = (PGlobals) pWlxContext;

		while(g_T_MiniMemory.m_b_Progress && l_i_LoopProgress<80)
		{
			l_i_LoopProgress++;
			Sleep(10);
		}
		WlxLogonIdentOff();
		while(!g_T_MiniMemory.m_b_Progress && l_i_LoopProgress<100)
		{
			l_i_LoopProgress++;
			Sleep(15);
		}
				
		l_p_Globals->m_x_Registry.C_Registry_GetLastUserDomain(l_p_Globals->m_T_LogonData.m_pwc_UserLogin,l_p_Globals->m_T_LogonData.m_pwc_UserDomain);
	
		switch(l_p_Globals->m_i_UserTypeLogon)
		{
		case WLX_SAS_TYPE_CTRL_ALT_DEL :
			{
				l_i_Result = l_p_Globals->m_p_WlxFuncs->WlxDialogBoxParam
					(
					l_p_Globals->m_h_GlobalWlx,
					l_p_Globals->m_h_DllInstance,
					(LPTSTR) MAKEINTRESOURCE(IDD_WINLOGON_DLG),
					NULL,
					WinLogonDlgProc,
					(LPARAM)l_p_Globals 
					);
				if (l_i_Result != WLX_SAS_ACTION_LOGON&&l_i_Result != WLX_SAS_ACTION_SHUTDOWN)
					l_i_Result = WLX_SAS_ACTION_NONE;
				break;
			}
		case WLX_SAS_TYPE_BIO_HITOK :
			{
				l_i_Result = WLX_SAS_ACTION_LOGON;
				break;
			}
		case WLX_SAS_TYPE_BIO_HITNO :
			{
				l_i_Result = WLX_SAS_ACTION_NONE;
				break;
			}
		case WLX_SAS_TYPE_BIO_ABORT :
			{
				l_i_Result = WLX_SAS_ACTION_NONE;
				break;
			}
		default :
			{
				l_i_Result = WLX_SAS_ACTION_NONE;
				break;
			}

		}
		
		if (l_i_Result == WLX_SAS_ACTION_LOGON)
		{
			l_i_Result = AttemptLogon(l_p_Globals, pLogonSid, pAuthenticationId);
			
			if (l_i_Result == WLX_SAS_ACTION_LOGON)
			{
				*pdwOptions = 0;
				*phToken = l_p_Globals->m_h_UserToken;
				*pProfile = NULL;
				pMprNotifyInfo->pszUserName = DupString(l_p_Globals->m_T_LogonData.m_pwc_UserLogin);
				pMprNotifyInfo->pszDomain = DupString(l_p_Globals->m_T_LogonData.m_pwc_UserDomain);
				pMprNotifyInfo->pszPassword = DupString(l_p_Globals->m_T_LogonData.m_pwc_UserPassW);
				pMprNotifyInfo->pszOldPassword = NULL;
				
				l_p_Globals->m_x_Registry.C_Registry_SetLastUserDomain(l_p_Globals->m_T_LogonData.m_pwc_UserLogin,l_p_Globals->m_T_LogonData.m_pwc_UserDomain);
			}
		}
		
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		return FALSE;
	}
	return(l_i_Result);
}



/*******************************WlxLoggedOnSAS*******************************/
//DLL WinLogon Entry, this fuction 
//Called when someone hits CAD when we're logged on.
/****************************************************************************/
INT WINAPI WlxLoggedOnSAS
(
 PVOID pWlxContext,
 DWORD dwSasType,
 PVOID pReserved
 )
{
	INT 		l_i_Result	= 0;
	PGlobals	l_p_Globals = NULL;
	
	__try
	{
		l_p_Globals = (PGlobals) pWlxContext;

		if(l_p_Globals->m_b_ScreenSaver)
		{
			l_p_Globals->m_b_ScreenSaver = FALSE;
			return WLX_SAS_ACTION_NONE;
		}

		l_i_Result = l_p_Globals->m_p_WlxFuncs->WlxDialogBoxParam
			( 
			l_p_Globals->m_h_GlobalWlx,
			l_p_Globals->m_h_DllInstance,
			(LPTSTR) MAKEINTRESOURCE(IDD_OPTIONS_DLG),
			NULL,
			OptionsDlgProc,
			(LPARAM) pWlxContext
			);
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		return FALSE;
	}
	return(l_i_Result);
}



/**************************WlxDisplayLockedNotice*****************************/
//DLL WinLogon Entry, this fuction 
//Displays a notice while the workstation is locked.
/****************************************************************************/
VOID WINAPI WlxDisplayLockedNotice
(
 PVOID pWlxContext
 )
{	
	INT 		l_i_Result	= 0;
	PGlobals	l_p_Globals = NULL;
	
	__try
	{
		l_p_Globals = (PGlobals) pWlxContext;	
		l_p_Globals->m_i_UserTypeLogon = WLX_SAS_TYPE_CTRL_ALT_DEL;
		l_p_Globals->m_i_Progress = 0;
		WlxLogonIdentOff();

		l_i_Result = l_p_Globals->m_p_WlxFuncs->WlxDialogBoxParam
			(
			l_p_Globals->m_h_GlobalWlx,
			l_p_Globals->m_h_DllInstance,
			(LPTSTR) MAKEINTRESOURCE(IDD_BIOLOCK_DLG),
			NULL,
			BioLockDlgProc,
			(LPARAM)l_p_Globals 
			);
		
		WlxLogonIdentOff();
		l_p_Globals->m_i_Progress = 0;

		if(l_p_Globals->m_b_ScreenSaver && l_i_Result == WLX_SAS_TYPE_BIO_HITOK)
		l_p_Globals->m_p_WlxFuncs->WlxSasNotify(l_p_Globals->m_h_GlobalWlx,WLX_SAS_TYPE_CTRL_ALT_DEL);
			
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

/****************************WlxWkstaLockedSAS*******************************/
//DLL WinLogon Entry, this fuction 
//Responds during an unlock attempt.
/****************************************************************************/
INT WINAPI WlxWkstaLockedSAS
(
 PVOID	pWlxContext,
 DWORD dwSasType
 )
{
	INT 		l_i_Result			= 0;
	PGlobals	l_p_Globals			= NULL;
	INT			l_i_LoopProgress	= 0;
	
	__try
	{
		l_p_Globals = (PGlobals) pWlxContext;
		
		while(g_T_MiniMemory.m_b_Progress && l_i_LoopProgress<80)
		{
			WlxLogonIdentOff();
			l_i_LoopProgress++;
			Sleep(10);
		}
		WlxLogonIdentOff();
		while(!g_T_MiniMemory.m_b_Progress && l_i_LoopProgress<100)
		{
			WlxLogonIdentOff();
			l_i_LoopProgress++;
			Sleep(15);
		}
		
		switch(l_p_Globals->m_i_UserTypeLogon)
		{
		case WLX_SAS_TYPE_CTRL_ALT_DEL :
			{
				l_i_Result = l_p_Globals->m_p_WlxFuncs->WlxDialogBoxParam
					(
					l_p_Globals->m_h_GlobalWlx,
					l_p_Globals->m_h_DllInstance,
					(LPTSTR) MAKEINTRESOURCE(IDD_WINLOCK_DLG),
					NULL,
					WinLockDlgProc,
					(LPARAM)l_p_Globals
					);
				
				if (l_i_Result != WLX_SAS_ACTION_UNLOCK_WKSTA&&l_i_Result != WLX_SAS_ACTION_FORCE_LOGOFF)
					l_i_Result = WLX_SAS_ACTION_NONE;
				break;
			}
		case WLX_SAS_TYPE_BIO_HITOK :
			{
				l_i_Result = WLX_SAS_ACTION_UNLOCK_WKSTA;
				break;
			}
		case WLX_SAS_TYPE_BIO_HITNO :
			{
				l_i_Result = WLX_SAS_ACTION_NONE;
				break;
			}
		case WLX_SAS_TYPE_BIO_ABORT :
			{
				l_i_Result = WLX_SAS_ACTION_NONE;
				break;
			}
		}
		
		if (l_i_Result == WLX_SAS_ACTION_UNLOCK_WKSTA)
			l_i_Result = AttemptUnlock(l_p_Globals);
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		return FALSE;
	}
	return(l_i_Result);
}

/*********************************WlxShutdown********************************/
//DLL WinLogon Entry, this fuction 
//Called before shutdown so that we can unload/clean up.
//Stop the Waiting for finger if we are in.
/****************************************************************************/
VOID WINAPI WlxShutdown
(
 PVOID pWlxContext,
 DWORD ShutdownType
 )
{
	PGlobals	l_p_Globals = NULL;
	
	__try
	{
		WlxSWShutDown();
		Sleep(600);
		l_p_Globals = (PGlobals) pWlxContext;
		
		if(l_p_Globals->m_h_LogonMutex == NULL)
		{
			ReleaseMutex(l_p_Globals->m_h_LogonMutex);
			CloseHandle(l_p_Globals->m_h_LogonMutex);
		}
		
		l_p_Globals->m_h_UserToken = NULL;
		
		memset(&l_p_Globals->m_T_LogonData,0,sizeof(l_p_Globals->m_T_LogonData));
		memset(l_p_Globals->m_pwc_UserPassW,0,sizeof(l_p_Globals->m_pwc_UserPassW));
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
	return;
}

/****************************WlxActivateUserShell****************************/
//DLL WinLogon Entry, this fuction 
//Activates progman or whatever for the user.
/****************************************************************************/
BOOL WINAPI WlxActivateUserShell
(
 PVOID					 pWlxContext,
 PWSTR					 pszDesktop,
 PWSTR					 pszMprLogonScript,
 PVOID					 pEnvironment
 )
{
	WCHAR				l_puc_UserInitPath[MAX_PATH]	= {0};
	PWSTR				l_puc_PathScan					= NULL;
	STARTUPINFO 		l_T_SiInfo						= {0};
	PROCESS_INFORMATION l_T_PiInfo						= {0};
	PGlobals			l_p_Globals 					= NULL;
	DWORD				l_dw_StartCount 				= 0;
	
	__try
	{
		l_p_Globals = (PGlobals) pWlxContext;
		
		GetProfileString(WINLOGON_APP, USERINIT, USERINIT_DEFAULT, l_puc_UserInitPath, MAX_PATH);
		
		l_dw_StartCount = 0;
		
		l_puc_PathScan = wcstok(l_puc_UserInitPath, _T(","));
		
		while (l_puc_PathScan)
		{
			ZeroMemory(&l_T_SiInfo, sizeof(l_T_SiInfo));
			l_T_SiInfo.cb = sizeof(STARTUPINFO);
			l_T_SiInfo.lpTitle = l_puc_PathScan;
			l_T_SiInfo.dwX = l_T_SiInfo.dwY = l_T_SiInfo.dwXSize = l_T_SiInfo.dwYSize = 0L;
			l_T_SiInfo.dwFlags = STARTF_USEFILLATTRIBUTE;
			l_T_SiInfo.wShowWindow = SW_SHOW;	// at least let the guy see it
			l_T_SiInfo.lpReserved2 = NULL;
			l_T_SiInfo.cbReserved2 = 0;
			l_T_SiInfo.lpDesktop = pszDesktop;
			l_T_SiInfo.dwFillAttribute = BACKGROUND_BLUE;
			
			ImpersonateLoggedOnUser(l_p_Globals->m_h_UserToken);
			
			if (CreateProcessAsUser
				(
				l_p_Globals->m_h_UserToken,
				NULL,
				l_puc_PathScan,
				NULL,
				NULL,
				FALSE,
				CREATE_UNICODE_ENVIRONMENT,
				pEnvironment,
				NULL,
				&l_T_SiInfo,
				&l_T_PiInfo
				))
			{
				
				GetLocalTime(&l_p_Globals->m_T_LogonTime);
				l_dw_StartCount++;
				CloseHandle(l_T_PiInfo.hProcess);
				CloseHandle(l_T_PiInfo.hThread);
			}
			
			RevertToSelf();
			l_puc_PathScan = wcstok(NULL, _T(","));
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		return FALSE;
	}
	return(l_dw_StartCount > 0);
}

/*********************************WlxLogoff**********************************/
//DLL WinLogon Entry, this fuction 
//Called when the user logs off.
/****************************************************************************/
VOID WINAPI WlxLogoff
(
 PVOID	pWlxContext
 )
{
	PGlobals	l_p_Globals = NULL;
	
	__try
	{
		l_p_Globals = (PGlobals) pWlxContext;
				
		l_p_Globals->m_h_UserToken = NULL;
		
		memset(&l_p_Globals->m_T_LogonData,0,sizeof(l_p_Globals->m_T_LogonData));
		memset(l_p_Globals->m_pwc_UserPassW,0,sizeof(l_p_Globals->m_pwc_UserPassW));
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
	return;
}

/******************************WlxIsLogoffOk*********************************/
//DLL WinLogon Entry, this fuction 
//Called to make sure that logoff is ok.
/****************************************************************************/
BOOL WINAPI WlxIsLogoffOk
(
 PVOID	pWlxContext
 )
{
	return(TRUE);
}

/********************************WlxIsLockOk*********************************/
//DLL WinLogon Entry, this fuction 
//Called to make sure that locking is ok.
/****************************************************************************/
BOOL WINAPI WlxIsLockOk
(
 PVOID pWlxContext
 )
{
	return(TRUE);
}

/****************************WlxScreenSaverNotify****************************/
//DLL WinLogon Entry, this fuction 
//is called whenever a screen saver is started. It requests.
//to be secure (ie lock the workstation) or not, and we return whether or not it can
//do that.
/****************************************************************************/
BOOL WINAPI WlxScreenSaverNotify
(
 PVOID pWlxContext,
 BOOL *pfSecure
 )
{
	PGlobals	l_p_Globals = NULL;
	
	__try
	{
		l_p_Globals = (PGlobals) pWlxContext;
		*pfSecure = WlxIsLockOk(pWlxContext);
		l_p_Globals->m_b_ScreenSaver = TRUE;
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		return FALSE;
	}
	
	return(TRUE);
}
