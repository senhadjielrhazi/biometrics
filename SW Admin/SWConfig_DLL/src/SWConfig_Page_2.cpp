/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWConfig_Page_2.cpp 										 //
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

IMPLEMENT_DYNCREATE(CPage_2, CPropertyPageEx)
CPage_2::CPage_2() : CPropertyPageEx(CPage_2::IDD)
{
	m_ui_TimerId	= 0;
	m_ui_TimerEd_1	= 50;
	m_ui_TimerEd_2	= 1000;
	m_i_Progress	= 0;
	m_b_Switch		= FALSE;
	
	m_p_Font_1.CreateFont(15, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 
		PROOF_QUALITY,VARIABLE_PITCH | FF_SWISS, L""); 
	
	//m_psp.dwFlags |= PSP_HIDEHEADER |PSP_HASHELP;
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
	DDX_Control(pDX, IDC_TEXT_PAGE_2_4, m_Text_Page_2_3_CWnd);
	DDX_Control(pDX, IDC_TEXT_PAGE_2_3, m_Text_Page_2_2_CWnd);
	DDX_Control(pDX, IDC_TEXT_PAGE_2_2, m_Text_Page_2_1_CWnd);
	DDX_Control(pDX, IDC_ANIMATE_PAGE_2_1, m_Anim_Page_2_1_CWnd);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPage_2, CPropertyPageEx)
//{{AFX_MSG_MAP(CPage_2)
ON_WM_SHOWWINDOW()
ON_WM_TIMER()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

VOID CPage_2::OnShowWindow
(
 BOOL bShow, 
 UINT nStatus
 ) 
{
	m_i_Progress	= 0;
	m_b_Switch		= FALSE;
	
	if(bShow)
	{
		m_Text_Page_2_1_CWnd.SetWindowText(_T(""));
		m_Text_Page_2_2_CWnd.SetWindowText(_T(""));
		m_Text_Page_2_3_CWnd.SetWindowText(_T(""));
		::AfxBeginThread(TaskPage_2,(LPVOID)this);
		m_Anim_Page_2_1_CWnd.Open(IDR_SW_SEARCH);
		m_Anim_Page_2_1_CWnd.Play(0,-1,-1);
	}
	else
	{
		m_Anim_Page_2_1_CWnd.Stop();
		m_Anim_Page_2_1_CWnd.Close();
		KillTimer(m_ui_TimerId);
	}
	CPropertyPageEx::OnShowWindow(bShow, nStatus);
}

UINT TaskPage_2
(
 LPVOID pParam 
 )
{
	CPage_2 *CPage_2_Data = (CPage_2*) pParam;
	return CPage_2_Data->TestPage_2();
}

UINT CPage_2::TestPage_2
(
 VOID
 )
{
	__try
	{
		SetTimer(m_ui_TimerId,m_ui_TimerEd_1,NULL);
		WlxSWReboot(*m_T_SWContex);
		if(m_i_Progress == 0)
		{
			m_Text_Page_2_1_CWnd.SetFont(&m_p_Font_1,TRUE);
			m_Text_Page_2_1_CWnd.SetWindowText(_T(VC_ADMIN_INITOK));
			KillTimer(m_ui_TimerId);
			m_i_Progress = 1;
		}
		SetTimer(m_ui_TimerId,m_ui_TimerEd_2,NULL);
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
	return 0;
}

VOID CPage_2::OnTimer
(
 UINT nIDEvent
 ) 
{	
	INT 	l_i_Result = 0;
	
	__try
	{
		if(nIDEvent == m_ui_TimerId)
		{
			switch(m_i_Progress)
			{
			case 0:
				{
					KillTimer(m_ui_TimerId);
					m_Text_Page_2_1_CWnd.SetFont(&m_p_Font_1,TRUE);
					m_Text_Page_2_1_CWnd.SetWindowText(_T(VC_ADMIN_INITOK));
					m_i_Progress++;
					break;
				}
			case 1:
				{
					m_Text_Page_2_1_CWnd.SetFont(m_p_Font_2,TRUE);
					if(m_T_SWContex->m_T_ComState == MSO_COM_OK)
					{
						m_Text_Page_2_1_CWnd.SetWindowText(_T(VC_ADMIN_COM_OK));
					}
					else
					{
						m_Text_Page_2_1_CWnd.SetWindowText(_T(VC_ADMIN_COM_ERR));
					}
					m_Text_Page_2_2_CWnd.SetFont(&m_p_Font_1,TRUE);
					m_Text_Page_2_2_CWnd.SetWindowText(_T(VC_ADMIN_INITOK));
					m_i_Progress++;
					break;
				}
			case 2:
				{
					if(m_T_SWContex->m_T_ComState == MSO_COM_OK)
					{
						switch(m_T_SWContex->m_T_DbState)
						{
						case MSO_DB_OK :
							{
								m_Text_Page_2_2_CWnd.SetFont(m_p_Font_2,TRUE);
								m_Text_Page_2_2_CWnd.SetWindowText(_T(VC_ADMIN_DB_OK));
								m_Text_Page_2_3_CWnd.SetFont(&m_p_Font_1,TRUE);
								m_Text_Page_2_3_CWnd.SetWindowText(_T(VC_ADMIN_INITKO));
								break;
							}
						case MSO_DB_INVALIDE :
							{
								m_Text_Page_2_2_CWnd.SetFont(m_p_Font_2,TRUE);
								m_Text_Page_2_2_CWnd.SetWindowText(_T(VC_ADMIN_DB_INVALID));
								KillTimer(m_ui_TimerId);
								l_i_Result = MessageBox(_T(VC_MESSAGE_INVALIDE),_T(VC_TITLE_INVALIDE),\
									MB_ICONQUESTION | MB_OKCANCEL | MB_DEFBUTTON1);
								SetTimer(m_ui_TimerId,m_ui_TimerEd_2,NULL);
								if(l_i_Result == IDOK)
								{	
									WlxAdminDbOn(*m_T_SWContex,TRUE);
								}
								break;
							}
						case MSO_DB_NOBASE :
							{
								m_Text_Page_2_2_CWnd.SetFont(m_p_Font_2,TRUE);
								m_Text_Page_2_2_CWnd.SetWindowText(_T(VC_ADMIN_DB_NOBASE));
								KillTimer(m_ui_TimerId);
								l_i_Result = MessageBox(_T(VC_MESSAGE_NOBASE),_T(VC_TITLE_NOBASE),\
									MB_ICONQUESTION | MB_OKCANCEL | MB_DEFBUTTON1);
								SetTimer(m_ui_TimerId,m_ui_TimerEd_2,NULL);
								if(l_i_Result == IDOK)
								{
									WlxAdminDbOn(*m_T_SWContex,FALSE);
								}
								break;
							}
						case MSO_DB_ERR :
							{
								m_Text_Page_2_2_CWnd.SetFont(m_p_Font_2,TRUE);
								m_Text_Page_2_2_CWnd.SetWindowText(_T(VC_ADMIN_DB_ERR));
								m_Text_Page_2_3_CWnd.SetFont(&m_p_Font_1,TRUE);
								m_Text_Page_2_3_CWnd.SetWindowText(_T(VC_ADMIN_INITKO));
								break;
							}
						case MSO_DB_FULL :
							{
								m_Text_Page_2_2_CWnd.SetFont(m_p_Font_2,TRUE);
								m_Text_Page_2_2_CWnd.SetWindowText(_T(VC_ADMIN_DB_FULL));
								m_Text_Page_2_3_CWnd.SetFont(&m_p_Font_1,TRUE);
								m_Text_Page_2_3_CWnd.SetWindowText(_T(VC_ADMIN_INITKO));
								break;
							}
						case MSO_DB_EMPTY : 
							{
								m_Text_Page_2_2_CWnd.SetFont(m_p_Font_2,TRUE);
								m_Text_Page_2_2_CWnd.SetWindowText(_T(VC_ADMIN_DB_EMPTY));
								m_Text_Page_2_3_CWnd.SetFont(&m_p_Font_1,TRUE);
								m_Text_Page_2_3_CWnd.SetWindowText(_T(VC_ADMIN_INITKO));
								break;
							}
						}
					}
					else
					{
						m_Text_Page_2_2_CWnd.SetFont(m_p_Font_2,TRUE);
						m_Text_Page_2_2_CWnd.SetWindowText(_T(VC_ADMIN_DB_ERR));
						m_Text_Page_2_3_CWnd.SetFont(&m_p_Font_1,TRUE);
						m_Text_Page_2_3_CWnd.SetWindowText(_T(VC_ADMIN_INITKO));
					}
					m_i_Progress++;
					break;
				}
			case 3:
				{
					if(m_T_SWContex->m_T_ComState == MSO_COM_OK)
					{
						switch(m_T_SWContex->m_T_DbState)
						{
						case MSO_DB_OK :
							{
								m_b_Switch = FALSE;
								m_Text_Page_2_2_CWnd.SetWindowText(_T(VC_ADMIN_DB_OK));
								break;
							}
						case MSO_DB_INVALIDE :
							{
								m_b_Switch = TRUE;
								m_Text_Page_2_2_CWnd.SetWindowText(_T(VC_ADMIN_DB_INVALID));
								break;
							}
						case MSO_DB_NOBASE :
							{
								m_b_Switch = TRUE;
								m_Text_Page_2_2_CWnd.SetWindowText(_T(VC_ADMIN_DB_NOBASE));
								break;
							}
						case MSO_DB_ERR :
							{
								m_b_Switch = TRUE;
								m_Text_Page_2_2_CWnd.SetWindowText(_T(VC_ADMIN_DB_ERR));
								break;
							}
						case MSO_DB_FULL :
							{
								m_b_Switch = FALSE;
								m_Text_Page_2_2_CWnd.SetWindowText(_T(VC_ADMIN_DB_FULL));
								break;
							}
						case MSO_DB_EMPTY : 
							{
								m_b_Switch = FALSE;
								m_Text_Page_2_2_CWnd.SetWindowText(_T(VC_ADMIN_DB_EMPTY));
								break;
							}
						}
					}
					else
					{
						m_b_Switch = TRUE;
						m_Text_Page_2_2_CWnd.SetWindowText(_T(VC_ADMIN_DB_ERR));
					}
					m_Text_Page_2_3_CWnd.SetFont(&m_p_Font_1,TRUE);
					m_Text_Page_2_3_CWnd.SetWindowText(_T(VC_ADMIN_INITKO));
					m_i_Progress++;
					break;
				}
				
			case 4:
				{
					KillTimer(m_ui_TimerId);
					m_i_Progress = 0;
					OnNextPage();			
					break;
				}
		}
	}
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

VOID CPage_2::OnNextPage
(
 VOID
 )
{
	m_Text_Page_2_1_CWnd.SetFont(m_p_Font_2,TRUE);
	m_Text_Page_2_2_CWnd.SetFont(m_p_Font_2,TRUE);
	m_Text_Page_2_3_CWnd.SetFont(m_p_Font_2,TRUE);
	
	if(m_b_Switch)
	{
		*m_i_PageCode  = 0;
		m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
		m_x_MainSheet->SetActivePage(7);
	}
	else
	{
		m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
		m_x_MainSheet->SetActivePage(2);
	}
}

VOID CPage_2::OnBackPage
(
 VOID
 )
{
	m_Text_Page_2_1_CWnd.SetFont(m_p_Font_2,TRUE);
	m_Text_Page_2_2_CWnd.SetFont(m_p_Font_2,TRUE);
	m_Text_Page_2_3_CWnd.SetFont(m_p_Font_2,TRUE);
	m_x_MainSheet->SetWizardButtons(PSWIZB_NEXT);
	m_x_MainSheet->SetActivePage(0);
}

BOOL CPage_2::OnInitDialog
(
 VOID
 ) 
{
	CPropertyPageEx::OnInitDialog();
	
	m_p_Font_2 = m_Text_Page_2_1_CWnd.GetFont();
	return TRUE;
}
