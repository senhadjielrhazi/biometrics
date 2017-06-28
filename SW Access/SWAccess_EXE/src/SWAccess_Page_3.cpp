/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWAccess_Page_3.cpp 										 //
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

IMPLEMENT_DYNCREATE(CPage_3, CPropertyPageEx)
CPage_3::CPage_3() : CPropertyPageEx(CPage_3::IDD)
{
	m_p_Font.CreateFont(18, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0,PROOF_QUALITY,VARIABLE_PITCH | FF_SWISS, L""); 
	//{{AFX_DATA_INIT(CPage_3)
	m_Edit_Page_3_1 = _T("");
	//}}AFX_DATA_INIT
}

CPage_3::~CPage_3
(
 )
{
}

VOID CPage_3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage_3)
	DDX_Control(pDX, IDC_EDIT_PAGE_3_1, m_Edit_Page_3_1_CWnd);
	DDX_Text(pDX, IDC_EDIT_PAGE_3_1, m_Edit_Page_3_1);
	DDV_MaxChars(pDX, m_Edit_Page_3_1, VI_APPPASSW_MAX-1);
	DDX_Control(pDX, IDC_RADIO_PAGE_3_1, m_Check_Page_3_1_CWnd);
	DDX_Control(pDX, IDC_RADIO_PAGE_3_2, m_Check_Page_3_2_CWnd);
	DDX_Check(pDX, IDC_RADIO_PAGE_3_1, m_Check_Page_3_1);
	DDX_Check(pDX, IDC_RADIO_PAGE_3_2, m_Check_Page_3_2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPage_3, CPropertyPageEx)
//{{AFX_MSG_MAP(CPage_3)
ON_WM_SHOWWINDOW()
ON_BN_CLICKED(IDC_RADIO_PAGE_3_1, OnCheckPage_3_1)
ON_BN_CLICKED(IDC_RADIO_PAGE_3_2, OnCheckPage_3_2)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CPage_3::OnInitDialog
(
 VOID
 ) 
{
	CPropertyPageEx::OnInitDialog();
	m_Edit_Page_3_1_CWnd.SetFont(&m_p_Font,TRUE); 
	return TRUE;  
}

VOID CPage_3::OnShowWindow
(
 BOOL bShow, 
 UINT nStatus
 ) 
{
	
	if(bShow)
	{
		m_Edit_Page_3_1_CWnd.SetPasswordChar('*');
		m_Check_Page_3_1_CWnd.SetCheck(1);
		m_Check_Page_3_2_CWnd.SetCheck(0);
		m_Check_Page_3_1 = TRUE;
		m_Check_Page_3_2 = FALSE;
		m_Wnd->m_T_WindowData.m_i_AppOption = 1;
	}
	
	CPropertyPageEx::OnShowWindow(bShow, nStatus);
}

BOOL CPage_3::PreTranslateMessage
(
 MSG* pMsg
 ) 
{
	if(!(m_Wnd->m_b_GlobalProgress) && pMsg->message == WM_MOUSEMOVE && (pMsg->wParam ==MK_LBUTTON) && (WindowFromPoint(pMsg->pt)->m_hWnd == m_Edit_Page_3_1_CWnd.m_hWnd))
	{
		m_x_MainSheet->SetWizardButtons(PSWIZB_BACK);
		m_Wnd->C_Wnd_StartSearch(m_Edit_Page_3_1_CWnd.m_hWnd,m_Wnd->m_T_WindowData.m_i_AppOption);
	}
	if(pMsg->message == WM_LBUTTONUP && (m_Wnd->m_b_GlobalProgress))
	{
		if(m_Wnd->C_Wnd_StopSearch())
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
		else
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK);
	}
	if(pMsg->message == WM_MOUSEMOVE && (m_Wnd->m_b_GlobalProgress))
	{
		m_Wnd->C_Wnd_ProcessSearch();
	}
	return CPropertyPageEx::PreTranslateMessage(pMsg);
}

VOID CPage_3::OnCheckPage_3_1
(
 VOID
 ) 
{
	if(m_Check_Page_3_1)
	{
		m_Check_Page_3_1 = FALSE;
		m_Edit_Page_3_1_CWnd.SetPasswordChar(0);
		if(m_Wnd->m_T_WindowData.m_i_AppOption >= 2)
			m_Wnd->m_T_WindowData.m_i_AppOption = 2;
		else
			m_Wnd->m_T_WindowData.m_i_AppOption = 0;
	}
	else
	{
		m_Check_Page_3_1 = TRUE;
		m_Edit_Page_3_1_CWnd.SetPasswordChar('*');
		if(m_Wnd->m_T_WindowData.m_i_AppOption >= 2)
			m_Wnd->m_T_WindowData.m_i_AppOption = 3;
		else
			m_Wnd->m_T_WindowData.m_i_AppOption = 1;
	}
	m_Edit_Page_3_1_CWnd.RedrawWindow(NULL,NULL,RDW_INVALIDATE | RDW_UPDATENOW);
}

VOID CPage_3::OnCheckPage_3_2
(
 VOID
 ) 
{
	if(!m_Check_Page_3_2)
	{
		m_Check_Page_3_2 = TRUE;
		if(m_Wnd->m_T_WindowData.m_i_AppOption == 1 || m_Wnd->m_T_WindowData.m_i_AppOption == 3)
			m_Wnd->m_T_WindowData.m_i_AppOption = 3;
		else
			m_Wnd->m_T_WindowData.m_i_AppOption = 2;
	}
	else
	{
		m_Check_Page_3_2 = FALSE;
		if(m_Wnd->m_T_WindowData.m_i_AppOption == 1 || m_Wnd->m_T_WindowData.m_i_AppOption == 3)
			m_Wnd->m_T_WindowData.m_i_AppOption = 1;	
		else
			m_Wnd->m_T_WindowData.m_i_AppOption = 0;	
	}
}

VOID CPage_3::OnNextPage
(
 VOID
 )
{
	if(((CButton *)GetDlgItem(IDC_RADIO_PAGE_3_1))->GetCheck() == 1)
	{
		m_Check_Page_3_1 = TRUE;
		if(((CButton *)GetDlgItem(IDC_RADIO_PAGE_3_2))->GetCheck() == 1)
		{
			m_Check_Page_3_2 = TRUE;
			m_Wnd->m_T_WindowData.m_i_AppOption = 3;
		}
		else
		{
			m_Check_Page_3_2 = FALSE;
			m_Wnd->m_T_WindowData.m_i_AppOption = 1;
		}
	}
	else
	{
		m_Check_Page_3_1 = FALSE;
		if(((CButton *)GetDlgItem(IDC_RADIO_PAGE_3_2))->GetCheck() == 1)
		{
			m_Check_Page_3_2 = TRUE;
			m_Wnd->m_T_WindowData.m_i_AppOption = 2;
		}
		else
		{
			m_Check_Page_3_2 = FALSE;
			m_Wnd->m_T_WindowData.m_i_AppOption = 0;
		}
	}
	m_x_MainSheet->SetWizardButtons(PSWIZB_BACK);
	m_x_MainSheet->SetActivePage(3);
}

VOID CPage_3::OnBackPage
(
 VOID
 )
{
	m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
	m_x_MainSheet->SetActivePage(1);
}

