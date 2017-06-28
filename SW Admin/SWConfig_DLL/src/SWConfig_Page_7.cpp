/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWConfig_Page_7.cpp 										 //
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

IMPLEMENT_DYNCREATE(CPage_7, CPropertyPageEx)
CPage_7::CPage_7() : CPropertyPageEx(CPage_7::IDD)
{
	m_i_Process = -1;
	m_T_Result	= SW_OKHIT_MD;
	//{{AFX_DATA_INIT(CPage_7)
	m_Combo_Page_7_1 = _T("");
	m_Edit_Page_7_1 = _T("");
	m_Edit_Page_7_2 = _T("");
	//}}AFX_DATA_INIT
}

CPage_7::~CPage_7
(
 )
{
}

VOID CPage_7::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage_7)
	DDX_Control(pDX, IDC_COMBO_PAGE_7_1, m_Combo_Page_7_1_CWnd);
	DDX_Control(pDX, IDC_EDIT_PAGE_7_2, m_Edit_Page_7_2_CWnd);
	DDX_Control(pDX, IDC_EDIT_PAGE_7_1, m_Edit_Page_7_1_CWnd);
	DDX_CBString(pDX, IDC_COMBO_PAGE_7_1, m_Combo_Page_7_1);
	DDX_Text(pDX, IDC_EDIT_PAGE_7_1, m_Edit_Page_7_1);
	DDV_MaxChars(pDX, m_Edit_Page_7_1, VI_USERLOGON_MAX-1);
	DDX_Text(pDX, IDC_EDIT_PAGE_7_2, m_Edit_Page_7_2);
	DDV_MaxChars(pDX, m_Edit_Page_7_2, VI_USERPASSW_MAX-1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPage_7, CPropertyPageEx)
//{{AFX_MSG_MAP(CPage_7)
ON_WM_SHOWWINDOW()
ON_BN_CLICKED(IDC_BUTTON_PAGE_7_1, OnButtonPage_7_1)
ON_BN_CLICKED(IDC_BUTTON_PAGE_7_2, OnButtonPage_7_2)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

VOID CPage_7::OnShowWindow
(
 BOOL bShow, 
 UINT nStatus
 ) 
{
	LPWSTR		*l_puc_TrustList;  
	DWORD		l_dw_TrustCount;	
	
	if(bShow)
	{
		m_Edit_Page_7_1_CWnd.SetWindowText(m_T_Logon->m_pwc_UserLogin);
		m_Edit_Page_7_2_CWnd.SetWindowText(m_T_Logon->m_pwc_UserPassW);
		
		l_dw_TrustCount = 0;
		l_puc_TrustList = (LPWSTR *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY ,DOMAIN_MAX_COUNT * sizeof(LPWSTR));
		
		if(BuildTrustList(&l_puc_TrustList, &l_dw_TrustCount))
		{
			if (l_dw_TrustCount)
			{
				for(INT i = 0 ; i < (INT)l_dw_TrustCount ; i++)
				{	
					if (memcmp(l_puc_TrustList[i], m_T_Logon->m_pwc_UserDomain,wcslen(l_puc_TrustList[i])*sizeof(WCHAR)) != 0)
						m_Combo_Page_7_1_CWnd.InsertString(-1,l_puc_TrustList[i] );
				}
			}
		}
		m_Combo_Page_7_1_CWnd.InsertString(-1,m_T_Logon->m_pwc_UserDomain); 		
		m_Combo_Page_7_1_CWnd.SetCurSel(m_Combo_Page_7_1_CWnd.GetCount()-1);
		for(INT i = 0; i < (INT)l_dw_TrustCount; i++) 
		{
			if(l_puc_TrustList[i] != NULL)
			{
				HeapFree(GetProcessHeap(), 0, l_puc_TrustList[i]);
			}
		}
		
		HeapFree(GetProcessHeap(), 0, l_puc_TrustList);
		
		m_Edit_Page_7_2_CWnd.SetFocus();
	}
	else
	{
		m_Combo_Page_7_1_CWnd.ResetContent( );
	}
	
	CPropertyPageEx::OnShowWindow(bShow, nStatus);	
}

BOOL CPage_7::OnInitDialog
(
 VOID
 ) 
{
	CPropertyPageEx::OnInitDialog();
	m_Combo_Page_7_1_CWnd.LimitText(VI_USERDOMAIN_MAX-1);
	return TRUE;
}

VOID CPage_7::OnButtonPage_7_1
(
 VOID
 ) 
{
	C_Crypto_AES	l_x_oRijndael;
	TUpDataOut		l_T_DataIn							= {NULL};
	UCHAR			*l_puc_Key							= NULL;
	UCHAR			*l_puc_szDataOut					= NULL;
	UCHAR			*l_puc_szDataIn 					= NULL;
	INT 			l_i_size_out						= 0;
	INT 			l_i_size_in 						= 0;
	TLogonField 	l_T_Logon							= {NULL};
	
	__try
	{
		memset(&l_T_Logon,0,sizeof(l_T_Logon));
		m_Edit_Page_7_1_CWnd.GetWindowText(l_T_Logon.m_pwc_UserLogin,VI_USERLOGON_MAX);
		m_Edit_Page_7_2_CWnd.GetWindowText(l_T_Logon.m_pwc_UserPassW,VI_USERPASSW_MAX);
		m_Combo_Page_7_1_CWnd.GetWindowText(l_T_Logon.m_pwc_UserDomain,VI_USERDOMAIN_MAX);
		
		m_i_Process = 0;
		
		l_puc_Key =(UCHAR *)malloc(VI_BASEKEY_MAX*sizeof(WCHAR));
		memset(l_puc_Key,0,VI_BASEKEY_MAX*sizeof(WCHAR));
		memcpy(l_puc_Key,m_T_Keys->m_pwc_UserKeyBase,VI_BASEKEY_MAX*sizeof(WCHAR));
		
		l_x_oRijndael.C_Crypto_MakeKey(l_puc_Key,C_Crypto_AES::Key32Bytes);
		
		l_i_size_in 	= sizeof(TLogonField);
		l_i_size_out	= l_x_oRijndael.C_Crypto_Length(l_i_size_in);
		
		l_puc_szDataIn	= (UCHAR *)malloc(l_i_size_in+1);
		l_puc_szDataOut = (UCHAR *)malloc(l_i_size_out+1);
		
		memset(l_puc_szDataIn,0,l_i_size_in+1);
		memset(l_puc_szDataOut,0,l_i_size_out+1);
		
		memcpy(l_puc_szDataIn,&l_T_Logon,sizeof(TLogonField));
		
		l_x_oRijndael.C_Crypto_Encrypt(l_puc_szDataIn,l_i_size_in,l_puc_szDataOut);
		
		memset(&l_T_DataIn,0,sizeof(l_T_DataIn));
		
		//UserId
		l_T_DataIn.m_i_FieldIndex = 2;
		memcpy(l_T_DataIn.m_pwc_UserId,m_pwc_UserId,VI_USERID_MAX*sizeof(WCHAR));
		memcpy(l_T_DataIn.m_pwc_Field,l_puc_szDataOut,l_i_size_out);
		
		free(l_puc_szDataOut);
		free(l_puc_szDataIn);
		free(l_puc_Key);
		
		m_T_Result = WlxAdminUpdateOn(l_T_DataIn);
		OnNextPage();
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

VOID CPage_7::OnButtonPage_7_2
(
 VOID
 ) 
{
	__try
	{
		m_i_Process = 1;
		
		m_T_Result = WlxAdminUserOn(m_pwc_UserId);
		if(m_T_Result == SW_OKHIT_MD)
		{
			WlxAdminRefresh(*m_T_SWContex);
		}
		OnNextPage();
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

VOID CPage_7::OnNextPage
(
 VOID
 )
{
	__try
	{
		switch(m_i_Process)
		{
		case 0:
			{
				switch(m_T_Result)
				{
				case SW_OKHIT_MD :
					{
						*m_i_PageCode  = 5;
						m_x_MainSheet->SetActivePage(7);
						m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
						break;
					}
				case SW_ABORT_MD :
					{
						*m_i_PageCode  = 9;
						m_x_MainSheet->SetActivePage(7);
						m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
						break;
					}
				default :
					{
						*m_i_PageCode  = 6;
						m_x_MainSheet->SetActivePage(7);
						m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
						break;
					}
				}
				break;
			}
		case 1:
			{
				switch(m_T_Result)
				{
				case SW_OKHIT_MD :
					{
						*m_i_PageCode  = 7;
						m_x_MainSheet->SetActivePage(7);
						m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
						break;
					}
				case SW_ABORT_MD :
					{
						*m_i_PageCode  = 9;
						m_x_MainSheet->SetActivePage(7);
						m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
						break;
					}
				default :
					{
						*m_i_PageCode  = 8;
						m_x_MainSheet->SetActivePage(7);
						m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
						break;
					}
				}
				break;
			}
		default :
			{
				*m_i_PageCode  = 10;
				m_x_MainSheet->SetActivePage(7);
				m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
				break;
			}
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

VOID CPage_7::OnBackPage
(
 VOID
 )
{
	m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
	m_x_MainSheet->SetActivePage(2);
}
