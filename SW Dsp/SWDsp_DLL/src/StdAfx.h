/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003. 									 //
//																			 //
//	File:		StdAfx.h		 											 //
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
//	SAGEM SA StdAfx Include Dsp Module										 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#ifndef SWSTDAFX_DSP_H
#define SWSTDAFX_DSP_H

#pragma warning(disable:4244)
#pragma warning(disable:4715)

#include <windows.h>
#include <tchar.h>
#include <winsvc.h>

#include "SWVariable_Ps.h"
#include "SWTypeDef_Ps.h"
#include "SWVariable_Dsp.h"
#include "SWTypeDef_Dsp.h"
#include "SWDsp.h"
#include "SWMD_Logon.h"
#include "SWMD_Access.h"
#include "SWMD_Data.h"
#include "SWMD_Admin.h"

extern TSharedMemory *g_T_SharedMemory;
extern TLocalMemory	 g_T_LocalMemory;

#endif//SWSTDAFX_DSP_H