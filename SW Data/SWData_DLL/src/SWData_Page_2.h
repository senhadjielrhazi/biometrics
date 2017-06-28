/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWData_Page_2.h 											 //
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




#ifndef SWDATA_PAGE_2_H
#define SWDATA_PAGE_2_H

UINT TaskPage_2
( 
 LPVOID pParam 
 );

class CPage_2 : public CPropertyPageEx
{
	DECLARE_DYNCREATE(CPage_2)
		
public:
	CPage_2();
	~CPage_2();
	
	UINT ThreadPage_2();
	VOID OnNextPage();
	VOID OnBackPage();
	VOID OnFinishPage();
	
	TModuleRet			m_T_Result;
	UINT				m_ui_TimerId,m_ui_TimerEd_1,m_ui_TimerEd_2;
	CPropertySheetEx	*m_x_MainSheet;
	BOOL				m_b_Progress;
	INT 				*m_i_PageCode;
	INT 				m_i_Progress;
	BOOL				m_b_UserOff;
	WCHAR				*m_pwc_UserKeyData;
	WCHAR				*m_pwc_UserLogin;
	CFont				*m_p_Font_2;
	CFont				m_p_Font_1; 
	INT 				m_i_TimeOut;
	
	//{{AFX_DATA(CPage_2)
	enum { IDD = IDD_PAGE_2 };
	CAnimateCtrl	m_Anim_Page_2_1_CWnd;
	CStatic m_Text_Page_2_3_CWnd;
	CStatic m_Text_Page_2_2_CWnd;
	CStatic m_Text_Page_2_1_CWnd;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CPage_2)
public:
	virtual VOID OnCancel();
protected:
	virtual VOID DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL
	
protected:
	//{{AFX_MSG(CPage_2)
	afx_msg void OnEndSession( BOOL bEnding );
	afx_msg VOID OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg VOID OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif //SWDATA_PAGE_2_H
