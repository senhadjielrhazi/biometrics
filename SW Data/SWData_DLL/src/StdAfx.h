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
//	SAGEM SA StdAfx Include Data Module 									 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#ifndef SWSTDAFX_DATA_H
#define SWSTDAFX_DATA_H

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#include <afxwin.h> 	// MFC core and standard components
#include <afxcmn.h> 		//Anim 
#include <afxdlgs.h>
#include <tchar.h>

#include <atlbase.h>//CComModule

//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>//IContexMenu

#include <list>
typedef std::list<std::basic_string<TCHAR> > string_list;
typedef std::list<std::basic_string<TCHAR>,HANDLE> HSFile_List;

#include <comdef.h>//Initializing IShellExtInit
#include <shlobj.h>//Initializing IShellExtInit

#include "SWVariable_Data.h"
#include "SWTypeDef_Data.h"

#include "SWVariable_Ps.h"
#include "SWTypeDef_Ps.h"

#include "SWCrypto_AES.h"

#include "SWMD_Data.h"

#include "resource.h"
#include "SWData_i.h"

#include "SWExtension.h"
#include "SWMenu.h"

#include "SWData_Page_1.h"
#include "SWData_Page_2.h"
#include "SWData_Page_3.h"
#include "SWData_Page_4.h"
#include "SWData_Property.h"

#endif//SWSTDAFX_DATA_H