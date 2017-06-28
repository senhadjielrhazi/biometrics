/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWMD_Logon.h													 //
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
//	SAGEM SA DSP Logon Module												 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#ifndef SWMD_LOGON_H
#define SWMD_LOGON_H

BOOL WlxIsSWValid
(
 VOID
 );

TModuleRet	WlxLogonIdentOn
(
 TSpeDataOut &o_T_Data
 );

VOID		WlxLogonIdentOff
(
 VOID
 );

VOID		WlxSWReboot
(
 TSWState &o_T_SWState
 );

BOOL		WlxIsSWLock
(
 VOID
 );

VOID		WlxSWShutDown
(
	VOID
	);

#endif//SWMD_LOGON_H
