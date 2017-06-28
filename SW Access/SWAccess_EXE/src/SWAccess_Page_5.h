/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWAccess_Page_5.h											 //
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




#ifndef SWACCESS_PAGE_5_H
#define SWACCESS_PAGE_5_H

class CPage_5 : public CPropertyPageEx
{	
	DECLARE_DYNCREATE(CPage_5)
		
public:
	CPage_5();
	~CPage_5();
	
	VOID OnNextPage();
	VOID OnBackPage();
	
	TAccessField		*m_T_Access;
	TKeyField			*m_T_Keys;
	WCHAR				*m_pwc_UserId;
	INT 				*m_i_NbApplication;
	INT 				m_pi_AppIndex[VI_NBAPPLI_MAX];
	INT 				*m_i_PageCode;
	
	CFont				m_p_Font_1;
	CFont				m_p_Font_2;
	CPropertySheetEx	*m_x_MainSheet;
	
	
	//{{AFX_DATA(CPage_5)
	enum { IDD = IDD_PAGE_5 };
	CButton m_Button_Page_5_1_CWnd;
	CEdit	m_Edit_Page_5_2_CWnd;
	CEdit	m_Edit_Page_5_1_CWnd;
	CComboBox	m_Combo_Page_5_1_CWnd;
	CString m_Edit_Page_5_1;
	CString m_Edit_Page_5_2;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CPage_5)
	virtual VOID DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL
	
protected:
	//{{AFX_MSG(CPage_5)
	afx_msg VOID OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	afx_msg VOID OnChangeEditPage_5_1();
	afx_msg VOID OnButtonPage_5_1();
	afx_msg VOID OnButtonPage_5_2();
	afx_msg VOID OnCloseupComboPage_5_1();
	afx_msg VOID OnSelchangeComboPage_5_1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif//SWACCESS_PAGE_5_H
