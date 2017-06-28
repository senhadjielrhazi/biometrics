/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003. 									 //
//																			 //
//	File:		SWConfig_Property.h 										 //
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




#ifndef SWCONFIG_PROPERTY_H
#define SWCONFIG_PROPERTY_H

class C_ConfigWizard : public CPropertySheetEx
{
	DECLARE_DYNCREATE(C_ConfigWizard)
		
public:
	C_ConfigWizard(CWnd *pParentWnd = NULL);
	~C_ConfigWizard();
	
	TSupDataOut m_T_DataIn;
	WCHAR		m_pwc_UserLogin[VI_USERLOGON_MAX];
	TSWState	m_T_SWContex;
	INT			m_i_PageCode;	
	TLogonField	m_T_Logon;
	TKeyField	m_T_Keys;
	WCHAR		m_pwc_UserId[VI_USERID_MAX];
	
protected:
	CPage_1 		m_Page_1;
	CPage_2 		m_Page_2;
	CPage_3 		m_Page_3;
	CPage_4 		m_Page_4;
	CPage_5 		m_Page_5;
	CPage_6 		m_Page_6;
	CPage_7 		m_Page_7;
	CPage_8 		m_Page_8;
	
	//{{AFX_VIRTUAL(C_ConfigWizard)
	//}}AFX_VIRTUAL
	
	//{{AFX_MSG(C_ConfigWizard)
	afx_msg VOID OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, VOID* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif //SWCONFIG_PROPERTY_H