/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWData_Page_1.cpp											 //
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
//	SAGEM SA Data Module													 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#include "stdafx.h"

IMPLEMENT_DYNCREATE(CPage_1, CPropertyPageEx)
CPage_1::CPage_1() : CPropertyPageEx(CPage_1::IDD)
{
	m_psp.dwFlags |= PSP_HIDEHEADER |PSP_USETITLE;
	m_psp.pszTitle = _T(VC_DATA_TITLE);
	
	m_p_Font.CreateFont(20, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 
		PROOF_QUALITY,VARIABLE_PITCH | FF_SWISS, L""); 
	
	//{{AFX_DATA_INIT(CPage_1)
	//}}AFX_DATA_INIT
}

CPage_1::~CPage_1
(
 )
{
}

VOID CPage_1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage_1)
	DDX_Control(pDX, IDC_TEXT_PAGE_1_1, m_Text_Page_1_1_CWnd);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPage_1, CPropertyPageEx)
//{{AFX_MSG_MAP(CPage_1)
ON_WM_SHOWWINDOW()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

VOID CPage_1::OnShowWindow
(
 BOOL bShow, 
 UINT nStatus
 ) 
{
	m_Text_Page_1_1_CWnd.SetFont(&m_p_Font,TRUE);
	
	CPropertyPageEx::OnShowWindow(bShow, nStatus);	
}

VOID CPage_1::OnNextPage
(
 VOID
 )
{
	m_x_MainSheet->SetActivePage(1);
	m_x_MainSheet->SetWizardButtons(PSWIZB_BACK);	
}

VOID CPage_1::OnBackPage
(
 VOID
 )
{
}
