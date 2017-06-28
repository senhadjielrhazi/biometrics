/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWMD_Admin.cpp												 //
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
//	SAGEM SA DSP Admin Module												 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#include "stdafx.h"

/*****************************WlxAdminRefresh*********************************/
//DLL EntryPoint, this fuction 
//Provide the current contex service.
/*****************************************************************************/
VOID WlxAdminRefresh
(
 TSWState &o_T_SWState
 )
{
	__try
	{
		memcpy(&o_T_SWState,&g_T_SharedMemory->m_T_SWState,sizeof(g_T_SharedMemory->m_T_SWState));
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

/*****************************WlxAdminLockSW**********************************/
//DLL LocalEntryPoint, this fuction 
//Lock all the service provider to the admin MD.
/*****************************************************************************/
VOID WlxAdminLockSW
(
 VOID
 )
{
	__try
	{
		g_T_SharedMemory->m_b_LockSW = TRUE;
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

/*****************************WlxAdminUnLock**********************************/
//DLL LocalEntryPoint, this fuction 
//Unlock the service provider.
/*****************************************************************************/
VOID WlxAdminUnLock
(
 VOID
 )
{
	__try
	{
		g_T_SharedMemory->m_b_LockSW = FALSE;
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

/******************************WlxAdminIdentOn********************************/
//DLL EntryPoint, this fuction 
//Provide data for the Admin Ident service.
/*****************************************************************************/
TModuleRet WlxAdminIdentOn
(
 TSpeDataOut &o_T_Data
 )
{
	HANDLE			l_h_Events[2]									= {NULL};
	DWORD			l_dw_EventRet									= -1;		
	
	__try
	{
		l_h_Events[0]		= g_T_LocalMemory.m_h_AdminIdent;
		l_h_Events[1]		= g_T_LocalMemory.m_h_ExistSW;
		
		if(!WlxIsDspLoaded())
			return SW_ABORT_MD;
		
		if(g_T_SharedMemory->m_b_AdminIdent)
			return SW_ABORT_MD;
		else
		{
			if(((g_T_SharedMemory->m_T_SWState.m_T_DbState != MSO_DB_OK)&&(g_T_SharedMemory->m_T_SWState.m_T_DbState != MSO_DB_FULL))||\
				(g_T_SharedMemory->m_T_SWState.m_T_ComState != MSO_COM_OK))
				return SW_ERRSTG_MD;
			else
			{
				do
				{
					g_T_SharedMemory->m_b_AdminIdent = TRUE;
					ResetEvent(g_T_LocalMemory.m_h_AdminIdent);
					PulseEvent(g_T_LocalMemory.m_h_WaitIdent);
					
					l_dw_EventRet = WaitForMultipleObjects(2,l_h_Events,FALSE,30000);
					
					if(l_dw_EventRet == WAIT_OBJECT_0)
					{
						if(g_T_SharedMemory->m_T_ResultAdminId == SW_OKHIT_MD)
						{
							memset(&o_T_Data,0,sizeof(TSpeDataOut));
							memcpy(o_T_Data.m_pwc_UserId,g_T_SharedMemory->m_T_MsoData.m_pwc_UserId,sizeof(o_T_Data.m_pwc_UserId));
							memcpy(o_T_Data.m_pwc_UserKey,g_T_SharedMemory->m_T_MsoData.m_pwc_UserKey,sizeof(o_T_Data.m_pwc_UserKey));
							memcpy(o_T_Data.m_pwc_UserLogon,g_T_SharedMemory->m_T_MsoData.m_pwc_UserLogon,sizeof(o_T_Data.m_pwc_UserLogon));
						}
						return g_T_SharedMemory->m_T_ResultAdminId;
					}
					else if(l_dw_EventRet == WAIT_OBJECT_0+1)
						return SW_ABORT_MD;
					else
					{
						if(((g_T_SharedMemory->m_T_SWState.m_T_DbState != MSO_DB_OK) && (g_T_SharedMemory->m_T_SWState.m_T_DbState != MSO_DB_FULL)) || 
							(g_T_SharedMemory->m_T_SWState.m_T_ComState != MSO_COM_OK))
						{
							g_T_SharedMemory->m_b_AdminIdent = FALSE;
							ResetEvent(g_T_LocalMemory.m_h_AdminIdent);
							//PulseEvent(g_T_LocalMemory.m_h_WaitIdent);
							return SW_ERRSTG_MD;
						}
						if(!WlxIsDspLoaded())
						{
							PulseEvent(g_T_LocalMemory.m_h_WaitCancel);
							WlxSWOn(g_T_SharedMemory->m_T_SWState);
							g_T_SharedMemory->m_b_AdminIdent = TRUE;
							ResetEvent(g_T_LocalMemory.m_h_AdminIdent);
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

/******************************WlxAdminIdentOff*******************************/
//DLL EntryPoint, this fuction 
//Provide the cancel of Admin Ident service.
/*****************************************************************************/
VOID WlxAdminIdentOff
(
 VOID
 )
{	
	__try
	{
		if(
			g_T_SharedMemory->m_b_AdminIdent && !g_T_SharedMemory->m_b_AccessIdent &&\
			!g_T_SharedMemory->m_b_DataIdent && !g_T_SharedMemory->m_b_LogonIdent &&\
			!g_T_SharedMemory->m_b_AdminEnroll
			)
			SetEvent(g_T_LocalMemory.m_h_WaitCancel);
		
		g_T_SharedMemory->m_b_AdminIdent = FALSE;
		g_T_SharedMemory->m_T_ResultAdminId = SW_ABORT_MD;
		PulseEvent(g_T_LocalMemory.m_h_AdminIdent);
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

/*****************************WlxAdminEnrollOn********************************/
//DLL EntryPoint, this fuction 
//Provide the Enroll for the Admin MD service.
/*****************************************************************************/
TModuleRet WlxAdminEnrollOn
(
 TSupDataOut i_T_Data
 )
{
	HANDLE			l_h_Events[2]									= {NULL};
	DWORD			l_dw_EventRet									= -1;		
	
	__try
	{
		l_h_Events[0]		= g_T_LocalMemory.m_h_AdminEnroll;
		l_h_Events[1]		= g_T_LocalMemory.m_h_ExistSW;
		
		if(!WlxIsDspLoaded())
			return SW_ABORT_MD;
		
		if(g_T_SharedMemory->m_b_AdminEnroll)
			return SW_ABORT_MD;
		else
		{
			if(((g_T_SharedMemory->m_T_SWState.m_T_DbState != MSO_DB_OK)&&(g_T_SharedMemory->m_T_SWState.m_T_DbState != MSO_DB_EMPTY))||\
				(g_T_SharedMemory->m_T_SWState.m_T_ComState != MSO_COM_OK))
				return SW_ERRSTG_MD;
			else
			{
				memset(&g_T_SharedMemory->m_T_PcData,0,sizeof(g_T_SharedMemory->m_T_PcData));
				memcpy(&g_T_SharedMemory->m_T_PcData,&i_T_Data,sizeof(g_T_SharedMemory->m_T_PcData));
				
				do
				{
					g_T_SharedMemory->m_b_AdminEnroll = TRUE;
					ResetEvent(g_T_LocalMemory.m_h_AdminEnroll);
					SetEvent(g_T_LocalMemory.m_h_WaitEnroll);
					
					l_dw_EventRet = WaitForMultipleObjects(2,l_h_Events,FALSE,30000);
					
					ResetEvent(g_T_LocalMemory.m_h_WaitEnroll);
					if(l_dw_EventRet == WAIT_OBJECT_0)
					{
						ResetEvent(g_T_LocalMemory.m_h_AdminEnroll);
						return g_T_SharedMemory->m_T_ResultAdminEn;
					}
					else if(l_dw_EventRet == WAIT_OBJECT_0+1)
						return SW_ABORT_MD;
					else
					{
						if(((g_T_SharedMemory->m_T_SWState.m_T_DbState != MSO_DB_OK) && (g_T_SharedMemory->m_T_SWState.m_T_DbState != MSO_DB_FULL)) || 
							(g_T_SharedMemory->m_T_SWState.m_T_ComState != MSO_COM_OK))
						{
							g_T_SharedMemory->m_b_AdminEnroll = FALSE;
							ResetEvent(g_T_LocalMemory.m_h_AdminEnroll);
							//PulseEvent(g_T_LocalMemory.m_h_WaitEnroll);
							return SW_ERRSTG_MD;
						}
						if(!WlxIsDspLoaded())
						{
							PulseEvent(g_T_LocalMemory.m_h_WaitCancel);
							WlxSWOn(g_T_SharedMemory->m_T_SWState); 
							g_T_SharedMemory->m_b_AdminEnroll = TRUE;
							ResetEvent(g_T_LocalMemory.m_h_AdminEnroll);
							PulseEvent(g_T_LocalMemory.m_h_WaitEnroll);
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

/******************************WlxAdminEnrollOff******************************/
//DLL EntryPoint, this fuction 
//Provide the cancel Enroll for the Admin MD service.
/*****************************************************************************/
VOID WlxAdminEnrollOff
(
 VOID
 )
{	
	__try
	{
		if(!g_T_SharedMemory->m_b_AdminEnroll)
			return;
		else
		{
			g_T_SharedMemory->m_b_AdminEnroll = FALSE;
			SetEvent(g_T_LocalMemory.m_h_WaitCancel);
			PulseEvent(g_T_LocalMemory.m_h_AdminEnroll);
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}	
/*****************************WlxAdminUpdateOn********************************/
//DLL EntryPoint, this fuction 
//Provide the Admin Update service.
/*****************************************************************************/
TModuleRet WlxAdminUpdateOn
(
 TUpDataOut i_T_Data
 )
{
	DWORD	l_dw_Result;
	
	__try
	{
		if(!WlxIsDspLoaded())
			return SW_ABORT_MD;
		
		memset(&g_T_SharedMemory->m_T_UpdateData,0,sizeof(TUpDataOut));
		memcpy(&g_T_SharedMemory->m_T_UpdateData,&i_T_Data,sizeof(i_T_Data));	
		
		ResetEvent(g_T_LocalMemory.m_h_AdminUpdate);
		PulseEvent(g_T_LocalMemory.m_h_WaitUpdateAdmin);
		l_dw_Result = WaitForSingleObject(g_T_LocalMemory.m_h_AdminUpdate,VI_TIMEOUT);
		
		if(l_dw_Result == WAIT_OBJECT_0)
		{
			ResetEvent(g_T_LocalMemory.m_h_AdminUpdate);
			return g_T_SharedMemory->m_T_ResultAdminUp; 
		}
		else
			l_dw_Result = WaitForSingleObject(g_T_LocalMemory.m_h_AdminUpdate,2*VI_TIMEOUT);
		
		ResetEvent(g_T_LocalMemory.m_h_AdminUpdate);
		
		if(l_dw_Result == WAIT_OBJECT_0)
			return g_T_SharedMemory->m_T_ResultAdminUp;
		else
			return SW_ABORT_MD;
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		return SW_ABORT_MD;
	}
}

/****************************WlxAdminEnrollPaint******************************/
//DLL EntryPoint, this fuction 
//Provide data for enroll page : MSg and Pictures.
/*****************************************************************************/
INT WlxAdminEnrollPaint
(
 VOID
 )
{	
	__try
	{
		PulseEvent(g_T_LocalMemory.m_h_WaitPaint);
		return g_T_SharedMemory->m_T_PcData.m_i_CurrentImage;
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		return 0;
	}
}

/******************************WlxAdminUserOn*********************************/
//DLL EntryPoint, this fuction 
//Provide the Del User for Admin MD service.
/*****************************************************************************/
TModuleRet WlxAdminUserOn
(
 WCHAR *i_pwc_UserId
 )
{
	DWORD	l_dw_Result;
	
	__try
	{
		if(!WlxIsDspLoaded())
			return SW_ABORT_MD;
		
		memset(g_T_SharedMemory->m_puc_UserID,0,VI_USERID_MAX*sizeof(WCHAR));
		memcpy(g_T_SharedMemory->m_puc_UserID,i_pwc_UserId,VI_USERID_MAX*sizeof(WCHAR));
		
		ResetEvent(g_T_LocalMemory.m_h_AdminUser);
		PulseEvent(g_T_LocalMemory.m_h_WaitAdminUser);
		l_dw_Result = WaitForSingleObject(g_T_LocalMemory.m_h_AdminUser,VI_TIMEOUT);
		
		if(l_dw_Result == WAIT_OBJECT_0)
		{
			ResetEvent(g_T_LocalMemory.m_h_AdminUser);
			return g_T_SharedMemory->m_T_ResultAdminUser;
		}
		else
			l_dw_Result = WaitForSingleObject(g_T_LocalMemory.m_h_AdminUser,2*VI_TIMEOUT);
		
		ResetEvent(g_T_LocalMemory.m_h_AdminUser);
		
		if(l_dw_Result == WAIT_OBJECT_0)
			return g_T_SharedMemory->m_T_ResultAdminUser;
		else
			return SW_ABORT_MD;
	}
	__except(EXCEPTION_EXECUTE_HANDLER )
	{
		return SW_ABORT_MD;
	}
}

/********************************WlxAdminDbOn*********************************/
//DLL EntryPoint, this fuction 
//Provide the Db Create or Db Del and Create for Admin MD service.
/*****************************************************************************/
VOID WlxAdminDbOn
(
 TSWState &o_T_SWState,
 BOOL i_b_EraseDel
 )
{
	DWORD	l_dw_Result;
	
	__try
	{
		if(!WlxIsDspLoaded())
			return;
		
		g_T_SharedMemory->m_b_EraseDel = i_b_EraseDel;
		
		ResetEvent(g_T_LocalMemory.m_h_AdminDb);
		PulseEvent(g_T_LocalMemory.m_h_WaitAdminDb);
		l_dw_Result = WaitForSingleObject(g_T_LocalMemory.m_h_AdminDb,VI_TIMEOUT);
		
		if(l_dw_Result != WAIT_OBJECT_0)
			l_dw_Result = WaitForSingleObject(g_T_LocalMemory.m_h_AdminDb,VI_TIMEOUT);
		
		if(l_dw_Result == WAIT_OBJECT_0)
		{
			o_T_SWState.m_T_ComState = g_T_SharedMemory->m_T_SWState.m_T_ComState;
			o_T_SWState.m_T_DbState = g_T_SharedMemory->m_T_SWState.m_T_DbState;
		}
		else
		{
			o_T_SWState.m_T_ComState = MSO_COM_ERR;
			o_T_SWState.m_T_DbState = MSO_DB_ERR;
		}
		ResetEvent(g_T_LocalMemory.m_h_AdminDb);
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}



