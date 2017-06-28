/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003. 									 //
//																			 //
//	File:		SWTypeDef_Access.h											 //
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




#ifndef SWTYPEDEF_ACCESS_H
#define SWTYPEDEF_ACCESS_H

typedef struct
{
	NOTIFYICONDATA	m_T_tnd;
	C_Registry		m_x_Registry;
	HANDLE			m_h_ExitOk;
	HANDLE			m_h_ExitKo;
	HANDLE			m_h_Start;
	HANDLE			m_h_Stop;
	BOOL			m_b_RunOnce;
	BOOL			m_b_UpdateOn;
	BOOL			m_b_StartStop;
	WCHAR			m_pwc_Path[256];
	INT				m_i_ExitTimeOut;
} TSWNotify,*PTSWNotify;

#endif//SWTYPEDEF_ACCESS_H
