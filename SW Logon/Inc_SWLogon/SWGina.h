/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWGina.h													 //
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




#ifndef SWGINA_H
#define SWGINA_H

BOOL WINAPI WlxNegotiate
(
 DWORD		dwWinlogonVersion,
 DWORD		*pdwDllVersion
 );

BOOL WINAPI WlxInitialize
(
 LPWSTR 				 lpWinsta,
 HANDLE 				 hWlx,
 PVOID					 pvReserved,
 PVOID					 pWinlogonFunctions,
 PVOID					 *pWlxContext
 );

VOID WINAPI WlxDisplaySASNotice
(
 PVOID	 pContext
 );

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
 );

BOOL WINAPI WlxActivateUserShell
(
 PVOID					 pWlxContext,
 PWSTR					 pszDesktop,
 PWSTR					 pszMprLogonScript,
 PVOID					 pEnvironment
 );

INT WINAPI WlxLoggedOnSAS
(
 PVOID					 pWlxContext,
 DWORD					 dwSasType,
 PVOID					 pReserved
 );

BOOL WINAPI WlxIsLockOk
(
 PVOID	pWlxContext
 );

VOID WINAPI WlxDisplayLockedNotice
(
 PVOID	 pWlxContext
 );

INT WINAPI WlxWkstaLockedSAS
(
 PVOID		pWlxContext,
 DWORD		dwSasType
 );

BOOL WINAPI WlxIsLogoffOk
(
 PVOID		pWlxContext
 );

VOID WINAPI WlxLogoff
(
 PVOID		pWlxContext
 );

VOID WINAPI WlxShutdown
(
 PVOID		pWlxContext,
 DWORD		ShutdownType
 );

BOOL WINAPI WlxScreenSaverNotify
(
 PVOID pWlxContext,
 BOOL *pfSecure
 );

#endif//SWGINA_H