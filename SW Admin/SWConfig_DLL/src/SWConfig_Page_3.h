/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003. 									 //
//																			 //
//	File:		SWConfig_Page_3.h 											 //
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




#ifndef SWCONFIG_PAGE_3_H
#define SWCONFIG_PAGE_3_H

class CPage_3 : public CPropertyPageEx
{
	DECLARE_DYNCREATE(CPage_3)
		
public:
	CPage_3();
	~CPage_3();
	
	VOID OnNextPage();
	VOID OnBackPage();
	
	TSWState			*m_T_SWContex;
	BOOL				m_b_Switch;
	INT					*m_i_PageCode;
	CPropertySheetEx	*m_x_MainSheet;
	
	//{{AFX_DATA(CPage_3)
	enum { IDD = IDD_PAGE_3 };
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CPage_3)
protected:
	virtual VOID DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL
	
protected:
	//{{AFX_MSG(CPage_3)
	afx_msg VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif //SWCONFIG_PAGE_3_H
