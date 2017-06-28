/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWAccess_Property.h 										 //
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




#ifndef SWACCESS_PROPERTY_H
#define SWACCESS_PROPERTY_H

class C_AccessWizard : public CPropertySheetEx
{
	DECLARE_DYNCREATE(C_AccessWizard)
		
public:
	C_AccessWizard(C_Wnd *i_Wnd = NULL, TAccessField *i_T_Access = NULL, TKeyField *i_T_Keys = NULL, WCHAR *i_pwc_UserId = NULL);
	virtual ~C_AccessWizard();
	
	INT 			m_i_NbApplication;
	INT 			m_i_PageCode;
	TAccessField	*m_T_Access;
	
protected:
	CPage_1 		m_Page_1;
	CPage_2 		m_Page_2;
	CPage_3 		m_Page_3;
	CPage_4 		m_Page_4;
	CPage_5 		m_Page_5;
	CPage_6 		m_Page_6;
	
	//{{AFX_VIRTUAL(C_AccessWizard)
	//}}AFX_VIRTUAL
	
	//{{AFX_MSG(C_AccessWizard)
	afx_msg VOID OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, VOID* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif//SWACCESS_PROPERTY_H