/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2003. 										 //
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
//	Secure Personal Computer Suite Product									 //
//	SAGEM SA Access Module													 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/


#ifndef STDAFX_H
#define STDAFX_H

#define _WIN32_IE		0x0500
#define _WIN32_WINNT	0x0500

#include <afxwin.h>
#include <afxcmn.h>
#include <afxdlgs.h>	
#include <winuser.h>
#include <tchar.h>
#include <exception>


#include <ntsecapi.h>

#include "shellapi.h"
#include "resource.h"

#include "SWRegistry.h"
#include "SWCrypto_AES.h"

#include "SWVariable_Ps.h"
#include "SWTypeDef_Ps.h"

#include "SWVariable_Wnd.h"
#include "SWTypeDef_Wnd.h"

#include "SWVariable_Access.h"
#include "SWTypeDef_Access.h"

#include "SWMD_Access.h"

#include "SWWnd.h"

#include "SWAccess_Page_1.h"
#include "SWAccess_Page_2.h"
#include "SWAccess_Page_3.h"
#include "SWAccess_Page_4.h"
#include "SWAccess_Page_5.h"
#include "SWAccess_Page_6.h"
#include "SWAccess_Property.h"

#include "SWAccess_Ihm.h"
#include "SWAccess.h"

#endif//STDAFX_H
