/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWConfig_Property.cpp										 //
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
//	SAGEM SA Administration Module											 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#include "stdafx.h"

IMPLEMENT_DYNCREATE(C_ConfigWizard, CPropertySheetEx)
C_ConfigWizard::C_ConfigWizard(CWnd *pParentWnd)
:CPropertySheetEx(_T(""),pParentWnd,0,NULL,NULL,NULL)
{
	m_psh.dwFlags |= PSH_HASHELP | PSH_MODELESS |PSH_WIZARD97|PSH_WATERMARK | PSH_HEADER | PSH_USEPAGELANG;
	m_psh.pszbmWatermark = MAKEINTRESOURCE(IDB_WATERMARKBMP);
	m_psh.pszbmHeader = MAKEINTRESOURCE(IDB_HEADERBMP);
	m_psh.hInstance = AfxGetInstanceHandle();
	
	m_i_PageCode = 0;
	
	m_Page_1.m_x_MainSheet		= this;
	m_Page_1.m_i_PageCode		= &m_i_PageCode;
	
	
	m_Page_2.m_x_MainSheet		= this;
	m_Page_2.m_i_PageCode		= &m_i_PageCode;
	m_Page_2.m_T_SWContex		= &m_T_SWContex;
	
	m_Page_3.m_x_MainSheet		= this;
	m_Page_3.m_i_PageCode		= &m_i_PageCode;
	m_Page_3.m_T_SWContex		= &m_T_SWContex;
	
	
	m_Page_4.m_T_DataIn 		= &m_T_DataIn;
	m_Page_4.m_pwc_UserLogin	= m_pwc_UserLogin;
	m_Page_4.m_i_PageCode		= &m_i_PageCode;
	m_Page_4.m_x_MainSheet		= this;
	
	m_Page_5.m_T_DataIn 		= &m_T_DataIn;
	m_Page_5.m_pwc_UserLogin	= m_pwc_UserLogin;
	m_Page_5.m_i_PageCode		= &m_i_PageCode;
	m_Page_5.m_x_MainSheet		= this;
	m_Page_5.m_T_SWContex		= &m_T_SWContex;
	
	m_Page_6.m_T_Logon			= &m_T_Logon;
	m_Page_6.m_T_Keys			= &m_T_Keys;
	m_Page_6.m_pwc_UserId		= m_pwc_UserId;
	m_Page_6.m_i_PageCode		= &m_i_PageCode;
	m_Page_6.m_x_MainSheet		= this;
	
	m_Page_7.m_T_Logon			= &m_T_Logon;
	m_Page_7.m_T_Keys			= &m_T_Keys;
	m_Page_7.m_pwc_UserId		= m_pwc_UserId;
	m_Page_7.m_i_PageCode		= &m_i_PageCode;
	m_Page_7.m_x_MainSheet		= this;
	m_Page_7.m_T_SWContex		= &m_T_SWContex;
	
	m_Page_8.m_i_PageCode		= &m_i_PageCode;
	m_Page_8.m_x_MainSheet		= this;
	
	AddPage(&m_Page_1);
	AddPage(&m_Page_2);
	AddPage(&m_Page_3);
	AddPage(&m_Page_4);
	AddPage(&m_Page_5);
	AddPage(&m_Page_6);
	AddPage(&m_Page_7);
	AddPage(&m_Page_8);
	
}

C_ConfigWizard::~C_ConfigWizard()
{
}

BEGIN_MESSAGE_MAP(C_ConfigWizard, CPropertySheetEx)
//{{AFX_MSG_MAP(C_ConfigWizard)
ON_WM_SHOWWINDOW()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL C_ConfigWizard::OnCmdMsg
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
			case 6:
				{
					m_Page_7.OnBackPage();
					break;
				}
			case 7:
				{
					m_Page_8.OnBackPage();
					break;
				}
			case 8:
				{
					m_Page_8.OnBackPage();
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
			case 6:
				{
					m_Page_7.OnNextPage();
					break;
				}
			case 7:
				{
					m_Page_8.OnNextPage();
					break;
				}
			case 8:
				{
					m_Page_8.OnNextPage();
					break;
				}
			}
			return 1;
		}
	case CANCEL :
		{ 
			switch (l_i_Page)
			{
			case 4:
				{
					m_Page_5.OnFinishPage();
					break;
				}
			case 5:
				{
					m_Page_6.OnFinishPage();
					break;	
				}
			default:
				break;
			}
			break;	
		}
	case FINISH :
		{	
			switch (l_i_Page)
			{
			case 4:
				{
					m_Page_5.OnFinishPage();
					break;
				}
			case 5:
				{
					m_Page_6.OnFinishPage();
					break;	
				}
			default:
				break;
			}
			break;	
		}
	}
	
	return CPropertySheetEx::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

VOID C_ConfigWizard::OnShowWindow
(
 BOOL bShow, 
 UINT nStatus
 ) 
{
	if(bShow)
	{
		SetForegroundWindow();
	}
	
	CPropertySheetEx::OnShowWindow(bShow, nStatus);
}



BOOL C_ConfigWizard::OnInitDialog
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