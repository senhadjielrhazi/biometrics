/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWConfig_Page_8.cpp											 //
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

IMPLEMENT_DYNCREATE(CPage_8, CPropertyPageEx)
CPage_8::CPage_8() : CPropertyPageEx(CPage_8::IDD)
{
	m_p_Font_1.CreateFont(17, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 
		PROOF_QUALITY,VARIABLE_PITCH | FF_SWISS, L"");
	m_p_Font_2.CreateFont(15, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 
		PROOF_QUALITY,VARIABLE_PITCH | FF_SWISS, L"");
	m_psp.dwFlags |= PSP_HIDEHEADER |PSP_HASHELP;
	
	//{{AFX_DATA_INIT(CPage_8)
	//}}AFX_DATA_INIT
}

CPage_8::~CPage_8()
{
}

VOID CPage_8::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage_8)
	DDX_Control(pDX, IDC_TEXT_PAGE_8_1, m_Text_Page_8_1_CWnd);
	DDX_Control(pDX, IDC_EDIT_PAGE_8_1, m_Edit_Page_8_1_CWnd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage_8, CPropertyPageEx)
//{{AFX_MSG_MAP(CPage_8)
ON_WM_SHOWWINDOW()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

VOID CPage_8::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CString 	l_c_InfoText ;
	
	
	if(bShow)
	{
		m_Text_Page_8_1_CWnd.SetFont(&m_p_Font_1,TRUE);
		m_Edit_Page_8_1_CWnd.SetFont(&m_p_Font_2,TRUE);
		
		switch(*m_i_PageCode)
		{
		case 0://Initialisation Err
			{
				l_c_InfoText.Format(_T(VC_ADMIN_INITERR));
				break;
			}
		case 1://Enroll OK
			{
				l_c_InfoText.Format(_T(VC_ADMIN_ENROLLOK));
				break;
			}
		case 2://Enroll Err
			{
				l_c_InfoText.Format(_T(VC_ADMIN_ENROLLERR));
				break;
			}
		case 3://Ident NoHit
			{
				l_c_InfoText.Format(_T(VC_ADMIN_IDENTNO));
				break;
			}
		case 4://Ident Err
			{
				l_c_InfoText.Format(_T(VC_ADMIN_IDENTERR));
				break;
			}
		case 5://Update Ok
			{
				l_c_InfoText.Format(_T(VC_ADMIN_UPDATEOK));
				break;
			}
		case 6://Update Err
			{
				l_c_InfoText.Format(_T(VC_ADMIN_UPDATEERR));
				break;
			}
		case 7://Del Ok
			{
				l_c_InfoText.Format(_T(VC_ADMIN_DELOK));
				break;
			}
		case 8://Del Err
			{
				l_c_InfoText.Format(_T(VC_ADMIN_DELERR));
				break;
			}
		default://Abort
			{
				l_c_InfoText.Format(_T(VC_ADMIN_ABORT));
				break;
			}
		}
		
		m_Edit_Page_8_1_CWnd.SetWindowText(l_c_InfoText);
	}
	
	CPropertyPageEx::OnShowWindow(bShow, nStatus);	
}

VOID CPage_8::OnNextPage
(
 VOID
 )
{
}
VOID CPage_8::OnBackPage
(
 VOID
 )
{
	switch(*m_i_PageCode)
	{
	case 0://Initialisation Err
		{
			m_x_MainSheet->SetWizardButtons(PSWIZB_NEXT);
			m_x_MainSheet->SetActivePage(0);
			break;
		}
	case 1://Enroll OK
		{
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
			m_x_MainSheet->SetActivePage(2);
			break;
		}
	case 2://Enroll Err
		{
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
			m_x_MainSheet->SetActivePage(3);
			break;
		}
	case 3://Ident NoHit
		{
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
			m_x_MainSheet->SetActivePage(2);
			break;
		}
	case 4://Ident Err
		{
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
			m_x_MainSheet->SetActivePage(2);
			break;
		}
	case 5://Update Ok
		{
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
			m_x_MainSheet->SetActivePage(2);
			break;
		}
	case 6://Update Err
		{
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
			m_x_MainSheet->SetActivePage(2);
			break;
		}
	case 7://Del Ok
		{
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
			m_x_MainSheet->SetActivePage(2);
			break;
		}
	case 8://Del Err
		{
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
			m_x_MainSheet->SetActivePage(2);
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
