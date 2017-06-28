/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWGlobals.h													 //
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




#ifndef SWGLOBALS_H
#define SWGLOBALS_H

INT CALLBACK BioLogonDlgProc
(
 HWND        hDlg,
 UINT        Message,
 WPARAM      wParam,
 LPARAM      lParam
 );

INT BioLogonDlgRet
(
 HWND hDlg,
 TModuleRet wParam
 );

BOOL BioLogonProgress
(
 HWND hDlg,
 WPARAM wParam
 );

INT BioLogonDlgInit
(
 HWND hDlg, 
 LPARAM lParam,
 BOOL	l_Font
 );

DWORD WINAPI LogonIdentThreadProc
(
 LPVOID lpvParam
 );

INT CALLBACK WinLogonDlgProc
(
 HWND        hDlg,
 UINT        Message,
 WPARAM      wParam,
 LPARAM      lParam
 );

INT WinLogonDlgInit
(
 HWND hDlg,
 LPARAM lParam
 );

INT WinLogonDlgRet
(
 HWND hDlg
 );

INT CALLBACK BioLockDlgProc
(
 HWND        hDlg,
 UINT        Message,
 WPARAM      wParam,
 LPARAM      lParam
 );

INT BioLockDlgRet
(
 HWND hDlg,
 TModuleRet wParam
 );

BOOL BioLockProgress
(
 HWND hDlg,
 WPARAM wParam
 );

INT BioLockDlgInit
(
 HWND hDlg, 
 LPARAM lParam,
 BOOL	l_Font
 );

DWORD WINAPI LockIdentThreadProc
(
 LPVOID lpvParam
 );

INT CALLBACK WinLockDlgProc
(
 HWND        hDlg,
 UINT        Message,
 WPARAM      wParam,
 LPARAM      lParam
 );

INT WinLockDlgInit
(
 HWND hDlg,
 LPARAM lParam
 );

INT WinLockDlgRet
(
 HWND hDlg
 );

INT CALLBACK OptionsDlgProc
(
 HWND        hDlg,
 UINT        Message,
 WPARAM      wParam,
 LPARAM      lParam
 );

INT OptionsDlgInit
(
 HWND hDlg,
 LPARAM lParam
 );

INT OptionsDlgShutdown
(
 HWND hDlg
 );

INT CALLBACK ShutdownDlgProc
(
 HWND        hDlg,
 UINT        Message,
 WPARAM      wParam,
 LPARAM      lParam
 );

INT OptionsDlgChangePassword
(
 HWND hDlg
 );


INT CALLBACK ChangePasswordDlgProc
(
 HWND        hDlg,
 UINT        Message,
 WPARAM      wParam,
 LPARAM      lParam
 );

INT ChangePasswordDlgInit
(
 HWND hDlg,
 LPARAM lParam
 );

BOOL TryToChangePassword
(
 HWND hDlg
 );

#endif//SWGLOBALS_H