/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWHost.cpp													 //
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
//	SAGEM SA Data Service Provider Service									 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#include "stdafx.h"

THostMemory 	g_T_HostMemory		= {NULL};
TSharedMemory	*g_T_SharedMemory	= NULL;
TLocalMemory	g_T_LocalMemory 	= {NULL};
CWinApp 		g_T_theApp;



INT APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR	   lpCmdLine,
					 INT	   nCmdShow)
{
	DWORD	l_dw_LoopRet	= 0;
	MSG 	l_x_msg 		= {0};
	
	if(!C_HostSrv_Open())
		return C_HostSrv_Close();
	
	do
	{
		l_dw_LoopRet = MsgWaitForMultipleObjects(1, &g_T_LocalMemory.m_h_HostExitEvent,FALSE, INFINITE, QS_ALLEVENTS | QS_ALLINPUT | QS_ALLPOSTMESSAGE	| QS_SENDMESSAGE | QS_POSTMESSAGE | QS_MOUSE | QS_MOUSEBUTTON | QS_PAINT | QS_MOUSEMOVE | QS_INPUT |  QS_TIMER);
		
		if(l_dw_LoopRet == WAIT_OBJECT_0)
			continue;
		
		while (PeekMessage(&l_x_msg, NULL, 0, 0, PM_REMOVE))
		{
			if(l_x_msg.message == WM_ENDSESSION || l_x_msg.message == WM_QUERYENDSESSION || l_x_msg.message == 0x003B || l_x_msg.message == WM_DESTROY || l_x_msg.message == WM_CLOSE)
			{
				if(g_T_HostMemory.m_px_MorphoSmart != NULL)
					g_T_HostMemory.m_px_MorphoSmart->CancelLiveAcquisition();
				l_dw_LoopRet = WAIT_OBJECT_0;
			}
			
			TranslateMessage(&l_x_msg);
			DispatchMessage(&l_x_msg);
		}
		
	}while(l_dw_LoopRet != WAIT_OBJECT_0);
	
	return C_HostSrv_Close();
}

/*****************************C_HostSrv_Open*********************************/
//Open the host, this fuction prevent 
//Running two instance of C_Host Instance
//If the mutex exist - The returned value is false otherwise true.
/****************************************************************************/
BOOL C_HostSrv_Open()
{
	DWORD					l_dw_LastEror		= 0;
	HANDLE					l_h_MapFile 		= NULL;
	PSECURITY_DESCRIPTOR	l_p_pSD 			= NULL;
	SECURITY_ATTRIBUTES 	l_T_sa				= {0};
	HANDLE					l_h_ThreadHandle	= NULL;
	
	__try
	{
		l_h_ThreadHandle = GetCurrentProcess();
		if(l_h_ThreadHandle != NULL)
			SetProcessPriorityBoost(l_h_ThreadHandle,TRUE);
		
		l_h_ThreadHandle = GetCurrentThread();
		if(l_h_ThreadHandle != NULL)
		{
			SetThreadPriority(l_h_ThreadHandle,THREAD_PRIORITY_ABOVE_NORMAL);
			SetPriorityClass(l_h_ThreadHandle,HIGH_PRIORITY_CLASS);
		}
		
		l_p_pSD = (PSECURITY_DESCRIPTOR) malloc( SECURITY_DESCRIPTOR_MIN_LENGTH );
		
		if (l_p_pSD == NULL)
			return FALSE;
		
		if (!InitializeSecurityDescriptor(l_p_pSD, SECURITY_DESCRIPTOR_REVISION))
			return FALSE;
		
		// add a NULL disc. ACL to the security descriptor.
		if (!SetSecurityDescriptorDacl(l_p_pSD, TRUE, (PACL) NULL, FALSE))
			return FALSE;
		
		l_T_sa.nLength = sizeof(l_T_sa);
		l_T_sa.lpSecurityDescriptor = l_p_pSD;
		l_T_sa.bInheritHandle = TRUE;
		
		g_T_HostMemory.m_h_HostMutex = CreateMutex
			(
			(LPSECURITY_ATTRIBUTES)&l_T_sa,
			(BOOL)TRUE,
			(LPCTSTR)_T(VC_HOSTMUTEX_NAME)	
			);
		
		l_dw_LastEror = GetLastError ();
		
		//If cannot create Mutex, exit.
		if (g_T_HostMemory.m_h_HostMutex == NULL)
		{
			free(l_p_pSD);
			return FALSE;
		}
		
		//If Mutex already existed, exit.
		if (l_dw_LastEror == ERROR_ALREADY_EXISTS)
		{
			ReleaseMutex(g_T_HostMemory.m_h_HostMutex);
			CloseHandle(g_T_HostMemory.m_h_HostMutex);
			g_T_HostMemory.m_h_HostMutex = NULL;
			free(l_p_pSD);
			return FALSE;
		}
		
		l_h_MapFile = ::CreateFileMapping((HANDLE)0xFFFFFFFF,&l_T_sa,PAGE_READWRITE,0,sizeof(TSharedMemory),_T(VC_DSPSHAREDMEMORY));
		
		if(l_h_MapFile == NULL)
		{
			free(l_p_pSD);
			return FALSE;
		}
		
		g_T_SharedMemory = (TSharedMemory *)MapViewOfFile(l_h_MapFile,FILE_MAP_WRITE,0,0,sizeof(TSharedMemory));
		
		if(g_T_SharedMemory == NULL)
		{
			free(l_p_pSD);
			return FALSE;
		}
		
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
		g_T_LocalMemory.m_h_ExistSW 		= CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_EXITDSPSWOK));	
		g_T_LocalMemory.m_h_HostExitEvent	= CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_HOSTEXIT_NAME)); 
		g_T_LocalMemory.m_h_HostExitEventKo = CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_HOSTEXITKO_NAME));  
		g_T_HostMemory.m_h_HostWaitMsoExit  = CreateEvent(&l_T_sa, FALSE, FALSE, _T(VC_HOSTWAITMSOEXIT_NAME));  
		
		if(
			!g_T_LocalMemory.m_h_HostExitEvent||!g_T_LocalMemory.m_h_HostExitEventKo||!g_T_HostMemory.m_h_HostWaitMsoExit||\
			!g_T_LocalMemory.m_h_LogonIdent||!g_T_LocalMemory.m_h_AccessIdent||!g_T_LocalMemory.m_h_AdminIdent||\
			!g_T_LocalMemory.m_h_AdminEnroll||!g_T_LocalMemory.m_h_AdminUser||!g_T_LocalMemory.m_h_SWOn||\
			!g_T_LocalMemory.m_h_SWOff||!g_T_LocalMemory.m_h_AdminDb||!g_T_LocalMemory.m_h_AccessUpdate||\
			!g_T_LocalMemory.m_h_WaitAdminUser||!g_T_LocalMemory.m_h_AdminUpdate||!g_T_LocalMemory.m_h_WaitAdminDb ||\
			!g_T_LocalMemory.m_h_WaitUpdateAccess || !g_T_LocalMemory.m_h_WaitUpdateAdmin ||!g_T_LocalMemory.m_h_WaitCancel||\
			!g_T_LocalMemory.m_h_WaitPaint ||!g_T_LocalMemory.m_h_WaitOn||!g_T_LocalMemory.m_h_WaitOff||\
			!g_T_LocalMemory.m_h_WaitIdent||!g_T_LocalMemory.m_h_WaitEnroll||!g_T_LocalMemory.m_h_ExistSW
			)
		{
			free(l_p_pSD);
			return FALSE;
		}
		
		l_h_ThreadHandle = CreateThread
			(
			&l_T_sa,
			0,
			(LPTHREAD_START_ROUTINE)IdentThreadProc,
			NULL,
			0,
			0
			);
		
		if(l_h_ThreadHandle != NULL)
		{
			SetThreadPriority(l_h_ThreadHandle,THREAD_PRIORITY_ABOVE_NORMAL);
			SetPriorityClass(l_h_ThreadHandle,HIGH_PRIORITY_CLASS);
		}
		
		l_h_ThreadHandle = CreateThread
			(
			&l_T_sa,
			0,
			(LPTHREAD_START_ROUTINE)EnrollThreadProc,
			NULL,
			0,
			0
			);
		
		if(l_h_ThreadHandle != NULL)
		{
			SetThreadPriority(l_h_ThreadHandle,THREAD_PRIORITY_ABOVE_NORMAL);
			SetPriorityClass(l_h_ThreadHandle,HIGH_PRIORITY_CLASS);
		}
		
		l_h_ThreadHandle = CreateThread
			(
			&l_T_sa,
			0,
			(LPTHREAD_START_ROUTINE)PaintThreadProc,
			NULL,
			0,
			0
			);
		
		if(l_h_ThreadHandle != NULL)
		{
			SetThreadPriority(l_h_ThreadHandle,THREAD_PRIORITY_ABOVE_NORMAL);
			SetPriorityClass(l_h_ThreadHandle,HIGH_PRIORITY_CLASS);
		}
		
		l_h_ThreadHandle = CreateThread
			(
			&l_T_sa,
			0,
			(LPTHREAD_START_ROUTINE)CancelThreadProc,
			NULL,
			0,
			0
			);
		
		if(l_h_ThreadHandle != NULL)
		{
			SetThreadPriority(l_h_ThreadHandle,THREAD_PRIORITY_ABOVE_NORMAL);
			SetPriorityClass(l_h_ThreadHandle,HIGH_PRIORITY_CLASS);
		}
		
		l_h_ThreadHandle = CreateThread
			(
			&l_T_sa,
			0,
			(LPTHREAD_START_ROUTINE)SWOffThreadProc,
			NULL,
			0,
			0
			);
		
		if(l_h_ThreadHandle != NULL)
		{
			SetThreadPriority(l_h_ThreadHandle,THREAD_PRIORITY_ABOVE_NORMAL);
			SetPriorityClass(l_h_ThreadHandle,HIGH_PRIORITY_CLASS);
		}
		
		l_h_ThreadHandle = CreateThread
			(
			&l_T_sa,
			0,
			(LPTHREAD_START_ROUTINE)SWOnThreadProc,
			NULL,
			0,
			0
			);
		
		if(l_h_ThreadHandle != NULL)
		{
			SetThreadPriority(l_h_ThreadHandle,THREAD_PRIORITY_ABOVE_NORMAL);
			SetPriorityClass(l_h_ThreadHandle,HIGH_PRIORITY_CLASS);
		}
		
		l_h_ThreadHandle = CreateThread
			(
			&l_T_sa,
			0,
			(LPTHREAD_START_ROUTINE)UserThreadProc,
			NULL,
			0,
			0
			);
		
		if(l_h_ThreadHandle != NULL)
		{
			SetThreadPriority(l_h_ThreadHandle,THREAD_PRIORITY_ABOVE_NORMAL);
			SetPriorityClass(l_h_ThreadHandle,HIGH_PRIORITY_CLASS);
		}
		
		l_h_ThreadHandle = CreateThread
			(
			&l_T_sa,
			0,
			(LPTHREAD_START_ROUTINE)DbThreadProc,
			NULL,
			0,
			0
			);
		
		if(l_h_ThreadHandle != NULL)
		{
			SetThreadPriority(l_h_ThreadHandle,THREAD_PRIORITY_ABOVE_NORMAL);
			SetPriorityClass(l_h_ThreadHandle,HIGH_PRIORITY_CLASS);
		}
		
		l_h_ThreadHandle = CreateThread
			(
			&l_T_sa,
			0,
			(LPTHREAD_START_ROUTINE)UpdateThreadProc,
			NULL,
			0,
			0
			);
		
		if(l_h_ThreadHandle != NULL)
		{
			SetThreadPriority(l_h_ThreadHandle,THREAD_PRIORITY_ABOVE_NORMAL);
			SetPriorityClass(l_h_ThreadHandle,HIGH_PRIORITY_CLASS);
		}
		
		l_h_ThreadHandle = CreateThread
			(
			&l_T_sa,
			0,
			(LPTHREAD_START_ROUTINE)SuperviseThreadProc,
			NULL,
			0,
			0
			);
		
		if(l_h_ThreadHandle != NULL)
		{
			SetThreadPriority(l_h_ThreadHandle,THREAD_PRIORITY_ABOVE_NORMAL);
			SetPriorityClass(l_h_ThreadHandle,HIGH_PRIORITY_CLASS);
		}
		
		SetEvent(g_T_LocalMemory.m_h_WaitOn);
		free(l_p_pSD);
		
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}	
	return TRUE;
}

/*****************************C_HostSrv_Close*********************************/
//Close the host, this fuction prevent 
//If the mutex exist - Rlease and close it.
/****************************************************************************/
INT C_HostSrv_Close()
{
	__try
	{
		if(g_T_HostMemory.m_px_MorphoSmart != NULL)
		{
			g_T_HostMemory.m_px_MorphoSmart->CancelLiveAcquisition();
			g_T_HostMemory.m_px_MorphoSmart->CloseDevice();
		}
		
		if(g_T_HostMemory.m_h_HostMutex != NULL)
		{
			ReleaseMutex (g_T_HostMemory.m_h_HostMutex);
			CloseHandle (g_T_HostMemory.m_h_HostMutex);
			g_T_HostMemory.m_h_HostMutex = NULL;
		}
		
		if(g_T_LocalMemory.m_h_SWOff != NULL && g_T_LocalMemory.m_h_ExistSW != NULL && g_T_LocalMemory.m_h_HostExitEventKo != NULL)
		{
			SetEvent(g_T_LocalMemory.m_h_SWOff);	
			SetEvent(g_T_LocalMemory.m_h_ExistSW);	
			SetEvent(g_T_LocalMemory.m_h_HostExitEventKo);
		}
		
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}	
	return 0;
}
