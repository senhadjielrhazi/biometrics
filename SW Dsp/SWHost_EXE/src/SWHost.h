/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWHost.h													 //
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
//	SAGEM SA Data Service Provider Service									 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#ifndef SWHOST_H
#define SWHOST_H

DWORD WINAPI SuperviseThreadProc
(
 LPVOID lpvParam
 );

VOID SWInitImage
(
 VOID
 );

VOID SWCreateObject
(
 VOID
 );

VOID SWDeleteObject
(
 VOID
 );

DWORD WINAPI CancelThreadProc
(
 LPVOID lpvParam
 );

DWORD WINAPI PaintThreadProc
(
 LPVOID lpvParam
 );

DWORD WINAPI IdentThreadProc
(
 LPVOID lpvParam
 );

DWORD WINAPI EnrollThreadProc
(
 LPVOID lpvParam
 );


DWORD WINAPI SWOffThreadProc
(
 LPVOID lpvParam
 );

DWORD WINAPI SWOnThreadProc
(
 LPVOID lpvParam
 );
DWORD WINAPI UserThreadProc
(
 LPVOID lpvParam
 );


DWORD WINAPI DbThreadProc
(
 LPVOID lpvParam
 );

DWORD WINAPI UpdateThreadProc
(
 LPVOID lpvParam
 );

INT Enroll_Callback
(	 
 PVOID 					  i_pv_context,
 T_MORPHO_CALLBACK_COMMAND  i_i_command,
 PVOID 					 i_pv_param  
 );

#endif//SWHOST_H