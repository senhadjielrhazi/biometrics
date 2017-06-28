/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003. 									 //
//																			 //
//	File:		SWWnd.h														 //
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




#ifndef SWWND_H
#define SWWND_H

#ifdef SWWND_EXPORTS
#define SWWND_API __declspec(dllexport)
#else
#define SWWND_API __declspec(dllimport)
#endif

class SWWND_API C_Wnd
{
public :
	C_Wnd();   
	~C_Wnd();
	
	TAccessField				m_T_WindowData;
	INT							m_i_AppOption;
	BOOL						m_b_GlobalProgress;
	HWND						m_h_hwndToSet;

private :
	HPEN						m_hp_Pen;
	HCURSOR 					m_hc_CursorSearch;
	HCURSOR 					m_hc_CursorPrevious;	
	HWND						m_h_hwndFound;
	HWND						m_h_hwndCurrent;
	LRESULT 					m_lr_ObjectResult;
	POINT						m_P_PointPosition;
	LONG						m_l_IndexPosition;
	
private:
	T_SEARCH_VALIDITY C_Wnd_CheckHtmlValidity (LONG l_IndexPosition);
	BOOL C_Wnd_CheckWindowValidity (HWND  i_h_hwndWindow, HWND  i_h_hwndToCheck);
	BOOL C_Wnd_HWnd2Html(HWND i_h_hwndBrowser);
	VOID C_Wnd_HighLightWindow(HWND  i_h_hwndFound);
	VOID C_Wnd_HighLightHtml(POINT i_P_ElementPosition);
	VOID C_Wnd_RefreshHtml(POINT i_P_ElementPosition);
	VOID C_Wnd_RefreshWindow (HWND  i_h_hwndToBeRefreshed);
	
public:	
	VOID C_Wnd_StartSearch(HWND	i_h_hwndCurrent,INT i_i_HideEnter);
	VOID C_Wnd_ProcessSearch();
	BOOL C_Wnd_StopSearch();

	BOOL C_Wnd_IsBrowser(HWND i_h_hwndBrowser);
	VOID C_Wnd_SetWndDataInHtml(TAccessField i_T_AccessField);
	BOOL C_Wnd_IsWndInHtml(TActiveWndData i_T_ActiveWnd, TAccessField i_T_AccessField);
	
	VOID C_Wnd_SetWndData(TAccessField i_T_AccessField);
	VOID C_Wnd_GetActiveWnd(TActiveWndData &o_T_ActiveWnd);
	BOOL C_Wnd_IsWndEqual(TActiveWndData i_T_ActiveWnd, TAccessField i_T_AccessField);
};

#endif//SWWND_H
