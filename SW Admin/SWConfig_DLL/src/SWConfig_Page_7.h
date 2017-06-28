/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWConfig_Page_7.h											 //
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




#ifndef SWCONFIG_PAGE_7_H
#define SWCONFIG_PAGE_7_H

class CPage_7 : public CPropertyPageEx
{
	DECLARE_DYNCREATE(CPage_7)
		
public:
	CPage_7();
	~CPage_7();
	
	VOID OnNextPage();
	VOID OnBackPage();
	
	TLogonField 		*m_T_Logon;
	TKeyField			*m_T_Keys;
	WCHAR				*m_pwc_UserId;
	TModuleRet			m_T_Result;
	CPropertySheetEx	*m_x_MainSheet;
	INT 				m_i_Result;//0 ok,1 no,2 abort,3 err.
	INT 				*m_i_PageCode;
	INT 				m_i_Process;
	TSWState			*m_T_SWContex;
	
	//{{AFX_DATA(CPage_7)
	enum { IDD = IDD_PAGE_7 };
	CComboBox	m_Combo_Page_7_1_CWnd;
	CEdit	m_Edit_Page_7_2_CWnd;
	CEdit	m_Edit_Page_7_1_CWnd;
	CString m_Combo_Page_7_1;
	CString m_Edit_Page_7_1;
	CString m_Edit_Page_7_2;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CPage_7)
protected:
	virtual VOID DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL
	
protected:
	//{{AFX_MSG(CPage_7)
	afx_msg VOID OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	afx_msg VOID OnButtonPage_7_1();
	afx_msg VOID OnButtonPage_7_2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif //SWCONFIG_PAGE_7_H
