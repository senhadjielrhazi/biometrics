/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWConfig_Page_5.cpp 										 //
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

IMPLEMENT_DYNCREATE(CPage_5, CPropertyPageEx)
CPage_5::CPage_5() : CPropertyPageEx(CPage_5::IDD)
{
	m_b_Progress = TRUE;
	
	m_p_Font.CreateFont(16, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 
		PROOF_QUALITY,VARIABLE_PITCH | FF_SWISS, L""); 
	
	//{{AFX_DATA_INIT(CPage_5)
	m_Text_Page_5_2 = _T("");
	m_Text_Page_5_3 = _T("");
	m_Image_Page_5_1 = _T("");
	m_Image_Page_5_2 = _T("");
	m_Image_Page_5_3 = _T("");
	m_Image_Page_5_4 = _T("");
	//}}AFX_DATA_INIT
}

CPage_5::~CPage_5
(
 )
{
}

VOID CPage_5::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage_5)
	DDX_Control(pDX, IDC_TEXT_PAGE_5_3, m_Text_Page_5_3_CWnd);
	DDX_Control(pDX, IDC_TEXT_PAGE_5_2, m_Text_Page_5_2_CWnd);
	DDX_Control(pDX, IDC_TEXT_PAGE_5_1, m_Text_Page_5_1_CWnd);
	DDX_Control(pDX, IDC_IMAGE_PAGE_5_4, m_Image_Page_5_4_CWnd);
	DDX_Control(pDX, IDC_IMAGE_PAGE_5_3, m_Image_Page_5_3_CWnd);
	DDX_Control(pDX, IDC_IMAGE_PAGE_5_2, m_Image_Page_5_2_CWnd);
	DDX_Control(pDX, IDC_IMAGE_PAGE_5_1, m_Image_Page_5_1_CWnd);
	DDX_Text(pDX, IDC_TEXT_PAGE_5_1, m_Text_Page_5_1);
	DDX_Text(pDX, IDC_TEXT_PAGE_5_2, m_Text_Page_5_2);
	DDX_Text(pDX, IDC_TEXT_PAGE_5_3, m_Text_Page_5_3);
	DDX_Text(pDX, IDC_IMAGE_PAGE_5_1, m_Image_Page_5_1);
	DDX_Text(pDX, IDC_IMAGE_PAGE_5_2, m_Image_Page_5_2);
	DDX_Text(pDX, IDC_IMAGE_PAGE_5_3, m_Image_Page_5_3);
	DDX_Text(pDX, IDC_IMAGE_PAGE_5_4, m_Image_Page_5_4);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPage_5, CPropertyPageEx)
//{{AFX_MSG_MAP(CPage_5)
ON_WM_SHOWWINDOW()
ON_WM_PAINT()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

VOID CPage_5::OnShowWindow
(
 BOOL bShow,
 UINT nStatus
 ) 
{
	CString l_c_TmpText;
	INT 	l_i_LoopProgress = 0 ;
	
	m_Image_Page_5_1_CWnd.SetWindowText(_T(""));
	m_Image_Page_5_2_CWnd.SetWindowText(_T(""));
	m_Image_Page_5_3_CWnd.SetWindowText(_T(""));
	m_Image_Page_5_4_CWnd.SetWindowText(_T(""));
	m_Text_Page_5_2_CWnd.SetWindowText(_T(""));
	m_Text_Page_5_3_CWnd.SetWindowText(_T(""));
	
	m_Image_Page_5_1_CWnd.RedrawWindow(NULL,NULL,RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE ); 
	m_Image_Page_5_2_CWnd.RedrawWindow(NULL,NULL,RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE );
	m_Image_Page_5_3_CWnd.RedrawWindow(NULL,NULL,RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE );
	m_Image_Page_5_4_CWnd.RedrawWindow(NULL,NULL,RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE );
	if(bShow)
	{
		m_b_UserOff = FALSE;
		l_c_TmpText.Format(L"%s",m_pwc_UserLogin);
		m_Text_Page_5_1_CWnd.SetWindowText(l_c_TmpText);
		while(!m_b_Progress && l_i_LoopProgress<80)
		{
			l_i_LoopProgress++;
			Sleep(10);
		}
		m_T_DataIn->m_h_hwndImage_1 = m_Image_Page_5_1_CWnd.m_hWnd;
		m_T_DataIn->m_h_hwndImage_2 = m_Image_Page_5_2_CWnd.m_hWnd;
		m_T_DataIn->m_h_hwndImage_3 = m_Image_Page_5_3_CWnd.m_hWnd;
		m_T_DataIn->m_h_hwndImage_4 = m_Image_Page_5_4_CWnd.m_hWnd;
		m_T_DataIn->m_h_hwndText_1	= m_Text_Page_5_2_CWnd.m_hWnd;
		m_T_DataIn->m_h_hwndText_2	= m_Text_Page_5_3_CWnd.m_hWnd;
		
		AfxBeginThread(TaskPage_5,(LPVOID)this);
		while(m_b_Progress && l_i_LoopProgress<200)
		{
			l_i_LoopProgress++;
			Sleep(20);
		}
	}
	CPropertyPageEx::OnShowWindow(bShow, nStatus);	
}

BOOL CPage_5::OnInitDialog
(
 VOID
 ) 
{
	CPropertyPageEx::OnInitDialog();
	m_Text_Page_5_1_CWnd.SetFont(&m_p_Font,TRUE);
	m_Text_Page_5_2_CWnd.SetFont(&m_p_Font,TRUE);
	m_Text_Page_5_3_CWnd.SetFont(&m_p_Font,TRUE);
	return TRUE;  
}

UINT TaskPage_5
(
 LPVOID pParam
 )
{
	CPage_5 *CPage_5_Data = (CPage_5*) pParam;
	return CPage_5_Data->TestPage_5();
}

UINT CPage_5::TestPage_5
(
 VOID
 )
{
	__try
	{
		m_b_Progress = FALSE;
		m_T_Result = WlxAdminEnrollOn(*m_T_DataIn);
		
		if(m_T_Result == SW_OKHIT_MD)
			WlxAdminRefresh(*m_T_SWContex);
		
		m_b_Progress = TRUE;
		OnNextPage();
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
	return TRUE;
}

VOID CPage_5::OnPaint
(
 VOID
 ) 
{
	CPaintDC dc(this);
	
	if(!m_b_Progress)
		WlxAdminEnrollPaint();
	else
	{
		m_Image_Page_5_1_CWnd.SetWindowText(_T(""));
		m_Image_Page_5_2_CWnd.SetWindowText(_T(""));
		m_Image_Page_5_3_CWnd.SetWindowText(_T(""));
		m_Image_Page_5_4_CWnd.SetWindowText(_T(""));
		m_Text_Page_5_2_CWnd.SetWindowText(_T(""));
		m_Text_Page_5_3_CWnd.SetWindowText(_T(""));
		
		m_Image_Page_5_1_CWnd.RedrawWindow(NULL,NULL,RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE ); 
		m_Image_Page_5_2_CWnd.RedrawWindow(NULL,NULL,RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE );
		m_Image_Page_5_3_CWnd.RedrawWindow(NULL,NULL,RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE );
		m_Image_Page_5_4_CWnd.RedrawWindow(NULL,NULL,RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE );
	}
	
	CDialog::OnPaint();
}

VOID CPage_5::OnNextPage
(
 VOID
 )
{
	__try
	{
		switch(m_T_Result)
		{
		case SW_OKHIT_MD :
			{
				*m_i_PageCode  = 1;
				m_x_MainSheet->SetActivePage(7);
				m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
				break;
			}
		case SW_NOHIT_MD :
			{
				*m_i_PageCode  = 2;
				m_x_MainSheet->SetActivePage(7);
				m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
				break;
			}
		case SW_ABORT_MD :
			{
				if(!m_b_UserOff)
				{
					*m_i_PageCode  = 9;
					m_x_MainSheet->SetActivePage(7);
					m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
				}
				break;
			}
		default :
			{
				*m_i_PageCode  = 2;
				m_x_MainSheet->SetActivePage(7);
				m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
				break;
			}
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

VOID CPage_5::OnBackPage
(
 VOID
 )
{
	INT l_i_LoopProgress = 0;
	
	__try
	{
		m_b_UserOff = TRUE;
		
		while(m_b_Progress && l_i_LoopProgress<80)
		{
			WlxAdminEnrollOff();
			l_i_LoopProgress++;
			Sleep(10);
		}
		WlxAdminEnrollOff();
		while(!m_b_Progress && l_i_LoopProgress<200)
		{
			WlxAdminEnrollOff();
			l_i_LoopProgress++;
			Sleep(20);
		}
		
		m_x_MainSheet->SetActivePage(3);
		m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

VOID CPage_5::OnFinishPage
(
 VOID
 )
{
	INT l_i_LoopProgress = 0;
	
	__try
	{
		while(m_b_Progress && l_i_LoopProgress<80)
		{
			WlxAdminEnrollOff();
			l_i_LoopProgress++;
			Sleep(10);
		}
		WlxAdminEnrollOff();
		while(!m_b_Progress && l_i_LoopProgress<200)
		{
			WlxAdminEnrollOff();
			l_i_LoopProgress++;
			Sleep(20);
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

VOID CPage_5::OnCancel
(
 VOID
 ) 
{	
	INT l_i_LoopProgress = 0;
	
	__try
	{
		m_b_UserOff = TRUE;
		
		while(m_b_Progress && l_i_LoopProgress<80)
		{
			WlxAdminEnrollOff();
			l_i_LoopProgress++;
			Sleep(10);
		}
		WlxAdminEnrollOff();
		while(!m_b_Progress && l_i_LoopProgress<200)
		{
			WlxAdminEnrollOff();
			l_i_LoopProgress++;
			Sleep(20);
		}
		CPropertyPageEx::OnCancel();
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}


VOID CPage_5::OnEndSession( BOOL bEnding )
{
	WlxAdminEnrollOff();
}

