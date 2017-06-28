/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWAdmin.h													 //
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
//	SAGEM SA Admin Module Tester											 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#ifndef SWADMIN_H
#define SWADMIN_H

class SWAdmin : public CWinApp
{
public:
	SWAdmin();
	~SWAdmin();
	
	HANDLE			m_h_Mutex;
	
	//{{AFX_VIRTUAL(SWAdmin)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	
	//{{AFX_MSG(SWAdmin)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif//SWADMIN_H