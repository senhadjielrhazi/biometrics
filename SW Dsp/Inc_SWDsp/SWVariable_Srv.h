/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003. 									 //
//																			 //
//	File:		SWVariable_Dsp.h											 //
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
//	SAGEM SA Data Service Provider Module									 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#ifndef SWVARIABLE_SRV_H
#define SWVARIABLE_SRV_H

#define	VI_MSOUSBDEVICE_SERIAL		-1
#define VI_MSORS232DEVICE_SERIAL	0
#define	VC_DBVERSION_NAME			"SWSP01"

#define VI_NB_RECORDS				100
#define VI_NB_FINGERS				2
#define VS_TIMEOUT					0
#define	VS_FAR						5

#define	VC_MSG_REMOVEFINGER			"Enlevez votre doigt"
#define	VC_MSG_LATENT				"Latente"
#define	VC_MSG_MOVEUP				"Déplacez en Haut"
#define	VC_MSG_MOVEDOWN				"Déplacez en Bas"
#define	VC_MSG_MOVELEFT				"Déplacez à Gauche"
#define	VC_MSG_MOVERIGHT			"Déplacez à Droite"
#define	VC_MSG_PRESSHEADER			"Appuyez Fort"
#define	VC_MSG_CAPTURE_1			"Capture du doigt 1/3"
#define	VC_MSG_CAPTURE_2			"Capture du doigt 2/3"
#define	VC_MSG_CAPTURE_3			"Capture du doigt 3/3"

#define BEEP_F_SHORT				600
#define BEEP_D_SHORT				100

#define BEEP_F_ERR					80
#define BEEP_D_ERR					500

#define BEEP_F_OK					440
#define BEEP_D_OK					500

#define VC_HOSTSERVICE_DISP			"User Authentication Service Provider"
#define VC_HOSTSERVICE_DESC			"Carring the terminal authentication and modules for Secure Workstation Product Suite."

#define VC_HOSTWAITMSOEXIT_NAME		"VCHOSTWAITMSOEXITNAMESAGEMSA"

#endif//SWVARIABLE_SRV_H
