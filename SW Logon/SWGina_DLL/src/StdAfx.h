/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		StdAfx.h													 //
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
//	SAGEM SA StdAfx Include Logon Module									 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#ifndef SWSTDAFX_LOGON_H
#define SWSTDAFX_LOGON_H

#define _WIN32_WINNT	0x0500

#include <windows.h>
#include <commctrl.h>
#include <lm.h>
#include <winwlx.h>
#include <ntsecapi.h>
#include <tchar.h>

#include "resource.h"

#include "SWRegistry.h"
#include "SWCrypto_AES.h"

#include "SWVariable_Ps.h"
#include "SWTypeDef_Ps.h"

#include "SWVariable_Gina.h"
#include "SWTypeDef_Gina.h"

#include "SWGlobals.h"
#include "SWLogon.h"
#include "SWMD_Logon.h"
#include "SWGina.h"
#include "SWConfig.h"

#endif//SWSTDAFX_LOGON_H