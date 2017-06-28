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
//	SAGEM SA StdAfx Include Admin Module									 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#ifndef SWSTDAFX_CONFIG_H
#define SWSTDAFX_CONFIG_H

#pragma warning(disable:4146)

#include <afxwin.h>		// MFC core and standard components
#include <afxcmn.h>		//Anim 
#include <afxdlgs.h>	//Property Sheet

#include <lm.h>	
#include <ntsecapi.h>

#include "resource.h"

#include "SWCrypto_AES.h"

#include "SWVariable_Ps.h"
#include "SWTypeDef_Ps.h"

#include "SWVariable_Config.h"
#include "SWTypeDef_Config.h"

#include "SWRegistry.h"

#include "SWMD_Admin.h"
#include "SWConfig.h"
#include "SWConfig_Page_1.h"
#include "SWConfig_Page_2.h"
#include "SWConfig_Page_3.h"
#include "SWConfig_Page_4.h"
#include "SWConfig_Page_5.h"
#include "SWConfig_Page_6.h"
#include "SWConfig_Page_7.h"
#include "SWConfig_Page_8.h"
#include "SWConfig_Property.h"

#endif//SWSTDAFX_CONFIG_H
