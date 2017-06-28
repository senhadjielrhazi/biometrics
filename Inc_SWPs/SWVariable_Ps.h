/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003. 									 //
//																			 //
//	File:		SWVariable_Ps.h												 //
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
//	SAGEM SA All Globals Variables											 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#ifndef SWVARIABLE_PS_H
#define SWVARIABLE_PS_H

//Enroll page identification

#define VC_ADMIN_TITLE					"Secure Workstation - Assistant d'Administration"

//Max number of domain
#define DOMAIN_MAX_COUNT				64

//Service identification
#define VC_HOSTSERVICE_NAME				"SWHost.exe"

#define VC_HOSTMUTEX_NAME				"SWPSHOSTMUTEXNAMESAGEMSA"
#define VC_ACCESSMUTEX_NAME				"SWPSACCESSMUTEXNAMESAGEMSA"
#define VC_DATAMUTEX_NAME				"SWPSDATAMUTEXNAMESAGEMSA"
#define VC_LOGONMUTEX_NAME				"SWPSLOGONMUTEXNAMESAGEMSA"
#define VC_ADMINMUTEX_NAME				"SWPSADMINMUTEXNAMESAGEMSA"


//SW MSG ident
#define WM_HWNDBIO_MSG					WM_USER + 100

//Ident user message
#define VC_MSOERR_COM					"Le terminal n'est pas connecté."
#define	VC_MSOERR_DB					"Le terminal n'est pas configuré."
#define VC_MSOOK_WAITING				"Veuillez poser votre doigt sur le capteur."

#define FINISH							0x3025
#define NEXT							0x3024
#define BACK							12323 //0x3023
#define HELP							0x0009
#define	CANCEL							0x0002

//Size of fields and struct in data base\\Less than 1 for PC.
#define	VI_DBFIELD_MAX					64
#define	VI_USERID_MAX					5

//Define for Data Fields
#define VI_BASEKEY_MAX					16
#define VI_DATAKEY_MAX					16

//Define for Logon Fields
#define	VI_USERLOGON_MAX				21
#define	VI_USERPASSW_MAX				21
#define	VI_USERDOMAIN_MAX				21

//Define for Access Fields
#define	VI_NBAPPLI_MAX					18
#define VI_APPCLASS_MAX					12
#define VI_APPCLASSP_MAX				12
#define VI_APPTITLE_MAX					13
#define VI_APPPASSW_MAX					15
#define VI_APPNAME_MAX					10

//Define for registry Gina user\domain 
#define VC_REGLASTLOGON_NAME			"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"
#define VC_REGACCESS_NAME				"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"
#define VC_REGRUNONCE_NAME				"Secure Access"
#define VC_REGLASTUSER_NAME				"AltDefaultUserName"
#define VC_REGLASTDOMAIN_NAME			"AltDefaultDomainName"

#endif//SWVARIABLE_PS_H


