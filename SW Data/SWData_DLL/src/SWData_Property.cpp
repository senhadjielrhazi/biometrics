/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWData_Property.cpp 										 //
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

IMPLEMENT_DYNCREATE(C_DataWizard, CPropertySheetEx)
C_DataWizard::C_DataWizard(TSWFile *i_p_File, INT i_i_NBFile, BOOL i_b_CryptWay)
:CPropertySheetEx(_T(""),NULL,0)
{ 
	INT 		l_i_Count				= 0;
	CHAR		l_puc_TmpName[MAX_PATH]	= {0};
	
	m_p_FileData	= (TSWFileDate *)malloc(sizeof(TSWFileDate)*i_i_NBFile);
	m_i_NbFileLen	= i_i_NBFile;
	
	memset(m_p_FileData,0,sizeof(TSWFileDate)*i_i_NBFile);
	
	for(l_i_Count = 0; l_i_Count< m_i_NbFileLen;l_i_Count++)
	{
		memset(l_puc_TmpName,0,sizeof(l_puc_TmpName));
		wcstombs(l_puc_TmpName, i_p_File[l_i_Count].m_pwc_FilePath,sizeof(l_puc_TmpName));
		
		m_p_FileData[l_i_Count].m_h_FileHandle	= _lopen(l_puc_TmpName,OF_READ);
		
		if(m_p_FileData[l_i_Count].m_h_FileHandle == HFILE_ERROR)
			m_p_FileData[l_i_Count].m_h_FileHandle = NULL;
		
		lstrcpy(m_p_FileData[l_i_Count].m_pwc_FileName,i_p_File[l_i_Count].m_pwc_FilePath); 
	}
	
	m_psh.dwFlags |= PSH_HASHELP |PSH_WIZARD97|PSH_WATERMARK | PSH_HEADER | PSH_USEHICON | PSH_USEPAGELANG;
	m_psh.pszbmWatermark = MAKEINTRESOURCE(IDB_WATERMARKBMP);
	m_psh.pszbmHeader = MAKEINTRESOURCE(IDB_HEADERBMP);
	m_psh.hInstance = AfxGetInstanceHandle();
	m_psh.hIcon   = ::LoadIcon(_Module.m_hInstResource,MAKEINTRESOURCE(IDI_DATA_ICON));
	
	m_pwc_UserKeyData	= (WCHAR *)malloc(VI_DATAKEY_MAX*sizeof(WCHAR));
	m_pwc_UserLogin 	= (WCHAR *)malloc(VI_USERLOGON_MAX*sizeof(WCHAR));
	
	m_Page_1.m_x_MainSheet	= this;
	m_Page_2.m_x_MainSheet	= this;
	m_Page_3.m_x_MainSheet	= this;
	m_Page_4.m_x_MainSheet	= this;
	
	m_Page_2.m_i_PageCode	= &m_i_PageCode;
	m_Page_4.m_i_PageCode	= &m_i_PageCode;
	
	m_Page_2.m_pwc_UserKeyData = m_pwc_UserKeyData;
	m_Page_3.m_pwc_UserKeyData = m_pwc_UserKeyData;
	
	m_Page_2.m_pwc_UserLogin = m_pwc_UserLogin;
	m_Page_3.m_pwc_UserLogin = m_pwc_UserLogin;
	
	m_Page_3.m_b_CryptWay = i_b_CryptWay;
	
	m_Page_3.m_p_FileData = m_p_FileData;
	
	m_Page_3.m_i_NbFileLen = m_i_NbFileLen;
	
	AddPage(&m_Page_1);
	AddPage(&m_Page_2);
	AddPage(&m_Page_3);
	AddPage(&m_Page_4);
}

C_DataWizard::~C_DataWizard
(
 )
{
	INT 		l_i_Count	= 0;
	
	WlxDataIdentOff();	
	
	for(l_i_Count = 0; l_i_Count< m_i_NbFileLen;l_i_Count++)
	{
		if(m_p_FileData[l_i_Count].m_h_FileHandle != NULL)
			_lclose(m_p_FileData[l_i_Count].m_h_FileHandle);
	}
	
	free(m_p_FileData);
	free(m_pwc_UserKeyData);
	free(m_pwc_UserLogin);
	
	m_i_NbFileLen = 0;
}

BEGIN_MESSAGE_MAP(C_DataWizard, CPropertySheetEx)
//{{AFX_MSG_MAP(C_DataWizard)
ON_WM_SHOWWINDOW()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//Handle the Property Sheets back next and finish button settings
BOOL C_DataWizard::OnCmdMsg
(
 UINT nID, 
 INT nCode, 
 VOID* pExtra, 
 AFX_CMDHANDLERINFO* pHandlerInfo
 ) 
{
	INT l_i_Page = GetActiveIndex( );
	
	switch(nID)
	{
	case BACK:
		{
			switch (l_i_Page)
			{
			case 0:
				{
					m_Page_1.OnBackPage();
					break;
				}
			case 1:
				{
					m_Page_2.OnBackPage();
					break;
				}
			case 3:
				{
					m_Page_4.OnBackPage();
					break;
				}
			}
			return 1;
		}
	case NEXT:
		{
			switch (l_i_Page)
			{
			case 0:
				{
					m_Page_1.OnNextPage();
					break;
				}
			case 1:
				{
					m_Page_2.OnNextPage();
					break;
				}
			case 3:
				{
					m_Page_4.OnNextPage();
					break;
				}
			}
			return 1;
		}
	case CANCEL :
		{
			if(l_i_Page == 1)
			{
				m_Page_2.OnFinishPage();
			}
			if(l_i_Page == 2)
			{
				m_Page_3.OnFinishPage();
			}
			break;	
		}
	case FINISH :
		{
			if(l_i_Page == 1)
			{
				m_Page_2.OnFinishPage();
			}
			if(l_i_Page == 2)
			{
				m_Page_3.OnFinishPage();
			}
			break;
		}
	case HELP:
		break;
	}
	return CPropertySheetEx::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

VOID C_DataWizard::OnShowWindow
(
 BOOL bShow, 
 UINT nStatus
 ) 
{
	if(bShow)
		SetForegroundWindow();
	
	CPropertySheetEx::OnShowWindow(bShow, nStatus);
}

BOOL C_DataWizard::OnInitDialog
(
 VOID
 ) 
{
	CRect			l_cr_Rect;
	WINDOWPLACEMENT lpwndpl_1		= {0};
	WINDOWPLACEMENT lpwndpl_2		= {0};
	WINDOWPLACEMENT lpwndpl_3		= {0};
	LONG			l_l_dx			= 0;
	INT 			l_l_dy			= 0;
	LONG			l_l_dxParent	= 0;
	LONG			l_l_dyParent	= 0;
	
	BOOL l_b_Result = CPropertySheetEx::OnInitDialog();
	
	((CPropertySheetEx *)this)->ModifyStyle(0,WS_CAPTION |WS_POPUPWINDOW,0);
	((CPropertySheetEx *)this)->SetForegroundWindow();
	
	CWnd* pApplyButton_1 = GetDlgItem (HELP);
	ASSERT (pApplyButton_1);
	pApplyButton_1->GetWindowPlacement(&lpwndpl_1);
	pApplyButton_1->ShowWindow (SW_HIDE);
	
	CWnd* pApplyButton_2 = GetDlgItem (CANCEL);
	ASSERT (pApplyButton_2);
	pApplyButton_2->GetWindowPlacement(&lpwndpl_2);
	
	CWnd* pApplyButton_3 = GetDlgItem (NEXT);
	ASSERT (pApplyButton_3);
	pApplyButton_3->GetWindowPlacement(&lpwndpl_3);
	
	CWnd* pApplyButton_5 = GetDlgItem (FINISH);
	
	CWnd* pApplyButton_4 = GetDlgItem (BACK);
	ASSERT (pApplyButton_4);
	
	pApplyButton_2->SetWindowPlacement(&lpwndpl_1);
	pApplyButton_3->SetWindowPlacement(&lpwndpl_2);
	pApplyButton_5->SetWindowPlacement(&lpwndpl_2);
	pApplyButton_4->SetWindowPlacement(&lpwndpl_3);
	
	GetWindowRect( &l_cr_Rect);
	l_l_dx = l_cr_Rect.right - l_cr_Rect.left;
	l_l_dy = l_cr_Rect.bottom - l_cr_Rect.top;
	
	l_l_dxParent = GetSystemMetrics(SM_CXSCREEN);
	l_l_dyParent = GetSystemMetrics(SM_CYSCREEN);
	
	l_cr_Rect.left = (l_l_dxParent - l_l_dx) / 2;
	l_cr_Rect.top  = (l_l_dyParent - l_l_dy) / 3;
	
	SetWindowPos(&wndTopMost, l_cr_Rect.left, l_cr_Rect.top, 0, 0, SWP_NOSIZE);
	
	SetWizardButtons(PSWIZB_NEXT);
	return l_b_Result;
}
