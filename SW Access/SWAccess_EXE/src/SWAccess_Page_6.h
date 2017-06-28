/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWAccess_Page_6.h											 //
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




#ifndef SWACCESS_PAGE_6_H
#define SWACCESS_PAGE_6_H

class CPage_6 : public CPropertyPageEx
{
	DECLARE_DYNCREATE(CPage_6)
		
public:
	CPage_6();
	~CPage_6();
	
	VOID OnNextPage();
	VOID OnBackPage();
	
	INT 				*m_i_PageCode;
	CPropertySheetEx	*m_x_MainSheet;
	CFont				m_p_Font_1;
	CFont				m_p_Font_2;
	//{{AFX_DATA(CPage_6)
	enum { IDD = IDD_PAGE_6 };
	CStatic m_Text_Page_6_1_CWnd;
	CEdit	m_Edit_Page_6_1_CWnd;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CPage_6)
protected:
	virtual VOID DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL
	
protected:
	//{{AFX_MSG(CPage_6)
	afx_msg VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif//SWACCESS_PAGE_6_H