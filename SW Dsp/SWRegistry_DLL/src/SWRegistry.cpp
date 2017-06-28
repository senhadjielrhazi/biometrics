/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWRegistry.cpp												 //
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
//	SAGEM SA Registry Module												 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#include "StdAfx.h"

C_Registry::C_Registry
(
 )
{
	//For Secure Access
	m_b_RunOnce 		= FALSE;
}

C_Registry::~C_Registry
(
 )
{
}

// Synopsis :
// 1. This routine Set the defined registry entry. for SW Access Onrun
BOOL C_Registry::C_Registry_GetAccessOnRun
(
 WCHAR *i_pwc_Path
 )
{
	BOOL	l_b_Ret = FALSE;
	WCHAR	l_pwc_Path[256];

	memset(l_pwc_Path,0,sizeof(l_pwc_Path));

	l_b_Ret = OpenKeyRegistry
		(
		localMachine,
		_T(VC_REGACCESS_NAME)
		);
	
	if(!l_b_Ret)
		l_b_Ret = CreateKeyRegistry(localMachine,_T(VC_REGACCESS_NAME));

	if(!l_b_Ret)
	{
		CloseKeyRegistry();
		return FALSE;
	}

	l_b_Ret = GetSTRValueRegistry
		(
		_T(VC_REGRUNONCE_NAME),
		l_pwc_Path
		);
	if(l_b_Ret)
	{
		if(memcmp(i_pwc_Path,l_pwc_Path,sizeof(l_pwc_Path)) !=0)
			l_b_Ret = SetSTRValueRegistry
			(
			_T(VC_REGRUNONCE_NAME),
			i_pwc_Path
			);
	}

	m_b_RunOnce = l_b_Ret;
	return(l_b_Ret);
}

// Synopsis :
// 1. This routine Set the defined registry entry. for SW Access Onrun
VOID C_Registry::C_Registry_SetAccessOnRun
(
 WCHAR *i_pwc_Path, 
 BOOL i_b_AddRemove
 )
{
	BOOL	l_b_Ret = FALSE;
	
	l_b_Ret = OpenKeyRegistry
			(
			localMachine,
			_T(VC_REGACCESS_NAME)
			);
	
	if(!l_b_Ret)
		l_b_Ret = CreateKeyRegistry(localMachine,_T(VC_REGACCESS_NAME));

	if(!l_b_Ret)
	{
		CloseKeyRegistry();
		return;
	}

	if(i_b_AddRemove)
	{
		l_b_Ret = SetSTRValueRegistry
			(
			_T(VC_REGRUNONCE_NAME),
			i_pwc_Path
			);
		m_b_RunOnce = TRUE;
	}
	else
	{
		l_b_Ret = DeleteValueRegistry(_T(VC_REGRUNONCE_NAME));
		m_b_RunOnce = FALSE;
	}
}

// Synopsis :
// 1. This routine Set the defined registry entry. for SW Logon Last Domain &User
BOOL C_Registry::C_Registry_GetLastUserDomain
(
 WCHAR *o_puc_User,
 WCHAR *o_puc_Domain
 )
{
	BOOL	l_b_Ret = FALSE;
	
	memset(o_puc_User, 0, VI_USERLOGON_MAX*sizeof(WCHAR));
	memset(o_puc_Domain, 0, VI_USERDOMAIN_MAX*sizeof(WCHAR));
		
	//Reg Entry For WinLogon
	l_b_Ret = OpenKeyRegistry(localMachine,_T(VC_REGLASTLOGON_NAME));
	
	if(!l_b_Ret)
		l_b_Ret = CreateKeyRegistry(localMachine,_T(VC_REGLASTUSER_NAME));
	
	if(!l_b_Ret)
	{
		CloseKeyRegistry();
		return FALSE;
	}
	
	//User Name
	l_b_Ret = GetSTRValueRegistry
		(
		_T(VC_REGLASTUSER_NAME),
		o_puc_User
		);
	
	if(!l_b_Ret)
		SetSTRValueRegistry
		(
		_T(VC_REGLASTUSER_NAME),
		o_puc_User
		);

	//Domain Name
	l_b_Ret = GetSTRValueRegistry
		(
		_T(VC_REGLASTDOMAIN_NAME),
		o_puc_Domain
		);
	
	if(!l_b_Ret)
		SetSTRValueRegistry
		(
		_T(VC_REGLASTDOMAIN_NAME),
		o_puc_Domain
		);
		
	CloseKeyRegistry();
	return TRUE;
} 

// Synopsis :
// 1. This routine Set the defined registry entry. for SW Logon Last Domain &User
VOID C_Registry::C_Registry_SetLastUserDomain
(
 WCHAR *i_puc_User,
 WCHAR *i_puc_Domain
 )
{
	BOOL	l_b_Ret = FALSE;

	//Reg Entry For WinLogon
	l_b_Ret = OpenKeyRegistry(localMachine,_T(VC_REGLASTUSER_NAME));
	
	if(!l_b_Ret)
		l_b_Ret = CreateKeyRegistry(localMachine,_T(VC_REGLASTUSER_NAME));

	if(!l_b_Ret)
	{
		CloseKeyRegistry();
		return;
	}
	
	//User Name
	l_b_Ret = SetSTRValueRegistry
		(
		_T(VC_REGLASTUSER_NAME),
		i_puc_User
		);
	
	if(!l_b_Ret)
	{
		CloseKeyRegistry();
		return;
	}
	//Domain Name
	l_b_Ret = SetSTRValueRegistry
		(
		_T(VC_REGLASTDOMAIN_NAME),
		i_puc_Domain
		);

	if(!l_b_Ret)
	{
		CloseKeyRegistry();
		return;
	}
} 

/************************Internal functions to help C_Registry**********************/
BOOL C_Registry::OpenKeyRegistry(enum Keys i_h_Key, LPCWSTR i_pwc_Key)
{	
	if(RegOpenKeyEx((HKEY)i_h_Key,(PCWCH)i_pwc_Key, 0, KEY_ALL_ACCESS, &m_h_Key) == ERROR_SUCCESS)
		return TRUE;
	m_h_Key = NULL;
	return FALSE;
}

BOOL C_Registry::CreateKeyRegistry(enum Keys i_h_Key, LPCWSTR i_pwc_Key)
{	
	if(RegCreateKeyEx((HKEY)i_h_Key,(PCWCH)i_pwc_Key, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &m_h_Key, NULL) == ERROR_SUCCESS)
		return TRUE;
	m_h_Key = NULL;
	return FALSE;
}

BOOL C_Registry::SetSTRValueRegistry(LPCWSTR i_pwc_ValueName, LPCWSTR o_pwc_Data)
{	
	DWORD	l_dw_Type	= REG_SZ;
	if(::RegSetValueEx(m_h_Key, (LPCWSTR)i_pwc_ValueName, 0, l_dw_Type, (LPBYTE)(LPCWSTR)o_pwc_Data, wcslen(o_pwc_Data)*sizeof(WCHAR)) == ERROR_SUCCESS)
	{
		::RegFlushKey(m_h_Key);
		return TRUE;
	}
	return FALSE;
}

BOOL C_Registry::SetDWORDValueRegistry(LPCWSTR i_pwc_ValueName, DWORD o_dw_Value)
{	
	DWORD	l_dw_Type	= REG_DWORD;
	
	if(::RegSetValueEx(m_h_Key, (LPCWSTR)i_pwc_ValueName, 0, l_dw_Type, (LPBYTE)&o_dw_Value, sizeof(DWORD)) == ERROR_SUCCESS)
	{
		::RegFlushKey(m_h_Key);
		return TRUE;
	}
	return FALSE;
}

BOOL C_Registry::GetSTRValueRegistry(LPCWSTR o_pwc_ValueName, PCWCH o_str_Value)
{
	BOOL	l_b_Ret 	= FALSE;
	DWORD	l_dw_Type	= REG_SZ;
	DWORD	l_dw_cbData = 1024;
	
	memset((LPVOID)o_str_Value, 0, wcslen(o_str_Value)*sizeof(WCHAR));
	
	if(::RegQueryValueEx(m_h_Key,
		o_pwc_ValueName,
		NULL,
		&l_dw_Type, 
		(LPBYTE)(PCWCH)o_str_Value,
		&l_dw_cbData) == ERROR_SUCCESS)
		return TRUE;
	else
		return FALSE;
}	

BOOL C_Registry::GetDWORDValueRegistry(LPCWSTR o_p_ValueName, DWORD& o_dw_Value)
{
	BOOL	l_b_Ret 	= FALSE;
	DWORD	l_dw_Type	= REG_DWORD;
	DWORD	l_dw_cbData = sizeof(DWORD);
	
	o_dw_Value			= 0;	
	
	if(RegQueryValueEx(m_h_Key,
		o_p_ValueName,
		NULL,
		&l_dw_Type, 
		(BYTE*)(DWORD)&o_dw_Value,
		&l_dw_cbData) == ERROR_SUCCESS)
		return TRUE;
	else
	return FALSE;
}

BOOL C_Registry::DeleteKeyRegistry(enum Keys i_h_Key, LPCWSTR i_pwc_Key)
{	
	return ::RegDeleteKey((HKEY)i_h_Key,(PCWCH)i_pwc_Key) == ERROR_SUCCESS;
}

BOOL C_Registry::DeleteValueRegistry(LPCWSTR i_p_ValueName)
{	
	if(::RegDeleteValue(m_h_Key,(PCWCH)i_p_ValueName) == ERROR_SUCCESS)
		return TRUE;
	return FALSE;	
}

VOID C_Registry::CloseKeyRegistry()
{
	::RegCloseKey(m_h_Key);
	m_h_Key = NULL;
}
/**************************************************************************************/
