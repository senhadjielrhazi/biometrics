/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWMD_Data.h 												 //
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
//	SAGEM SA DSP Data Module												 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#ifndef SWMD_DATA_H
#define SWMD_DATA_H

BOOL WlxIsSWValid
(
 VOID
 );


TModuleRet	WlxDataIdentOn
(
 TSpeDataOut &o_T_Data
 );

VOID		WlxDataIdentOff
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

#endif//SWMD_DATA_H
