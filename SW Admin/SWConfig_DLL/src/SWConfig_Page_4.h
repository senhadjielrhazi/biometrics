/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003. 									 //
//																			 //
//	File:		SWConfig_Page_4.h 											 //
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




#ifndef SWCONFIG_PAGE_4_H
#define SWCONFIG_PAGE_4_H

class CPage_4 : public CPropertyPageEx
{
	DECLARE_DYNCREATE(CPage_4)
		
public:
	CPage_4();
	~CPage_4();
	
	VOID OnNextPage();
	VOID OnBackPage();
	
	TSupDataOut			*m_T_DataIn;
	WCHAR				*m_pwc_UserLogin;
	INT					*m_i_PageCode;
	CPropertySheetEx	*m_x_MainSheet;
	
	//{{AFX_DATA(CPage_4)
	enum { IDD = IDD_PAGE_4 };
	CComboBox	m_Combo_Page_4_1_CWnd;
	CEdit	m_Edit_Page_4_2_CWnd;
	CEdit	m_Edit_Page_4_1_CWnd;
	CString	m_Combo_Page_4_1;
	CString	m_Edit_Page_4_1;
	CString	m_Edit_Page_4_2;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CPage_4)
protected:
	virtual VOID DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL
	
protected:
	//{{AFX_MSG(CPage_4)
	virtual BOOL OnInitDialog();
	afx_msg VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif //SWCONFIG_PAGE_4_H
