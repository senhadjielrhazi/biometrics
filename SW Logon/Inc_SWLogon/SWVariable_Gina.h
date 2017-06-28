/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003. 									 //
//																			 //
//	File:		SWVariable_Gina.h											 //
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




#ifndef SWVARIABLE_GINA_H
#define SWVARIABLE_GINA_H

#define WLX_SAS_TYPE_BIO_HITOK      256
#define WLX_SAS_TYPE_BIO_HITNO      257
#define WLX_SAS_TYPE_BIO_ABORT		258


#define VC_BIOADMINLOCALEXIT		"BIOADMINLOCALEXITSAGEMSA"

#define VC_CHANGPASS_OK				"Votre mot de passe a été correctement changé."
#define VC_CHANGPASS_TITLE			"Changer le mot de passe"	
#define VC_CHANGPASS_ACCESS			"Vous n'avez pas le droit d'accès."
#define VC_CHANGPASS_INVALIDPASS	"Votre mot de passe est invalide."
#define VC_CHANGPASS_INVALIDDOMAIN	"Votre nom de domain est invalide."
#define VC_CHANGPASS_NOUSER			"Votre nom d'utilisateur est invalide."
#define VC_CHANGPASS_PASSSHORT		"Votre mot de passe est trop court."
#define VC_CHANGPASS_ERR			"Erreur inconnue."

#define WINLOGON_APP				TEXT("Winlogon")
#define USERINIT					TEXT("Userinit")
#define USERINIT_DEFAULT			TEXT("Userinit.exe")

#define VC_LOGON_WAITOK				"Identification..."
#define VC_LOGON_WAITKO				"Identification terminée."
#define VC_LOGON_AUTH_OK			"Identification réussie."
#define VC_LOGON_AUTH_ABORT			"Identification annulée."
#define VC_LOGON_AUTH_ERR			"Erreur d'identification."
#define VC_LOGON_PROCESSOK			"Action en cours..."
#define VC_LOGON_USER_OK			"Utilisateur reconnu."
#define VC_LOGON_USER_NO			"Utilisateur inconnu."
#define VC_LOGON_USER_ABORT			"Veuillez corriger le problème."
#define VC_LOGON_USER_ERR			"Veuillez corriger le problème."

#define VC_LOCK_USERSHOW			"Seul %s\\%s peut déverrouiller l'ordinateur."

#define VC_LOGON_WAITOKERR			"Erreur - Re-essai en cours..."

#endif //SWVARIABLE_GINA_H
