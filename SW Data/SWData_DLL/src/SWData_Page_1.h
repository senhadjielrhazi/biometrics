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




#ifndef SWDATA_PAGE_1_H
#define SWDATA_PAGE_1_H

class CPage_1 : public CPropertyPageEx
{
	DECLARE_DYNCREATE(CPage_1)
		
public:
	CPage_1();
	~CPage_1();
	
	VOID OnNextPage();
	VOID OnBackPage();
	
	CFont				m_p_Font;
	CPropertySheetEx	*m_x_MainSheet;
	
	//{{AFX_DATA(CPage_1)
	enum { IDD = IDD_PAGE_1 };
	CStatic m_Text_Page_1_1_CWnd;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CPage_1)
protected:
	virtual VOID DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL
	
protected:
	//{{AFX_MSG(CPage_1)
	afx_msg VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif//SWDATA_PAGE_1_H
