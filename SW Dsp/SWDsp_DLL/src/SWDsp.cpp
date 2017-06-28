/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWDsp.cpp													 //
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




#include "stdafx.h"

#pragma hdrstop
TSharedMemory	*g_T_SharedMemory	= NULL;
TLocalMemory	g_T_LocalMemory 	= {NULL};
HANDLE			g_h_MapFile 		= NULL;

/********************************DllMain*************************************/
//DLL EntryPoint, this fuction 
//Provide the instance of resources.
/****************************************************************************/
extern "C" BOOL WINAPI DllMain
(
 HINSTANCE hInstance, 
 DWORD dwReason, 
 LPVOID
 )
{
	switch(dwReason)
	{
	case DLL_PROCESS_ATTACH:
		{
			DisableThreadLibraryCalls(hInstance);
			AllocAndStoreDllData();
			break;
		}
	case DLL_PROCESS_DETACH:
		{
			FreeAndCloseDllData();
			break;
		}
	default:
		break;
	}
	return(TRUE);
}

/****************************AllocAndStoreDllData******************************/
//DLL LocalEntryPoint, this fuction 
//Get the shared memory handle.
/*****************************************************************************/
VOID AllocAndStoreDllData
(
 VOID
 )
{	
	PSECURITY_DESCRIPTOR	l_p_pSD 			= NULL;
	SECURITY_ATTRIBUTES 	l_T_sa				= {0};
	
	l_p_pSD = (PSECURITY_DESCRIPTOR) malloc( SECURITY_DESCRIPTOR_MIN_LENGTH );
	
	if (l_p_pSD == NULL)
		return;
	
	if (!InitializeSecurityDescriptor(l_p_pSD, SECURITY_DESCRIPTOR_REVISION))
	{
		free(l_p_pSD);
		return;
	}
	
	// add a NULL disc. ACL to the security descriptor.
	if (!SetSecurityDescriptorDacl(l_p_pSD, TRUE, (PACL) NULL, FALSE))
	{
		free(l_p_pSD);
		return;
	}
	
	l_T_sa.nLength = sizeof(l_T_sa);
	l_T_sa.lpSecurityDescriptor = l_p_pSD;
	l_T_sa.bInheritHandle = FALSE;
	
	g_h_MapFile 		= ::CreateFileMapping((HANDLE)0xFFFFFFFF,&l_T_sa,PAGE_READWRITE,0,sizeof(TSharedMemory),_T(VC_DSPSHAREDMEMORY));
	g_T_SharedMemory	= (TSharedMemory *)MapViewOfFile(g_h_MapFile,FILE_MAP_ALL_ACCESS,0,0,sizeof(TSharedMemory));
	
	g_T_LocalMemory.m_h_LogonIdent		= CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_LOGONDSPIDENTOK));
	g_T_LocalMemory.m_h_AccessIdent 	= CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_ACCESSDSPIDENTOK));
	g_T_LocalMemory.m_h_DataIdent		= CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_DATADSPIDENTOK));
	g_T_LocalMemory.m_h_AdminIdent		= CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_ADMINDSPIDENTOK));
	g_T_LocalMemory.m_h_AdminEnroll 	= CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_ADMINDSPENROLLOK));
	g_T_LocalMemory.m_h_AdminUser		= CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_ADMINDSPUSEROK));
	g_T_LocalMemory.m_h_SWOn			= CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_ADMINDSPSWONOK));
	g_T_LocalMemory.m_h_SWOff			= CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_ADMINDSPSWOFFOK));
	g_T_LocalMemory.m_h_AdminDb 		= CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_ADMINDSPDBOK));
	g_T_LocalMemory.m_h_AccessUpdate	= CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_ACCESSSDSPUPDATEOK));
	g_T_LocalMemory.m_h_AdminUpdate 	= CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_ADMINDSPUPDATEOK));
	g_T_LocalMemory.m_h_WaitAdminUser	= CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_WAITDSPADMINUSEROK));
	g_T_LocalMemory.m_h_WaitAdminDb 	= CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_WAITDSPADMINDBOK));
	g_T_LocalMemory.m_h_WaitUpdateAccess= CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_WAITDSPACCESSUPDATEOK));
	g_T_LocalMemory.m_h_WaitUpdateAdmin = CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_WAITDSPADMINUPDATEOK));
	g_T_LocalMemory.m_h_WaitCancel		= CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_WAITDSPCANCELOK));
	g_T_LocalMemory.m_h_WaitPaint		= CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_WAITDSPPAINTOK)); 
	g_T_LocalMemory.m_h_WaitOn			= CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_WAITDSPSWONOK));
	g_T_LocalMemory.m_h_WaitOff 		= CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_WAITDSPSWOFFOK));
	g_T_LocalMemory.m_h_WaitIdent		= CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_WAITDSPIDENTOK));
	g_T_LocalMemory.m_h_WaitEnroll		= CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_WAITDSPENROLLOK));
	g_T_LocalMemory.m_h_HostExitEvent	= CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_HOSTEXIT_NAME));  
	g_T_LocalMemory.m_h_HostExitEventKo = CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_HOSTEXITKO_NAME));  
	g_T_LocalMemory.m_h_ExistSW 		= CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_EXITDSPSWOK));	
	
	free(l_p_pSD);
}

/****************************FreeAndCloseDllData******************************/
//DLL LocalEntryPoint, this fuction 
//Free the shared memory and close it's handle.
/*****************************************************************************/
VOID FreeAndCloseDllData
(
 VOID
 )
{	
	if(g_T_SharedMemory != NULL)
		::UnmapViewOfFile(g_T_SharedMemory);
	if(g_h_MapFile != NULL)
		::CloseHandle(g_h_MapFile);
}

/****************************WlxIsSWValid******************************/
//DLL LocalEntryPoint, this fuction 
//Test Context for modules.
/*****************************************************************************/
BOOL WlxIsSWValid
(
 VOID
 )
{
	__try
	{
		return !(((g_T_SharedMemory->m_T_SWState.m_T_DbState != MSO_DB_OK) && (g_T_SharedMemory->m_T_SWState.m_T_DbState != MSO_DB_FULL)) || 
			(g_T_SharedMemory->m_T_SWState.m_T_ComState != MSO_COM_OK));
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		return FALSE;
	}
}

/******************************WlxIsDspLoaded**********************************/
//DLL LocalEntryPoint, this fuction 
//Find out if the Dsp was made on.
/*****************************************************************************/
BOOL WlxIsDspLoaded
(
 VOID
 )
{
	HANDLE					l_h_HostMutex				= NULL;
	DWORD					l_dw_LastEror				= 0;
	BOOL					l_b_Process 				= 0;
	PSECURITY_DESCRIPTOR	l_p_pSD 					= NULL;
	SECURITY_ATTRIBUTES 	l_T_sa						= {0};
	LPTSTR					l_psz_CurrentVariable		= NULL; 
	LPTSTR					l_psz_tchNewEnv 			= NULL; 
	PROCESS_INFORMATION 	l_pi_ProcInfo				= {0}; 
	STARTUPINFO 			l_si_StartInfo				= {0}; 
	WCHAR					l_pwc_System32[MAX_PATH]	= {0};
	WCHAR					l_pwc_HostPath[MAX_PATH+20]	= {0};
	
	__try
	{	
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
		
		l_h_HostMutex = CreateMutex
			(
			(LPSECURITY_ATTRIBUTES)&l_T_sa,
			(BOOL)TRUE,
			(LPCTSTR)_T(VC_HOSTMUTEX_NAME)	
			);
		
		l_dw_LastEror = GetLastError ();
		
		//If cannot create Mutex, exit.
		if (l_h_HostMutex == NULL)
		{
			free(l_p_pSD);
			return FALSE;
		}
		
		ReleaseMutex(l_h_HostMutex);
		CloseHandle(l_h_HostMutex);
		
		//If Mutex already existed, exit.
		if (l_dw_LastEror == ERROR_ALREADY_EXISTS)
		{
			free(l_p_pSD);
			return(TRUE);
		}
		else
		{			
			l_T_sa.nLength = sizeof(l_T_sa);
			l_T_sa.lpSecurityDescriptor = l_p_pSD;
			l_T_sa.bInheritHandle = TRUE;
			
			ZeroMemory( &l_si_StartInfo, sizeof(STARTUPINFO) );
			l_si_StartInfo.cb = sizeof(STARTUPINFO); 
			
			l_psz_tchNewEnv = (LPTSTR)malloc(200);
			memset(l_psz_tchNewEnv,0,200);
			l_psz_CurrentVariable = l_psz_tchNewEnv;
			lstrcpy(l_psz_CurrentVariable, L"OperatingSystem=Windows");
			
			l_psz_CurrentVariable += lstrlen(l_psz_CurrentVariable) + 1; 
			lstrcpy(l_psz_CurrentVariable, L"API=Win32"); 
			l_psz_CurrentVariable += lstrlen(l_psz_CurrentVariable) + 1; 
			*l_psz_CurrentVariable = '\0'; 
						
			GetWindowsDirectory(l_pwc_System32,MAX_PATH);
			
			wsprintf(l_pwc_HostPath,L"%s\\system32\\",l_pwc_System32);
			
			SetCurrentDirectory(l_pwc_HostPath);
			
			l_b_Process = CreateProcess
				(
				_T(VC_HOSTSERVICE_NAME),
				GetCommandLine(),
				&l_T_sa,
				&l_T_sa,
				TRUE,
				CREATE_UNICODE_ENVIRONMENT|HIGH_PRIORITY_CLASS,
				l_psz_tchNewEnv,
				NULL,
				&l_si_StartInfo,
				&l_pi_ProcInfo
				);
			free(l_p_pSD);
			free(l_psz_tchNewEnv);
			WaitForSingleObject(g_T_LocalMemory.m_h_SWOn,3*VI_TIMEOUT); 
		}
		
		return(g_T_SharedMemory->m_i_DataCreateOrNo == VI_DATACREATED_INDEC);
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		return FALSE;
	}
}

/******************************WlxSWReboot************************************/
//DLL EntryPoint, this fuction 
//Provide the reboot off the context.
/*****************************************************************************/
VOID WlxSWReboot
(
 TSWState &o_T_SWState
 )
{
	HANDLE					l_h_HostMutex				= NULL;
	DWORD					l_dw_LastEror				= 0;
	BOOL					l_b_Process 				= 0;
	PSECURITY_DESCRIPTOR	l_p_pSD 					= NULL;
	SECURITY_ATTRIBUTES 	l_T_sa						= {0};
	LPTSTR					l_psz_CurrentVariable		= NULL; 
	LPTSTR					l_psz_tchNewEnv 			= NULL; 
	PROCESS_INFORMATION 	l_pi_ProcInfo				= {0}; 
	STARTUPINFO 			l_si_StartInfo				= {0}; 
	DWORD					l_dw_Result 				= 0;
	WCHAR					l_pwc_System32[MAX_PATH]	= {0};
	WCHAR					l_pwc_HostPath[MAX_PATH+20]	= {0};

	__try
	{	
		if(g_T_LocalMemory.m_b_RebootOk)
		{
			l_dw_Result = WaitForSingleObject(g_T_LocalMemory.m_h_SWOn,6*VI_TIMEOUT); 
			if(l_dw_Result != WAIT_OBJECT_0)
			{
				o_T_SWState.m_T_ComState = MSO_COM_ERR;
				o_T_SWState.m_T_DbState = MSO_DB_ERR;
			}
			else
			{
				o_T_SWState.m_T_ComState = g_T_SharedMemory->m_T_SWState.m_T_ComState;
				o_T_SWState.m_T_DbState = g_T_SharedMemory->m_T_SWState.m_T_DbState;
			}
			return;
		}
		else
		{
			g_T_LocalMemory.m_b_RebootOk = TRUE;
			l_p_pSD = (PSECURITY_DESCRIPTOR) malloc(SECURITY_DESCRIPTOR_MIN_LENGTH);
			
			if (l_p_pSD == NULL)
			{
				g_T_LocalMemory.m_b_RebootOk = FALSE;
				return;
			}
			
			if (!InitializeSecurityDescriptor(l_p_pSD,SECURITY_DESCRIPTOR_REVISION))
			{
				free(l_p_pSD);
				g_T_LocalMemory.m_b_RebootOk = FALSE;
				return;
			}
			
			// add a NULL disc. ACL to the security descriptor.
			if (!SetSecurityDescriptorDacl(l_p_pSD, TRUE, (PACL) NULL, FALSE))
			{
				free(l_p_pSD);
				g_T_LocalMemory.m_b_RebootOk = FALSE;
				return;
			}
			
			l_T_sa.nLength = sizeof(l_T_sa);
			l_T_sa.lpSecurityDescriptor = l_p_pSD;
			l_T_sa.bInheritHandle = FALSE;

			l_h_HostMutex = CreateMutex
				(
				(LPSECURITY_ATTRIBUTES)&l_T_sa,
				(BOOL)TRUE,
				(LPCTSTR)_T(VC_HOSTMUTEX_NAME)	
				);
			
			l_dw_LastEror = GetLastError ();
			
			//If cannot create Mutex, exit.
			if (l_h_HostMutex == NULL)
				return;
			
			ReleaseMutex(l_h_HostMutex);
			CloseHandle(l_h_HostMutex);
			
			//If Mutex already existed, exit.
			if (l_dw_LastEror == ERROR_ALREADY_EXISTS)
			{
				SetEvent(g_T_LocalMemory.m_h_WaitCancel);
				SetEvent(g_T_LocalMemory.m_h_HostExitEvent);
				l_dw_Result = WaitForSingleObject(g_T_LocalMemory.m_h_HostExitEventKo,6*VI_TIMEOUT); 
			}
			
			ZeroMemory( &l_si_StartInfo, sizeof(STARTUPINFO) );
			l_si_StartInfo.cb = sizeof(STARTUPINFO); 
			
			l_psz_tchNewEnv = (LPTSTR)malloc(200);
			memset(l_psz_tchNewEnv,0,200);
			l_psz_CurrentVariable = l_psz_tchNewEnv;
			lstrcpy(l_psz_CurrentVariable, L"OperatingSystem=Windows");
			
			l_psz_CurrentVariable += lstrlen(l_psz_CurrentVariable) + 1; 
			lstrcpy(l_psz_CurrentVariable, L"API=Win32"); 
			l_psz_CurrentVariable += lstrlen(l_psz_CurrentVariable) + 1; 
			*l_psz_CurrentVariable = '\0'; 
			
			GetWindowsDirectory(l_pwc_System32,MAX_PATH);
			
			wsprintf(l_pwc_HostPath,L"%s\\system32\\",l_pwc_System32);
			
			SetCurrentDirectory(l_pwc_HostPath);

			l_b_Process = CreateProcess
				(
				_T(VC_HOSTSERVICE_NAME),
				GetCommandLine(),
				&l_T_sa,
				&l_T_sa,
				TRUE,
				CREATE_UNICODE_ENVIRONMENT|HIGH_PRIORITY_CLASS,
				l_psz_tchNewEnv,
				NULL,
				&l_si_StartInfo,
				&l_pi_ProcInfo
				);
			free(l_p_pSD);
			free(l_psz_tchNewEnv);
			l_dw_Result = WaitForSingleObject(g_T_LocalMemory.m_h_SWOn,12*VI_TIMEOUT); 
			if(l_dw_Result != WAIT_OBJECT_0)
			{
				o_T_SWState.m_T_ComState = MSO_COM_ERR;
				o_T_SWState.m_T_DbState = MSO_DB_ERR;
			}
			else
			{
				o_T_SWState.m_T_ComState = g_T_SharedMemory->m_T_SWState.m_T_ComState;
				o_T_SWState.m_T_DbState = g_T_SharedMemory->m_T_SWState.m_T_DbState;
			}
			g_T_LocalMemory.m_b_RebootOk = FALSE;
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

/******************************WlxIsSWLock*********************************/
//DLL LocalEntryPoint, this fuction 
//Find out if the service provider was been locked.
/*****************************************************************************/
BOOL WlxIsSWLock
(
 VOID
 )
{
	__try
	{
		return g_T_SharedMemory->m_b_LockSW;
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		return FALSE;
	}
}

/*****************************WlxSWShoutDown**********************************/
//DLL EntryPoint, this fuction 
//Provide the clear up for shutdown.
/*****************************************************************************/
VOID WlxSWShutDown
(
 VOID
 )
{
	__try
	{
		SetEvent(g_T_LocalMemory.m_h_HostExitEvent);
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

/******************************WlxSWReboot************************************/
//DLL EntryPoint, this fuction 
//Provide the start on of the context.
/*****************************************************************************/
VOID WlxSWOn
(
 TSWState &o_T_SWState
 )
{
	DWORD	l_dw_Result;
	
	__try
	{
		SetEvent(g_T_LocalMemory.m_h_WaitOn);
		l_dw_Result = WaitForSingleObject(g_T_LocalMemory.m_h_SWOn,VI_TIMEOUT);
		if(l_dw_Result != WAIT_OBJECT_0)
		{
			l_dw_Result = WaitForSingleObject(g_T_LocalMemory.m_h_SWOn,3*VI_TIMEOUT);
			if(l_dw_Result != WAIT_OBJECT_0)
			{
				o_T_SWState.m_T_ComState = MSO_COM_ERR;
				o_T_SWState.m_T_DbState = MSO_DB_ERR;
			}
			else
			{
				o_T_SWState.m_T_ComState = g_T_SharedMemory->m_T_SWState.m_T_ComState;
				o_T_SWState.m_T_DbState = g_T_SharedMemory->m_T_SWState.m_T_DbState;
			}
		}
		else
		{
			o_T_SWState.m_T_ComState = g_T_SharedMemory->m_T_SWState.m_T_ComState;
			o_T_SWState.m_T_DbState = g_T_SharedMemory->m_T_SWState.m_T_DbState;
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

/******************************WlxSWReboot************************************/
//DLL EntryPoint, this fuction 
//Provide the start off of the context.
/*****************************************************************************/
VOID WlxSWOff
(
 VOID
 )
{
	DWORD	l_dw_Result;
	
	__try
	{
		SetEvent(g_T_LocalMemory.m_h_WaitOff);
		l_dw_Result = WaitForSingleObject(g_T_LocalMemory.m_h_SWOff,VI_TIMEOUT);
		
		if(l_dw_Result != WAIT_OBJECT_0)
			l_dw_Result = WaitForSingleObject(g_T_LocalMemory.m_h_SWOff,3*VI_TIMEOUT);
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}
