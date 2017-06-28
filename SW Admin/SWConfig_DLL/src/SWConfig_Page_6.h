/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWConfig_Page_6.h											 //
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
//	SAGEM SA Adminstration Module											 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#ifndef SWCONFIG_PAGE_6_H
#define SWCONFIG_PAGE_6_H

UINT TaskPage_6
( 
 LPVOID pParam 
 );

class CPage_6 : public CPropertyPageEx
{
	DECLARE_DYNCREATE(CPage_6)
		
public:
	CPage_6();
	~CPage_6();
	
	VOID OnNextPage();
	VOID OnBackPage();
	VOID OnFinishPage();
	UINT TestPage_6();
	
	TModuleRet			m_T_Result;
	TLogonField 		*m_T_Logon;
	TKeyField			*m_T_Keys;
	WCHAR				*m_pwc_UserId;
	UINT				m_ui_TimerId,m_ui_TimerEd_1,m_ui_TimerEd_2;
	CPropertySheetEx	*m_x_MainSheet;
	BOOL				m_b_Progress;
	INT 				m_i_Result;//0 ok,1 no,2 abort,3 err.
	INT 				*m_i_PageCode;
	INT 				m_i_Progress;
	CFont				m_p_Font_1;
	CFont				*m_p_Font_2;
	BOOL				m_b_UserOff;
	
	//{{AFX_DATA(CPage_6)
	enum { IDD = IDD_PAGE_6 };
	CStatic m_Text_Page_6_3_CWnd;
	CStatic m_Text_Page_6_2_CWnd;
	CStatic m_Text_Page_6_1_CWnd;
	CAnimateCtrl	m_Anim_Page_6_1_CWnd;
	CString m_Text_Page_6_1;
	CString m_Text_Page_6_2;
	CString m_Text_Page_6_3;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CPage_6)
public:
	virtual VOID OnCancel();
protected:
	virtual VOID DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL
	
protected:
	//{{AFX_MSG(CPage_6)
	afx_msg void OnEndSession( BOOL bEnding );
	afx_msg VOID OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg VOID OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif //SWCONFIG_PAGE_6_H
