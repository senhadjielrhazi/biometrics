/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWData_Page_3.h 											 //
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




#ifndef SWDATA_PAGE_3_H
#define SWDATA_PAGE_3_H

UINT TaskPage_3
( 
 LPVOID pParam
 );

class CPage_3 : public CPropertyPageEx
{
	DECLARE_DYNCREATE(CPage_3)
		
public:
	CPage_3();
	~CPage_3();
	
	VOID OnFinishPage();
	
	UINT ThreadPage_3();
	
	WCHAR				*m_pwc_UserKeyData;
	WCHAR				*m_pwc_UserLogin;
	TSWFileDate 		*m_p_FileData;
	CPropertySheetEx	*m_x_MainSheet;
	
	CFont				m_p_Font;
	INT 				m_i_NbFileLen;
	BOOL				m_b_CryptWay;
	BOOL				m_b_Progress;
	BOOL				m_b_Exit;
	LONG				*m_i_FileSize;	
	
	//{{AFX_DATA(CPage_3)
	enum { IDD = IDD_PAGE_3 };
	CListCtrl	m_List_Page_3_1_CWnd;
	CProgressCtrl	m_Progress_Page_3_1_CWnd;
	CStatic m_Text_Page_3_2_CWnd;
	CStatic m_Text_Page_3_1_CWnd;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CPage_3)
protected:
	virtual VOID OnCancel();
	virtual VOID DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL
	
protected:
	//{{AFX_MSG(CPage_3)
	afx_msg VOID OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif //SWDATA_PAGE_3_H
