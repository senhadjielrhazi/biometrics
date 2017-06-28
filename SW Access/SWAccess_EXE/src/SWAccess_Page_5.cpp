/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWAccess_Page_5.cpp 										 //
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

IMPLEMENT_DYNCREATE(CPage_5, CPropertyPageEx)
CPage_5::CPage_5() : CPropertyPageEx(CPage_5::IDD)
{
	m_psp.dwFlags |= PSP_PREMATURE ;
	
	m_p_Font_1.CreateFont(16, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0,PROOF_QUALITY,VARIABLE_PITCH | FF_SWISS, L""); 
	m_p_Font_2.CreateFont(16, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 
		PROOF_QUALITY,VARIABLE_PITCH | FF_SWISS, L"");
	//{{AFX_DATA_INIT(CPage_5)
	m_Edit_Page_5_1 = _T("");
	m_Edit_Page_5_2 = _T("");
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
	DDX_Control(pDX, IDC_BUTTON_PAGE_5_1, m_Button_Page_5_1_CWnd);
	DDX_Control(pDX, IDC_EDIT_PAGE_5_3, m_Edit_Page_5_2_CWnd);
	DDX_Control(pDX, IDC_EDIT_PAGE_5_2, m_Edit_Page_5_1_CWnd);
	DDX_Control(pDX, IDC_COMBO_PAGE_5_1, m_Combo_Page_5_1_CWnd);
	DDX_Text(pDX, IDC_EDIT_PAGE_5_2, m_Edit_Page_5_1);
	DDV_MaxChars(pDX, m_Edit_Page_5_1,	VI_APPNAME_MAX-1);
	DDX_Text(pDX, IDC_EDIT_PAGE_5_3, m_Edit_Page_5_2);
	DDV_MaxChars(pDX, m_Edit_Page_5_2, VI_APPPASSW_MAX-1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPage_5, CPropertyPageEx)
//{{AFX_MSG_MAP(CPage_5)
ON_WM_SHOWWINDOW()
ON_BN_CLICKED(IDC_BUTTON_PAGE_5_1, OnButtonPage_5_1)
ON_BN_CLICKED(IDC_BUTTON_PAGE_5_2, OnButtonPage_5_2)
ON_CBN_CLOSEUP(IDC_COMBO_PAGE_5_1, OnCloseupComboPage_5_1)
ON_CBN_SELCHANGE(IDC_COMBO_PAGE_5_1, OnSelchangeComboPage_5_1)
ON_EN_CHANGE(IDC_EDIT_PAGE_5_2, OnChangeEditPage_5_1)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

VOID CPage_5::OnShowWindow
(
 BOOL bShow, 
 UINT nStatus
 ) 
{	
	TAccessField	l_T_AccessFieldNull 			= {NULL};
	INT 			l_i_CurrentIndex				= 1;
	INT 			l_i_CurrentField				= 0;
	CString 		l_c_IndexString;
	
	memset(&l_T_AccessFieldNull,0,sizeof(l_T_AccessFieldNull));
	memset(m_pi_AppIndex,-1,sizeof(m_pi_AppIndex));
	
	if(bShow)
	{
		for(INT i = 0; i<VI_NBAPPLI_MAX;i++)
		{
			if(memcmp(&m_T_Access[i],&l_T_AccessFieldNull,sizeof(TAccessField)) != 0)
			{
				l_i_CurrentField = i;
				m_pi_AppIndex[i] = l_i_CurrentIndex;
				l_c_IndexString.Format(L"%d",l_i_CurrentIndex);
				m_Combo_Page_5_1_CWnd.InsertString(-1,l_c_IndexString);
				l_i_CurrentIndex++;
			}
		}
		m_Combo_Page_5_1_CWnd.SetCurSel(l_i_CurrentIndex-2);
		m_Edit_Page_5_1_CWnd.SetWindowText(m_T_Access[l_i_CurrentField].m_pwc_AppName);
		m_Edit_Page_5_2_CWnd.SetWindowText(m_T_Access[l_i_CurrentField].m_pwc_AppPassW);			
	}
	else
	{
		m_Combo_Page_5_1_CWnd.ResetContent( );
		m_Edit_Page_5_1_CWnd.SetWindowText(_T(""));
		m_Edit_Page_5_2_CWnd.SetWindowText(_T("")); 		
	}
	
	CPropertyPageEx::OnShowWindow(bShow, nStatus);
}

BOOL CPage_5::OnInitDialog
(
 VOID
 ) 
{
	CPropertyPageEx::OnInitDialog();
	m_Combo_Page_5_1_CWnd.SetFont(&m_p_Font_2,TRUE);
	m_Edit_Page_5_1_CWnd.SetFont(&m_p_Font_1,TRUE);
	m_Edit_Page_5_2_CWnd.SetFont(&m_p_Font_1,TRUE);
	return TRUE;
}

VOID CPage_5::OnButtonPage_5_1
(
 VOID
 ) 
{
	TModuleRet		l_T_Result;
	C_Crypto_AES	l_x_oRijndael;
	TAccessField	l_T_AccessFieldTmp					= {NULL};
	TUpDataOut		l_T_Data							= {NULL};
	UCHAR			*l_puc_Key							= NULL;
	UCHAR			*l_puc_szDataOut					= NULL;
	UCHAR			*l_puc_szDataIn 					= NULL;
	INT 			l_i_size_out						= NULL;
	INT 			l_i_size_in 						= 0;
	INT 			l_i_CurrentIndex					= 0;
	
	__try
	{
		l_puc_Key =(UCHAR *)malloc(VI_BASEKEY_MAX*sizeof(WCHAR));
		memset(l_puc_Key,0,VI_BASEKEY_MAX*sizeof(WCHAR));
		memcpy(l_puc_Key,m_T_Keys->m_pwc_UserKeyBase,VI_BASEKEY_MAX*sizeof(WCHAR));
		
		l_x_oRijndael.C_Crypto_MakeKey(l_puc_Key,C_Crypto_AES::Key32Bytes);
		
		//Set App Field
		l_i_size_in 	= sizeof(TAccessField);
		l_i_size_out	= l_x_oRijndael.C_Crypto_Length(l_i_size_in);
		
		l_puc_szDataIn	= (UCHAR *)malloc(l_i_size_in+1);
		l_puc_szDataOut = (UCHAR *)malloc(l_i_size_out+1);
		
		memset(l_puc_szDataIn,0,l_i_size_in+1);
		memset(l_puc_szDataOut,0,l_i_size_out+1);
		memset(&l_T_Data,0,sizeof(l_T_Data));
		
		l_i_CurrentIndex = m_Combo_Page_5_1_CWnd.GetCurSel();
		
		for(INT i = 0; i<VI_NBAPPLI_MAX;i++)
		{
			if(m_pi_AppIndex[i] == l_i_CurrentIndex + 1)
			{
				m_Edit_Page_5_1_CWnd.GetWindowText(l_T_AccessFieldTmp.m_pwc_AppName,sizeof(l_T_AccessFieldTmp.m_pwc_AppName)-1);
				m_Edit_Page_5_2_CWnd.GetWindowText(l_T_AccessFieldTmp.m_pwc_AppPassW,sizeof(l_T_AccessFieldTmp.m_pwc_AppPassW)-1);
				memcpy(l_T_AccessFieldTmp.m_pwc_AppClassN,m_T_Access[i].m_pwc_AppClassN,sizeof(l_T_AccessFieldTmp.m_pwc_AppClassN));
				memcpy(l_T_AccessFieldTmp.m_pwc_AppClassNP,m_T_Access[i].m_pwc_AppClassNP,sizeof(l_T_AccessFieldTmp.m_pwc_AppClassNP));
				memcpy(l_T_AccessFieldTmp.m_pwc_AppTitleB,m_T_Access[i].m_pwc_AppTitleB,sizeof(l_T_AccessFieldTmp.m_pwc_AppTitleB));
				l_T_AccessFieldTmp.m_i_AppOption = m_T_Access[i].m_i_AppOption;
				l_T_Data.m_i_FieldIndex = i + 3;
				break;
			}
		}
		
		memcpy(l_puc_szDataIn,&l_T_AccessFieldTmp,sizeof(TAccessField));
		
		l_x_oRijndael.C_Crypto_Encrypt(l_puc_szDataIn,l_i_size_in,l_puc_szDataOut);
		
		//UserId
		memcpy(l_T_Data.m_pwc_UserId,m_pwc_UserId,VI_USERID_MAX*sizeof(WCHAR));
		
		memcpy(l_T_Data.m_pwc_Field,l_puc_szDataOut,sizeof(l_T_Data.m_pwc_Field));
		
		free(l_puc_szDataOut);
		free(l_puc_szDataIn);
		free(l_puc_Key);
		
		l_T_Result = WlxAccessUpdateOn(l_T_Data);
		
		switch(l_T_Result)
		{
		case SW_OKHIT_MD :
			{
				memcpy(&m_T_Access[l_T_Data.m_i_FieldIndex-3],&l_T_AccessFieldTmp,sizeof(TAccessField));
				*m_i_PageCode  = 4;
				m_x_MainSheet->SetActivePage(5);
				m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
				break;
			}
		case SW_ABORT_MD :
			{
				*m_i_PageCode  = 5;
				m_x_MainSheet->SetActivePage(5);
				m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
				break;
			}
		default :
			{
				*m_i_PageCode  = 6;
				m_x_MainSheet->SetActivePage(5);
				m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
				break;
			}
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

VOID CPage_5::OnButtonPage_5_2
(
 VOID
 ) 
{
	TModuleRet		l_T_Result;
	C_Crypto_AES	l_x_oRijndael;
	TUpDataOut		l_T_Data							= {NULL};
	UCHAR			*l_puc_Key							= NULL;
	UCHAR			*l_puc_szDataOut,*l_puc_szDataIn	= NULL;
	INT 			l_i_size_out,l_i_size_in			= 0;
	INT 			l_i_CurrentIndex					= 0;
	
	__try
	{
		l_puc_Key =(UCHAR *)malloc(VI_BASEKEY_MAX*sizeof(WCHAR));
		memset(l_puc_Key,0,VI_BASEKEY_MAX*sizeof(WCHAR));
		memcpy(l_puc_Key,m_T_Keys->m_pwc_UserKeyBase,VI_BASEKEY_MAX*sizeof(WCHAR));
		
		l_x_oRijndael.C_Crypto_MakeKey(l_puc_Key,C_Crypto_AES::Key32Bytes);
		
		//Set App Field
		l_i_size_in 	= sizeof(TAccessField);
		l_i_size_out	= l_x_oRijndael.C_Crypto_Length(l_i_size_in);
		
		l_puc_szDataIn	= (UCHAR *)malloc(l_i_size_in+1);
		l_puc_szDataOut = (UCHAR *)malloc(l_i_size_out+1);
		
		memset(l_puc_szDataIn,0,l_i_size_in+1);
		memset(l_puc_szDataOut,0,l_i_size_out+1);
		memset(&l_T_Data,0,sizeof(l_T_Data));
		
		l_i_CurrentIndex = m_Combo_Page_5_1_CWnd.GetCurSel();
		
		for(INT i = 0; i<VI_NBAPPLI_MAX;i++)
		{
			if(m_pi_AppIndex[i] == l_i_CurrentIndex + 1)
			{
				l_T_Data.m_i_FieldIndex = i + 3;
				break;
			}
		}
		
		l_x_oRijndael.C_Crypto_Encrypt(l_puc_szDataIn,l_i_size_in,l_puc_szDataOut);
		
		//UserId
		memcpy(l_T_Data.m_pwc_UserId,m_pwc_UserId,VI_USERID_MAX*sizeof(WCHAR));
		
		memcpy(l_T_Data.m_pwc_Field,l_puc_szDataOut,sizeof(l_T_Data.m_pwc_Field));
		
		free(l_puc_szDataOut);
		free(l_puc_szDataIn);
		free(l_puc_Key);
		
		l_T_Result = WlxAccessUpdateOn(l_T_Data);
		
		switch(l_T_Result)
		{
		case SW_OKHIT_MD :
			{
				memset(&m_T_Access[l_T_Data.m_i_FieldIndex-3],0,sizeof(TAccessField));
				(*m_i_NbApplication)--;
				*m_i_PageCode  = 7;
				m_x_MainSheet->SetActivePage(5);
				m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
				break;
			}
		case SW_ABORT_MD :
			{
				*m_i_PageCode  = 8;
				m_x_MainSheet->SetActivePage(5);
				m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
				break;
			}
		default :
			{
				*m_i_PageCode  = 9;
				m_x_MainSheet->SetActivePage(5);
				m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
				break;
			}
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

VOID CPage_5::OnNextPage
(
 VOID
 )
{
}

VOID CPage_5::OnBackPage
(
 VOID
 )
{
	m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
	m_x_MainSheet->SetActivePage(1);
}

VOID CPage_5::OnCloseupComboPage_5_1
(
 VOID
 ) 
{
	INT 		l_i_CurrentIndex = 0;
	
	l_i_CurrentIndex = m_Combo_Page_5_1_CWnd.GetCurSel();
	
	for(INT i = 0; i<VI_NBAPPLI_MAX;i++)
	{
		if(m_pi_AppIndex[i] == l_i_CurrentIndex + 1)
		{
			m_Edit_Page_5_1_CWnd.SetWindowText(m_T_Access[i].m_pwc_AppName);
			m_Edit_Page_5_2_CWnd.SetWindowText(m_T_Access[i].m_pwc_AppPassW);			
			break;
		}
	}
}

VOID CPage_5::OnSelchangeComboPage_5_1
(
 VOID
 ) 
{
	INT 		l_i_CurrentIndex = 0;
	
	l_i_CurrentIndex = m_Combo_Page_5_1_CWnd.GetCurSel();
	
	for(INT i = 0; i<VI_NBAPPLI_MAX;i++)
	{
		if(m_pi_AppIndex[i] == l_i_CurrentIndex + 1)
		{
			m_Edit_Page_5_1_CWnd.SetWindowText(m_T_Access[i].m_pwc_AppName);
			m_Edit_Page_5_2_CWnd.SetWindowText(m_T_Access[i].m_pwc_AppPassW);			
			break;
		}
	}
}

VOID CPage_5::OnChangeEditPage_5_1
(
 VOID
 ) 
{
	CString 		l_c_AppName;
	INT 			l_b_AppExist					= 0;
	INT 			l_pi_AppFill[VI_NBAPPLI_MAX]	= {0};
	TAccessField	l_T_AccessFieldNull 			= {0};
	WCHAR			l_pwc_Name[VI_APPNAME_MAX]		= {0};
	INT 			l_i_CurrentIndex				= 0;
	INT 			l_i_Index						= 0;
	
	memset(l_pwc_Name,0,sizeof(l_pwc_Name));
	
	l_i_CurrentIndex = m_Combo_Page_5_1_CWnd.GetCurSel();
	
	m_Edit_Page_5_1_CWnd.GetWindowText(l_c_AppName);
	if(l_c_AppName.IsEmpty())
		(GetDlgItem(IDC_BUTTON_PAGE_5_1))->EnableWindow(FALSE);
	else
	{
		memcpy(l_pwc_Name,l_c_AppName,sizeof(l_pwc_Name)-1);
		
		for(INT i = 0; i<VI_NBAPPLI_MAX;i++)
		{
			if(m_pi_AppIndex[i] == l_i_CurrentIndex + 1)
			{
				l_i_Index = i;		
				break;
			}
		}
		
		for(i = 0; i<VI_NBAPPLI_MAX;i++)
		{
			if(i!=l_i_Index && memcmp(m_T_Access[i].m_pwc_AppName,l_pwc_Name,sizeof(l_pwc_Name)) == 0)
				l_b_AppExist = TRUE;
		}
		
		if(l_b_AppExist)
			(GetDlgItem(IDC_BUTTON_PAGE_5_1))->EnableWindow(FALSE);
		else
			(GetDlgItem(IDC_BUTTON_PAGE_5_1))->EnableWindow(TRUE);
	}
}

