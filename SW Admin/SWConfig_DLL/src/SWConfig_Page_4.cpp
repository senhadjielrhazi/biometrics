/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWConfig_Page_4.cpp 										 //
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

IMPLEMENT_DYNCREATE(CPage_4, CPropertyPageEx)
CPage_4::CPage_4() : CPropertyPageEx(CPage_4::IDD)
{
	//{{AFX_DATA_INIT(CPage_4)
	m_Combo_Page_4_1 = _T("");
	m_Edit_Page_4_1 = _T("");
	m_Edit_Page_4_2 = _T("");
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
	DDX_Control(pDX, IDC_COMBO_PAGE_4_1, m_Combo_Page_4_1_CWnd);
	DDX_Control(pDX, IDC_EDIT_PAGE_4_2, m_Edit_Page_4_2_CWnd);
	DDX_Control(pDX, IDC_EDIT_PAGE_4_1, m_Edit_Page_4_1_CWnd);
	DDX_CBString(pDX, IDC_COMBO_PAGE_4_1, m_Combo_Page_4_1);
	DDX_Text(pDX, IDC_EDIT_PAGE_4_1, m_Edit_Page_4_1);
	DDV_MaxChars(pDX, m_Edit_Page_4_1, VI_USERLOGON_MAX-1);
	DDX_Text(pDX, IDC_EDIT_PAGE_4_2, m_Edit_Page_4_2);
	DDV_MaxChars(pDX, m_Edit_Page_4_2, VI_USERPASSW_MAX-1);
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
	C_Registry		l_x_Registry;
	LPWSTR			*l_puc_TrustList					= NULL;  
	DWORD			l_dw_TrustCount 					= 0;	
	WCHAR			l_pwc_UserName[VI_USERLOGON_MAX]	= {0};
	WCHAR			l_pwc_UserDomain[VI_USERDOMAIN_MAX]	= {0};
	
	l_x_Registry.C_Registry_GetLastUserDomain(l_pwc_UserName,l_pwc_UserDomain);
	m_Combo_Page_4_1_CWnd.LimitText(VI_USERDOMAIN_MAX-1);
	
	if(bShow)
	{
		m_Edit_Page_4_1_CWnd.SetWindowText(l_pwc_UserName);
		m_Edit_Page_4_2_CWnd.SetWindowText(_T(""));
		
		l_dw_TrustCount = 0;
		l_puc_TrustList = (LPWSTR *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY ,DOMAIN_MAX_COUNT * sizeof(LPWSTR));
		
		if(BuildTrustList(&l_puc_TrustList, &l_dw_TrustCount))
		{
			if (l_dw_TrustCount)
			{
				for(INT i = 0 ; i < (INT)l_dw_TrustCount ; i++)
				{	
					if (memcmp(l_puc_TrustList[i], l_pwc_UserDomain,wcslen(l_puc_TrustList[i])*sizeof(WCHAR)) != 0)
						m_Combo_Page_4_1_CWnd.InsertString(-1,l_puc_TrustList[i] );
				}
			}
		}
		m_Combo_Page_4_1_CWnd.InsertString(-1,l_pwc_UserDomain); 		
		m_Combo_Page_4_1_CWnd.SetCurSel(m_Combo_Page_4_1_CWnd.GetCount()-1);
		
		for(INT i = 0; i < (INT)l_dw_TrustCount; i++) 
		{
			if(l_puc_TrustList[i] != NULL)
			{
				HeapFree(GetProcessHeap(), 0, l_puc_TrustList[i]);
			}
		}
		
		HeapFree(GetProcessHeap(), 0, l_puc_TrustList);
		
		m_Edit_Page_4_2_CWnd.SetFocus();
	}
	else
		m_Combo_Page_4_1_CWnd.ResetContent( );
	
	CPropertyPageEx::OnShowWindow(bShow, nStatus);	
}

BOOL CPage_4::OnInitDialog
(
 VOID
 ) 
{
	CPropertyPageEx::OnInitDialog();
	m_Combo_Page_4_1_CWnd.LimitText(VI_USERDOMAIN_MAX-1);
	return TRUE;
}

VOID CPage_4::OnNextPage
(
 VOID
 )
{
	C_Crypto_AES	l_x_oRijndael;
	UCHAR			*l_puc_Key							= NULL;
	UCHAR			*l_puc_szDataOut,*l_puc_szDataIn	= NULL;
	INT 			l_i_size_out						= 0;
	INT 			l_i_size_in 						= 0;
	TKeyField		l_T_Keys							= {NULL};
	TLogonField 	l_T_Logon							= {NULL};
	
	__try
	{
		memset(m_T_DataIn,0,sizeof(TSupDataOut));
		memset(&l_T_Logon,0,sizeof(TLogonField));
		memset(&l_T_Keys,0,sizeof(TKeyField));
		
		m_Edit_Page_4_1_CWnd.GetWindowText(l_T_Logon.m_pwc_UserLogin,VI_USERLOGON_MAX);
		m_Edit_Page_4_2_CWnd.GetWindowText(l_T_Logon.m_pwc_UserPassW,VI_USERPASSW_MAX);
		m_Combo_Page_4_1_CWnd.GetWindowText(l_T_Logon.m_pwc_UserDomain,VI_USERDOMAIN_MAX);
		
		l_puc_Key =(UCHAR *)malloc(VI_DATAKEY_MAX*sizeof(WCHAR));
		memset(l_puc_Key,0,VI_DATAKEY_MAX*sizeof(WCHAR));
		l_x_oRijndael.C_Crypto_GenerateKey(l_puc_Key,C_Crypto_AES::Key32Bytes);
		memcpy(l_T_Keys.m_pwc_UserKeyData, l_puc_Key,VI_DATAKEY_MAX*sizeof(WCHAR));
		free(l_puc_Key);
		
		l_puc_Key =(UCHAR *)malloc(VI_BASEKEY_MAX*sizeof(WCHAR));
		memset(l_puc_Key,0,VI_BASEKEY_MAX*sizeof(WCHAR));
		l_x_oRijndael.C_Crypto_GenerateKey(l_puc_Key,C_Crypto_AES::Key32Bytes);
		memcpy(l_T_Keys.m_pwc_UserKeyBase, l_puc_Key,VI_BASEKEY_MAX*sizeof(WCHAR));
		l_x_oRijndael.C_Crypto_MakeKey(l_puc_Key,C_Crypto_AES::Key32Bytes);
		free(l_puc_Key);
		
		l_i_size_in 	= sizeof(l_T_Logon);
		l_i_size_out	= l_x_oRijndael.C_Crypto_Length(l_i_size_in);
		
		l_puc_szDataIn	= (UCHAR *)malloc(l_i_size_in+1);
		l_puc_szDataOut = (UCHAR *)malloc(l_i_size_out+1);
		
		memset(l_puc_szDataIn,0,l_i_size_in+1);
		memset(l_puc_szDataOut,0,l_i_size_out+1);
		
		memcpy(l_puc_szDataIn,&l_T_Logon,sizeof(l_T_Logon));
		
		memcpy(m_pwc_UserLogin,&l_T_Logon.m_pwc_UserLogin,sizeof(l_T_Logon.m_pwc_UserLogin));
		
		l_x_oRijndael.C_Crypto_Encrypt(l_puc_szDataIn,l_i_size_in,l_puc_szDataOut);
		
		memcpy(m_T_DataIn->m_pwc_UserLogon,l_puc_szDataOut,l_i_size_out);
		memcpy(m_T_DataIn->m_pwc_UserKey,&l_T_Keys,sizeof(l_T_Keys));
		
		free(l_puc_szDataIn);
		free(l_puc_szDataOut);
		
		l_i_size_in 	= sizeof(TAccessField);
		l_i_size_out	= l_x_oRijndael.C_Crypto_Length(l_i_size_in);
		
		l_puc_szDataIn	= (UCHAR *)malloc(l_i_size_in+1);
		l_puc_szDataOut = (UCHAR *)malloc(l_i_size_out+1);
		
		memset(l_puc_szDataIn,0,l_i_size_in+1);
		memset(l_puc_szDataOut,0,l_i_size_out+1);
		
		l_x_oRijndael.C_Crypto_Encrypt(l_puc_szDataIn,l_i_size_in,l_puc_szDataOut);
		
		memcpy(m_T_DataIn->m_pwc_Field,l_puc_szDataOut,sizeof(m_T_DataIn->m_pwc_Field));
		
		free(l_puc_szDataIn);
		free(l_puc_szDataOut);
		
		m_x_MainSheet->SetActivePage(4);
		m_x_MainSheet->SetWizardButtons(PSWIZB_BACK);
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

VOID CPage_4::OnBackPage
(
 VOID
 )
{
	m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
	m_x_MainSheet->SetActivePage(2);
}