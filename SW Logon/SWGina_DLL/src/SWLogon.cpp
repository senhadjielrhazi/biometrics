/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWLogon.cpp 												 //
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

HIMAGELIST		hiLogonSmall;
HIMAGELIST		hiLogonLarge;

INT AttemptUnlock
(
 PGlobals pWlxContext
 )
{	
	__try
	{
		if (memcmp(pWlxContext->m_T_LogonData.m_pwc_UserPassW,
			pWlxContext->m_pwc_UserPassW,sizeof(pWlxContext->m_pwc_UserPassW)) != 0)
			return(WLX_SAS_ACTION_NONE);
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
	return(WLX_SAS_ACTION_UNLOCK_WKSTA);
}

INT AttemptLogon
(
 PGlobals		pWlxContext,
 PSID			pLogonSid,
 PLUID			pLogonId
 )
{
	HANDLE				hUser;
	TOKEN_STATISTICS	TStats;
	TOKEN_GROUPS	*	pGroups;
	DWORD				size;
	DWORD				i;
	
	__try
	{
		if (LogonUser(pWlxContext->m_T_LogonData.m_pwc_UserLogin,
			pWlxContext->m_T_LogonData.m_pwc_UserDomain,
			pWlxContext->m_T_LogonData.m_pwc_UserPassW,
			LOGON32_LOGON_INTERACTIVE,
			LOGON32_PROVIDER_DEFAULT,
			&hUser))
		{
			pWlxContext->m_h_UserToken = hUser;
			
			//
			// Now, grovel the token we got back for interesting stuff:
			//
			
			GetTokenInformation(hUser,
				TokenStatistics,
				&TStats,
				sizeof(TStats),
				&size);
			
			*pLogonId = TStats.AuthenticationId;
			
			pGroups = (TOKEN_GROUPS *)LocalAlloc(LMEM_FIXED, 1024);
			
			if (!pGroups)
			{
				CloseHandle(hUser);
				return(WLX_SAS_ACTION_NONE);
			}
			
			// The tricky part.  We need to get the Logon SID from the token,
			// since that is what Winlogon will use to protect the windowstation
			// and desktop.
						
			GetTokenInformation
				(
				hUser,
				TokenGroups,
				pGroups,
				1024,
				&size);
			
			if (size > 1024)
			{
				pGroups = (TOKEN_GROUPS *)LocalReAlloc(pGroups, LMEM_FIXED, size);
				GetTokenInformation(hUser,
					TokenGroups,
					pGroups,
					size,
					&size);
			}
			
			for (i = 0; i < pGroups->GroupCount ; i++)
			{
				if ((pGroups->Groups[i].Attributes & SE_GROUP_LOGON_ID) == SE_GROUP_LOGON_ID)
				{
					CopySid(GetLengthSid(pLogonSid),
						pLogonSid,
						pGroups->Groups[i].Sid );
					break;
				}
			}
			
			LocalFree(pGroups);
			return(WLX_SAS_ACTION_LOGON);
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
	return(WLX_SAS_ACTION_NONE);
}


PWSTR AllocAndCaptureText
(
 HWND	 hDlg,
 INT	 Id
 )
{
	WCHAR	szTemp[MAX_PATH];
	PWSTR	New;
	DWORD	cb;
	
	__try
	{
		cb = GetDlgItemText(hDlg, Id, szTemp, MAX_PATH);
		New = (PWSTR)LocalAlloc(LMEM_FIXED, (cb + 1) * sizeof(WCHAR));
		if (New)
			wcscpy(New, szTemp);
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
	return(New);
}

PWSTR DupString
(
 PWSTR	 pszText
 )
{
	PWSTR	New;
	DWORD	cb;
	
	__try
	{
		cb = (wcslen(pszText) + 1) * sizeof(WCHAR);
		New = (PWSTR)LocalAlloc(LMEM_FIXED, cb);
		
		if (New)
			wcscpy(New, pszText);
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
	return(New);
}

INT CenterWindow
(
 HWND i_hwnd
 )
{
	RECT	rect;
	LONG	dx, dy;
	LONG	dxParent, dyParent;
	LONG	Style;
	
	__try
	{
		// Get window rect
		GetWindowRect(i_hwnd, &rect);
		dx = rect.right - rect.left;
		dy = rect.bottom - rect.top;
		// Get parent rect
		Style = GetWindowLong(i_hwnd, GWL_STYLE);
		if ((Style & WS_CHILD) == 0) 
		{
			// Return the desktop windows size (size of main screen)
			dxParent = GetSystemMetrics(SM_CXSCREEN);
			dyParent = GetSystemMetrics(SM_CYSCREEN);
		} 
		else 
		{
			HWND	hwndParent;
			RECT	rectParent;
			
			hwndParent = GetParent(i_hwnd);
			if (hwndParent == NULL) 
			{
				hwndParent = GetDesktopWindow();
			}
			GetWindowRect(hwndParent, &rectParent);
			dxParent = rectParent.right - rectParent.left;
			dyParent = rectParent.bottom - rectParent.top;
		}
		// Centre the child in the parent
		rect.left = (dxParent - dx) / 2;
		rect.top  = (dyParent - dy) / 3;
		// Move the child into position
		SetWindowPos(i_hwnd, HWND_TOPMOST, rect.left, rect.top, 0, 0, SWP_NOSIZE);
		SetForegroundWindow(i_hwnd);
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
	return(TRUE);
}
