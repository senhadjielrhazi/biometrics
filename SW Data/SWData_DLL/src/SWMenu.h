/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWData.h													 //
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




#ifndef SWMENU_H
#define SWMENU_H


class ATL_NO_VTABLE C_Menu : 
public CComObjectRootEx<CComSingleThreadModel>,
public CComCoClass<C_Menu, &CLSID_DLLSWData>,
public IDispatchImpl<IDLSWData, &IID_IDLSWData, &LIBID_DLSWDataLib>,
public IShellExtInit,
public IContextMenu
{
public:
	C_Menu();
	~C_Menu();
	
	// IShellExtInit
	STDMETHOD(Initialize)(LPCITEMIDLIST, LPDATAOBJECT, HKEY);
	
	// IContextMenu
	STDMETHOD(GetCommandString)(UINT, UINT, UINT*, LPSTR, UINT);
	STDMETHOD(InvokeCommand)(LPCMINVOKECOMMANDINFO);
	STDMETHOD(QueryContextMenu)(HMENU, UINT, UINT, UINT, UINT);
	
	DECLARE_REGISTRY_RESOURCEID(IDR_DLLSWDATA)
		DECLARE_NOT_AGGREGATABLE(C_Menu)
		
		DECLARE_PROTECT_FINAL_CONSTRUCT()
		
		BEGIN_COM_MAP(C_Menu)
		COM_INTERFACE_ENTRY(IDLSWData)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IShellExtInit)
		COM_INTERFACE_ENTRY(IContextMenu)
		END_COM_MAP()
		
		// IDLSWData
public:
	HRESULT IsMenuAlreadyPopUp(VOID);
	VOID	SetMenuNoPopUp(VOID);
protected:
	HBITMAP 	m_h_DataBmp;
	HBITMAP 	m_h_CryptBmp;
	HBITMAP 	m_h_DecryptBmp;
	
	string_list   m_ls_Files;
	
	TSWFile 	*m_p_File;
	INT 		m_i_NBFile;
	
	HANDLE		m_h_DataMutex;
};

#endif//SWMENU_H
