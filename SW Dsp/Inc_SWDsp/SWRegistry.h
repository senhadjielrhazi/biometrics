/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003. 									 //
//																			 //
//	File:		SWRegistry.h	 											 //
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




#ifndef SWREGISTRY_H
#define SWREGISTRY_H

#ifdef SWREGISTRY_EXPORTS
#define REGISTRYMANAGER_API __declspec(dllexport)
#else
#define REGISTRYMANAGER_API __declspec(dllimport)
#endif

class REGISTRYMANAGER_API C_Registry
{
	
public:
	// Attributes
	//For Registry class :
	enum cregRestoreEnum
	{
		regVolatile		= REG_WHOLE_HIVE_VOLATILE,
		regRefresh		= REG_REFRESH_HIVE,
		regNoLazy		= REG_NO_LAZY_FLUSH
	};
	enum Keys
	{
		classesRoot 	= HKEY_CLASSES_ROOT,
		currentUser 	= HKEY_CURRENT_USER,
		localMachine	= HKEY_LOCAL_MACHINE,
		currentConfig	= HKEY_CURRENT_CONFIG,
		users			= HKEY_USERS,
		performanceData = HKEY_PERFORMANCE_DATA,
		dynData 		= HKEY_DYN_DATA
	};
	
	//For Secure Access
	BOOL	 m_b_RunOnce;
	
	// Constructor and destructor
	C_Registry();
	~C_Registry();
	
	//Operations
	BOOL C_Registry_GetLastUserDomain(WCHAR *o_pwc_User,WCHAR *o_pwc_Domain);
	VOID C_Registry_SetLastUserDomain(WCHAR *o_pwc_User,WCHAR *o_pwc_Domain);
	BOOL C_Registry_GetAccessOnRun(WCHAR *i_pwc_Path);
	VOID C_Registry_SetAccessOnRun(WCHAR *i_pwc_Path,BOOL i_b_AddRemove);

protected:
	//Attributes
	HKEY	m_h_Key;	
	BOOL OpenKeyRegistry(enum Keys hKey, LPCWSTR szKey);
	BOOL CreateKeyRegistry(enum Keys hKey, LPCWSTR szKey);
	BOOL DeleteKeyRegistry(enum Keys hKey, LPCWSTR szKey);
	BOOL DeleteValueRegistry(LPCWSTR lpValueName);
	BOOL GetSTRValueRegistry(LPCWSTR lpValueName, PCWCH strValue);
	BOOL GetDWORDValueRegistry(LPCWSTR lpValueName, DWORD& dwValue);
	BOOL SetSTRValueRegistry(LPCWSTR lpValueName, LPCWSTR lpData);
	BOOL SetDWORDValueRegistry(LPCWSTR lpValueName, DWORD dwValue);
	VOID CloseKeyRegistry();
};

#endif//SWREGISTRY_H