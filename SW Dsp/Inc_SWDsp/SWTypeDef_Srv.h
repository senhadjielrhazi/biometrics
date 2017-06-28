/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003. 									 //
//																			 //
//	File:		SWTypeDef_Dsp.h												 //
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
//	SAGEM SA Data Service Provider Module									 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#ifndef SWTYPEDEF_SRV_H
#define SWTYPEDEF_SRV_H

typedef struct{
	C_MORPHO_Device 		*m_px_MorphoSmart;
	C_MORPHO_Database		*m_px_Database;
	C_MORPHO_User			*m_px_User;
	C_MORPHO_Image			*m_px_Image;
	SC_HANDLE				m_sc_HostService;
    SC_HANDLE				m_sc_LocalSCManager;
	SERVICE_STATUS			m_ss_ServiceStatus;
	SERVICE_STATUS_HANDLE   m_ss_StatusHandle;
	DWORD					m_dw_LastError;
	HANDLE					m_h_HostMutex;
	HANDLE					m_h_HostWaitMsoExit;
	ULONG					m_ul_nbFreeRecord;
	ULONG					m_ul_nbUsedRecord;
	ULONG					m_ul_nbTotalRecord;
} THostMemory, *PTHostMemory;

#endif//SWTYPEDEF_SRV_H
