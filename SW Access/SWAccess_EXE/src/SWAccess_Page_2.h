/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWAccess_Page_2.h											 //
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




#ifndef SWACCESS_PAGE_2_H
#define SWACCESS_PAGE_2_H

class CPage_2 : public CPropertyPageEx
{	
	DECLARE_DYNCREATE(CPage_2)
		
public:
	CPage_2();
	~CPage_2();
	
	VOID OnNextPage();
	VOID OnBackPage();
	
	
	INT 				*m_i_NbApplication;
	CPropertySheetEx	*m_x_MainSheet;
	
	//{{AFX_DATA(CPage_2)
	enum { IDD = IDD_PAGE_2 };
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CPage_2)
	virtual VOID DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL
	
protected:
	//{{AFX_MSG(CPage_2)
	afx_msg VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif//SWACCESS_PAGE_2_H
