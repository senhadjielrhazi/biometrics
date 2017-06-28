/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWDsp.h 													 //
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




#ifndef SWDSP_H
#define SWDSP_H

BOOL WlxIsSWValid
(
 VOID
 );

VOID FreeAndCloseDllData
(
 VOID
 );

VOID AllocAndStoreDllData
(
 VOID
 );

VOID WlxSWOn
(
 TSWState &o_T_SWState
 );

VOID WlxSWOff
(
 VOID
 );

BOOL WlxIsDspLoaded
(
 VOID
 );

BOOL WlxIsSWLock
(
 VOID
 );

VOID WlxSWShutDown
(
 VOID
 );

#endif//SWDSP_H