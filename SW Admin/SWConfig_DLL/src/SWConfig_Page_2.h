/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003. 									 //
//																			 //
//	File:		SWConfig_Page_2.h											 //
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




#ifndef SWCONFIG_PAGE_2_H
#define SWCONFIG_PAGE_2_H

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
	
	VOID OnNextPage();
	VOID OnBackPage();
	UINT TestPage_2();
	
	TSWState			*m_T_SWContex;
	UINT				m_ui_TimerId,m_ui_TimerEd_1,m_ui_TimerEd_2;
	INT					m_i_Progress;
	BOOL				m_b_Switch;
	CFont				m_p_Font_1;
	CFont				*m_p_Font_2;
	CPropertySheetEx	*m_x_MainSheet;
	INT					*m_i_PageCode;
	
	//{{AFX_DATA(CPage_2)
	enum { IDD = IDD_PAGE_2 };
	CStatic	m_Text_Page_2_3_CWnd;
	CStatic	m_Text_Page_2_2_CWnd;
	CStatic	m_Text_Page_2_1_CWnd;
	CAnimateCtrl	m_Anim_Page_2_1_CWnd;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CPage_2)
protected:
	virtual VOID DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL
	
protected:
	//{{AFX_MSG(CPage_2)
	afx_msg VOID OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg VOID OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif //SWCONFIG_PAGE_2_H
