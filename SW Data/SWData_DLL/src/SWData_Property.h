/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWData_Property.h											 //
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




#ifndef SWDATA_PROPERTY_H
#define SWDATA_PROPERTY_H

class C_DataWizard : public CPropertySheetEx
{
	DECLARE_DYNCREATE(C_DataWizard)
		
public:
	C_DataWizard(TSWFile *i_p_File = NULL, INT i_i_NBFile = 0, BOOL i_b_CryptWay = FALSE);
	virtual ~C_DataWizard();
	
	TSWFileDate 			*m_p_FileData;
	INT 					m_i_NbFileLen;
	WCHAR					*m_pwc_UserKeyData;
	WCHAR					*m_pwc_UserLogin;
	INT 					m_i_PageCode;
	
protected:
	CPage_1 		m_Page_1;
	CPage_2 		m_Page_2;
	CPage_3 		m_Page_3;
	CPage_4 		m_Page_4;
	
	//{{AFX_VIRTUAL(C_DataWizard)
	//}}AFX_VIRTUAL
	
	//{{AFX_MSG(C_DataWizard)
	afx_msg VOID OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	virtual BOOL OnCmdMsg(UINT nID, INT nCode, VOID* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif //SWDATA_PROPERTY_H
