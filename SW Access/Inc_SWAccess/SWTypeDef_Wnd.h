/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003. 									 //
//																			 //
//	File:		SWTypeDef_Wnd.h												 //
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




#ifndef SWTYPEDEF_WND_H
#define SWTYPEDEF_WND_H

typedef struct
{
	WCHAR m_pwc_AppClassN[VI_APPCLASS_MAX];
	WCHAR m_pwc_AppClassNP[VI_APPCLASSP_MAX];
	WCHAR m_pwc_AppTitleB[VI_APPTITLE_MAX];
} TActiveWndData, *PTActiveWndData;

enum T_SEARCH_VALIDITY
{
		HtmlNew 		= 0,
		HtmlOld 		= 1,
		HtmlNotValid	= 2
};

#endif//SWTYPEDEF_WND_H
