/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003. 									 //
//																			 //
//	File:		SWLogon.h		 											 //
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




#ifndef SWLOGON_H
#define SWLOGON_H

INT AttemptUnlock
(
 PGlobals pWlxContext
 );

INT AttemptLogon
(
 PGlobals		pWlxContext,
 PSID			pLogonSid,
 PLUID			pLogonId
 );


BOOL TryToChangePassword
(
 HWND hDlg, 
 PTSTR pszUsername,
 PTSTR pszDomain,
 PTSTR pszOld,
 PTSTR pszNew
 );

PWSTR AllocAndCaptureText
(
 HWND    hDlg,
 INT     Id
 );

PWSTR DupString
(
 PWSTR   pszText
 );
INT CenterWindow
(
 HWND i_hwnd
 );

#endif //SWLOGON_H