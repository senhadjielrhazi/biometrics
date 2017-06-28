/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWConfig_Page_3.cpp 										 //
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

IMPLEMENT_DYNCREATE(CPage_3, CPropertyPageEx)
CPage_3::CPage_3() : CPropertyPageEx(CPage_3::IDD)
{
	m_b_Switch = FALSE;
	//m_psp.dwFlags |= PSP_HIDEHEADER |PSP_HASHELP;
	//{{AFX_DATA_INIT(CPage_3)
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
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPage_3, CPropertyPageEx)
//{{AFX_MSG_MAP(CPage_3)
ON_WM_SHOWWINDOW()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

VOID CPage_3::OnShowWindow
(
 BOOL bShow, 
 UINT nStatus
 ) 
{
	if(bShow)
	{
		switch(m_T_SWContex->m_T_DbState)
		{
		case MSO_DB_OK :
			{
				m_b_Switch = TRUE;
				((CButton *)GetDlgItem(IDC_RADIO_PAGE_3_1))->SetCheck(1);
				((CButton *)GetDlgItem(IDC_RADIO_PAGE_3_2))->SetCheck(0);
				((CButton *)GetDlgItem(IDC_RADIO_PAGE_3_1))->EnableWindow(TRUE);
				((CButton *)GetDlgItem(IDC_RADIO_PAGE_3_2))->EnableWindow(TRUE);
				break;
			}
		case MSO_DB_FULL :
			{
				m_b_Switch = FALSE;
				((CButton *)GetDlgItem(IDC_RADIO_PAGE_3_1))->SetCheck(0);
				((CButton *)GetDlgItem(IDC_RADIO_PAGE_3_2))->SetCheck(1);
				((CButton *)GetDlgItem(IDC_RADIO_PAGE_3_1))->EnableWindow(FALSE);
				((CButton *)GetDlgItem(IDC_RADIO_PAGE_3_2))->EnableWindow(TRUE);
				break;
			}
		case MSO_DB_EMPTY : 
			{
				m_b_Switch = TRUE;
				((CButton *)GetDlgItem(IDC_RADIO_PAGE_3_1))->SetCheck(1);
				((CButton *)GetDlgItem(IDC_RADIO_PAGE_3_2))->SetCheck(0);
				((CButton *)GetDlgItem(IDC_RADIO_PAGE_3_1))->EnableWindow(TRUE);
				((CButton *)GetDlgItem(IDC_RADIO_PAGE_3_2))->EnableWindow(FALSE);
				break;
			}
		}
	}
	
	CPropertyPageEx::OnShowWindow(bShow, nStatus);
}

VOID CPage_3::OnNextPage
(
 VOID
 )
{
	if(((CButton *)GetDlgItem(IDC_RADIO_PAGE_3_1))->GetCheck() == 1)
	{
		m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
		m_x_MainSheet->SetActivePage(3);
	}
	else
	{
		m_x_MainSheet->SetWizardButtons(PSWIZB_BACK);
		m_x_MainSheet->SetActivePage(5);
	}
}

VOID CPage_3::OnBackPage
(
 VOID
 )
{
	m_x_MainSheet->SetWizardButtons(PSWIZB_NEXT);
	m_x_MainSheet->SetActivePage(0);
}
