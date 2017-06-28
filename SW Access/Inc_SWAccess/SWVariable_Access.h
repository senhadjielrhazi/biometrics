/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003. 									 //
//																			 //
//	File:		SWVariable_Access.h											 //
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
//	SAGEM SA Access Module													 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#ifndef SWVARIABLE_ACCESS_H
#define SWVARIABLE_ACCESS_H

#define WM_HWNDNOTIFY_MSG			WM_USER + 200

#define VC_TIPACCESS_OK				"Secure Access Ok"
#define VC_TIPACCESS_NO				"Secure Access Erreur"

#define VC_ACCESSEXITOK				"SWACCESSEVENTEXITOKSAGEMSA"
#define VC_ACCESSEXITKO				"SWACCESSEVENTEXITKOSAGEMSA"
#define VC_ACCESSSTART				"SWACCESSEVENTSTARTSAGEMSA"
#define VC_ACCESSSTOP				"SWACCESSEVENTSTOPSAGEMSA"
#define VC_ACCESSADMIN				"SWACCESSEVENTADMINSAGEMSA"
#define VC_ACCESSADMINTHREAD		"ACCESSADMINTHREADSAGEMSA"
#define VC_ACCESSEXITTHREAD			"ACCESSEXITTHREADSAGEMSA"
#define VC_ACCESSSTARTTHREAD		"ACCESSSTARTTHREADSAGEMSA"
#define VC_ACCESSSTOPTHREAD			"ACCESSSTOPTHREADSAGEMSA"

#define	VC_NOTIFYCLASS_NAME			"AccessNotify"
#define VC_ACCESS_TITLE				"Secure Workstation - Assistant d'enregistrement du formulaire"
	
#define VC_YESUSER_DISPLAY_NAME		"Bonjour"
#define VC_NOUSER_DISPLAY_NAME		"Utilisateur Inconnu"

#define VC_ACCESSLIST_NAME			"La liste des formulaires disponibles"

#define VC_HELP_NAME				"Secure Workstation.hlp"

#define VC_ACCESSPAGE2_VIDE			"Le nom est vide."
#define VC_ACCESSPAGE2_EXIST		"Le nom existe déjà."
#define VC_ACCESSPAGE2_OK			"Le nom est correct."
 
#define VC_NOTIFYINFO_TITLE			"Secure Access"
#define VC_NOTIFYINFO_WARNING		"Le terminal n'est pas bien configuré. Il est impératif de :\r\n\r\n1- Branchez votre terminal biométrique.   \r\n2- Lancer l'assistant Secure Admin.\r\n3- Configurez votre matériel biométrique.   "
#define VC_NOTIFYINFO_ERREUR		"Le terminal a rencontré une erreur. Il est impératif de :  \r\n\r\n1- Re-branchez votre terminal biométrique.\r\n2- Lancer l'assistant Secure Admin.\r\n3- Re-configurez votre matériel biométrique. "

#define VC_ACCESS_REGOK				"Enregsitrement réussi."
#define VC_ACCESS_REGABORT			"Enregistrement annulé."
#define VC_ACCESS_REGERR			"Erreur d'enregistrement."
#define VC_ACCESS_UPDATEOK			"Mise à jour réussie."
#define VC_ACCESS_UPDATEABORT		"Mise à jour annulée."
#define VC_ACCESS_UPDATEERR			"Erreur de mise à jour."
#define VC_ACCESS_DELOK				"Suppresion du formulaire\r\nréussie."
#define VC_ACCESS_DELABORT			"Suppression du formulaire\r\nannulée."
#define VC_ACCESS_DELERR			"Erreur de suppression\r\ndu formulaire."
#define VC_ACCESS_ABORT				"Action annulée."

#endif//SWVARIABLE_ACCESS_H
