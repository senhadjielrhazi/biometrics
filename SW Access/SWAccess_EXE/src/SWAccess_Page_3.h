/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWAccess_Page_3.h											 //
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




#ifndef SWACCESS_PAGE_3_H
#define SWACCESS_PAGE_3_H

class CPage_3 : public CPropertyPageEx
{
	DECLARE_DYNCREATE(CPage_3)
		
public:
	CPage_3();
	~CPage_3();
	
	VOID OnNextPage();
	VOID OnBackPage();
	
	C_Wnd				*m_Wnd;
	CFont				m_p_Font;
	CPropertySheetEx	*m_x_MainSheet;
	
	//{{AFX_DATA(CPage_3)
	enum { IDD = IDD_PAGE_3 };
	CButton m_Check_Page_3_1_CWnd;
	BOOL	m_Check_Page_3_1;
	CButton m_Check_Page_3_2_CWnd;
	BOOL	m_Check_Page_3_2;
	CEdit	m_Edit_Page_3_1_CWnd;
	CString m_Edit_Page_3_1;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CPage_3)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual VOID DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL
	
protected:
	//{{AFX_MSG(CPage_3)
	virtual BOOL OnInitDialog();
	afx_msg VOID OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg VOID OnCheckPage_3_1();
	afx_msg VOID OnCheckPage_3_2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif//SWACCESS_PAGE_3_H
