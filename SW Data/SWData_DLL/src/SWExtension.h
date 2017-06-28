/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWExstension.h												 //
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




#ifndef SWEXTENSION_H
#define SWEXTENSION_H

STDAPI DllCanUnloadNow
(
 VOID
 );

STDAPI DllGetClassObject
(
 REFCLSID rclsid, 
 REFIID riid, 
 LPVOID* ppv
 );

STDAPI DllRegisterServer
(
 VOID
 );

STDAPI DllUnregisterServer
(
 VOID
 );

VOID CALLBACK DllEncodingFile
(
  HWND hwnd,
  HINSTANCE hinst,
  LPTSTR lpCmdLine,
  int nCmdShow
);

HRESULT IsMenuAlreadyPopUp
(
 VOID
 );

VOID	SetMenuNoPopUp
(
 VOID
 );

#endif//SWEXTENSION_H
