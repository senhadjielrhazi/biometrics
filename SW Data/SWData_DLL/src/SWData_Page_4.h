/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWData_Page_1.h 											 //
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




#ifndef SWDATA_PAGE_4_H
#define SWDATA_PAGE_4_H

class CPage_4 : public CPropertyPageEx
{
	DECLARE_DYNCREATE(CPage_4)
		
public:
	CPage_4();
	~CPage_4();
	
	VOID OnNextPage();
	VOID OnBackPage();
	
	INT 				*m_i_PageCode;
	CPropertySheetEx	*m_x_MainSheet;
	CFont				m_p_Font_1;
	CFont				m_p_Font_2;
	
	//{{AFX_DATA(CPage_4)
	enum { IDD = IDD_PAGE_4 };
	CEdit	m_Edit_Page_4_1_CWnd;
	CStatic m_Text_Page_4_1_CWnd;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CPage_4)
protected:
	virtual VOID DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL
	
protected:
	//{{AFX_MSG(CPage_4)
	afx_msg VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
};

#endif//SWDATA_PAGE_4_H
