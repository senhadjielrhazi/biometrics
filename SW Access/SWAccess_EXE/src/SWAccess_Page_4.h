/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWAccess_Page_4.h											 //
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




#ifndef SWACCESS_PAGE_4_H
#define SWACCESS_PAGE_4_H

class CPage_4 : public CPropertyPageEx
{	
	DECLARE_DYNCREATE(CPage_4)
		
public:
	CPage_4();
	~CPage_4();
	
	VOID OnNextPage();
	VOID OnBackPage();
	
	C_Wnd				*m_Wnd;
	TAccessField		*m_T_Access;
	TKeyField			*m_T_Keys;
	WCHAR				*m_pwc_UserId;
	INT 				*m_i_NbApplication;
	INT 				*m_i_PageCode;
	
	CFont				m_p_Font;
	CPropertySheetEx	*m_x_MainSheet;
	
	//{{AFX_DATA(CPage_4)
	enum { IDD = IDD_PAGE_4 };
	CEdit	m_Edit_Page_4_1_CWnd;
	CStatic m_Text_Page_4_4_CWnd;
	CString m_Edit_Page_4_1;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CPage_4)
	virtual VOID DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL
	
protected:
	//{{AFX_MSG(CPage_4)
	afx_msg VOID OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	afx_msg VOID OnChangeEditPage_4_1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif//SWACCESS_PAGE_4_H
