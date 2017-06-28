/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWMD_Access.cpp 											 //
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
//	SAGEM SA DSP Access Module												 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#include "stdafx.h"

/******************************WlxAccessIdentOn*******************************/
//DLL EntryPoint, this fuction 
//Provide data for the Access Ident service.
/*****************************************************************************/
TModuleRet WlxAccessIdentOn
(
 TAllDataOut &o_T_Data
 )
{
	HANDLE			l_h_Events[2]									= {NULL};
	DWORD			l_dw_EventRet									= -1;		
	
	__try
	{
		l_h_Events[0]		= g_T_LocalMemory.m_h_AccessIdent;
		l_h_Events[1]		= g_T_LocalMemory.m_h_ExistSW;
				
		if(WlxIsSWLock()||g_T_SharedMemory->m_b_AccessIdent)
			return SW_ABORT_MD;
		if(!WlxIsDspLoaded())
			WlxSWOn(g_T_SharedMemory->m_T_SWState);
		else
		{
			if(((g_T_SharedMemory->m_T_SWState.m_T_DbState != MSO_DB_OK) && (g_T_SharedMemory->m_T_SWState.m_T_DbState != MSO_DB_FULL)) || 
				(g_T_SharedMemory->m_T_SWState.m_T_ComState != MSO_COM_OK))
				return SW_ERRSTG_MD;
			else
			{
				do
				{
					g_T_SharedMemory->m_b_AccessIdent = TRUE;
					ResetEvent(g_T_LocalMemory.m_h_AccessIdent);
					PulseEvent(g_T_LocalMemory.m_h_WaitIdent);
					l_dw_EventRet = WaitForMultipleObjects(2,l_h_Events,FALSE,30000);
					
					if(l_dw_EventRet == WAIT_OBJECT_0)
					{
						ResetEvent(g_T_LocalMemory.m_h_AccessIdent);
						if(g_T_SharedMemory->m_T_ResultAccessId == SW_OKHIT_MD)
						{
							memset(&o_T_Data,0,sizeof(TAllDataOut));
							memcpy(&o_T_Data,&g_T_SharedMemory->m_T_MsoData,sizeof(o_T_Data));	
						}
						return g_T_SharedMemory->m_T_ResultAccessId;
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
							g_T_SharedMemory->m_b_AccessIdent = FALSE;
							ResetEvent(g_T_LocalMemory.m_h_AccessIdent);
							//PulseEvent(g_T_LocalMemory.m_h_WaitIdent);
							return SW_ERRSTG_MD;
						}
						if(!WlxIsDspLoaded())
						{
							PulseEvent(g_T_LocalMemory.m_h_WaitCancel);
							WlxSWOn(g_T_SharedMemory->m_T_SWState);
							g_T_SharedMemory->m_b_AccessIdent = TRUE;
							ResetEvent(g_T_LocalMemory.m_h_AccessIdent);
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

/*****************************WlxAccessIdentOff*******************************/
//DLL EntryPoint, this fuction 
//Provide the cancel of Access Ident service.
/*****************************************************************************/
VOID WlxAccessIdentOff
(
 VOID
 )
{
	__try
	{
		g_T_SharedMemory->m_b_AccessIdent = FALSE;
		g_T_SharedMemory->m_T_ResultAccessId = SW_ABORT_MD;
		SetEvent(g_T_LocalMemory.m_h_AccessIdent);
		
		if(!WlxIsDspLoaded())//||WlxIsSWLock())
			return;
		if(
			!g_T_SharedMemory->m_b_AdminIdent&&!g_T_SharedMemory->m_b_DataIdent&&\
			!g_T_SharedMemory->m_b_LogonIdent&&!g_T_SharedMemory->m_b_AdminEnroll
			)
			SetEvent(g_T_LocalMemory.m_h_WaitCancel); 	
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

/*****************************WlxAccessUpdateOn*******************************/
//DLL EntryPoint, this fuction 
//Provide the Access Update service.
/*****************************************************************************/
TModuleRet WlxAccessUpdateOn
(
 TUpDataOut i_T_Data
 )
{
	DWORD	l_dw_Result;
	
	__try
	{
		if(!WlxIsDspLoaded())
			WlxSWOn(g_T_SharedMemory->m_T_SWState);
		
		if(WlxIsSWLock())
			return SW_ABORT_MD;
		
		memset(&g_T_SharedMemory->m_T_UpdateData,0,sizeof(TUpDataOut));
		memcpy(&g_T_SharedMemory->m_T_UpdateData,&i_T_Data,sizeof(i_T_Data));	
		
		ResetEvent(g_T_LocalMemory.m_h_AccessUpdate);
		PulseEvent(g_T_LocalMemory.m_h_WaitUpdateAccess);
		l_dw_Result = WaitForSingleObject(g_T_LocalMemory.m_h_AccessUpdate,VI_TIMEOUT);
		
		if(l_dw_Result == WAIT_OBJECT_0)
		{
			ResetEvent(g_T_LocalMemory.m_h_AccessUpdate);
			return g_T_SharedMemory->m_T_ResultAccessUp;
		}
		else
			l_dw_Result = WaitForSingleObject(g_T_LocalMemory.m_h_AccessUpdate,2*VI_TIMEOUT);
		
		if(l_dw_Result == WAIT_OBJECT_0)
		{
			ResetEvent(g_T_LocalMemory.m_h_AccessUpdate);
			return g_T_SharedMemory->m_T_ResultAccessUp;
		}
		else
			return SW_ABORT_MD;
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		return SW_ABORT_MD;
	}
}
