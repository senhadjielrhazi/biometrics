/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWData_Page_3.cpp											 //
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

IMPLEMENT_DYNCREATE(CPage_3, CPropertyPageEx)
CPage_3::CPage_3() : CPropertyPageEx(CPage_3::IDD)
{
	m_p_Font.CreateFont(15, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, 0, 0, 0, 
		PROOF_QUALITY,VARIABLE_PITCH | FF_SWISS, L""); 
	
	m_i_FileSize = NULL;
	
	//{{AFX_DATA_INIT(CPage_3)
	//}}AFX_DATA_INIT
}

CPage_3::~CPage_3()
{
	if(m_i_FileSize != NULL)
		free(m_i_FileSize);
}

VOID CPage_3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage_3)
	DDX_Control(pDX, IDC_LIST_PAGE_3_1, m_List_Page_3_1_CWnd);
	DDX_Control(pDX, IDC_PROGRESS_PAGE_3_1, m_Progress_Page_3_1_CWnd);
	DDX_Control(pDX, IDC_TEXT_PAGE_3_2, m_Text_Page_3_2_CWnd);
	DDX_Control(pDX, IDC_TEXT_PAGE_3_1, m_Text_Page_3_1_CWnd);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPage_3, CPropertyPageEx)
//{{AFX_MSG_MAP(CPage_3)
ON_WM_SHOWWINDOW()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

VOID CPage_3::OnShowWindow(BOOL bShow, UINT nStatus) 
{	
	CString 	l_c_TempUser;
	
	if(bShow)
	{
		m_b_Exit = FALSE;
		l_c_TempUser.Format(L"%s.",m_pwc_UserLogin);
		m_Text_Page_3_1_CWnd.SetFont(&m_p_Font);
		m_Text_Page_3_1_CWnd.SetWindowText(l_c_TempUser);
		m_Text_Page_3_2_CWnd.SetWindowText(L"0%");
		AfxBeginThread(TaskPage_3,(LPVOID)this);
	}
	else
		m_List_Page_3_1_CWnd.DeleteAllItems();
	
	CPropertyPageEx::OnShowWindow(bShow, nStatus);
}

UINT TaskPage_3( LPVOID pParam )
{
	CPage_3 *CPage_3_Data = (CPage_3*) pParam;
	return CPage_3_Data->ThreadPage_3();
}

UINT CPage_3::ThreadPage_3() 
{
	C_Crypto_AES	l_x_oRijndael;
	WCHAR			l_pwc_TmpPath[MAX_PATH] 		= {0};
	WCHAR			l_pwc_TmpState[256] 			= {0};
	ULONGLONG		l_i_size_out					= 0;
	ULONGLONG		l_i_size_in 					= 0;
	INT 			l_i_Item						= 0;
	ULONG			l_l_SizeOfAll					= 0;
	DWORD			l_dw_Result 					= 0;
	UCHAR			*l_p_DataIn 					= NULL;
	UCHAR			*l_p_DataOut					= NULL;
	UCHAR			*l_puc_Key						= NULL;
	HFILE			l_h_FileCrypt					= NULL;
	WCHAR			l_pwc_NewFileName[MAX_PATH+4]	= {0};
	BOOL			l_b_Result						= FALSE;
	WCHAR			l_pwc_FileNameTmp_1[MAX_PATH]	= {0};
	WCHAR			l_pwc_FileNameTmp_2[MAX_PATH]	= {0};
	LONG			l_l_Result						= 0;
	DWORD			l_dw_FileSizeHigh				= 0;
	CHAR			l_puc_TmpName[MAX_PATH] 		= {0};
	ULONGLONG		l_l_Process 					= 0;
	WCHAR			l_pwc_ProgressText_1[40]		= {0};
	WCHAR			l_pwc_ProgressText_2[40]		= {0};
				
	__try
	{
		m_b_Progress = TRUE;
		
		m_x_MainSheet->SetWizardButtons(0);
		if(::IsWindow(m_Progress_Page_3_1_CWnd.m_hWnd))
			m_Progress_Page_3_1_CWnd.SetPos(0);
		if(::IsWindow(m_Progress_Page_3_1_CWnd.m_hWnd))
			m_Progress_Page_3_1_CWnd.SetRange(0, m_i_NbFileLen*2);
		
		//Add Itms
		for(l_i_Item = 0;l_i_Item<m_i_NbFileLen;l_i_Item++)
		{
			if(m_p_FileData[l_i_Item].m_h_FileHandle == NULL)
			{
				memset(l_pwc_TmpState,0,sizeof(l_pwc_TmpState));
				wsprintf(l_pwc_TmpState,L"%s",_T(VC_ITEMNO));
				m_i_FileSize[l_i_Item] = 0;
			}
			else
			{
				l_dw_Result = GetFileSize((HANDLE)m_p_FileData[l_i_Item].m_h_FileHandle,&l_dw_FileSizeHigh);
				if(l_dw_Result == 0xFFFFFFFF)
				{
					_lclose(m_p_FileData[l_i_Item].m_h_FileHandle);
					m_p_FileData[l_i_Item].m_h_FileHandle = NULL;
					memset(l_pwc_TmpState,0,sizeof(l_pwc_TmpState));
					wsprintf(l_pwc_TmpState,L"%s",_T(VC_ITEMNO));
					m_i_FileSize[l_i_Item] = 0;
				}
				else
				{
					m_i_FileSize[l_i_Item] = l_dw_Result;
					l_l_SizeOfAll += l_dw_Result;
					memset(l_pwc_TmpState,0,sizeof(l_pwc_TmpState));
					wsprintf(l_pwc_TmpState,L"%s",_T(VC_ITEMOK));
				}
			}
			if(::IsWindow(m_Progress_Page_3_1_CWnd.m_hWnd))
				m_Progress_Page_3_1_CWnd.SetStep(1);
			if(::IsWindow(m_Progress_Page_3_1_CWnd.m_hWnd))
				m_Progress_Page_3_1_CWnd.StepIt();
			
			memset(l_pwc_TmpPath,0,sizeof(l_pwc_TmpPath));
			wsprintf(l_pwc_TmpPath,L"%s",m_p_FileData[l_i_Item].m_pwc_FileName);
			
			if(::IsWindow(m_List_Page_3_1_CWnd.m_hWnd))
				m_List_Page_3_1_CWnd.InsertItem(l_i_Item, l_pwc_TmpPath);
			if(::IsWindow(m_List_Page_3_1_CWnd.m_hWnd))
				m_List_Page_3_1_CWnd.SetItemState(1,LVIS_SELECTED,LVIF_STATE | LVIF_PARAM);
			if(::IsWindow(m_List_Page_3_1_CWnd.m_hWnd))
				m_List_Page_3_1_CWnd.SetItemText( l_i_Item,1,l_pwc_TmpState);
			if(::IsWindow(m_Progress_Page_3_1_CWnd.m_hWnd))
				m_Progress_Page_3_1_CWnd.SetStep(1);
			if(::IsWindow(m_Progress_Page_3_1_CWnd.m_hWnd))
				m_Progress_Page_3_1_CWnd.StepIt();
		}
		
		if(::IsWindow(m_Progress_Page_3_1_CWnd.m_hWnd))
			m_Progress_Page_3_1_CWnd.SetPos(0);
		if(::IsWindow(m_Progress_Page_3_1_CWnd.m_hWnd))
			m_Progress_Page_3_1_CWnd.SetRange(0, 100);
		
		memset(l_pwc_NewFileName,0,sizeof(l_pwc_NewFileName));
		
		l_puc_Key =(UCHAR *)malloc(VI_DATAKEY_MAX*sizeof(WCHAR));
		memset(l_puc_Key,0,VI_DATAKEY_MAX*sizeof(WCHAR));
		memcpy(l_puc_Key,m_pwc_UserKeyData,VI_DATAKEY_MAX*sizeof(WCHAR));
		l_x_oRijndael.C_Crypto_MakeKey(l_puc_Key,C_Crypto_AES::Key32Bytes);
		
		for(l_i_Item = 0;l_i_Item<m_i_NbFileLen;l_i_Item++)
		{
			if(!m_b_Progress)
			{
				m_b_Exit = FALSE;
				if(::IsWindow(m_x_MainSheet->m_hWnd))
					m_x_MainSheet->SetWizardButtons(PSWIZB_FINISH);
				return 0;
			}
			
			if(m_p_FileData[l_i_Item].m_h_FileHandle != NULL)
			{			
				l_i_size_in 	= m_i_FileSize[l_i_Item];
				l_i_size_out	= l_x_oRijndael.C_Crypto_Length(l_i_size_in);
				
				l_p_DataIn	= (UCHAR *)malloc(l_i_size_in+1);
				l_p_DataOut = (UCHAR *)malloc(l_i_size_out+1);
				
				memset(l_p_DataIn,0,l_i_size_in+1);
				memset(l_p_DataOut,0,l_i_size_out+1);
				
				l_l_Result = _lread
					(
					m_p_FileData[l_i_Item].m_h_FileHandle,
					l_p_DataIn,
					l_i_size_in 
					);
				
				if(l_l_Result == HFILE_ERROR)
				{
					_lclose(m_p_FileData[l_i_Item].m_h_FileHandle);
					m_p_FileData[l_i_Item].m_h_FileHandle = NULL;
					memset(l_pwc_TmpState,0,sizeof(l_pwc_TmpState));
					wsprintf(l_pwc_TmpState,L"%s",_T(VC_ITEMNO));
				}
				else
				{				
					if(m_b_CryptWay)
					{
						memset(l_pwc_FileNameTmp_1,0,sizeof(l_pwc_FileNameTmp_1));
						memset(l_pwc_FileNameTmp_2,0,sizeof(l_pwc_FileNameTmp_2));
						
						memcpy(l_pwc_FileNameTmp_2,m_p_FileData[l_i_Item].m_pwc_FileName,sizeof(m_p_FileData[l_i_Item].m_pwc_FileName));
						memcpy(l_pwc_FileNameTmp_1,m_p_FileData[l_i_Item].m_pwc_FileName,sizeof(m_p_FileData[l_i_Item].m_pwc_FileName));
						
						PathRemoveExtension(l_pwc_FileNameTmp_2);
						wsprintf(l_pwc_FileNameTmp_1,L"%s.Enc",l_pwc_FileNameTmp_2);
						if(memcmp(l_pwc_FileNameTmp_1,m_p_FileData[l_i_Item].m_pwc_FileName,sizeof(m_p_FileData[l_i_Item].m_pwc_FileName)) == 0)
							memcpy(l_pwc_NewFileName,l_pwc_FileNameTmp_2,sizeof(l_pwc_NewFileName));
						else
						{
							wsprintf(l_pwc_FileNameTmp_1,L"%s.Dec",m_p_FileData[l_i_Item].m_pwc_FileName);
							memcpy(l_pwc_NewFileName,l_pwc_FileNameTmp_1,sizeof(l_pwc_NewFileName));
						}
						l_x_oRijndael.C_Crypto_Decrypt(l_p_DataIn,l_i_size_in,l_p_DataOut);
					}
					else
					{
						memset(l_pwc_FileNameTmp_1,0,sizeof(l_pwc_FileNameTmp_1));
						memset(l_pwc_FileNameTmp_2,0,sizeof(l_pwc_FileNameTmp_2));
						
						memcpy(l_pwc_FileNameTmp_2,m_p_FileData[l_i_Item].m_pwc_FileName,sizeof(m_p_FileData[l_i_Item].m_pwc_FileName));
						memcpy(l_pwc_FileNameTmp_1,m_p_FileData[l_i_Item].m_pwc_FileName,sizeof(m_p_FileData[l_i_Item].m_pwc_FileName));
						
						
						PathRemoveExtension(l_pwc_FileNameTmp_2);
						wsprintf(l_pwc_FileNameTmp_1,L"%s.Dec",l_pwc_FileNameTmp_2);
						if(memcmp(l_pwc_FileNameTmp_1,m_p_FileData[l_i_Item].m_pwc_FileName,sizeof(m_p_FileData[l_i_Item].m_pwc_FileName)) == 0)
							memcpy(l_pwc_NewFileName,l_pwc_FileNameTmp_2,sizeof(l_pwc_NewFileName));
						else
						{
							wsprintf(l_pwc_FileNameTmp_1,L"%s.Enc",m_p_FileData[l_i_Item].m_pwc_FileName);
							memcpy(l_pwc_NewFileName,l_pwc_FileNameTmp_1,sizeof(l_pwc_NewFileName));
						}
						l_x_oRijndael.C_Crypto_Encrypt(l_p_DataIn,l_i_size_in,l_p_DataOut);
					}
					
					memset(l_puc_TmpName,0,sizeof(l_puc_TmpName));
					wcstombs(l_puc_TmpName,l_pwc_NewFileName,sizeof(l_puc_TmpName));
					
					l_h_FileCrypt = _lcreat
						(
						l_puc_TmpName,
						0
						); 
					
					if(l_h_FileCrypt == HFILE_ERROR)
					{
						_lclose(m_p_FileData[l_i_Item].m_h_FileHandle);
						m_p_FileData[l_i_Item].m_h_FileHandle = NULL;
						memset(l_pwc_TmpState,0,sizeof(l_pwc_TmpState));
						wsprintf(l_pwc_TmpState,L"%s",_T(VC_ITEMNO));
					}
					else
					{
						l_l_Result = _lwrite
							(
							l_h_FileCrypt,
							(CHAR *)l_p_DataOut,
							l_i_size_out
							);
						
						_lclose(l_h_FileCrypt);
						_lclose(m_p_FileData[l_i_Item].m_h_FileHandle);
						m_p_FileData[l_i_Item].m_h_FileHandle = NULL;
						
						if(l_l_Result != HFILE_ERROR)
						{
							l_b_Result = DeleteFile(m_p_FileData[l_i_Item].m_pwc_FileName);
							m_p_FileData[l_i_Item].m_h_FileHandle = NULL;
							if(!l_b_Result)
							{
								memset(l_pwc_TmpState,0,sizeof(l_pwc_TmpState));
								wsprintf(l_pwc_TmpState,L"%s",_T(VC_ITEMNO));
							}							else
							{
								memset(l_pwc_TmpState,0,sizeof(l_pwc_TmpState));
								wsprintf(l_pwc_TmpState,L"%s",_T(VC_ITEMKO));
							}
						}
						else
						{
							memset(l_pwc_TmpState,0,sizeof(l_pwc_TmpState));
							wsprintf(l_pwc_TmpState,L"%s",_T(VC_ITEMNO));
						}	
					}
					
					l_l_Process = 0;
					for(int j = 0; j < l_i_Item; j++)
						l_l_Process += m_i_FileSize[j];
					
					if(100*l_l_Process/(l_l_SizeOfAll+1)<0)
					{
						memset(l_pwc_ProgressText_2,0,sizeof(l_pwc_ProgressText_2));
						memset(l_pwc_ProgressText_1,0,sizeof(l_pwc_ProgressText_1));
						wsprintf(l_pwc_ProgressText_2,L"%d",100+100*l_l_Process/(l_l_SizeOfAll+1));
						wsprintf(l_pwc_ProgressText_1,L"%s %s",l_pwc_ProgressText_2,L"%");
						if(::IsWindow(m_Text_Page_3_2_CWnd.m_hWnd))
							m_Text_Page_3_2_CWnd.SetWindowText(l_pwc_ProgressText_1);
						
						if(::IsWindow(m_Progress_Page_3_1_CWnd.m_hWnd))
							m_Progress_Page_3_1_CWnd.SetPos(100+100*l_l_Process/(l_l_SizeOfAll+1));
					}
					else
					{
						memset(l_pwc_ProgressText_2,0,sizeof(l_pwc_ProgressText_2));
						memset(l_pwc_ProgressText_1,0,sizeof(l_pwc_ProgressText_1));
						wsprintf(l_pwc_ProgressText_2,L"%d",100*l_l_Process/(l_l_SizeOfAll+1));
						wsprintf(l_pwc_ProgressText_1,L"%s %s",l_pwc_ProgressText_2,L"%");
						if(::IsWindow(m_Text_Page_3_2_CWnd.m_hWnd))
							m_Text_Page_3_2_CWnd.SetWindowText(l_pwc_ProgressText_1);
						
						if(::IsWindow(m_Progress_Page_3_1_CWnd.m_hWnd))
							m_Progress_Page_3_1_CWnd.SetPos(100*l_l_Process/(l_l_SizeOfAll+1));
					}
				}
				free(l_p_DataOut);
				free(l_p_DataIn);
				if(::IsWindow(m_List_Page_3_1_CWnd.m_hWnd))
					m_List_Page_3_1_CWnd.SetItemText( l_i_Item,1,l_pwc_TmpState);
			}
		}
		if(::IsWindow(m_Progress_Page_3_1_CWnd.m_hWnd)) 		
			m_Progress_Page_3_1_CWnd.SetPos(100);
		if(::IsWindow(m_Text_Page_3_2_CWnd.m_hWnd))
			m_Text_Page_3_2_CWnd.SetWindowText(L"100 %");
		free(l_puc_Key);
		m_b_Exit = FALSE;
		m_x_MainSheet->SetWizardButtons(PSWIZB_FINISH);
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		m_b_Exit = FALSE;
	}
	return TRUE;
}

BOOL CPage_3::OnInitDialog() 
{
	CString Tmp;
	CRect	CTmp;
	CPropertyPageEx::OnInitDialog();
	
	m_i_FileSize = (LONG *)malloc(m_i_NbFileLen*sizeof(LONG));
	
	m_List_Page_3_1_CWnd.GetClientRect( CTmp);
	Tmp.Format(_T(VC_LISTDATAITEM));
	m_List_Page_3_1_CWnd.InsertColumn(0, Tmp,LVCFMT_LEFT,(CTmp.right-CTmp.left)/2-4);
	Tmp.Format(_T(VC_LISTDATASTATE));
	m_List_Page_3_1_CWnd.InsertColumn(1, Tmp,LVCFMT_LEFT,(CTmp.right-CTmp.left)/2-4);
	m_List_Page_3_1_CWnd.SetExtendedStyle(m_List_Page_3_1_CWnd.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	
	return TRUE; 
}

VOID CPage_3::OnFinishPage()
{
	INT l_i_LoopProgress = 0;
	__try
	{
	m_b_Progress = FALSE;
	
	while(m_b_Exit && l_i_LoopProgress<100)
	{
		l_i_LoopProgress++;
		Sleep(100);
	}
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}


VOID CPage_3::OnCancel() 
{	
	INT l_i_LoopProgress = 0;
	__try
	{
	m_b_Progress = FALSE;
	
	while(m_b_Exit && l_i_LoopProgress<100)
	{
		l_i_LoopProgress++;
		Sleep(100);
	}
	
	CPropertyPageEx::OnCancel();
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}
