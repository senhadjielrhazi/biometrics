/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWData_Page_2.cpp											 //
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

IMPLEMENT_DYNCREATE(CPage_2, CPropertyPageEx)
CPage_2::CPage_2() : CPropertyPageEx(CPage_2::IDD)
{
	m_b_Progress	= TRUE;
	m_i_Progress	= 0;
	m_ui_TimerId	= 0;
	m_ui_TimerEd_1	= 50;
	m_ui_TimerEd_2	= 1000;
	m_b_UserOff 	= FALSE;
	m_i_TimeOut 	= 100;
	
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
	DDX_Control(pDX, IDC_ANIMATE_PAGE_2_1, m_Anim_Page_2_1_CWnd);
	DDX_Control(pDX, IDC_TEXT_PAGE_2_3, m_Text_Page_2_3_CWnd);
	DDX_Control(pDX, IDC_TEXT_PAGE_2_2, m_Text_Page_2_2_CWnd);
	DDX_Control(pDX, IDC_TEXT_PAGE_2_1, m_Text_Page_2_1_CWnd);
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
	CString l_c_Tmp;
	INT 	l_i_LoopProgress = 0;
	
	if(bShow)
	{		
		m_Text_Page_2_2_CWnd.SetWindowText(_T(""));
		m_Text_Page_2_3_CWnd.SetWindowText(_T(""));
		
		while(!m_b_Progress && l_i_LoopProgress<80)
		{
			l_i_LoopProgress++;
			Sleep(10);
		}
		AfxBeginThread(TaskPage_2,(LPVOID)this);
		while(m_b_Progress && l_i_LoopProgress<200)
		{
			l_i_LoopProgress++;
			Sleep(20);
		}
		m_Anim_Page_2_1_CWnd.Open(IDR_SW_WAIT);
		m_Anim_Page_2_1_CWnd.Play(0,-1,-1);
	}
	else
	{
		m_Text_Page_2_1_CWnd.SetWindowText(_T(""));
		m_Anim_Page_2_1_CWnd.Stop( );
		m_Anim_Page_2_1_CWnd.Close( );
	}
	CPropertyPageEx::OnShowWindow(bShow, nStatus);
}

UINT TaskPage_2
( 
 LPVOID pParam 
 )
{
	CPage_2 *CPage_2_Data = (CPage_2*) pParam;
	return CPage_2_Data->ThreadPage_2();
}

UINT CPage_2::ThreadPage_2
(
 VOID
 ) 
{
	C_Crypto_AES	l_x_oRijndael;
	TSpeDataOut 	l_T_DataIn		= {NULL};
	UCHAR			*l_puc_Key		= NULL;
	UCHAR			*l_puc_szDataOut= NULL;
	UCHAR			*l_puc_szDataIn = NULL;
	INT 			l_i_size_out	= 0;
	INT 			l_i_size_in 	= 0;
	TKeyField		l_T_Keys		= {0};
	TLogonField 	l_T_Logon		= {0};
	TSWState		l_T_SWState;
	
	__try
	{
		m_b_Progress = FALSE;
		m_i_Progress = 0;
		memset(&l_T_DataIn,0,sizeof(TSpeDataOut));
		SetTimer(m_ui_TimerId,m_ui_TimerEd_1,NULL);
		m_T_Result = WlxDataIdentOn(l_T_DataIn);
		m_x_MainSheet->SetWizardButtons(0);
		
		if(m_T_Result == SW_OKHIT_MD)
		{
			memset(&l_T_Keys,0,sizeof(TKeyField));
			memset(&l_T_Logon,0,sizeof(TLogonField));
			
			//Encryption Keys.
			memset(&l_T_Keys,0,sizeof(TKeyField));
			memcpy(&l_T_Keys,l_T_DataIn.m_pwc_UserKey,sizeof(TKeyField));
			
			l_puc_Key =(UCHAR *)malloc(VI_BASEKEY_MAX*sizeof(WCHAR));
			memset(l_puc_Key,0,VI_BASEKEY_MAX*sizeof(WCHAR));
			memcpy(l_puc_Key,l_T_Keys.m_pwc_UserKeyBase,VI_BASEKEY_MAX*sizeof(WCHAR));
			
			l_x_oRijndael.C_Crypto_MakeKey(l_puc_Key,C_Crypto_AES::Key32Bytes);
			
			l_i_size_in 	= sizeof(l_T_DataIn.m_pwc_UserLogon);
			l_i_size_out	= l_x_oRijndael.C_Crypto_Length(l_i_size_in);
			
			l_puc_szDataIn	= (UCHAR *)malloc(l_i_size_in+1);
			l_puc_szDataOut = (UCHAR *)malloc(l_i_size_out+1);
			
			memset(l_puc_szDataIn,0,l_i_size_in+1);
			memset(l_puc_szDataOut,0,l_i_size_out+1);
			
			memcpy(l_puc_szDataIn,l_T_DataIn.m_pwc_UserLogon,sizeof(l_T_DataIn.m_pwc_UserLogon));
			
			l_x_oRijndael.C_Crypto_Decrypt(l_puc_szDataIn,l_i_size_in,l_puc_szDataOut);
			
			//Logon
			memcpy(&l_T_Logon,l_puc_szDataOut,sizeof(TLogonField));
			
			memset(m_pwc_UserKeyData,0,VI_DATAKEY_MAX*sizeof(WCHAR));
			memset(m_pwc_UserLogin,0,VI_USERLOGON_MAX*sizeof(WCHAR));	
			memcpy(m_pwc_UserKeyData,l_T_Keys.m_pwc_UserKeyData,VI_DATAKEY_MAX*sizeof(WCHAR));
			memcpy(m_pwc_UserLogin,l_T_Logon.m_pwc_UserLogin,VI_USERLOGON_MAX*sizeof(WCHAR));
			
			free(l_puc_szDataOut);
			free(l_puc_szDataIn);
			free(l_puc_Key);
		}
		
		if(m_i_Progress == 0)
		{
			m_Text_Page_2_1_CWnd.SetFont(&m_p_Font_1,TRUE);
			m_Text_Page_2_1_CWnd.SetWindowText(_T(VC_DATA_WAITOK));
			KillTimer(m_ui_TimerId);
			m_i_Progress = 1;
		}
		
		if(m_T_Result == SW_ERRSTG_MD || m_T_Result == SW_ERRACT_MD)
		{
			m_Text_Page_2_1_CWnd.SetWindowText(_T(VC_DATA_WAITOKERR));
			if(!WlxIsSWLock())
				WlxSWReboot(l_T_SWState);
			
			if(WlxIsSWValid())
			{
				KillTimer(m_ui_TimerId);
				m_i_Progress = 0;
				OnShowWindow(TRUE,0);
				return FALSE;
			}
		}
		
		m_b_Progress = TRUE;
		SetTimer(m_ui_TimerId,m_ui_TimerEd_2,NULL);
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		m_b_Progress = TRUE;
	}
	return TRUE;
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
					m_Text_Page_2_1_CWnd.SetWindowText(_T(VC_DATA_WAITOK));
					m_i_Progress++;
					break;
				}
			case 1:
				{
					m_Text_Page_2_1_CWnd.SetFont(m_p_Font_2,TRUE);
					m_Anim_Page_2_1_CWnd.Stop();
					m_Anim_Page_2_1_CWnd.Close();
					switch(m_T_Result)
					{
					case SW_OKHIT_MD :
						{
							m_Anim_Page_2_1_CWnd.Open(IDR_SW_OK);
							m_Anim_Page_2_1_CWnd.Play(0,-1,1); 
							m_Text_Page_2_1_CWnd.SetWindowText(_T(VC_DATA_AUTH_OK));
							break;
						}
					case SW_NOHIT_MD :
						{
							m_Anim_Page_2_1_CWnd.Open(IDR_SW_ERR);
							m_Anim_Page_2_1_CWnd.Play(0,-1,1);
							m_Text_Page_2_1_CWnd.SetWindowText(_T(VC_DATA_AUTH_OK));
							break;
						}
					case SW_ABORT_MD :
						{
							m_Anim_Page_2_1_CWnd.Open(IDR_SW_ERR);
							m_Anim_Page_2_1_CWnd.Play(0,-1,1);
							m_Text_Page_2_1_CWnd.SetWindowText(_T(VC_DATA_AUTH_ABORT));
							break;
						}
					default :
						{
							m_Anim_Page_2_1_CWnd.Open(IDR_SW_ERR);
							m_Anim_Page_2_1_CWnd.Play(0,-1,1);
							m_Text_Page_2_1_CWnd.SetWindowText(_T(VC_DATA_AUTH_ERR));
							break;
						}
					}
					m_Text_Page_2_2_CWnd.SetFont(&m_p_Font_1,TRUE);
					m_Text_Page_2_2_CWnd.SetWindowText(_T(VC_DATA_PROCESSOK));
					m_i_Progress++;
					break;
				}
			case 2:
				{
					m_Text_Page_2_2_CWnd.SetFont(m_p_Font_2,TRUE);
					
					switch(m_T_Result)
					{
					case SW_OKHIT_MD :
						{	
							m_Text_Page_2_2_CWnd.SetWindowText(_T(VC_DATA_USER_OK));
							break;
						}
					case SW_NOHIT_MD :
						{
							m_Text_Page_2_2_CWnd.SetWindowText(_T(VC_DATA_USER_NO));
							break;
						}
					case SW_ABORT_MD :
						{
							m_Text_Page_2_2_CWnd.SetWindowText(_T(VC_DATA_USER_ABORT));
							break;
						}
					default :
						{
							m_Text_Page_2_2_CWnd.SetWindowText(_T(VC_DATA_USER_ERR));
							break;
						}
					}
					m_Text_Page_2_3_CWnd.SetFont(&m_p_Font_1,TRUE);
					m_Text_Page_2_3_CWnd.SetWindowText(_T(VC_DATA_WAITKO));
					m_i_Progress++;
					break;
				}
			case 3:
				{				
					m_i_Progress++;
					break;
				}	
			case 4:
				{
					m_i_Progress = 0;
					KillTimer(m_ui_TimerId);
					m_Anim_Page_2_1_CWnd.Stop();
					m_Anim_Page_2_1_CWnd.Close();
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
	__try
	{
	KillTimer(m_ui_TimerId);
	m_i_Progress = 0;
	
	KillTimer(m_ui_TimerId);
	m_i_Progress = 0;
		
	switch(m_T_Result)
	{
	case SW_OKHIT_MD :
		{
			m_x_MainSheet->SetActivePage(2);
			m_x_MainSheet->SetWizardButtons(0);
			break;
		}
	case SW_NOHIT_MD :
		{
			*m_i_PageCode  = 0;
			m_x_MainSheet->SetActivePage(3);
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
			break;
		}
	case SW_ABORT_MD :
		{
			if(!m_b_UserOff)
			{
				*m_i_PageCode  = 1;
				m_x_MainSheet->SetActivePage(3);
				m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
			}
			break;
		}
	default :
		{
			*m_i_PageCode  = 2;
			m_x_MainSheet->SetActivePage(3);
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
			break;
		}
	}
	m_Text_Page_2_1_CWnd.SetFont(m_p_Font_2,TRUE);
	m_Text_Page_2_2_CWnd.SetFont(m_p_Font_2,TRUE);
	m_Text_Page_2_3_CWnd.SetFont(m_p_Font_2,TRUE);
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

VOID CPage_2::OnBackPage
(
 VOID
 )
{
	INT l_i_LoopProgress = 0;
	
	__try
	{
		m_b_UserOff = TRUE;
		
		KillTimer(m_ui_TimerId);
		m_i_Progress = 0;
		
		m_x_MainSheet->SetWizardButtons(0);
		while(m_b_Progress && l_i_LoopProgress<80)
		{
			l_i_LoopProgress++;
			Sleep(10);
		}
		WlxDataIdentOff();
		while(!m_b_Progress && l_i_LoopProgress<200)
		{
			l_i_LoopProgress++;
			Sleep(20);
		}
		
		m_Text_Page_2_1_CWnd.SetFont(m_p_Font_2,TRUE);
		m_Text_Page_2_2_CWnd.SetFont(m_p_Font_2,TRUE);
		m_Text_Page_2_3_CWnd.SetFont(m_p_Font_2,TRUE);
		
		m_Anim_Page_2_1_CWnd.Stop();
		m_Anim_Page_2_1_CWnd.Close();
		
		m_x_MainSheet->SetActivePage(0);
		m_x_MainSheet->SetWizardButtons(PSWIZB_NEXT);
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

VOID CPage_2::OnFinishPage
(
 VOID
 )
{
	INT l_i_LoopProgress = 0;
	
	__try
	{
		m_b_UserOff = TRUE;
		
		m_x_MainSheet->SetWizardButtons(0);
		while(m_b_Progress && l_i_LoopProgress<80)
		{
			WlxDataIdentOff();
			l_i_LoopProgress++;
			Sleep(10);
		}
		WlxDataIdentOff();
		while(!m_b_Progress && l_i_LoopProgress<200)
		{
			WlxDataIdentOff();
			l_i_LoopProgress++;
			Sleep(20);
		}
		
		m_Anim_Page_2_1_CWnd.Stop();
		m_Anim_Page_2_1_CWnd.Close();
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
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

VOID CPage_2::OnCancel
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
			WlxDataIdentOff();
			l_i_LoopProgress++;
			Sleep(10);
		}
		WlxDataIdentOff();
		while(!m_b_Progress && l_i_LoopProgress<200)
		{
			WlxDataIdentOff();
			l_i_LoopProgress++;
			Sleep(20);
		}
		Sleep(600);
		CPropertyPageEx::OnCancel();
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

VOID CPage_2::OnEndSession( BOOL bEnding )
{
	WlxDataIdentOff();
}