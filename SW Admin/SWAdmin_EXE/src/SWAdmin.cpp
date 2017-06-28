/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWAdmin.cpp 												 //
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
//	SAGEM SA Admin Module Tester											 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#include "stdafx.h"

BEGIN_MESSAGE_MAP(SWAdmin, CWinApp)
//{{AFX_MSG_MAP(SWAdmin)
//}}AFX_MSG
END_MESSAGE_MAP()

SWAdmin::SWAdmin
(
 )
{
	m_h_Mutex	= NULL;
}

SWAdmin::~SWAdmin
(
 )
{
}

SWAdmin theApp;

BOOL SWAdmin::InitInstance
(
 VOID
 )
{	
	DWORD					l_dw_LastError		= 0;
	PSECURITY_DESCRIPTOR	l_p_pSD 			= NULL;
	SECURITY_ATTRIBUTES 	l_T_sa				= {0};
	
	SetProcessShutdownParameters(0x4FF,0x000010);

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
		(LPCTSTR)_T(VC_ADMINMUTEX_NAME) 
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
		CloseHandle(m_h_Mutex);
		return FALSE;
	}
	
	C_Config_StartAdministration(); 
	if(m_h_Mutex != NULL)
	{
		ReleaseMutex(m_h_Mutex);
		CloseHandle(m_h_Mutex);
	}
	return FALSE;
}