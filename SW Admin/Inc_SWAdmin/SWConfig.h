/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWConfig.h													 //
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
//	SAGEM SA Adminstration Module											 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#ifndef SWCONFIG_H
#define SWCONFIG_H

VOID C_Config_StartAdministration
(
 VOID
 );

BOOL BuildTrustList
(
	LPWSTR		**l_TrustList,	
	DWORD		*l_TrustCount 
	);

BOOL AddTrustToList
(
	PLSA_UNICODE_STRING UnicodeString,
	LPWSTR				**l_TrustList,	
	DWORD				*l_TrustCount	
	);

BOOL EnumTrustedDomains
(
	LSA_HANDLE PolicyHandle,
	LPWSTR		**l_TrustList,	
	DWORD		*l_TrustCount 
	);

BOOL IsDomainController
(
	LPBOOL bDomainController
	);

NTSTATUS OpenPolicy
(
	LPWSTR ServerName,
	DWORD DesiredAccess,
	PLSA_HANDLE PolicyHandle
	);
VOID InitLsaString
(
	PLSA_UNICODE_STRING LsaString,
	LPWSTR String
	);

#endif//SWCONFIG_H