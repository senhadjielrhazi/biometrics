/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWMenu.cpp													 //
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

/**********************************C_Menu************************************/
//DLL IContexMenu, this fuction 
//C_Menu construction.
/****************************************************************************/
C_Menu::C_Menu
(
 )
{	
	m_h_DataBmp = LoadBitmap ( _Module.GetModuleInstance(),
		MAKEINTRESOURCE(IDB_DATABMP) );
	
	m_h_CryptBmp = LoadBitmap ( _Module.GetModuleInstance(),
		MAKEINTRESOURCE(IDB_CRYPTBMP) );
	
	m_h_DecryptBmp = LoadBitmap ( _Module.GetModuleInstance(),
		MAKEINTRESOURCE(IDB_DECRYPTBMP) );
	
	m_p_File	= NULL;
	m_i_NBFile	= 0;
}

/**********************************~C_Menu***********************************/
//DLL IContexMenu, this fuction 
//C_Menu Destruction.
/****************************************************************************/
C_Menu::~C_Menu
(
 )
{
	if(m_p_File != NULL)
		free(m_p_File);
	
	m_i_NBFile	= 0;
}

/********************************Initialize**********************************/
//DLL IContexMenu, this fuction 
//Reads in the list of selected folders and stores them for later use.
/****************************************************************************/
HRESULT C_Menu::Initialize 
( 
 LPCITEMIDLIST pidlFolder,
 LPDATAOBJECT  pDO,
 HKEY		   hProgID 
 )
{
	WCHAR		l_pwc_FileName[MAX_PATH];
	UINT		l_ui_NumFiles;
	HDROP		l_h_drop;
	INT 		l_i_Count;
	FORMATETC	l_T_Etc = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	STGMEDIUM	l_T_Stg = { TYMED_HGLOBAL };
	BOOL		l_b_ChangedDir = FALSE;
	string_list l_ls_Files;
	string_list::const_iterator l_ls_it;
	
	
	// Read the list of folders from the data object.  They're stored in HDROP
	// form, so just get the HDROP handle and then use the drag 'n' drop APIs
	// on it.
	
	if ( FAILED( pDO->GetData ( &l_T_Etc, &l_T_Stg )))
		return E_INVALIDARG;
	
	// Get an HDROP handle.
	
	l_h_drop = (HDROP) GlobalLock ( l_T_Stg.hGlobal );
	
	if ( NULL == l_h_drop )
	{
		ReleaseStgMedium ( &l_T_Stg );
		return E_INVALIDARG;
	}
	
	// Determine how many files are involved in this operation.
	l_ui_NumFiles = DragQueryFile ( l_h_drop, 0xFFFFFFFF, NULL, 0 );
	
	for ( UINT uFile = 0; uFile < l_ui_NumFiles; uFile++ )
	{
		// Get the next filename.
		
		memset(l_pwc_FileName,0,sizeof(l_pwc_FileName));
		
		if ( 0 == DragQueryFile ( l_h_drop, uFile, l_pwc_FileName, MAX_PATH ))
			continue;
		
		l_ls_Files.push_back ( l_pwc_FileName);  
	}
	
	m_i_NBFile = l_ls_Files.size();
	m_p_File = (TSWFile *)malloc(sizeof(TSWFile)*m_i_NBFile);
	memset(m_p_File,0,sizeof(TSWFile)*m_i_NBFile);
	
	for(l_i_Count = 0,l_ls_it = l_ls_Files.begin(); l_i_Count<m_i_NBFile; l_i_Count++,l_ls_it++)
		lstrcpy(m_p_File[l_i_Count].m_pwc_FilePath,const_cast<LPTSTR>( l_ls_it->c_str()));
	
	// Release resources.
	GlobalUnlock ( l_T_Stg.hGlobal );
	ReleaseStgMedium ( &l_T_Stg );
	
	// If we found any files we can work with, return S_OK.  Otherwise,
	// return E_INVALIDARG so we don't get called again for this right-click
	return ( l_ls_Files.size() > 0 ) ? S_OK : E_INVALIDARG;
}

/*****************************QueryContextMenu*******************************/
//DLL IContexMenu, this fuction 
//Adds our items to the supplied menu.
/****************************************************************************/
HRESULT C_Menu::QueryContextMenu 
( 
 HMENU hMenu,		
 UINT uMenuIndex,										   
 UINT  uidFirstCmd, 
 UINT uidLastCmd,										   
 UINT  uFlags 
 )
{
	UINT	uCmdID		= uidFirstCmd;
	HMENU	l_hlSubMenu = NULL;
	
	// If the flags include CMF_DEFAULTONLY then we shouldn't do anything.
	if ( uFlags & CMF_DEFAULTONLY )
		return MAKE_HRESULT ( SEVERITY_SUCCESS, FACILITY_NULL, 0 );
	
	//Separator First.
	InsertMenu(hMenu, uMenuIndex, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
	uMenuIndex++;
	
	l_hlSubMenu = CreateMenu();
	if(l_hlSubMenu)
	{
		InsertMenu(l_hlSubMenu, 0, MF_STRING | MF_BYPOSITION, uCmdID++, _T(VC_MENUNAME_ENC));
		if ( m_h_CryptBmp != NULL )
			SetMenuItemBitmaps ( l_hlSubMenu, 0, MF_BYPOSITION, m_h_CryptBmp, NULL );
		
		InsertMenu(l_hlSubMenu, 1, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
		
		InsertMenu(l_hlSubMenu, 2, MF_STRING | MF_BYPOSITION, uCmdID++, _T(VC_MENUNAME_DEC));
		
		if ( m_h_DecryptBmp != NULL )
			SetMenuItemBitmaps ( l_hlSubMenu, 2, MF_BYPOSITION, m_h_DecryptBmp, NULL );
	}
	
	// Add our Secure Data items.
	InsertMenu ( hMenu, uMenuIndex, MF_STRING | MF_POPUP | MF_BYPOSITION, (UINT_PTR)l_hlSubMenu,
		_T(VC_MENUNAME_APP) );
	
	// Set the bitmap for the register item.
	if ( m_h_DataBmp != NULL )
		SetMenuItemBitmaps ( hMenu, uMenuIndex, MF_BYPOSITION, m_h_DataBmp, NULL );
	
	uMenuIndex++;
	
	InsertMenu(hMenu, uMenuIndex, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);	
	
	// The return value tells the shell how many top-level items we added.
	//DestroyMenu(l_hlSubMenu);?
	
	return MAKE_HRESULT ( SEVERITY_SUCCESS, FACILITY_NULL, 2 );
}

/*****************************GetCommandString*******************************/
//DLL IContexMenu, this fuction 
//Sets the flyby help string for the Explorer status bar.
/****************************************************************************/
HRESULT C_Menu::GetCommandString 
( 
 UINT  uCmdID,	   
 UINT uFlags,
 UINT* puReserved,
 LPSTR szName,
 UINT  cchMax 
 )
{
	LPCTSTR szPrompt;
	
	USES_CONVERSION;
	
	if ( uFlags & GCS_HELPTEXT )
	{
		switch ( uCmdID )
		{
		case 0:
			szPrompt = _T(VC_CRYPTEXPLORER_NAME);
			break;
			
		case 1:
			szPrompt = _T(VC_DECRYPTEXPLORER_NAME);
			break;
			
		default:
			ATLASSERT(0);			// should never get here
			return E_INVALIDARG;
			break;
		}
		
		// Copy the help text into the supplied buffer.  If the shell wants
		// a Unicode string, we need to case szName to an LPCWSTR.
		
		if ( uFlags & GCS_UNICODE )
			lstrcpynW ( (LPWSTR) szName, T2CW(szPrompt), cchMax );
		else
			lstrcpynA ( szName, T2CA(szPrompt), cchMax );
	}
	else if ( uFlags & GCS_VERB )
	{
		// Copy the verb name into the supplied buffer.  If the shell wants
		// a Unicode string, we need to case szName to an LPCWSTR.
		
		switch ( uCmdID )
		{
		case 0:
			if ( uFlags & GCS_UNICODE )
				lstrcpynW ( (LPWSTR) szName, L"Crypter", cchMax );
			else
				lstrcpynA ( szName, "Crypter", cchMax );
			break;
			
		case 1:
			if ( uFlags & GCS_UNICODE )
				lstrcpynW ( (LPWSTR) szName, L"Décrypter", cchMax );
			else
				lstrcpynA ( szName, "Décrypter", cchMax );
			break;
			
		default:
			ATLASSERT(0);			// should never get here
			return E_INVALIDARG;
			break;
		}
	}
	
	return S_OK;
}

/******************************InvokeCommand*********************************/
//DLL IContexMenu, this fuction 
//Carries out the selected command.
/****************************************************************************/
HRESULT C_Menu::InvokeCommand 
(
 LPCMINVOKECOMMANDINFO pInfo
 )
{
	// If lpVerb really points to a string, ignore this function call and bail out.  
	if ( 0 != HIWORD( pInfo->lpVerb ))
		return E_INVALIDARG;
	
	// Check that lpVerb is one of our commands (0 or 1)
	switch ( LOWORD( pInfo->lpVerb ))
	{
	case 0:
	case 1:
		{	
			if(IsMenuAlreadyPopUp() == S_OK)
			{
				C_DataWizard dlg (m_p_File,m_i_NBFile, (BOOL)LOWORD (pInfo->lpVerb) );
				dlg.DoModal();
			}
			SetMenuNoPopUp();
			return S_OK;
		}
		break;
		
	default:
		ATLASSERT(0);				// should never get here
		return E_INVALIDARG;
		break;
	}
}

/*****************************IsMenuAlreadyPopUp*****************************/
//DLL IContexMenu, this fuction 
//Try to verify the Secure Data execution and cree it's mutex.
/****************************************************************************/
HRESULT C_Menu::IsMenuAlreadyPopUp
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
		m_h_DataMutex = NULL;
		return FALSE;
	}
	
	if (!InitializeSecurityDescriptor(l_p_pSD, SECURITY_DESCRIPTOR_REVISION))
	{
		m_h_DataMutex = NULL;
		free(l_p_pSD);
		return FALSE;
	}
	
	// add a NULL disc. ACL to the security descriptor.
	if (!SetSecurityDescriptorDacl(l_p_pSD, TRUE, (PACL) NULL, FALSE))
	{
		m_h_DataMutex = NULL;
		free(l_p_pSD);
		return FALSE;
	}
	
	l_T_sa.nLength = sizeof(l_T_sa);
	l_T_sa.lpSecurityDescriptor = l_p_pSD;
	l_T_sa.bInheritHandle = FALSE;
	
	m_h_DataMutex = CreateMutex
		(
		(LPSECURITY_ATTRIBUTES)&l_T_sa,
		(BOOL)TRUE, 
		(LPCTSTR)_T(VC_DATAMUTEX_NAME)
		);
	
	if(m_h_DataMutex == NULL)
		return S_FALSE;
	
	free(l_p_pSD);
	l_dw_LastError = GetLastError ();
	
	if (l_dw_LastError == ERROR_ALREADY_EXISTS)
		return S_FALSE;
	
	return S_OK;
}

/******************************SetMenuNoPopUp********************************/
//DLL IContexMenu, this fuction 
//Release the Secure Data mutex.
/****************************************************************************/
VOID C_Menu::SetMenuNoPopUp
(
 VOID
 )
{
	if(m_h_DataMutex != NULL)
	{
		ReleaseMutex(m_h_DataMutex);
		CloseHandle(m_h_DataMutex);
		m_h_DataMutex = NULL;
	}
}