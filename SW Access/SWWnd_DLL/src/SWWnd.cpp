/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWWnd.cpp													 //
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




#include "stdafx.h"

#pragma data_seg(".Wnd")
static MSHTML::IHTMLDocument2Ptr	g_p_HTMLDocument2		= NULL;
static MSHTML::IHTMLElement 		*g_p_HTMLElementToCheck = NULL;
static HINSTANCE					g_h_Hinstance			= NULL;
#pragma data_seg()
#pragma comment(linker,"/SECTION:.Wnd,RWS")

extern "C" BOOL WINAPI DllMain
(
 HINSTANCE hInstance, 
 DWORD dwReason, 
 LPVOID
 )
{
	if (dwReason == DLL_PROCESS_ATTACH)
		g_h_Hinstance = hInstance;
	else if (dwReason == DLL_PROCESS_DETACH){}
	return TRUE; 
}

C_Wnd::C_Wnd
(
 )
{
	m_b_GlobalProgress		= FALSE;	
	m_hc_CursorSearch		= ::LoadCursor(g_h_Hinstance,MAKEINTRESOURCE(IDC_CURSOR_SEARCH));
	m_hc_CursorPrevious 	= NULL; 
	m_h_hwndFound			= NULL;
	m_l_IndexPosition		= 0;
	m_lr_ObjectResult		= 0;
	
	m_hp_Pen = ::CreatePen (PS_SOLID, 2,RGB(0,0,254));
	
	memset(&m_T_WindowData,0,sizeof(TAccessField)); 
}

C_Wnd::~C_Wnd
(
 )
{
}

BOOL C_Wnd::C_Wnd_IsWndInHtml
(
 TActiveWndData i_T_ActiveWnd, 
 TAccessField i_T_AccessField
 )
{
	if(memcmp(i_T_ActiveWnd.m_pwc_AppClassN,i_T_AccessField.m_pwc_AppClassN,sizeof(i_T_AccessField.m_pwc_AppClassN))!=0)
		return FALSE;	
	if(memcmp(i_T_ActiveWnd.m_pwc_AppTitleB,i_T_AccessField.m_pwc_AppTitleB,sizeof(i_T_AccessField.m_pwc_AppTitleB))!=0)
		return FALSE;
	
	return TRUE;
}

VOID C_Wnd::C_Wnd_SetWndDataInHtml
(
 TAccessField i_T_AccessField
 )
{
	LONG							l_l_IndexPosition		= 0;
	LONG							l_l_IndexAccess 		= 0;
	bstr_t							l_bst_TextContain		= bstr_t();
	HRESULT 						l_hr_SuccedResult		= 0; 
	VARIANT 						l_v_Index				= {0}; 
	VARIANT 						l_v_Null				= {0};
	LPDISPATCH						l_p_Dispatch			= NULL;  
	LONG							l_l_CurrentIrem 		= 0; 
	MSHTML::IHTMLElement*			l_p_HTMLElement 		= NULL; 
	MSHTML::IHTMLElementCollection* l_pHTMLElementCollection= NULL;
	
	l_l_IndexAccess = _wcsnextc(i_T_AccessField.m_pwc_AppClassNP);
	
	if (SUCCEEDED(l_hr_SuccedResult = g_p_HTMLDocument2->get_all( &l_pHTMLElementCollection )))
	{ 
		// retrieve the count of elements in the collection 
		if (SUCCEEDED(l_hr_SuccedResult = l_pHTMLElementCollection->get_length( &l_l_CurrentIrem ))) 
		{ 
			// for each element retrieve Index 
			for (INT i=0; i<l_l_CurrentIrem; i++ ) 
			{ 
				l_v_Index.vt = VT_UINT; 
				l_v_Index.lVal = i;
				
				if (SUCCEEDED(l_hr_SuccedResult = l_pHTMLElementCollection->raw_item( l_v_Index, l_v_Null, &l_p_Dispatch )))
				{	
					if (SUCCEEDED(l_hr_SuccedResult = l_p_Dispatch->QueryInterface( IID_IHTMLElement, (LPVOID*)&l_p_HTMLElement )))
					{ 
						l_p_HTMLElement->get_sourceIndex(&l_l_IndexPosition);
						
						if(l_l_IndexAccess == l_l_IndexPosition)
						{
							l_bst_TextContain = i_T_AccessField.m_pwc_AppPassW;
							l_p_HTMLElement->put_innerText(l_bst_TextContain);
							if(i_T_AccessField.m_i_AppOption == 2 || i_T_AccessField.m_i_AppOption == 3)
							{
								::PostMessage(m_h_hwndToSet,WM_KEYDOWN,VK_RETURN,0);
								::PostMessage(m_h_hwndToSet,WM_KEYUP,VK_RETURN,0);
							}
							break;
						}
					}
				}
			}
		}
	}
	C_Wnd_RefreshWindow(m_h_hwndToSet);
}

VOID C_Wnd::C_Wnd_SetWndData
(
 TAccessField i_T_AccessField
 )
{
	HRESULT 				l_hr_SuccedResult	= 0;
	MSHTML::IHTMLElement	*l_p_HTMLElement	= NULL;
	bstr_t					l_bst_TextContain	= bstr_t();
	
	if(i_T_AccessField.m_i_AppOption == 1 || i_T_AccessField.m_i_AppOption == 3)
		::PostMessage(m_h_hwndToSet,EM_SETPASSWORDCHAR,'*',0);
	else
		::PostMessage(m_h_hwndToSet,EM_SETPASSWORDCHAR,0,0);		
	
	if(C_Wnd_IsBrowser(m_h_hwndToSet))
	{	
		if (!C_Wnd_HWnd2Html(m_h_hwndToSet) )
			return;
		
		l_hr_SuccedResult = g_p_HTMLDocument2->get_activeElement(&l_p_HTMLElement);
		l_bst_TextContain = i_T_AccessField.m_pwc_AppPassW;
		l_p_HTMLElement->put_innerText(l_bst_TextContain);
	}
	else
		::SendMessage(m_h_hwndToSet,WM_SETTEXT,0,(LPARAM)(LPCTSTR)i_T_AccessField.m_pwc_AppPassW);
	
	if(i_T_AccessField.m_i_AppOption == 2 || i_T_AccessField.m_i_AppOption == 3)
	{
		::PostMessage(m_h_hwndToSet,WM_KEYDOWN,VK_RETURN,0);
		::PostMessage(m_h_hwndToSet,WM_KEYUP,VK_RETURN,0);
	}
	
	C_Wnd_RefreshWindow(m_h_hwndToSet);
}

VOID C_Wnd::C_Wnd_GetActiveWnd
(
 TActiveWndData &o_T_ActiveWnd
 )
{
	HRESULT 				l_hr_SuccedResult	= 0;
	BSTR					l_bs_bstrResult 	= NULL;
	MSHTML::IHTMLElement	*l_p_HTMLElement	= NULL;
	LONG					l_l_IndexPosition	= NULL;
	INT 					l_i_UrlLenMax		= 0;
	INT 					l_i_UrlLen			= 0;
	WCHAR					*l_pwc_CharUrl		= NULL;
	HWND					l_h_hwndToSetP		= NULL;
	DWORD					l_dw_IDMain 		= 0;
	DWORD					l_dw_IDSetWindow	= 0;
	
	//Thread Ids
	l_dw_IDMain = ::GetCurrentThreadId();
	l_dw_IDSetWindow = ::GetWindowThreadProcessId(::GetForegroundWindow(),NULL);
	
	//Get active windows
	::AttachThreadInput(l_dw_IDMain,l_dw_IDSetWindow,TRUE);
	m_h_hwndToSet	= ::GetFocus();
	l_h_hwndToSetP	= ::GetParent(m_h_hwndToSet);
	::AttachThreadInput(l_dw_IDMain,l_dw_IDSetWindow,FALSE);
	
	//Full The User active window informations	
	if(C_Wnd_IsBrowser(m_h_hwndToSet))
	{
		memcpy(o_T_ActiveWnd.m_pwc_AppClassN,VC_BROWSERCLASS_NAME,VI_APPCLASS_MAX*sizeof(WCHAR)-1);
		
		if (!C_Wnd_HWnd2Html(m_h_hwndToSet) )
			return;
		l_hr_SuccedResult = g_p_HTMLDocument2->get_activeElement(&l_p_HTMLElement);
		if (l_hr_SuccedResult != S_OK )
			return;
		
		//Title Bar == URL
		g_p_HTMLDocument2->get_url(&l_bs_bstrResult);
		l_pwc_CharUrl = l_bs_bstrResult;		
		l_i_UrlLenMax = VI_APPTITLE_MAX*sizeof(WCHAR)-1;
		l_i_UrlLen = wcslen(l_pwc_CharUrl);
		memcpy(o_T_ActiveWnd.m_pwc_AppTitleB,l_pwc_CharUrl,(l_i_UrlLen>l_i_UrlLenMax)?l_i_UrlLenMax:l_i_UrlLen);
		
		//Window Parent == Index
		l_p_HTMLElement->get_sourceIndex(&l_l_IndexPosition);
		memcpy(o_T_ActiveWnd.m_pwc_AppClassNP,&l_l_IndexPosition,sizeof(l_l_IndexPosition));
	}
	else
	{
		::GetClassName(m_h_hwndToSet,o_T_ActiveWnd.m_pwc_AppClassN,VI_APPCLASS_MAX);
		
		if(l_h_hwndToSetP == NULL)
		{
			wsprintf(o_T_ActiveWnd.m_pwc_AppTitleB,L"%s",L"");
			wsprintf(o_T_ActiveWnd.m_pwc_AppClassNP,L"%s",L"");
		}
		else				
		{
			::GetWindowText(l_h_hwndToSetP,o_T_ActiveWnd.m_pwc_AppTitleB,VI_APPTITLE_MAX);
			::GetClassName(l_h_hwndToSetP,o_T_ActiveWnd.m_pwc_AppClassNP,VI_APPCLASSP_MAX); 
		}
	}
}

BOOL C_Wnd::C_Wnd_IsWndEqual
(
 TActiveWndData i_T_ActiveWnd, 
 TAccessField i_T_AccessField
 )
{
	if(memcmp(i_T_ActiveWnd.m_pwc_AppClassN,i_T_AccessField.m_pwc_AppClassN,sizeof(i_T_AccessField.m_pwc_AppClassN))!=0)
		return FALSE;
	
	if(memcmp(i_T_ActiveWnd.m_pwc_AppClassNP,i_T_AccessField.m_pwc_AppClassNP,sizeof(i_T_AccessField.m_pwc_AppClassNP))!=0)
		return FALSE;
	
	if(memcmp(i_T_ActiveWnd.m_pwc_AppTitleB,i_T_AccessField.m_pwc_AppTitleB,sizeof(i_T_AccessField.m_pwc_AppTitleB))!=0)
		return FALSE;
	
	return TRUE;
}

VOID C_Wnd::C_Wnd_StartSearch
(
 HWND	i_h_hwndCurrent,
 INT i_i_HideEnter
 )
{
	//Initialize the current object
	m_h_hwndCurrent 	= i_h_hwndCurrent;
	m_i_AppOption		= i_i_HideEnter;
	
	//Global variable
	m_b_GlobalProgress	= TRUE;
	
	//Initialize User Info
	memset(&m_T_WindowData,0,sizeof(TAccessField));
	
	//Initialize window
	m_h_hwndFound		= NULL;
	m_l_IndexPosition	= 0;
	
	//Update cursor
	m_hc_CursorPrevious = ::GetCursor ();
	
	//Update cursor
	::SetCursor(m_hc_CursorSearch);
	
	//Release mouse and capture it to search window
	::ReleaseCapture();
	::SetCapture(m_h_hwndCurrent);
}

VOID C_Wnd::C_Wnd_ProcessSearch
(
 VOID
 )
{
	
	LONG							l_l_IndexPosition			= 0;
	HRESULT 						l_hr_SuccedResult			= 0;
	POINT							l_P_ScreenPoint 			= {NULL,NULL};
	HWND							l_h_hwndFound				= NULL;
	MSHTML::IHTMLElement			*l_p_HTMLElement			= NULL;
	T_SEARCH_VALIDITY				T_SearchState				= T_SEARCH_VALIDITY(0);
	
	::GetCursorPos(&l_P_ScreenPoint);
	l_h_hwndFound = ::WindowFromPoint(l_P_ScreenPoint);
	
	if(C_Wnd_IsBrowser(l_h_hwndFound))
	{
		if(m_h_hwndFound != l_h_hwndFound && m_h_hwndFound)
		{
			C_Wnd_RefreshWindow(m_h_hwndFound);
			m_h_hwndFound = l_h_hwndFound;
		}
		if(C_Wnd_HWnd2Html(l_h_hwndFound))
		{
			::ScreenToClient(l_h_hwndFound,&l_P_ScreenPoint);
			
			l_hr_SuccedResult = g_p_HTMLDocument2->raw_elementFromPoint
				(
				l_P_ScreenPoint.x,
				l_P_ScreenPoint.y,
				&l_p_HTMLElement
				);
			
			l_p_HTMLElement->get_sourceIndex(&l_l_IndexPosition);
			g_p_HTMLElementToCheck = l_p_HTMLElement;
			T_SearchState = C_Wnd_CheckHtmlValidity(l_l_IndexPosition);
			switch(T_SearchState)
			{
			case HtmlNew:
				{
					C_Wnd_RefreshHtml(m_P_PointPosition);
					m_l_IndexPosition = l_l_IndexPosition;
					m_P_PointPosition.x = l_P_ScreenPoint.x;
					m_P_PointPosition.y = l_P_ScreenPoint.y;
					C_Wnd_HighLightHtml(m_P_PointPosition); 
					break;
				}
			case HtmlOld :
				break;
			default:
				{
					C_Wnd_RefreshHtml(m_P_PointPosition); 
					m_l_IndexPosition = 0;
					break;
				}
			}
		}
		else
			C_Wnd_RefreshHtml(m_P_PointPosition);
	}
	
	else
	{
		if(m_l_IndexPosition != 0)
		{
			C_Wnd_RefreshHtml(m_P_PointPosition);
			m_l_IndexPosition = 0;
		}
		
		//Check the window validity
		if(C_Wnd_CheckWindowValidity(m_h_hwndCurrent,l_h_hwndFound))
		{
			if(m_h_hwndFound)
				C_Wnd_RefreshWindow(m_h_hwndFound);
			
			m_h_hwndFound = l_h_hwndFound;
			C_Wnd_HighLightWindow(m_h_hwndFound);
		}
	}
}

BOOL C_Wnd::C_Wnd_StopSearch
(
 VOID
 )
{
	HRESULT 				l_hr_SuccedResult	= 0;
	LONG					l_l_IndexPosition	= 0;
	MSHTML::IHTMLElement	*l_p_HTMLElement	= NULL;
	bstr_t					l_bst_TextContain	= bstr_t();
	INT 					l_i_UrlLenMax		= 0;
	INT 					l_i_UrlLen			= 0;
	BSTR					l_bs_bstrResult 	= NULL;
	POINT					l_P_ScreenPosition	= {NULL,NULL};
	HWND					l_h_hwndFound		= NULL;
	HWND					l_h_hwndFoundP		= NULL;
	WCHAR					*l_pwc_CharUrl		= NULL;
	
	m_b_GlobalProgress = FALSE;
	
	//Update cursor
	::SetCursor(m_hc_CursorPrevious);
	
	//Release mouse and capture it to search window
	::ReleaseCapture();
	
	::GetCursorPos(&l_P_ScreenPosition);
	l_h_hwndFound = ::WindowFromPoint(l_P_ScreenPosition);
	
	if(C_Wnd_IsBrowser(l_h_hwndFound))
	{
		::ScreenToClient(l_h_hwndFound,&l_P_ScreenPosition);
		l_hr_SuccedResult = g_p_HTMLDocument2->raw_elementFromPoint
			(
			l_P_ScreenPosition.x,
			l_P_ScreenPosition.y,
			&l_p_HTMLElement
			);
		if (l_hr_SuccedResult != S_OK )
			return FALSE;
		
		l_p_HTMLElement->get_sourceIndex(&l_l_IndexPosition);
		
		if(m_l_IndexPosition != l_l_IndexPosition )
		{
			C_Wnd_RefreshHtml(m_P_PointPosition);
			return FALSE;
		}
		else
		{
			//Hide & Enter Option
			m_T_WindowData.m_i_AppOption = m_i_AppOption;
			
			//Set the password to the choisen window && erase it from the password box.
			::GetWindowText(m_h_hwndCurrent,m_T_WindowData.m_pwc_AppPassW,VI_APPPASSW_MAX);
			::SetWindowText(m_h_hwndCurrent,L"");
			l_bst_TextContain = m_T_WindowData.m_pwc_AppPassW;
			l_p_HTMLElement->put_innerText(l_bst_TextContain);
			
			//Window Class.
			memcpy(m_T_WindowData.m_pwc_AppClassN,VC_BROWSERCLASS_NAME,VI_APPCLASS_MAX*sizeof(WCHAR)-1);
			
			//Window Parent is index now.
			memcpy(m_T_WindowData.m_pwc_AppClassNP,&l_l_IndexPosition,sizeof(l_l_IndexPosition));
			
			//Window Title is URL now.
			g_p_HTMLDocument2->get_url(&l_bs_bstrResult);
			l_pwc_CharUrl = l_bs_bstrResult;
			l_i_UrlLenMax = VI_APPTITLE_MAX*sizeof(WCHAR)-1;
			l_i_UrlLen = wcslen(l_pwc_CharUrl);
			memcpy(m_T_WindowData.m_pwc_AppTitleB,l_pwc_CharUrl,(l_i_UrlLen>l_i_UrlLenMax)?l_i_UrlLenMax:l_i_UrlLen);
			
			//Remove highlight
			C_Wnd_RefreshHtml(m_P_PointPosition);
			m_l_IndexPosition = 0;
			return TRUE;	
		}
	}
	else
	{
		//If we are in the final valide window 
		if(m_h_hwndFound != l_h_hwndFound)
		{
			//Remove highlight
			if(m_h_hwndFound)
				C_Wnd_RefreshWindow (m_h_hwndFound);
			
			return FALSE;
		}
		else
		{
			//Hide & Enter Option
			m_T_WindowData.m_i_AppOption = m_i_AppOption;
			if(m_i_AppOption == 1 || m_i_AppOption == 3)
				::PostMessage(m_h_hwndFound,EM_SETPASSWORDCHAR,'*',0);	
			else
				::PostMessage(m_h_hwndFound,EM_SETPASSWORDCHAR,0,0);
			
			//Set the password to the choisen window && erase it from the password box.
			::GetWindowText(m_h_hwndCurrent,m_T_WindowData.m_pwc_AppPassW,VI_APPPASSW_MAX);
			::SetWindowText(m_h_hwndCurrent,L"");
			//Fix Microsoft Bug!
			::SendMessage(m_h_hwndFound,WM_SETTEXT,0,(LPARAM)(LPCTSTR)m_T_WindowData.m_pwc_AppPassW);
			
			//Window Class
			::GetClassName(m_h_hwndFound,m_T_WindowData.m_pwc_AppClassN,VI_APPCLASS_MAX);
			
			//Window Parent Class & Title: NULL /*Big Problem!*/
			l_h_hwndFoundP = ::GetParent(m_h_hwndFound);
			if(l_h_hwndFoundP == NULL)
			{
				wsprintf(m_T_WindowData.m_pwc_AppClassNP,L"%s",L"");
				wsprintf(m_T_WindowData.m_pwc_AppTitleB,L"%s",L"");
			}
			//Window Parent Class & Title Ok!
			else
			{
				::GetWindowText(l_h_hwndFoundP,m_T_WindowData.m_pwc_AppTitleB,VI_APPTITLE_MAX);
				::GetClassName(l_h_hwndFoundP,m_T_WindowData.m_pwc_AppClassNP,VI_APPCLASSP_MAX);
			}
			//Remove highlight
			C_Wnd_RefreshWindow (m_h_hwndFound);			
			return TRUE;
		}	
	}
}

BOOL C_Wnd::C_Wnd_IsBrowser
(
 HWND i_h_hwndBrowser
 )
{
	WCHAR		l_pwc_TmpNameClass[200] = {NULL};
	
	memset(l_pwc_TmpNameClass,0,sizeof(l_pwc_TmpNameClass));
	::GetClassName(i_h_hwndBrowser,l_pwc_TmpNameClass,sizeof(l_pwc_TmpNameClass)/sizeof(WCHAR));	
	return(memcmp(l_pwc_TmpNameClass,_T(VC_BROWSERCLASS_NAME),sizeof(_T(VC_BROWSERCLASS_NAME))) == 0);
}

BOOL C_Wnd::C_Wnd_HWnd2Html
(
 HWND i_h_hwndBrowser
 )
{	
	UINT		l_ui_MsgTimeOut 	= 0;
	LRESULT 	l_lr_TimeOutRes 	= 0;
	HRESULT 	l_hr_SuccedResult	= 0;
	
	CoInitialize(NULL);
	l_ui_MsgTimeOut = ::RegisterWindowMessage(_T("WM_HTML_GETOBJECT"));
	l_lr_TimeOutRes = ::SendMessageTimeout
		(
		i_h_hwndBrowser, l_ui_MsgTimeOut,
		0L, 0L, SMTO_ABORTIFHUNG, 1000, 
		(DWORD*)&m_lr_ObjectResult 
		);
	if(!l_lr_TimeOutRes)
		return FALSE;
	
	l_hr_SuccedResult = ::ObjectFromLresult
		(
		m_lr_ObjectResult, 
		__uuidof(MSHTML::IHTMLDocument2),
		0, (VOID**)&g_p_HTMLDocument2
		);
	
	return (l_hr_SuccedResult == S_OK );
}

VOID C_Wnd::C_Wnd_RefreshWindow 
(
 HWND  i_h_hwndToBeRefreshed
 )
{	
	::RedrawWindow (i_h_hwndToBeRefreshed, NULL, NULL,RDW_ERASE | RDW_FRAME| RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
}

VOID C_Wnd::C_Wnd_RefreshHtml
(
 POINT i_P_ElementPosition
 )
{
	HRESULT 				l_hr_SuccedResult	= 0;
	MSHTML::IHTMLStyle		*l_p_HTMLStyle		= NULL;
	MSHTML::IHTMLElement	*l_p_HTMLElement	= NULL; 
	
	if(m_l_IndexPosition !=0)
	{
		l_hr_SuccedResult = g_p_HTMLDocument2->raw_elementFromPoint
			(
			i_P_ElementPosition.x,
			i_P_ElementPosition.y,
			&l_p_HTMLElement
			);
		
		if (l_hr_SuccedResult != S_OK )
			return;
		
		l_p_HTMLElement->get_style(&l_p_HTMLStyle);
		l_p_HTMLStyle->put_borderColor(NULL);
	}
}

VOID C_Wnd::C_Wnd_HighLightHtml
(
 POINT i_P_ElementPosition
 )
{	
	HRESULT 				l_hr_SuccedResult	= 0;
	MSHTML::IHTMLStyle		*l_p_HTMLStyle		= NULL;
	MSHTML::IHTMLElement	*l_p_HTMLElement	= NULL;
	
	l_hr_SuccedResult = g_p_HTMLDocument2->raw_elementFromPoint(
		i_P_ElementPosition.x,
		i_P_ElementPosition.y,
		&l_p_HTMLElement
		);
	
	if (l_hr_SuccedResult != S_OK )
		return;
	
	l_p_HTMLElement->get_style(&l_p_HTMLStyle);
	l_p_HTMLStyle->put_borderColor(_T(VC_PENCOLOR_NAME));
}

VOID C_Wnd::C_Wnd_HighLightWindow
(
 HWND	i_h_hwndFound
 )
{
	HDC 			l_h_WindowDC	= NULL;
	HGDIOBJ 		l_h_PrevPen 	= NULL;
	HGDIOBJ 		l_h_PrevBrush	= NULL;
	RECT			l_rc_Rect		= {NULL,NULL,NULL,NULL};
	
	::GetWindowRect(i_h_hwndFound,&l_rc_Rect);
	l_h_WindowDC = ::GetWindowDC(i_h_hwndFound);
	
	if(l_h_WindowDC)
	{
		l_h_PrevPen = ::SelectObject(l_h_WindowDC,m_hp_Pen);
		l_h_PrevBrush = ::SelectObject(l_h_WindowDC,::GetStockObject(HOLLOW_BRUSH));
		::Rectangle(l_h_WindowDC,2,2,l_rc_Rect.right-l_rc_Rect.left-2,l_rc_Rect.bottom-l_rc_Rect.top-2);
		::SelectObject(l_h_WindowDC,l_h_PrevPen);
		::SelectObject(l_h_WindowDC,l_h_PrevBrush);
		::ReleaseDC(i_h_hwndFound,l_h_WindowDC);	
	}
}	

BOOL C_Wnd::C_Wnd_CheckWindowValidity 
(
 HWND  i_h_hwndWindow, 
 HWND  i_h_hwndToCheck
 )
{
	HWND		l_h_hwndTemp = NULL;
	
	l_h_hwndTemp = ::GetParent (::GetParent (i_h_hwndWindow));
	
	// The window must not be NULL.
	if (i_h_hwndToCheck == NULL)
		return FALSE;
	
	// It must also be a valid window as far as the OS is concerned.
	if (::IsWindow(i_h_hwndToCheck) == FALSE)
		return FALSE;
	
	// Ensure that the window is not the current one which has already been found.
	if (i_h_hwndToCheck == m_h_hwndFound)
		return FALSE;
	
	// It also must not be the "Search Window" dialog box itself.
	if (i_h_hwndToCheck == l_h_hwndTemp)
		return FALSE;
	
	// It also must not be one of the dialog box's children...
	if (::IsChild(l_h_hwndTemp, i_h_hwndToCheck))
		return FALSE;
	
	return TRUE;
}

T_SEARCH_VALIDITY C_Wnd::C_Wnd_CheckHtmlValidity
(
 LONG i_l_IndexPosition
 )
{
	HRESULT 						l_hr_SuccedResult			= 0;
	bstr_t							l_bst_TypeInput 			= bstr_t(_T("INPUT"));
	bstr_t							l_bst_TypeText				= bstr_t(_T("text"));
	bstr_t							l_bst_TypePassword			= bstr_t(_T("password"));
	BSTR							l_bs_bstrResult 			= NULL;
	MSHTML::IHTMLElementCollection	*l_p_HTMLElementCollection	= NULL;
	LPDISPATCH						l_p_Dispatsh				= NULL;
	MSHTML::IHTMLInputElementPtr	l_p_HTMLInputElementPtr 	= NULL;
	bstr_t							l_bst_BsToBst				= bstr_t();
	
	l_hr_SuccedResult	= g_p_HTMLElementToCheck->get_tagName(&l_bs_bstrResult); 
	l_bst_BsToBst		= l_bs_bstrResult;
	
	if(l_bst_BsToBst == l_bst_TypeInput)
	{
		l_hr_SuccedResult = g_p_HTMLDocument2->get_all(&l_p_HTMLElementCollection);
		if (l_hr_SuccedResult != S_OK )
			return HtmlNotValid;
		
		l_p_Dispatsh = l_p_HTMLElementCollection->item(i_l_IndexPosition, i_l_IndexPosition);	
		l_hr_SuccedResult = l_p_Dispatsh->QueryInterface(&l_p_HTMLInputElementPtr); 
		if (l_hr_SuccedResult != S_OK )
			return HtmlNotValid;
		
		l_p_HTMLInputElementPtr->get_type(&l_bs_bstrResult);
		l_bst_BsToBst = l_bs_bstrResult;
		if(l_bst_BsToBst== l_bst_TypeText ||l_bst_BsToBst== l_bst_TypePassword )
		{
			if(i_l_IndexPosition != m_l_IndexPosition)
				return HtmlNew;
			
			return HtmlOld;
		}
		else
			return HtmlNotValid;
	}
	else
		return HtmlNotValid;
}
