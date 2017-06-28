/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWMD_Logon.cpp												 //
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
//	SAGEM SA DSP Logon Module												 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#include "stdafx.h"

/*******************************WlxLogonIdentOn********************************/
//DLL EntryPoint, this fuction 
//Provide data for the Logon Ident service.
/*****************************************************************************/
TModuleRet WlxLogonIdentOn
(
 TSpeDataOut &o_T_Data
 )
{	
	HANDLE			l_h_Events[2]									= {NULL};
	DWORD			l_dw_EventRet									= -1;		
	
	__try
	{
		l_h_Events[0]		= g_T_LocalMemory.m_h_LogonIdent;
		l_h_Events[1]		= g_T_LocalMemory.m_h_ExistSW;
		
		if(WlxIsSWLock()||g_T_SharedMemory->m_b_LogonIdent)
			return SW_ABORT_MD;

		if(!WlxIsDspLoaded())
			WlxSWOn(g_T_SharedMemory->m_T_SWState);
		else
		{
			if(((g_T_SharedMemory->m_T_SWState.m_T_DbState != MSO_DB_OK)&&(g_T_SharedMemory->m_T_SWState.m_T_DbState != MSO_DB_FULL))||\
				(g_T_SharedMemory->m_T_SWState.m_T_ComState != MSO_COM_OK))
				return SW_ERRSTG_MD;
			else
			{
				do
				{
					g_T_SharedMemory->m_b_LogonIdent = TRUE;
					ResetEvent(g_T_LocalMemory.m_h_LogonIdent);
					PulseEvent(g_T_LocalMemory.m_h_WaitIdent);
					
					l_dw_EventRet = WaitForMultipleObjects(2,l_h_Events,FALSE,30000);
					
					if(l_dw_EventRet == WAIT_OBJECT_0)
					{
						ResetEvent(g_T_LocalMemory.m_h_LogonIdent);	
						if(g_T_SharedMemory->m_T_ResultLogonId == SW_OKHIT_MD)
						{
							memset(&o_T_Data,0,sizeof(TSpeDataOut));
							memcpy(o_T_Data.m_pwc_UserId,g_T_SharedMemory->m_T_MsoData.m_pwc_UserId,sizeof(o_T_Data.m_pwc_UserId));
							memcpy(o_T_Data.m_pwc_UserKey,g_T_SharedMemory->m_T_MsoData.m_pwc_UserKey,sizeof(o_T_Data.m_pwc_UserKey));
							memcpy(o_T_Data.m_pwc_UserLogon,g_T_SharedMemory->m_T_MsoData.m_pwc_UserLogon,sizeof(o_T_Data.m_pwc_UserLogon));	
						}
						return g_T_SharedMemory->m_T_ResultLogonId;
					}
					else if(l_dw_EventRet == WAIT_OBJECT_0+1)
						return SW_ABORT_MD;
					else
					{
						if(WlxIsSWLock())
							return SW_ABORT_MD;
						if(((g_T_SharedMemory->m_T_SWState.m_T_DbState != MSO_DB_OK) && (g_T_SharedMemory->m_T_SWState.m_T_DbState != MSO_DB_FULL)) || 
							(g_T_SharedMemory->m_T_SWState.m_T_ComState != MSO_COM_OK))
						{
							g_T_SharedMemory->m_b_LogonIdent = FALSE;
							ResetEvent(g_T_LocalMemory.m_h_LogonIdent);
							//PulseEvent(g_T_LocalMemory.m_h_WaitIdent);
							return SW_ERRSTG_MD;
						}
						if(!WlxIsDspLoaded())
						{
							PulseEvent(g_T_LocalMemory.m_h_WaitCancel);
							WlxSWOn(g_T_SharedMemory->m_T_SWState);	
							g_T_SharedMemory->m_b_LogonIdent = TRUE;
							ResetEvent(g_T_LocalMemory.m_h_LogonIdent);
							PulseEvent(g_T_LocalMemory.m_h_WaitIdent);
							continue;
						}
					}
				}while(l_dw_EventRet != WAIT_OBJECT_0);
			}
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		return SW_ABORT_MD;
	}
}

/*****************************WlxLogonIdentOff********************************/
//DLL EntryPoint, this fuction 
//Provide the cancel of Logon Ident service.
/*****************************************************************************/
VOID WlxLogonIdentOff
(
 VOID
 )
{
	__try
	{
		g_T_SharedMemory->m_b_LogonIdent = FALSE;
		g_T_SharedMemory->m_T_ResultLogonId = SW_ABORT_MD;
		PulseEvent(g_T_LocalMemory.m_h_LogonIdent);
		
		if(!WlxIsDspLoaded())//||WlxIsSWLock())
			return;
		if(
			!g_T_SharedMemory->m_b_AccessIdent && !g_T_SharedMemory->m_b_AdminIdent &&\
			!g_T_SharedMemory->m_b_DataIdent && !g_T_SharedMemory->m_b_AdminEnroll
			)
			SetEvent(g_T_LocalMemory.m_h_WaitCancel);
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}
