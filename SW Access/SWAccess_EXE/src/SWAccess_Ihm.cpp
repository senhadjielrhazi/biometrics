/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWAccess_Notify.cpp 										 //
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

/*****************************************ShellNotify*************************************/
C_Notify::C_Notify 
(
 HANDLE i_h_ExitOk,
 HANDLE i_h_ExitKo,
 HANDLE i_h_Start,
 HANDLE i_h_Stop
 )
{
	WNDCLASSEX		wcex			= {0};
	WCHAR			l_pwc_Path[254]	= {0};

	m_c_Tip_Ok.Format(_T(VC_TIPACCESS_OK));
	m_c_Tip_No.Format(_T(VC_TIPACCESS_NO));
	
	m_h_Icon_Ok = AfxGetApp()->LoadIcon(MAKEINTRESOURCE(IDI_ACCESSOK_ICON));
	m_h_Icon_No = AfxGetApp()->LoadIcon(MAKEINTRESOURCE(IDI_ACCESSNO_ICON));
	
	// load up the NOTIFYICONDATA structure
	m_T_WndData.m_T_tnd.cbSize = sizeof(NOTIFYICONDATA) ;
	m_T_WndData.m_T_tnd.hWnd = m_h_hwnd = NULL;
	m_T_WndData.m_T_tnd.uID = 1 ;
	m_T_WndData.m_T_tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;	
	m_T_WndData.m_T_tnd.uCallbackMessage = WM_HWNDNOTIFY_MSG; 
	wcscpy (m_T_WndData.m_T_tnd.szTip, m_c_Tip_Ok);
	m_T_WndData.m_T_tnd.hIcon = m_h_Icon_Ok;
	
	m_T_WndData.m_h_ExitOk	= i_h_ExitOk;
	m_T_WndData.m_h_ExitKo	= i_h_ExitKo;
	m_T_WndData.m_h_Start	= i_h_Start;
	m_T_WndData.m_h_Stop	= i_h_Stop; 
	
	m_T_WndData.m_b_UpdateOn	= 0;
	m_T_WndData.m_b_StartStop	= 1;
	m_T_WndData.m_b_RunOnce 	= 0;
	m_T_WndData.m_i_ExitTimeOut = 10;
	
	/***********************Main Window******************/
	//we create a bite hiden window 0x0000 to have a loop message
	wcex.cbSize 		= sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= NotifyProc;
	wcex.cbClsExtra 	= 0;
	wcex.cbWndExtra 	= 0;
	wcex.hInstance		= AfxGetInstanceHandle();
	wcex.hIcon			= wcex.hIconSm = NULL;
	wcex.hCursor		= NULL;
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= _T(VC_NOTIFYCLASS_NAME);
	
	::RegisterClassEx(&wcex);
	
	m_h_hwnd = CreateWindow(_T(VC_NOTIFYCLASS_NAME),_T(""),WS_OVERLAPPEDWINDOW,0,0,0,0,
		NULL,NULL,AfxGetInstanceHandle(),&m_T_WndData);
	
	m_T_WndData.m_T_tnd.hWnd = m_h_hwnd;
	
	memset(l_pwc_Path,0,sizeof(l_pwc_Path));
	memset(m_T_WndData.m_pwc_Path, 0,sizeof(m_T_WndData.m_pwc_Path));

	GetModuleFileName(NULL,l_pwc_Path,sizeof(l_pwc_Path));
	
	wsprintf(m_T_WndData.m_pwc_Path,L"\"%s\"",l_pwc_Path);
	SetWindowLong(m_h_hwnd,GWL_USERDATA,(LONG)&m_T_WndData);
	
	Shell_NotifyIcon (NIM_ADD,&m_T_WndData.m_T_tnd);
}

C_Notify::~C_Notify
(
 VOID
 )
{
	Shell_NotifyIcon (NIM_DELETE, &m_T_WndData.m_T_tnd);
}

VOID C_Notify::SetState 
(
 BOOL i_b_Err, 
 BOOL i_b_ErrStrOuAct,
 BOOL i_b_Display
 )
{
	if(i_b_Err)
	{
		m_T_WndData.m_T_tnd.hIcon = m_h_Icon_Ok;
		wcscpy ( m_T_WndData.m_T_tnd.szTip, m_c_Tip_Ok);
	}
	else
	{
		m_T_WndData.m_T_tnd.hIcon = m_h_Icon_No;
		wcscpy ( m_T_WndData.m_T_tnd.szTip, m_c_Tip_No);
	}
	
	if(i_b_Display)
	{
		m_T_WndData.m_T_tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_INFO; 
		m_T_WndData.m_T_tnd.uTimeout = 20;
		m_T_WndData.m_T_tnd.uVersion = NOTIFYICON_VERSION;
		wcscpy (m_T_WndData.m_T_tnd.szInfoTitle, _T(VC_NOTIFYINFO_TITLE));
		
		if(i_b_ErrStrOuAct)
		{
			wcscpy (m_T_WndData.m_T_tnd.szInfo, _T(VC_NOTIFYINFO_WARNING));
			m_T_WndData.m_T_tnd.dwInfoFlags = NIIF_WARNING;
		}
		else
		{
			wcscpy (m_T_WndData.m_T_tnd.szInfo, _T(VC_NOTIFYINFO_ERREUR));
			m_T_WndData.m_T_tnd.dwInfoFlags = NIIF_ERROR;
		}
	}
	else
		m_T_WndData.m_T_tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;	
	
	Shell_NotifyIcon(NIM_MODIFY, &m_T_WndData.m_T_tnd);
	
	SetWindowLong(m_h_hwnd,GWL_USERDATA,(LONG)&m_T_WndData);
}

LRESULT CALLBACK NotifyProc
(
 HWND hWnd,
 UINT message,
 WPARAM wParam,
 LPARAM lParam
 )
{
	static UINT s_ui_TaskbarRestart;
	BOOL		l_b_Ret 			= FALSE;
	static INT	s_i_LoopExit		= 0;
	
	TSWNotify *l_T_WndData = (TSWNotify *)GetWindowLong(hWnd,GWL_USERDATA);
	
	switch (message)
	{
	case WM_CREATE :
		{
			s_ui_TaskbarRestart = RegisterWindowMessage(_T("TaskbarCreated"));
			break;
		}
		
	case WM_INITDIALOG:
		{
			l_b_Ret = TRUE;
			break;
		}
	case WM_KEYDOWN :
		{
			l_b_Ret = FALSE;
			break;
		}
	case WM_COMMAND :
		{
			WORD		wID = LOWORD(wParam);
			switch (wID) 
			{
			case IDM_ACCESS_ONRUN :
				{
					if(l_T_WndData->m_b_RunOnce)
						l_T_WndData->m_x_Registry.C_Registry_SetAccessOnRun(l_T_WndData->m_pwc_Path,FALSE); 
					else
						l_T_WndData->m_x_Registry.C_Registry_SetAccessOnRun(l_T_WndData->m_pwc_Path,TRUE);
					break;
				}
			case IDM_ACCESS_START :
				{
					if(l_T_WndData->m_b_StartStop)
					{
						l_T_WndData->m_b_StartStop = FALSE;
						SetEvent(l_T_WndData->m_h_Stop);
						ResetEvent(l_T_WndData->m_h_Start);
					}
					
					else
					{
						l_T_WndData->m_b_StartStop = TRUE;
						SetEvent(l_T_WndData->m_h_Start);
						ResetEvent(l_T_WndData->m_h_Stop);
					}
					SetWindowLong(hWnd,GWL_USERDATA,(LONG)l_T_WndData);
					break;
				}
			case IDM_ACCESS_STOP :
				{
					if(l_T_WndData->m_b_StartStop)
					{
						l_T_WndData->m_b_StartStop = FALSE;
						SetEvent(l_T_WndData->m_h_Stop);
						ResetEvent(l_T_WndData->m_h_Start);
					}
					else
					{
						l_T_WndData->m_b_StartStop = TRUE;
						SetEvent(l_T_WndData->m_h_Start);
						ResetEvent(l_T_WndData->m_h_Stop);
					}
					SetWindowLong(hWnd,GWL_USERDATA,(LONG)l_T_WndData);
					break;
				}
			case IDM_ACCESS_HELP :
				{
					l_b_Ret = TRUE;
					SetCurrentDirectory(l_T_WndData->m_pwc_Path);
					WinHelp(NULL,_T(VC_HELP_NAME),HELP_FINDER,NULL);
					break;
				}
			case IDM_ACCESS_CLOSE:
				{					
					l_b_Ret 	= TRUE; 				
					SetEvent(l_T_WndData->m_h_ExitOk);
					while((WaitForSingleObject(l_T_WndData->m_h_ExitKo,l_T_WndData->m_i_ExitTimeOut) != WAIT_OBJECT_0) && s_i_LoopExit<l_T_WndData->m_i_ExitTimeOut)
					{
						s_i_LoopExit++;
						Sleep(l_T_WndData->m_i_ExitTimeOut);
					}
					DestroyWindow(hWnd);
					PostQuitMessage(0);
					break;
				}
				break;
			}
		}
	case WM_HWNDNOTIFY_MSG :
		{
			CMenu			menu;
			CMenu			pPopup;
			wParam;
			switch (lParam)
			{
			case WM_RBUTTONDOWN:
				{
					l_b_Ret = TRUE;
					/// Load and Verify Menu
					VERIFY(menu.LoadMenu(IDR_ACCESS_MENU));
					pPopup.Attach((menu.GetSubMenu (0))->m_hMenu);
					ASSERT(pPopup != NULL);
					
					// Get the cursor position
					POINT pt ;
					GetCursorPos (&pt) ;
					
					// Fix Microsofts' BUG!!!!
					SetForegroundWindow(hWnd);
					if(l_T_WndData->m_x_Registry.C_Registry_GetAccessOnRun(l_T_WndData->m_pwc_Path))
					{
						l_T_WndData->m_b_RunOnce = TRUE;
						pPopup.CheckMenuItem( IDM_ACCESS_ONRUN, MF_CHECKED);
					}
					else
					{
						l_T_WndData->m_b_RunOnce = FALSE;
						pPopup.CheckMenuItem( IDM_ACCESS_ONRUN, MF_UNCHECKED);
					}
					SetWindowLong(hWnd,GWL_USERDATA,(LONG)l_T_WndData);
					
					if(l_T_WndData->m_b_StartStop)
						pPopup.DeleteMenu(0,MF_BYPOSITION); 
					else
						pPopup.DeleteMenu(1,MF_BYPOSITION); 
					
					::SetMenuDefaultItem(pPopup.m_hMenu, 0, TRUE);
					///////////////////////////////////
					// Display The Menu
					pPopup.TrackPopupMenu(TPM_LEFTALIGN |
						TPM_RIGHTBUTTON,pt.x, pt.y, AfxGetMainWnd());
					break ;
				}
			case WM_LBUTTONDBLCLK :
				{
					LockWorkStation();
					break;
				}
			}
			
			PostMessage (hWnd, WM_USER, 0, 0);
			break;
		}
	case WM_DESTROY :
		{
			l_b_Ret 	= TRUE;
			WlxAccessIdentOff();
			SetEvent(l_T_WndData->m_h_ExitOk);
			while((WaitForSingleObject(l_T_WndData->m_h_ExitKo,l_T_WndData->m_i_ExitTimeOut) != WAIT_OBJECT_0) && s_i_LoopExit<l_T_WndData->m_i_ExitTimeOut)
			{
				WlxAccessIdentOff();
				s_i_LoopExit++;
				Sleep(l_T_WndData->m_i_ExitTimeOut);
			}
			break;
		}
	case WM_QUERYENDSESSION :
		{
			l_b_Ret 	= TRUE;
			WlxAccessIdentOff();
			SetEvent(l_T_WndData->m_h_ExitOk);
			while((WaitForSingleObject(l_T_WndData->m_h_ExitKo,l_T_WndData->m_i_ExitTimeOut/5) != WAIT_OBJECT_0) && s_i_LoopExit<l_T_WndData->m_i_ExitTimeOut)
			{
				WlxAccessIdentOff();
				s_i_LoopExit++;
				Sleep(l_T_WndData->m_i_ExitTimeOut);
			}
			break;
		}
	case WM_ENDSESSION : 
		{
			l_b_Ret 	= TRUE;
			WlxAccessIdentOff();
			SetEvent(l_T_WndData->m_h_ExitOk);
			while((WaitForSingleObject(l_T_WndData->m_h_ExitKo,l_T_WndData->m_i_ExitTimeOut/5) != WAIT_OBJECT_0) && s_i_LoopExit<l_T_WndData->m_i_ExitTimeOut)
			{
				WlxAccessIdentOff();
				s_i_LoopExit++;
				Sleep(l_T_WndData->m_i_ExitTimeOut);
			}
			break;
		}
	}
	if(message == 0x003B)
	{
		l_b_Ret = TRUE;
		WlxAccessIdentOff();
		SetEvent(l_T_WndData->m_h_ExitOk);
		while((WaitForSingleObject(l_T_WndData->m_h_ExitKo,l_T_WndData->m_i_ExitTimeOut/5) != WAIT_OBJECT_0) && s_i_LoopExit<l_T_WndData->m_i_ExitTimeOut)
		{
			WlxAccessIdentOff();
			s_i_LoopExit++;
			Sleep(l_T_WndData->m_i_ExitTimeOut);
		}
		DestroyWindow(hWnd);
		PostQuitMessage(0);
	}
	if(message == s_ui_TaskbarRestart)
		Shell_NotifyIcon (NIM_ADD,&l_T_WndData->m_T_tnd);
	
	if(!l_b_Ret)
		return DefWindowProc(hWnd, message, wParam, lParam);
	else
		return l_b_Ret;
}

/*************************************C_Info******************************************/
C_Info::C_Info(CWnd* pParent /*=NULL*/)
: CDialog(C_Info::IDD, pParent)
{
	m_TimerID = 1;
	m_TimerED = 1000;
	
	//{{AFX_DATA_INIT(C_Info)
	//}}AFX_DATA_INIT
}

VOID C_Info::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C_Info)
	DDX_Control(pDX, IDC_TEXT_INFO, m_Info_CWnd_1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(C_Info, CDialog)
//{{AFX_MSG_MAP(C_Info)
ON_WM_SHOWWINDOW()
ON_WM_TIMER()
ON_WM_PAINT()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

VOID C_Info::OnShowWindow
(
 BOOL bShow, 
 UINT nStatus
 ) 
{
	SetTimer(m_TimerID,m_TimerED,NULL);
	CDialog::OnShowWindow(bShow, nStatus);	
}

VOID C_Info::OnTimer
(
 UINT nIDEvent
 ) 
{
	if(nIDEvent == m_TimerID)
	{
		KillTimer(m_TimerID);
		EndDialog( 0 );
	}
	CDialog::OnTimer(nIDEvent);
}

BOOL C_Info::OnInitDialog
(
 VOID
 ) 
{
	CDialog::OnInitDialog();
	
	return TRUE;
}

VOID C_Info::OnPaint
(
 VOID
 ) 
{
	CPaintDC	dc(this);
	CRect		l_cr_Rect_1;
	CRect		l_cr_Rect_2;
	CFont		l_p_Font;
	TEXTMETRIC	l_p_Metrics;
	CString 	l_c_DisplayText;
	
	GetClientRect(&l_cr_Rect_1);
	CBrush l_cb_Brush(RGB(255,255,255) );
	dc.FillRect(&l_cr_Rect_1,&l_cb_Brush);	
	dc.SetTextColor(RGB(0,0,255));
	dc.GetTextMetrics(&l_p_Metrics );
	m_Info_CWnd_1.GetClientRect(&l_cr_Rect_2);
	if(m_b_HitNoHit)
		l_c_DisplayText.Format(L"%s %s !",_T(VC_YESUSER_DISPLAY_NAME),m_c_Info_UserName);
	else
		l_c_DisplayText.Format(L"%s !",_T(VC_NOUSER_DISPLAY_NAME));
	
	dc.SetTextAlign(TA_CENTER);

	if(l_c_DisplayText.GetLength()>23)
	{
		l_p_Font.CreateFont(18, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 
			PROOF_QUALITY,VARIABLE_PITCH | FF_SWISS, L""); 
		dc.SelectObject(&l_p_Font);
		dc.TextOut((l_cr_Rect_1.right-l_cr_Rect_1.left)-(l_cr_Rect_2.right-l_cr_Rect_2.left)/2
			,(l_cr_Rect_1.bottom-l_cr_Rect_1.top)-(l_cr_Rect_2.bottom-l_cr_Rect_2.top)/2-l_p_Metrics.tmHeight,l_c_DisplayText);
	}
	else
	{
		l_p_Font.CreateFont(24, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 
			PROOF_QUALITY,VARIABLE_PITCH | FF_SWISS, L""); 
		dc.SelectObject(&l_p_Font);
		dc.TextOut((l_cr_Rect_1.right-l_cr_Rect_1.left)-(l_cr_Rect_2.right-l_cr_Rect_2.left)/2
			,(l_cr_Rect_1.bottom-l_cr_Rect_1.top)-(l_cr_Rect_2.bottom-l_cr_Rect_2.top)/2-l_p_Metrics.tmHeight*3/2,l_c_DisplayText);
	}
		
}

/**************************************C_Profil********************************/
C_Profil::C_Profil(CWnd* pParent /*=NULL*/)
: CDialog(C_Profil::IDD, pParent)
{
	m_h_Icon = AfxGetApp()->LoadIcon(IDI_ACCESSOK_ICON);
	//{{AFX_DATA_INIT(C_Profil)
	//}}AFX_DATA_INIT
}

VOID C_Profil::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C_Profil)
	DDX_Control(pDX, IDOK, m_Button_Profil_Ok);
	DDX_Control(pDX, IDCANCEL, m_Button_Profil_No);
	DDX_Control(pDX, IDC_LIST_PROFIL_1, m_List_Profil);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(C_Profil, CDialog)
//{{AFX_MSG_MAP(C_Profil)
ON_WM_SHOWWINDOW()
ON_NOTIFY(NM_CLICK, IDC_LIST_PROFIL_1, OnClickListProfil)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

VOID C_Profil::OnShowWindow
(
 BOOL bShow, 
 UINT nStatus
 ) 
{
	WCHAR	l_pwc_TmpNameApp[VI_APPNAME_MAX+1];
	INT 	l_i_Index = 0;
	
	CDialog::OnShowWindow(bShow, nStatus);
	
	if(bShow)
	{
		for(INT i = 0;i<VI_NBAPPLI_MAX;i++)
		{
			if(m_pi_AppEqual[i] == 1)
			{
				memset(l_pwc_TmpNameApp,0,sizeof(l_pwc_TmpNameApp));
				memcpy(l_pwc_TmpNameApp,m_T_Access[i].m_pwc_AppName,sizeof(m_T_Access[i].m_pwc_AppName));
				m_List_Profil.InsertItem(l_i_Index, l_pwc_TmpNameApp);
				l_i_Index++;
			}
		}
		m_List_Profil.SetItemState(1,LVIS_SELECTED,LVIF_STATE | LVIF_PARAM); 
		m_i_Index = 0;
	}
}

VOID C_Profil::OnClickListProfil
(
 NMHDR* pNMHDR, 
 LRESULT* pResult
 ) 
{
	POSITION		l_pos;
	INT 			l_i_Index,l_i_Counter = 0;
	l_pos = m_List_Profil.GetFirstSelectedItemPosition();
	l_i_Index = m_List_Profil.GetNextSelectedItem(l_pos); 
	
	if(!((INT)l_i_Index < VI_NBAPPLI_MAX && l_i_Index >0))
	{
		m_i_Index = 0 ; 
		return;
	}
	
	for(INT i = 0;i<VI_NBAPPLI_MAX;i++)
	{
		if(m_pi_AppEqual[i] == 1)
		{
			if(l_i_Counter == l_i_Index)
			{
				m_i_Index = i;
				break;
			}
			l_i_Counter++;
		}	
	}
	
	*pResult = 0;
	pNMHDR;
}

BOOL C_Profil::OnInitDialog
(
 VOID
 ) 
{
	CString l_c_StrTmp;
	CRect	l_cr_RectTmp;	
	
	CDialog::OnInitDialog();
	SetIcon(m_h_Icon, TRUE);
	SetIcon(m_h_Icon, FALSE);
	m_List_Profil.GetClientRect(l_cr_RectTmp);
	l_c_StrTmp.Format(_T(VC_ACCESSLIST_NAME));
	m_List_Profil.InsertColumn(0,l_c_StrTmp,LVCFMT_LEFT,(l_cr_RectTmp.right-l_cr_RectTmp.left)-4);
	m_List_Profil.SetExtendedStyle(m_List_Profil.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	SetForegroundWindow();
	SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE );
	return TRUE;  
}
/***********************************************************************************/

