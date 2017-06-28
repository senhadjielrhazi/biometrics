/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWAccess_Page_2.cpp 										 //
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

IMPLEMENT_DYNCREATE(CPage_2, CPropertyPageEx)
CPage_2::CPage_2() : CPropertyPageEx(CPage_2::IDD)
{
	//{{AFX_DATA_INIT(CPage_2)
	//}}AFX_DATA_INIT
}

CPage_2::~CPage_2
(
 )
{
}

VOID CPage_2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage_2)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPage_2, CPropertyPageEx)
//{{AFX_MSG_MAP(CPage_2)
ON_WM_SHOWWINDOW()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

VOID CPage_2::OnShowWindow
(
 BOOL bShow, 
 UINT nStatus
 ) 
{	
	if(bShow)
	{
		if(*m_i_NbApplication == 0)
		{
			((CButton *)GetDlgItem(IDC_RADIO_PAGE_2_1))->SetCheck(1);
			((CButton *)GetDlgItem(IDC_RADIO_PAGE_2_2))->SetCheck(0);
			((CButton *)GetDlgItem(IDC_RADIO_PAGE_2_1))->EnableWindow(TRUE);
			((CButton *)GetDlgItem(IDC_RADIO_PAGE_2_2))->EnableWindow(FALSE);
		}
		else if(*m_i_NbApplication == VI_NBAPPLI_MAX)
		{
			((CButton *)GetDlgItem(IDC_RADIO_PAGE_2_1))->SetCheck(0);
			((CButton *)GetDlgItem(IDC_RADIO_PAGE_2_2))->SetCheck(1);
			((CButton *)GetDlgItem(IDC_RADIO_PAGE_2_1))->EnableWindow(FALSE);
			((CButton *)GetDlgItem(IDC_RADIO_PAGE_2_2))->EnableWindow(TRUE);
		}
		else
		{
			((CButton *)GetDlgItem(IDC_RADIO_PAGE_2_1))->SetCheck(1);
			((CButton *)GetDlgItem(IDC_RADIO_PAGE_2_2))->SetCheck(0);
			((CButton *)GetDlgItem(IDC_RADIO_PAGE_2_1))->EnableWindow(TRUE);
			((CButton *)GetDlgItem(IDC_RADIO_PAGE_2_2))->EnableWindow(TRUE);
		}
	}
	
	CPropertyPageEx::OnShowWindow(bShow, nStatus);
}

VOID CPage_2::OnNextPage
(
 VOID
 )
{
	if(((CButton *)GetDlgItem(IDC_RADIO_PAGE_2_1))->GetCheck() == 1)
	{
		m_x_MainSheet->SetWizardButtons(PSWIZB_BACK);
		m_x_MainSheet->SetActivePage(2);
	}
	else
	{
		m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
		m_x_MainSheet->SetActivePage(4);
	}
}

VOID CPage_2::OnBackPage
(
 VOID
 )
{
	m_x_MainSheet->SetWizardButtons(PSWIZB_NEXT);
	m_x_MainSheet->SetActivePage(0);
}
