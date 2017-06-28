/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWModule.h													 //
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




#ifndef SWMODULE_H
#define SWMODULE_H

TModuleRet	WlxLogonIdentOn(TLogonOut &in_Data);
void		WlxLogonIdentOff();

TModuleRet	WlxDataIdentOn(TDataOut &in_Data);
void		WlxDataIdentOff();


TModuleRet	WlxAccessIdentOn(TAccessOut &in_Data);
void		WlxAccessIdentOff();
TModuleRet	WlxAccessUpdateOn(TAccessOut &in_Data);

#endif//SWMODULE
