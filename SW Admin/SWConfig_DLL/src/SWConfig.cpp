/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWConfig.cpp												 //
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
//	SAGEM SA Administration Module											 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#include "stdafx.h"

CWinApp 		g_T_theApp;
HANDLE			g_h_Mutex	= NULL;

VOID C_Config_StartAdministration
(
 )
{
	///g_T_theApp.SetDialogBkColor(RGB(1, 192, 192));
	WlxAdminLockSW();
	C_ConfigWizard	*l_ConfigWizard = new C_ConfigWizard();
	l_ConfigWizard->DoModal();
	delete(l_ConfigWizard);
	Sleep(800);
	WlxAdminUnLock();
}

BOOL BuildTrustList
(
	LPWSTR		**i_pwc_TrustList,	
	DWORD		*i_dw_TrustCount 
	)
{
	LSA_HANDLE					PolicyHandle	= {0};
	NTSTATUS					Status			= NULL;
	PPOLICY_ACCOUNT_DOMAIN_INFO AccountDomain	= NULL;
	BOOL						bDC 			= FALSE;
	NET_API_STATUS				nas 			= NERR_Success; // assume success
	BOOL						l_b_Ret 		= FALSE; // assume this function will fail
	
	// open the policy on the specified machine
	Status = OpenPolicy
		(
		NULL,
		POLICY_VIEW_LOCAL_INFORMATION,
		&PolicyHandle
		);
	
	if(Status != STATUS_SUCCESS) 
		return(FALSE);
	
	// obtain the AccountDomain, which is common to all three cases
	Status = LsaQueryInformationPolicy
		(
		PolicyHandle,
		PolicyAccountDomainInformation,
		(VOID **)&AccountDomain
		);
	
	if(Status != STATUS_SUCCESS)
		goto cleanup;
	
	AddTrustToList
		(
		&AccountDomain->DomainName,
		i_pwc_TrustList,
		i_dw_TrustCount
		);
	
	// free memory allocated for account domain
	LsaFreeMemory(AccountDomain);
	
	// find out if the target machine is a domain controller
	if(!IsDomainController(&bDC)) 
		goto cleanup;
	
	if(!bDC) 
	{
		PPOLICY_PRIMARY_DOMAIN_INFO PrimaryDomain;
		LPWSTR szPrimaryDomainName = NULL;
		LPWSTR DomainController = NULL;
		
		// get the primary domain
		Status = LsaQueryInformationPolicy
			(
			PolicyHandle,
			PolicyPrimaryDomainInformation,
			(VOID **)&PrimaryDomain
			);
		
		if(Status != STATUS_SUCCESS)
			goto cleanup;
		
		// if the primary domain Sid is NULL, we are a non-member, and
		// our work is done.
		if(PrimaryDomain->Sid == NULL) 
		{
			LsaFreeMemory(PrimaryDomain);
			l_b_Ret = TRUE;
			goto cleanup;
		}
		
		AddTrustToList
			(
			&PrimaryDomain->Name,
			i_pwc_TrustList, 
			i_dw_TrustCount
			);
		
		// build a copy of what we just added.	This is necessary in order
		// to lookup the domain controller for the specified domain.
		// the Domain name must be NULL terminated for NetGetDCName(),
		// and the LSA_UNICODE_STRING buffer is not necessarilly NULL
		// terminated.	Note that in a practical implementation, we
		// could just extract the element we added, since it ends up
		// NULL terminated.
		
		szPrimaryDomainName = (LPWSTR)HeapAlloc
			(
			GetProcessHeap(), 0,
			PrimaryDomain->Name.Length + sizeof(WCHAR) // existing length + NULL
			);
		
		if(szPrimaryDomainName != NULL) {
			// copy the existing buffer to the new storage, appending a NULL
			lstrcpynW
				(
				szPrimaryDomainName,
				PrimaryDomain->Name.Buffer,
				(PrimaryDomain->Name.Length / sizeof(WCHAR)) + 1
				);
		}
		
		LsaFreeMemory(PrimaryDomain);
		
		if(szPrimaryDomainName == NULL)
			goto cleanup;
		
		// get the primary domain controller computer name
		nas = NetGetDCName
			(
			NULL,
			szPrimaryDomainName,
			(LPBYTE *)&DomainController
			);
		
		HeapFree(GetProcessHeap(), 0, szPrimaryDomainName);
		
		if(nas != NERR_Success)
			goto cleanup;
		
		// close the policy handle, because we don't need it anymore
		// for the workstation case, as we open a handle to a DC
		// policy below
		LsaClose(PolicyHandle);
		PolicyHandle = INVALID_HANDLE_VALUE; // invalidate handle value
		
		// open the policy on the domain controller
		Status = OpenPolicy
			(
			DomainController,
			POLICY_VIEW_LOCAL_INFORMATION,
			&PolicyHandle
			);
		
		// free the domaincontroller buffer
		NetApiBufferFree(DomainController);
		
		if(Status != STATUS_SUCCESS)
			goto cleanup;
	}
	
	// build additional trusted domain(s) list and indicate if successful
	l_b_Ret = EnumTrustedDomains(PolicyHandle, i_pwc_TrustList, i_dw_TrustCount);
	
cleanup:
	
	// close the policy handle
	if(PolicyHandle != INVALID_HANDLE_VALUE)
		LsaClose(PolicyHandle);
	
	if(!l_b_Ret) 
	{
		if(Status != STATUS_SUCCESS)
			SetLastError( LsaNtStatusToWinError(Status) );
		else if(nas != NERR_Success)
			SetLastError( nas );
	}
	
	return l_b_Ret;
}


BOOL AddTrustToList
(
	PLSA_UNICODE_STRING UnicodeString,
	LPWSTR				**i_pwc_TrustList,	
	DWORD				*i_dw_TrustCount   
	)
{
	if(*i_dw_TrustCount >= DOMAIN_MAX_COUNT) 
		return FALSE;
	
	// allocate storage for array element
	(*i_pwc_TrustList)[*i_dw_TrustCount] = (LPWSTR)HeapAlloc
		(
		GetProcessHeap(), 0,
		UnicodeString->Length + sizeof(WCHAR) // existing length + NULL
		);
	
	if((*i_pwc_TrustList)[*i_dw_TrustCount] == NULL) 
		return FALSE;
	
	// copy the existing buffer to the new storage, appending a NULL
	lstrcpynW
		(
		(*i_pwc_TrustList)[*i_dw_TrustCount],
		UnicodeString->Buffer,
		(UnicodeString->Length / sizeof(WCHAR)) + 1
		);
	
	(*i_dw_TrustCount)++; // increment the trust count
	
	return TRUE;
}

BOOL EnumTrustedDomains
(
	LSA_HANDLE PolicyHandle,
	LPWSTR		**i_pwc_TrustList,	
	DWORD		*i_dw_TrustCount 
	)
{
	LSA_ENUMERATION_HANDLE lsaEnumHandle=0; // start an enum
	PLSA_TRUST_INFORMATION	TrustInfo;
	ULONG					ulReturned; 			  // number of items returned
	ULONG					ulCounter;				  // counter for items returned
	NTSTATUS				Status;
	
	do {
		Status = LsaEnumerateTrustedDomains
			(
			PolicyHandle,	// open policy handle
			&lsaEnumHandle, // enumeration tracker
			(VOID **)&TrustInfo,	 // buffer to receive data
			32000,			// recommended buffer size
			&ulReturned 	// number of items returned
			);
		
		// get out if an error occurred
		if( (Status != STATUS_SUCCESS) &&
			(Status != STATUS_MORE_ENTRIES) &&
			(Status != STATUS_NO_MORE_ENTRIES)) 
		{
			SetLastError( LsaNtStatusToWinError(Status) );
			
			return FALSE;
		}
		
		// Display results
		// Note: Sids are in TrustInfo[ulCounter].Sid
		for(ulCounter = 0 ; ulCounter < ulReturned ; ulCounter++)
			AddTrustToList(&TrustInfo[ulCounter].Name, i_pwc_TrustList, i_dw_TrustCount);
		
		
		// free the buffer
		LsaFreeMemory(TrustInfo);
		
	} while (Status != STATUS_NO_MORE_ENTRIES);
	
	return TRUE;
}

BOOL IsDomainController
(
 LPBOOL bDomainController
 )
{
	PSERVER_INFO_101	si101;
	NET_API_STATUS		nas;
	
	nas = NetServerGetInfo
		(
		NULL,
		101,	// info-level
		(LPBYTE *)&si101
		);
	
	if(nas != NERR_Success) 
	{
		SetLastError(nas);
		return FALSE;
	}
	
	if((si101->sv101_type & SV_TYPE_DOMAIN_CTRL) || (si101->sv101_type & SV_TYPE_DOMAIN_BAKCTRL)) 
		*bDomainController = TRUE;
	else 
		*bDomainController = FALSE;
	
	NetApiBufferFree(si101);
	
	return TRUE;
}

NTSTATUS OpenPolicy
(
	LPWSTR ServerName,
	DWORD DesiredAccess,
	PLSA_HANDLE PolicyHandle
	)
{
	LSA_OBJECT_ATTRIBUTES ObjectAttributes;
	LSA_UNICODE_STRING ServerString;
	PLSA_UNICODE_STRING Server;
	
	// Always initialize the object attributes to all zeroes
	ZeroMemory(&ObjectAttributes, sizeof(ObjectAttributes));
	
	if(ServerName != NULL) 
	{
		// Make a LSA_UNICODE_STRING out of the LPWSTR passed in
		InitLsaString(&ServerString, ServerName);
		
		Server = &ServerString;
	} 
	else 
		Server = NULL;
	
	// Attempt to open the policy
	return LsaOpenPolicy
		(
		Server,
		&ObjectAttributes,
		DesiredAccess,
		PolicyHandle
		);
}

VOID InitLsaString
(
	PLSA_UNICODE_STRING LsaString,
	LPWSTR String
	)
{
	DWORD StringLength;
	
	if (String == NULL) 
	{
		LsaString->Buffer = NULL;
		LsaString->Length = 0;
		LsaString->MaximumLength = 0;
		
		return;
	}
	
	StringLength = lstrlenW(String);
	LsaString->Buffer = String;
	LsaString->Length = (USHORT) StringLength * sizeof(WCHAR);
	LsaString->MaximumLength = (USHORT) (StringLength + 1) * sizeof(WCHAR);
}