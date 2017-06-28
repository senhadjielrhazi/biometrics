/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWMD_Admin.h												 //
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
//	SAGEM SA DSP Admin Module												 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#ifndef SWMD_ADMIN_H
#define SWMD_ADMIN_H

BOOL		WlxIsSWValid
(
 VOID
 );

VOID		WlxAdminLockSW
(
 VOID
 );

BOOL		WlxIsSWLock
(
 VOID
 );

VOID		WlxAdminUnLock
(
 VOID
 );

TModuleRet	WlxAdminIdentOn
(
 TSpeDataOut &o_T_Data
 );

VOID		WlxAdminIdentOff
(
 VOID
 );

TModuleRet	WlxAdminUpdateOn
(
 TUpDataOut i_T_Data
 );

TModuleRet	WlxAdminEnrollOn
(
 TSupDataOut i_T_Data
 );

VOID		WlxAdminEnrollOff
(
 VOID
 );

INT 		WlxAdminEnrollPaint
(
 VOID
 );

VOID		WlxAdminDbOn
(
 TSWState	 &o_T_SWState,
 BOOL		i_b_EraseDel
 );

TModuleRet	WlxAdminUserOn
(
 WCHAR		*i_puc_UserId
 );

VOID		WlxAdminRefresh
(
 TSWState	 &o_T_SWState
 );

VOID		WlxSWReboot
(
 TSWState	&o_T_SWState
 );

#endif//SWMD_ADMIN_H
