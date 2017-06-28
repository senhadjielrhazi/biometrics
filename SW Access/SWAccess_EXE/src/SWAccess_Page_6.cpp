/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWAccess_Page_6.cpp 										 //
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

IMPLEMENT_DYNCREATE(CPage_6, CPropertyPageEx)
CPage_6::CPage_6() : CPropertyPageEx(CPage_6::IDD)
{
	m_p_Font_1.CreateFont(17, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 
		PROOF_QUALITY,VARIABLE_PITCH | FF_SWISS, L"");
	m_p_Font_2.CreateFont(15, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 
		PROOF_QUALITY,VARIABLE_PITCH | FF_SWISS, L"");
	m_psp.dwFlags |= PSP_HIDEHEADER;
	
	//{{AFX_DATA_INIT(CPage_6)
	//}}AFX_DATA_INIT
}

CPage_6::~CPage_6
(
 )
{
}

VOID CPage_6::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage_6)
	DDX_Control(pDX, IDC_TEXT_PAGE_6_1, m_Text_Page_6_1_CWnd);
	DDX_Control(pDX, IDC_EDIT_PAGE_6_1, m_Edit_Page_6_1_CWnd);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPage_6, CPropertyPageEx)
//{{AFX_MSG_MAP(CPage_6)
ON_WM_SHOWWINDOW()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

VOID CPage_6::OnShowWindow
(
 BOOL bShow, 
 UINT nStatus
 ) 
{
	CString 	l_c_InfoText ;
	
	if(bShow)
	{
		m_Text_Page_6_1_CWnd.SetFont(&m_p_Font_1,TRUE);
		m_Edit_Page_6_1_CWnd.SetFont(&m_p_Font_2,TRUE);
		
		switch(*m_i_PageCode)
		{
		case 1://Registration OK
			{
				l_c_InfoText.Format(_T(VC_ACCESS_REGOK));
				break;
			}
		case 2://Registration Abort
			{
				l_c_InfoText.Format(_T(VC_ACCESS_REGABORT));
				break;
			}
		case 3://Regsitration Err
			{
				l_c_InfoText.Format(_T(VC_ACCESS_REGERR));
				break;
			}
		case 4://Updata Ok
			{
				l_c_InfoText.Format(_T(VC_ACCESS_UPDATEOK));
				break;
			}
		case 5://Update Abort
			{
				l_c_InfoText.Format(_T(VC_ACCESS_UPDATEABORT));
				break;
			}
		case 6://Update Err
			{
				l_c_InfoText.Format(_T(VC_ACCESS_UPDATEERR));
				break;
			}
		case 7://Del App Ok
			{
				l_c_InfoText.Format(_T(VC_ACCESS_DELOK));
				break;
			}
		case 8://Del Abort
			{
				l_c_InfoText.Format(_T(VC_ACCESS_DELABORT));
				break;
			}
		case 9://Del Err
			{
				l_c_InfoText.Format(_T(VC_ACCESS_DELERR));
				break;
			}
		default://Abort
			{
				l_c_InfoText.Format(_T(VC_ACCESS_ABORT));
				break;
			}
		}
		
		m_Edit_Page_6_1_CWnd.SetWindowText(l_c_InfoText);
	}
	
	CPropertyPageEx::OnShowWindow(bShow, nStatus);	
}

VOID CPage_6::OnNextPage
(
 VOID
 )
{
}

VOID CPage_6::OnBackPage
(
 VOID
 )
{
	switch(*m_i_PageCode)
	{
	case 1://Reg Ok
		{
			m_x_MainSheet->SetWizardButtons(PSWIZB_NEXT | PSWIZB_NEXT);
			m_x_MainSheet->SetActivePage(1);
			break;
		}
	case 2://Reg Abort
		{
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK);
			m_x_MainSheet->SetActivePage(3);
			break;
		}
	case 3://Reg Err
		{
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK);
			m_x_MainSheet->SetActivePage(3);
			break;
		}
	case 4://Update Ok
		{
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
			m_x_MainSheet->SetActivePage(1);
			break;
		}
	case 5://Update Abort
		{
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
			m_x_MainSheet->SetActivePage(4);
			break;
		}
	case 6://Update Err
		{
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
			m_x_MainSheet->SetActivePage(4);
			break;
		}
	case 7://Del Ok
		{
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
			m_x_MainSheet->SetActivePage(1);
			break;
		}
	case 8://Del Abort
		{
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
			m_x_MainSheet->SetActivePage(4);
			break;
		}
	case 9://Del Err
		{
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
			m_x_MainSheet->SetActivePage(4);
			break;
		}
	default://Abort
		{
			m_x_MainSheet->SetWizardButtons(PSWIZB_NEXT);
			m_x_MainSheet->SetActivePage(0);
			break;
		}
	}
}
