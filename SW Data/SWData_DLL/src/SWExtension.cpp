/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWExtension.cpp 											 //
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
//	SAGEM SA Data Module													 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#include "stdafx.h"

CComModule _Module;
CWinApp 	g_T_App;
HANDLE		g_h_DataMutex;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_DLLSWData, C_Menu)
END_OBJECT_MAP()

/********************************DllMain*************************************/
//DLL EntryPoint, this fuction 
//Provide the instance of resources.
/****************************************************************************/
extern "C" BOOL WINAPI DllMain
(
 HINSTANCE hInstance, 
 DWORD dwReason, 
 LPVOID /*lpReserved*/
 )
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		g_T_App.m_hInstance = hInstance;
		afxCurrentInstanceHandle = hInstance;
		afxCurrentResourceHandle = hInstance;
		_Module.Init(ObjectMap, hInstance, &LIBID_DLSWDataLib);
		DisableThreadLibraryCalls(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
		_Module.Term();
	return TRUE; 
}

/*****************************DllCanUnloadNow********************************/
//DLL EntryPoint, this fuction 
//Used to determine whether the DLL can be unloaded by OLE.
/****************************************************************************/
STDAPI DllCanUnloadNow
(
 VOID
 )
{
	return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/****************************DllGetClassObject*******************************/
//DLL EntryPoint, this fuction 
//Returns a class factory to create an object of the requested type.
/****************************************************************************/
STDAPI DllGetClassObject
(
 REFCLSID rclsid, 
 REFIID riid, 
 LPVOID* ppv
 )
{
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/****************************DllRegisterServer*******************************/
//DLL EntryPoint, this fuction 
//Adds entries to the system registry.
/****************************************************************************/
STDAPI DllRegisterServer
(
 VOID
 )
{	 // registers object, typelib and all interfaces in typelib
	return _Module.RegisterServer(TRUE);
}

/****************************DllUnregisterServer*****************************/
//DLL EntryPoint, this fuction 
//Removes entries from the system registry.
/****************************************************************************/ 
STDAPI DllUnregisterServer
(
 VOID
 )
{
	return _Module.UnregisterServer(TRUE);
}

/*****************************DllEncodingFile********************************/
//DLL, this fuction 
//Try to Encode or Decode File.
/****************************************************************************/
VOID CALLBACK DllEncodingFile
(
  HWND hwnd,
  HINSTANCE hinst,
  LPTSTR lpCmdLine,
  int nCmdShow
)
{
	TSWFile 			l_p_File				= {0};
	INT					l_i_nNumArgs			= 0;   
	LPWSTR				*l_pwc_szArglist		= 0;

	l_pwc_szArglist = CommandLineToArgvW(GetCommandLine(), &l_i_nNumArgs); 
	
	memset(l_p_File.m_pwc_FilePath,0,sizeof(l_p_File.m_pwc_FilePath));
	memcpy(l_p_File.m_pwc_FilePath,l_pwc_szArglist[2],wcslen(l_pwc_szArglist[2])*sizeof(WCHAR));

	if(IsMenuAlreadyPopUp() == S_OK)
	{
		C_DataWizard dlg (&l_p_File,1,(BOOL)StrToInt(l_pwc_szArglist[3]));
		dlg.DoModal();
	}
	SetMenuNoPopUp();
}

/*****************************IsMenuAlreadyPopUp*****************************/
//DLL, this fuction 
//Try to verify the Secure Data execution and cree it's mutex.
/****************************************************************************/
HRESULT IsMenuAlreadyPopUp
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
	{
		g_h_DataMutex = NULL;
		return FALSE;
	}
	
	if (!InitializeSecurityDescriptor(l_p_pSD, SECURITY_DESCRIPTOR_REVISION))
	{
		g_h_DataMutex = NULL;
		free(l_p_pSD);
		return FALSE;
	}
	
	// add a NULL disc. ACL to the security descriptor.
	if (!SetSecurityDescriptorDacl(l_p_pSD, TRUE, (PACL) NULL, FALSE))
	{
		g_h_DataMutex = NULL;
		free(l_p_pSD);
		return FALSE;
	}
	
	l_T_sa.nLength = sizeof(l_T_sa);
	l_T_sa.lpSecurityDescriptor = l_p_pSD;
	l_T_sa.bInheritHandle = FALSE;
	
	g_h_DataMutex = CreateMutex
		(
		(LPSECURITY_ATTRIBUTES)&l_T_sa,
		(BOOL)TRUE, 
		(LPCTSTR)_T(VC_DATAMUTEX_NAME)
		);
	
	if(g_h_DataMutex == NULL)
		return S_FALSE;
	
	free(l_p_pSD);
	l_dw_LastError = GetLastError ();
	
	if (l_dw_LastError == ERROR_ALREADY_EXISTS)
		return S_FALSE;
	
	return S_OK;
}

/******************************SetMenuNoPopUp********************************/
//DLL, this fuction 
//Release the Secure Data mutex.
/****************************************************************************/
VOID SetMenuNoPopUp
(
 VOID
 )
{
	if(g_h_DataMutex != NULL)
	{
		ReleaseMutex(g_h_DataMutex);
		CloseHandle(g_h_DataMutex);
		g_h_DataMutex = NULL;
	}
}