/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWAccess_Page_4.cpp 										 //
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

IMPLEMENT_DYNCREATE(CPage_4, CPropertyPageEx)
CPage_4::CPage_4() : CPropertyPageEx(CPage_4::IDD)
{
	m_psp.dwFlags |= PSP_PREMATURE ;
	
	m_p_Font.CreateFont(18, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0,PROOF_QUALITY,VARIABLE_PITCH | FF_SWISS, L""); 
	//{{AFX_DATA_INIT(CPage_4)
	m_Edit_Page_4_1 = _T("");
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
	DDX_Control(pDX, IDC_STATIC_PAGE_4_1, m_Text_Page_4_4_CWnd);
	DDX_Text(pDX, IDC_EDIT_PAGE_4_1, m_Edit_Page_4_1);
	DDV_MaxChars(pDX, m_Edit_Page_4_1, VI_APPNAME_MAX-1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPage_4, CPropertyPageEx)
//{{AFX_MSG_MAP(CPage_4)
ON_WM_SHOWWINDOW()
ON_EN_CHANGE(IDC_EDIT_PAGE_4_1, OnChangeEditPage_4_1)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

VOID CPage_4::OnShowWindow
(
 BOOL bShow, 
 UINT nStatus
 ) 
{	
	CString 		l_c_AppName;
	BOOL			l_b_AppExist					= FALSE;
	WCHAR			l_pwc_Name[VI_APPNAME_MAX]		= {0};
	
	if(bShow)
	{
		m_Edit_Page_4_1_CWnd.GetWindowText(l_c_AppName);
		if(l_c_AppName.IsEmpty())
		{
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK);
			m_Text_Page_4_4_CWnd.SetWindowText(_T(VC_ACCESSPAGE2_VIDE));
		}
		else
		{
			memcpy(l_pwc_Name,l_c_AppName,sizeof(l_pwc_Name)-1);
			
			for(INT i = 0; i<VI_NBAPPLI_MAX;i++)
			{
				if(memcmp(m_T_Access[i].m_pwc_AppName,l_pwc_Name,sizeof(l_pwc_Name)) == 0)
				{
					l_b_AppExist = TRUE;
					break;
				}
			}
			
			if(l_b_AppExist)
			{
				m_Text_Page_4_4_CWnd.SetWindowText(_T(VC_ACCESSPAGE2_EXIST));
				m_x_MainSheet->SetWizardButtons(PSWIZB_BACK);
			}
			else
			{
				m_Text_Page_4_4_CWnd.SetWindowText(_T(VC_ACCESSPAGE2_OK));
				m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
			}
		}
	}
	
	CPropertyPageEx::OnShowWindow(bShow, nStatus);
}

BOOL CPage_4::OnInitDialog
(
 VOID
 ) 
{
	CPropertyPageEx::OnInitDialog();
	m_Edit_Page_4_1_CWnd.SetFont(&m_p_Font,TRUE);
	return TRUE;
}

VOID CPage_4::OnChangeEditPage_4_1
(
 VOID
 ) 
{
	CString 		l_c_AppName;
	BOOL			l_b_AppExist					= FALSE;
	INT 			l_pi_AppFill[VI_NBAPPLI_MAX]	= {0};
	TAccessField	l_T_AccessFieldNull 			= {0};
	WCHAR			l_pwc_Name[VI_APPNAME_MAX]		= {0};
	
	memset(l_pwc_Name,0,sizeof(l_pwc_Name));
	
	m_Edit_Page_4_1_CWnd.GetWindowText(l_c_AppName);
	if(l_c_AppName.IsEmpty())
	{
		m_x_MainSheet->SetWizardButtons(PSWIZB_BACK);
		m_Text_Page_4_4_CWnd.SetWindowText(_T(VC_ACCESSPAGE2_VIDE));
		memset(m_Wnd->m_T_WindowData.m_pwc_AppName,0,sizeof(m_Wnd->m_T_WindowData.m_pwc_AppName));
	}
	else
	{
		memcpy(l_pwc_Name,l_c_AppName,sizeof(l_pwc_Name)-1);
		
		for(INT i = 0; i<VI_NBAPPLI_MAX;i++)
		{
			if(memcmp(m_T_Access[i].m_pwc_AppName,l_pwc_Name,sizeof(l_pwc_Name)) == 0)
			{
				l_b_AppExist = TRUE;
				break;
			}
		}
		
		if(l_b_AppExist)
		{
			m_Text_Page_4_4_CWnd.SetWindowText(_T(VC_ACCESSPAGE2_EXIST));
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK);
			memset(m_Wnd->m_T_WindowData.m_pwc_AppName,0,sizeof(m_Wnd->m_T_WindowData.m_pwc_AppName));
		}
		else
		{
			m_Text_Page_4_4_CWnd.SetWindowText(_T(VC_ACCESSPAGE2_OK));
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
			memcpy(m_Wnd->m_T_WindowData.m_pwc_AppName,l_c_AppName,sizeof(m_Wnd->m_T_WindowData.m_pwc_AppName)-1);
		}
	}
}

VOID CPage_4::OnNextPage
(
 VOID
 )
{
	TModuleRet		m_T_Result;
	C_Crypto_AES	l_x_oRijndael;
	CString 		l_c_AppName;
	INT 			l_i_AppExist						= 0;
	INT 			l_pi_AppFill[VI_NBAPPLI_MAX]		= {0};
	TAccessField	l_T_AccessFieldNull 				= {0};	
	TUpDataOut		l_T_Data							= {NULL};
	UCHAR			*l_puc_Key							= NULL;
	UCHAR			*l_puc_szDataOut					= NULL;
	UCHAR			*l_puc_szDataIn 					= NULL;
	INT 			l_i_size_out						= 0;
	INT 			l_i_size_in 						= 0;
	
	memset(&l_T_AccessFieldNull,0,sizeof(l_T_AccessFieldNull));
	
	m_Edit_Page_4_1_CWnd.GetWindowText(l_c_AppName);
	memcpy(m_Wnd->m_T_WindowData.m_pwc_AppName,l_c_AppName,sizeof(m_Wnd->m_T_WindowData.m_pwc_AppName)-1);
	
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
	
	memcpy(l_puc_szDataIn,&m_Wnd->m_T_WindowData,sizeof(TAccessField));
	
	l_x_oRijndael.C_Crypto_Encrypt(l_puc_szDataIn,l_i_size_in,l_puc_szDataOut);
	
	memset(&l_T_Data,0,sizeof(l_T_Data));
	
	//UserId
	memcpy(l_T_Data.m_pwc_UserId,m_pwc_UserId,VI_USERID_MAX*sizeof(WCHAR));
	
	for(INT i = 0; i<VI_NBAPPLI_MAX;i++)
	{
		if(memcmp(&m_T_Access[i],&l_T_AccessFieldNull,sizeof(TAccessField)) == 0)
		{
			l_i_AppExist = i;
			break;
		}
	}
	l_T_Data.m_i_FieldIndex = l_i_AppExist + 3;
	memcpy(l_T_Data.m_pwc_Field,l_puc_szDataOut,sizeof(l_T_Data.m_pwc_Field));
	
	free(l_puc_szDataOut);
	free(l_puc_szDataIn);
	free(l_puc_Key);
	
	m_T_Result = WlxAccessUpdateOn(l_T_Data);
	
	switch(m_T_Result)
	{
	case SW_OKHIT_MD :
		{
			memcpy(&m_T_Access[l_i_AppExist],&m_Wnd->m_T_WindowData,sizeof(TAccessField));
			(*m_i_NbApplication)++;
			*m_i_PageCode  = 1;
			m_x_MainSheet->SetActivePage(5);
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
			break;
		}
	case SW_ABORT_MD :
		{
			*m_i_PageCode  = 2;
			m_x_MainSheet->SetActivePage(5);
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
			break;
		}
	default :
		{
			*m_i_PageCode  = 3;
			m_x_MainSheet->SetActivePage(5);
			m_x_MainSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
			break;
		}
	}
}

VOID CPage_4::OnBackPage
(
 VOID
 )
{
	m_x_MainSheet->SetWizardButtons(PSWIZB_BACK);
	m_x_MainSheet->SetActivePage(2);
}

