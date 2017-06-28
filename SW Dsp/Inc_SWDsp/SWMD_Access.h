/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWMD_Access.h												 //
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
//	SAGEM SA DSP Access Module												 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#ifndef SWMD_ACCESS_H
#define SWMD_ACCESS_H

BOOL WlxIsSWValid
(
 VOID
 );


TModuleRet	WlxAccessIdentOn
(
 TAllDataOut &o_T_Data
 );

VOID		WlxAccessIdentOff
(
 VOID
 );

TModuleRet	WlxAccessUpdateOn
(
 TUpDataOut i_T_Data
 );

VOID		WlxSWReboot
(
 TSWState &o_T_SWState
 );

BOOL		WlxIsSWLock
(
 VOID
 );

BOOL WlxIsSWLock
(
 VOID
 );

#endif//SWMD_ACCESS_H
