/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003. 									 //
//																			 //
//	File:		SWConfig_Page_8.h 											 //
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




#ifndef SWCONFIG_PAGE_8_H
#define SWCONFIG_PAGE_8_H

class CPage_8 : public CPropertyPageEx
{
	DECLARE_DYNCREATE(CPage_8)
		
public:
	CPage_8();
	~CPage_8();
	
	VOID OnNextPage();
	VOID OnBackPage();
	
	INT					*m_i_PageCode;
	CPropertySheetEx	*m_x_MainSheet;
	CFont				m_p_Font_1;
	CFont				m_p_Font_2;
	//{{AFX_DATA(CPage_8)
	enum { IDD = IDD_PAGE_8 };
	CStatic	m_Text_Page_8_1_CWnd;
	CEdit	m_Edit_Page_8_1_CWnd;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CPage_8)
protected:
	virtual VOID DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL
	
protected:
	//{{AFX_MSG(CPage_8)
	afx_msg VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif //SWCONFIG_PAGE_8_H