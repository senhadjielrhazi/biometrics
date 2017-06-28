/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWAccess_Property.cpp										 //
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

IMPLEMENT_DYNCREATE(C_AccessWizard, CPropertySheetEx)
C_AccessWizard::C_AccessWizard(C_Wnd *i_Wnd,TAccessField *i_T_Access,TKeyField *i_T_Keys,WCHAR	*i_pwc_UserId)
:CPropertySheetEx(_T(""),NULL,0 )
{ 
	m_psh.dwFlags |= PSH_HASHELP | PSH_WIZARD97|PSH_WATERMARK | PSH_HEADER | PSH_USEPAGELANG;
	m_psh.pszbmWatermark = MAKEINTRESOURCE(IDB_WATERMARK_BITMAP);
	m_psh.pszbmHeader = MAKEINTRESOURCE(IDB_HEADER_BITMAP);
	m_psh.hInstance = AfxGetInstanceHandle();
	m_psh.pszIcon = MAKEINTRESOURCE(IDI_ACCESSOK_ICON);
	
	m_i_NbApplication				= 0;
	m_T_Access						= i_T_Access;
	
	m_Page_1.m_x_MainSheet			= (CPropertySheetEx *)this;
	
	m_Page_2.m_x_MainSheet			= (CPropertySheetEx *)this;
	m_Page_2.m_i_NbApplication		= &m_i_NbApplication;
	
	m_Page_3.m_x_MainSheet			= (CPropertySheetEx *)this;
	m_Page_3.m_Wnd					= i_Wnd;
	
	m_Page_4.m_i_NbApplication		= &m_i_NbApplication;
	m_Page_4.m_x_MainSheet			= (CPropertySheetEx *)this;
	m_Page_4.m_Wnd					= i_Wnd;
	m_Page_4.m_i_PageCode			= &m_i_PageCode;
	m_Page_4.m_T_Access 			= i_T_Access;
	m_Page_4.m_T_Keys				= i_T_Keys;
	m_Page_4.m_pwc_UserId			= i_pwc_UserId;
	
	m_Page_5.m_i_NbApplication		= &m_i_NbApplication;
	m_Page_5.m_x_MainSheet			= (CPropertySheetEx *)this;
	m_Page_5.m_i_PageCode			= &m_i_PageCode;
	m_Page_5.m_T_Access 		= i_T_Access;
	m_Page_5.m_T_Keys				= i_T_Keys;
	m_Page_5.m_pwc_UserId			= i_pwc_UserId;
	
	
	m_Page_6.m_x_MainSheet			= (CPropertySheetEx *)this;
	m_Page_6.m_i_PageCode			= &m_i_PageCode;
	
	AddPage(&m_Page_1);
	AddPage(&m_Page_2);
	AddPage(&m_Page_3);
	AddPage(&m_Page_4);
	AddPage(&m_Page_5);
	AddPage(&m_Page_6);
}

C_AccessWizard::~C_AccessWizard()
{
}

BEGIN_MESSAGE_MAP(C_AccessWizard, CPropertySheetEx)
//{{AFX_MSG_MAP(C_AccessWizard)
ON_WM_SHOWWINDOW()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//Handle the Property Sheets back next and finish button settings
BOOL C_AccessWizard::OnCmdMsg
(
 UINT nID, 
 INT nCode, 
 VOID* pExtra, 
 AFX_CMDHANDLERINFO* pHandlerInfo
 ) 
{
	//Handle the Property Sheets back next and finish button settings
	INT l_i_Page = GetActiveIndex( );
	
	switch(nID)
	{
	case BACK:
		{
			switch (l_i_Page)
			{
			case 0:
				{
					m_Page_1.OnBackPage();
					break;
				}
			case 1:
				{
					m_Page_2.OnBackPage();
					break;
				}
			case 2:
				{
					m_Page_3.OnBackPage();
					break;
				}
			case 3:
				{
					m_Page_4.OnBackPage();
					break;
				}
			case 4:
				{
					m_Page_5.OnBackPage();
					break;
				}
			case 5:
				{
					m_Page_6.OnBackPage();
					break;
				}
			}
			return 1;
		}
	case NEXT:
		{
			switch (l_i_Page)
			{
			case 0:
				{
					m_Page_1.OnNextPage();
					break;
				}
			case 1:
				{
					m_Page_2.OnNextPage();
					break;
				}
			case 2:
				{
					m_Page_3.OnNextPage();
					break;
				}
			case 3:
				{
					m_Page_4.OnNextPage();
					break;
				}
			case 4:
				{
					m_Page_5.OnNextPage();
					break;
				}
			case 5:
				{
					m_Page_6.OnNextPage();
					break;
				}
			}
			return 1;
		}
	case CANCEL :
		break;	
	case FINISH :	
		break;	
	case HELP:
		break;
	}
	return CPropertySheetEx::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

VOID C_AccessWizard::OnShowWindow
(
 BOOL bShow, 
 UINT nStatus
 ) 
{
	TAccessField	l_T_AccessFieldNull 			= {NULL};
	
	memset(&l_T_AccessFieldNull,0,sizeof(l_T_AccessFieldNull));
	
	if(bShow)
	{
		m_i_NbApplication = 0;
		
		for(int i = 0; i<VI_NBAPPLI_MAX;i++)
		{
			if(memcmp(&m_T_Access[i],&l_T_AccessFieldNull,sizeof(l_T_AccessFieldNull)) != 0)
				m_i_NbApplication++;
		}
		SetForegroundWindow();
	}
	
	CPropertySheetEx::OnShowWindow(bShow, nStatus);
}

BOOL C_AccessWizard::OnInitDialog
(
 VOID
 ) 
{
	
	WINDOWPLACEMENT lpwndpl_1;
	WINDOWPLACEMENT lpwndpl_2;
	WINDOWPLACEMENT lpwndpl_3;
	CRect			l_cr_Rect;
	LONG			l_l_dx, l_l_dy;
	LONG			l_l_dxParent, l_l_dyParent;
	
	
	BOOL l_b_Result = CPropertySheetEx::OnInitDialog();
	
	((CPropertySheetEx *)this)->ModifyStyle(0,WS_CAPTION |WS_POPUPWINDOW,0);
	((CPropertySheetEx *)this)->SetForegroundWindow();
	
	CWnd* pApplyButton_1 = GetDlgItem (HELP);
	ASSERT (pApplyButton_1);
	pApplyButton_1->GetWindowPlacement(&lpwndpl_1);
	pApplyButton_1->ShowWindow (SW_HIDE);
	
	CWnd* pApplyButton_2 = GetDlgItem (CANCEL);
	ASSERT (pApplyButton_2);
	pApplyButton_2->GetWindowPlacement(&lpwndpl_2);
	
	CWnd* pApplyButton_3 = GetDlgItem (NEXT);
	ASSERT (pApplyButton_3);
	pApplyButton_3->GetWindowPlacement(&lpwndpl_3);
	
	CWnd* pApplyButton_5 = GetDlgItem (FINISH);
	
	CWnd* pApplyButton_4 = GetDlgItem (BACK);
	ASSERT (pApplyButton_4);
	
	pApplyButton_2->SetWindowPlacement(&lpwndpl_1);
	pApplyButton_3->SetWindowPlacement(&lpwndpl_2);
	pApplyButton_5->SetWindowPlacement(&lpwndpl_2);
	pApplyButton_4->SetWindowPlacement(&lpwndpl_3);
	
	GetWindowRect( &l_cr_Rect);
	l_l_dx = l_cr_Rect.right - l_cr_Rect.left;
	l_l_dy = l_cr_Rect.bottom - l_cr_Rect.top;
	
	l_l_dxParent = GetSystemMetrics(SM_CXSCREEN);
	l_l_dyParent = GetSystemMetrics(SM_CYSCREEN);
	
	l_cr_Rect.left = (l_l_dxParent - l_l_dx) / 2;
	l_cr_Rect.top  = (l_l_dyParent - l_l_dy) / 3;
	
	SetWindowPos(&wndTopMost, l_cr_Rect.left, l_cr_Rect.top, 0, 0, SWP_NOSIZE);
	SetWizardButtons(PSWIZB_NEXT);
	return l_b_Result;
}