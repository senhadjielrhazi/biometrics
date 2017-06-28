/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWModule.cpp												 //
//																			 //
//	Contents:																 //
//																			 //
//	Classes:																 //
//																			 //
//	Functions:																 //
//																			 //
//	History:	22-05-2003	 O. Senhadji El Rhazi   Created						 //
//				25-05-2003	 O. Senhadji El Rhazi   1 ere Release				 //
///////////////////////////////////////////////////////////////////////////////
//																			 //
//	Secure Workstation Suite Product										 //
//	SAGEM SA Logon Module													 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#include "stdafx.h"


/********************************WlxStartSWOn*********************************/
//DLL EntryPoint, this fuction 
//Provide the instance of resources.
/*****************************************************************************/
void WlxStartSWOn()
{
	//Metre g_T_SWState;
}

/*******************************WlxStartSWOff*********************************/
//DLL EntryPoint, this fuction 
//Provide the instance of resources.
/*****************************************************************************/
void WlxStartSWOff()
{
	//Metre g_T_SWState a null;
}

/******************************WlxLogonIdentOn********************************/
//DLL EntryPoint, this fuction 
//Provide the instance of resources.
/*****************************************************************************/
TModuleRet WlxLogonIdentOn(TLogonOut &in_Data)
{
	return SW_ABORT_MD;
}

/*****************************WlxLogonIdentOff********************************/
//DLL EntryPoint, this fuction 
//Provide the instance of resources.
/*****************************************************************************/
void WlxLogonIdentOff()
{
}

/******************************WlxDataIdentOn*********************************/
//DLL EntryPoint, this fuction 
//Provide the instance of resources.
/*****************************************************************************/
TModuleRet WlxDataIdentOn(TDataOut &in_Data)
{
	return SW_ABORT_MD;
}

/*****************************WlxDataIdentOff*********************************/
//DLL EntryPoint, this fuction 
//Provide the instance of resources.
/*****************************************************************************/
void WlxDataIdentOff()
{
}

/******************************WlxAccessIdentOn*******************************/
//DLL EntryPoint, this fuction 
//Provide the instance of resources.
/*****************************************************************************/
TModuleRet WlxAccessIdentOn(TAccessOut &in_Data)
{
	return SW_ABORT_MD;
}

/*****************************WlxAccessIdentOff*******************************/
//DLL EntryPoint, this fuction 
//Provide the instance of resources.
/*****************************************************************************/
void WlxAccessIdentOff()
{
}

/*****************************WlxAccessUpdateOn*******************************/
//DLL EntryPoint, this fuction 
//Provide the instance of resources.
/*****************************************************************************/
TModuleRet WlxAccessUpdateOn(TAccessOut &in_Data)
{
	return SW_ABORT_MD;
}