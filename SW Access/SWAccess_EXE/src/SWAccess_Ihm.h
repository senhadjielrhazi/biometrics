/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWAccess_Notify 											 //
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




#ifndef SWACCESSNOTIFY_H
#define SWACCESSNOTIFY_H

LRESULT CALLBACK NotifyProc
(
 HWND hWnd,
 UINT message,
 WPARAM wParam,
 LPARAM lParam
 );

class C_Notify : public CObject
{
public:
	C_Notify(HANDLE i_h_ExitOk = NULL,HANDLE i_h_ExitKo = NULL,HANDLE i_h_Start = NULL,HANDLE i_h_Stop = NULL);
	~C_Notify();
	
	VOID SetState (BOOL i_b_ErrAct, BOOL i_b_ErrStr, BOOL i_b_Display);
	
	HWND			m_h_hwnd;	
	CString 		m_c_Tip_Ok;
	CString 		m_c_Tip_No;
	HICON			m_h_Icon_Ok;
	HICON			m_h_Icon_No;
	POINT			m_P_IconPoint;
	TSWNotify		m_T_WndData;
	
	//{{AFX_VIRTUAL(C_Notify)
	//}}AFX_VIRTUAL 
};


class C_Info : public CDialog
{
public:
	C_Info(CWnd* pParent = NULL);
	
	CString 		m_c_Info_UserName;
	UINT			m_TimerID,m_TimerED;
	BOOL			m_b_HitNoHit;
	
	//{{AFX_DATA(C_Info)
	enum { IDD = IDD_ACCESS_INFO };
	CStatic m_Info_CWnd_1;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(C_Info)
protected:
	virtual VOID DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL
	
protected:
	//{{AFX_MSG(C_Info)
	afx_msg VOID OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg VOID OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg VOID OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class C_Profil : public CDialog
{
public:
	C_Profil(CWnd* pParent = NULL);
	
	INT 			*m_pi_AppEqual;//[VI_NBAPPLI_MAX]
	INT 			m_i_NbAppEqual;
	TAccessField	*m_T_Access;//[VI_NBAPPLI_MAX]
	INT 			m_i_Index;
	
	HICON			m_h_Icon;
	
	//{{AFX_DATA(C_Profil)
	enum { IDD = IDD_ACCESS_PROFIL };
	CButton 	m_Button_Profil_Ok;
	CButton 	m_Button_Profil_No;
	CListCtrl	m_List_Profil;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(C_Profil)
protected:
	virtual VOID DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL
	
protected:
	//{{AFX_MSG(C_Profil)
	afx_msg VOID OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg VOID OnClickListProfil(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif//SWACCESSNOTIFY_H
