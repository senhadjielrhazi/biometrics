/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003. 									 //
//																			 //
//	File:		SWConfig_Page_5.h 											 //
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




#ifndef SWCONFIG_PAGE_5_H
#define SWCONFIG_PAGE_5_H

UINT TaskPage_5
( 
 LPVOID pParam 
 );

class CPage_5 : public CPropertyPageEx
{
	DECLARE_DYNCREATE(CPage_5)
		
public:
	CPage_5();
	~CPage_5();
	
	VOID OnNextPage();
	VOID OnBackPage();
	VOID OnFinishPage();
	UINT TestPage_5();
	
	TSWState			*m_T_SWContex;
	TSupDataOut			*m_T_DataIn;
	WCHAR				*m_pwc_UserLogin;
	BOOL				m_b_Progress;
	CFont				m_p_Font;
	INT					m_i_Result;//0 ok,1 no,2 abort,3 err.
	CPropertySheetEx	*m_x_MainSheet;
	INT					*m_i_PageCode;
	TModuleRet			m_T_Result;
	BOOL				m_b_UserOff;
	
	//{{AFX_DATA(CPage_5)
	enum { IDD = IDD_PAGE_5 };
	CStatic	m_Text_Page_5_3_CWnd;
	CStatic	m_Text_Page_5_2_CWnd;
	CStatic	m_Text_Page_5_1_CWnd;
	CStatic	m_Image_Page_5_4_CWnd;
	CStatic	m_Image_Page_5_3_CWnd;
	CStatic	m_Image_Page_5_2_CWnd;
	CStatic	m_Image_Page_5_1_CWnd;
	CString	m_Text_Page_5_1;
	CString	m_Text_Page_5_2;
	CString	m_Text_Page_5_3;
	CString	m_Image_Page_5_1;
	CString	m_Image_Page_5_2;
	CString	m_Image_Page_5_3;
	CString	m_Image_Page_5_4;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CPage_5)
public:
	virtual VOID OnCancel();
protected:
	virtual VOID DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL
	
protected:
	//{{AFX_MSG(CPage_5)
	afx_msg void OnEndSession( BOOL bEnding );
	afx_msg VOID OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	afx_msg VOID OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif //SWCONFIG_PAGE_5_H
