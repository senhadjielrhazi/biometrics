/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003. 									 //
//																			 //
//	File:		SWTypeDef_Data.h											 //
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




#ifndef SWTYPEDEF_DATA_H
#define SWTYPEDEF_DATA_H

typedef struct
{
	WCHAR	m_pwc_FilePath[MAX_PATH];
} TSWFile,*PTSWFile;

typedef struct
{
	HFILE	m_h_FileHandle;
	WCHAR	m_pwc_FileName[MAX_PATH];
} TSWFileDate,*PTSWFileDate;

#endif //SWTYPEDEF_DATA_H
