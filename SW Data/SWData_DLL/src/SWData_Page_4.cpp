/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWData_Page_4.cpp											 //
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

IMPLEMENT_DYNCREATE(CPage_4, CPropertyPageEx)
CPage_4::CPage_4() : CPropertyPageEx(CPage_4::IDD)
{
	m_psp.dwFlags |= PSP_HIDEHEADER;
	m_p_Font_1.CreateFont(17, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 
		PROOF_QUALITY,VARIABLE_PITCH | FF_SWISS, L"");
	m_p_Font_2.CreateFont(15, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 
		PROOF_QUALITY,VARIABLE_PITCH | FF_SWISS, L"");
	
	//{{AFX_DATA_INIT(CPage_4)
	//}}AFX_DATA_INIT
}

CPage_4::~CPage_4
(
 )
{
}

VOID CPage_4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage_4)
	DDX_Control(pDX, IDC_EDIT_PAGE_4_1, m_Edit_Page_4_1_CWnd);
	DDX_Control(pDX, IDC_TEXT_PAGE_4_1, m_Text_Page_4_1_CWnd);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPage_4, CPropertyPageEx)
//{{AFX_MSG_MAP(CPage_4)
ON_WM_SHOWWINDOW()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

VOID CPage_4::OnShowWindow
(
 BOOL bShow, 
 UINT nStatus
 ) 
{
	CString 	l_c_InfoText ;	
	
	if(bShow)
	{
		m_Text_Page_4_1_CWnd.SetFont(&m_p_Font_1,TRUE);
		m_Edit_Page_4_1_CWnd.SetFont(&m_p_Font_2,TRUE);
		
		switch(*m_i_PageCode)
		{
		case 0://Ident NoHit
			{
				l_c_InfoText.Format(_T(VC_DATA_IDENTNO));
				break;
			}
		case 2://Ident Err
			{
				l_c_InfoText.Format(_T(VC_DATA_IDENTERR));
				break;
			}
		default://Abort
			{
				l_c_InfoText.Format(_T(VC_DATA_ABORT));
				break;
			}
		}
		
		m_Edit_Page_4_1_CWnd.SetWindowText(l_c_InfoText);
	}
	
	CPropertyPageEx::OnShowWindow(bShow, nStatus);	
}

VOID CPage_4::OnNextPage
(
 VOID
 )
{
}

VOID CPage_4::OnBackPage
(
 VOID
 )
{
	m_x_MainSheet->SetWizardButtons(PSWIZB_NEXT);
	m_x_MainSheet->SetActivePage(0);
}
