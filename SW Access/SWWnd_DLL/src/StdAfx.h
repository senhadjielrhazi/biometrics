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
//	SAGEM SA StdAfx Include Wnd Module										 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#ifndef SWSTDAFX_WND_H
#define SWSTDAFX_WND_H

//#include <afxwin.h>// MFC core and standard components


#pragma warning(disable:4146)
#pragma warning(disable:4192)

#include <windows.h> 
#import <mshtml.tlb> // Internet Explorer 5+
#include <mshtml.h>
#include <tchar.h>


#include "resource.h"

#include "SWVariable_Ps.h"
#include "SWTypeDef_Ps.h"

#include "SWVariable_Wnd.h"
#include "SWTypeDef_Wnd.h"

#include "SWWnd.h"

#include <oleacc.h>

#endif//SWSTDAFX_WND_H
