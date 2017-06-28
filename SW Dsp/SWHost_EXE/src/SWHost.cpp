/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWHost.cpp													 //
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
//	SAGEM SA Data Service Provider Service									 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#include "stdafx.h"

extern TSharedMemory	*g_T_SharedMemory;
extern THostMemory		g_T_HostMemory; 
extern TLocalMemory 	g_T_LocalMemory;

DWORD WINAPI SuperviseThreadProc
(
 LPVOID lpvParam
 )
{
	DWORD					l_dw_EventRet		= -1;
	INT 					l_i_AppWait 		= 0;
	HANDLE					l_h_Mutex			= NULL;
	DWORD					l_dw_LastEror		= 0;
	PSECURITY_DESCRIPTOR	l_p_pSD 			= NULL;
	SECURITY_ATTRIBUTES 	l_T_sa				= {0};
	HANDLE					l_h_Events[2]		= {NULL};
	__try
	{
		if(g_T_SharedMemory != NULL)
		{
			l_p_pSD = (PSECURITY_DESCRIPTOR) malloc( SECURITY_DESCRIPTOR_MIN_LENGTH );
			
			if (l_p_pSD == NULL)
				return FALSE;
			
			if (!InitializeSecurityDescriptor(l_p_pSD, SECURITY_DESCRIPTOR_REVISION))
			{
				free(l_p_pSD);
				return FALSE;
			}
			
			// add a NULL disc. ACL to the security descriptor.
			if (!SetSecurityDescriptorDacl(l_p_pSD, TRUE, (PACL) NULL, FALSE))
			{
				free(l_p_pSD);
				return FALSE;
			}
			
			l_T_sa.nLength = sizeof(l_T_sa);
			l_T_sa.lpSecurityDescriptor = l_p_pSD;
			l_T_sa.bInheritHandle = TRUE;
			
			do
			{
				l_h_Events[0] = g_T_LocalMemory.m_h_ExistSW;
				l_h_Events[1] = g_T_LocalMemory.m_h_SWOff;
				
				l_dw_EventRet = WaitForMultipleObjects(2,l_h_Events,FALSE,3000);
				
				l_i_AppWait = 0;
				
				if(l_dw_EventRet == WAIT_OBJECT_0)
					return 0;
				
				if(l_dw_EventRet == WAIT_OBJECT_0+1)
					Sleep(100);
				
				l_h_Mutex = CreateMutex
					(
					(LPSECURITY_ATTRIBUTES)&l_T_sa,
					(BOOL)TRUE,
					(LPCTSTR)_T(VC_ACCESSMUTEX_NAME) 
					);
				
				l_dw_LastEror = GetLastError ();
				
				//If cannot create Mutex, exit.
				if (l_h_Mutex == NULL)
					continue;
				
				ReleaseMutex(l_h_Mutex);
				CloseHandle(l_h_Mutex);
				
				//If Mutex already existed, exit.
				if (l_dw_LastEror != ERROR_ALREADY_EXISTS)
				{
					if(g_T_SharedMemory->m_b_AccessIdent)
						l_i_AppWait++;
					g_T_SharedMemory->m_T_ResultAccessUp	= SW_ABORT_MD;
					g_T_SharedMemory->m_T_ResultAccessId	= SW_ABORT_MD;	
					g_T_SharedMemory->m_b_AccessIdent		= FALSE;
					SetEvent(g_T_LocalMemory.m_h_AccessUpdate);
					SetEvent(g_T_LocalMemory.m_h_AccessIdent);
					ResetEvent(g_T_LocalMemory.m_h_WaitUpdateAccess);
					Sleep(30);
					SetEvent(g_T_LocalMemory.m_h_AccessUpdate);
					SetEvent(g_T_LocalMemory.m_h_AccessIdent);
				}
				else
					l_i_AppWait = -10;
				
				l_h_Mutex = CreateMutex
					(
					(LPSECURITY_ATTRIBUTES)&l_T_sa,
					(BOOL)TRUE,
					(LPCTSTR)_T(VC_DATAMUTEX_NAME)	
					);
				
				l_dw_LastEror = GetLastError ();
				
				//If cannot create Mutex, exit.
				if (l_h_Mutex == NULL)
					continue;
				
				ReleaseMutex(l_h_Mutex);
				CloseHandle(l_h_Mutex);
				
				//If Mutex already existed, exit.
				if (l_dw_LastEror != ERROR_ALREADY_EXISTS)
				{
					if(g_T_SharedMemory->m_b_DataIdent)
						l_i_AppWait++;
					g_T_SharedMemory->m_T_ResultDataId	= SW_ABORT_MD;
					g_T_SharedMemory->m_b_DataIdent 	= FALSE;
					SetEvent(g_T_LocalMemory.m_h_DataIdent);
					Sleep(30);
					ResetEvent(g_T_LocalMemory.m_h_DataIdent);
				}
				else
					l_i_AppWait = -10;
				
				l_h_Mutex = CreateMutex
					(
					(LPSECURITY_ATTRIBUTES)&l_T_sa,
					(BOOL)TRUE,
					(LPCTSTR)_T(VC_LOGONMUTEX_NAME) 
					);
				
				l_dw_LastEror = GetLastError ();
				
				//If cannot create Mutex, exit.
				if (l_h_Mutex == NULL)
					continue;
				
				ReleaseMutex(l_h_Mutex);
				CloseHandle(l_h_Mutex);
				
				//If Mutex already existed, exit.
				if (l_dw_LastEror != ERROR_ALREADY_EXISTS)
				{
					if(g_T_SharedMemory->m_b_LogonIdent)
						l_i_AppWait++;
					g_T_SharedMemory->m_T_ResultLogonId 	= SW_ABORT_MD;
					g_T_SharedMemory->m_b_LogonIdent		= FALSE;
					SetEvent(g_T_LocalMemory.m_h_LogonIdent);
					Sleep(30);
					ResetEvent(g_T_LocalMemory.m_h_LogonIdent);
				}
				else
					l_i_AppWait = -10;
				
				l_h_Mutex = CreateMutex
					(
					(LPSECURITY_ATTRIBUTES)&l_T_sa,
					(BOOL)TRUE,
					(LPCTSTR)_T(VC_ADMINMUTEX_NAME) 
					);
				
				l_dw_LastEror = GetLastError ();
				
				//If cannot create Mutex, exit.
				if (l_h_Mutex == NULL)
					continue;
				
				ReleaseMutex(l_h_Mutex);
				CloseHandle(l_h_Mutex);
				
				//If Mutex already existed, exit.
				if (l_dw_LastEror != ERROR_ALREADY_EXISTS)
				{
					if(g_T_SharedMemory->m_b_AdminEnroll||g_T_SharedMemory->m_b_AdminIdent)
						l_i_AppWait++;
					g_T_SharedMemory->m_b_LockSW			= FALSE;
					g_T_SharedMemory->m_T_ResultAdminEn 	= SW_ABORT_MD;
					g_T_SharedMemory->m_T_ResultAdminId 	= SW_ABORT_MD;
					g_T_SharedMemory->m_T_ResultAdminUp 	= SW_ABORT_MD;
					g_T_SharedMemory->m_T_ResultAdminUser	= SW_ABORT_MD;
					g_T_SharedMemory->m_b_AdminIdent		= FALSE;
					g_T_SharedMemory->m_b_AdminEnroll		= FALSE;
					SetEvent(g_T_LocalMemory.m_h_AdminDb);
					SetEvent(g_T_LocalMemory.m_h_AdminUpdate);
					SetEvent(g_T_LocalMemory.m_h_AdminIdent);
					SetEvent(g_T_LocalMemory.m_h_AdminEnroll);
					SetEvent(g_T_LocalMemory.m_h_AdminUser);
					ResetEvent(g_T_LocalMemory.m_h_WaitPaint);
					ResetEvent(g_T_LocalMemory.m_h_WaitAdminUser);
					ResetEvent(g_T_LocalMemory.m_h_WaitAdminDb);
					ResetEvent(g_T_LocalMemory.m_h_WaitUpdateAdmin);
					ResetEvent(g_T_LocalMemory.m_h_WaitEnroll); 
					Sleep(30);
					ResetEvent(g_T_LocalMemory.m_h_AdminDb);
					ResetEvent(g_T_LocalMemory.m_h_AdminUpdate);
					ResetEvent(g_T_LocalMemory.m_h_AdminIdent);
					ResetEvent(g_T_LocalMemory.m_h_AdminEnroll);
					ResetEvent(g_T_LocalMemory.m_h_AdminUser);
				}
				else
					l_i_AppWait = -10;
				
				if(l_i_AppWait > 0)
				{
					SetEvent(g_T_LocalMemory.m_h_WaitCancel); 
					Sleep(30);
					ResetEvent(g_T_LocalMemory.m_h_WaitCancel);
				}
	}while(l_dw_EventRet != WAIT_OBJECT_0);
	
	free(l_p_pSD);
	}
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}	
	return 0;
}

DWORD WINAPI IdentThreadProc
(
 LPVOID lpvParam
 )
{
	HANDLE		l_h_Events[2]	= {NULL};
	DWORD		l_dw_EventRet	= -1;
	INT 		l_i_Result		= 0;
	ULONG		l_ul_FieldIndex = 0;
	ULONG		l_ul_LenField	= 0;
	PUC 		l_puc_DataField = NULL;
	INT 		i				= 0;
	
	do
	{
		__try
		{	
			if(
				g_T_SharedMemory != NULL &&\
				g_T_HostMemory.m_px_Database != NULL && g_T_HostMemory.m_px_MorphoSmart != NULL &&\
				g_T_HostMemory.m_px_Image != NULL && g_T_HostMemory.m_px_User != NULL
				)
			{
				l_h_Events[0] = g_T_LocalMemory.m_h_ExistSW;
				l_h_Events[1] = g_T_LocalMemory.m_h_WaitIdent;
				
				SetEvent(g_T_HostMemory.m_h_HostWaitMsoExit);
				
				l_dw_EventRet = WaitForMultipleObjects(2,l_h_Events,FALSE,INFINITE);
				
				if(l_dw_EventRet == WAIT_OBJECT_0)
					return 0;
				
				ResetEvent(g_T_LocalMemory.m_h_WaitIdent);
				ResetEvent(g_T_HostMemory.m_h_HostWaitMsoExit);
				
				if(g_T_HostMemory.m_px_MorphoSmart == NULL)
				{
					l_i_Result = MORPHOERR_CMDE_ABORTED;
				}
				else
				{
					l_i_Result = g_T_HostMemory.m_px_Database->Identify 
						(
						VS_TIMEOUT,
						(T_MORPHO_FAR) VS_FAR,
						0,
						NULL,
						NULL,
						*g_T_HostMemory.m_px_User
						);	
				}
				SetEvent(g_T_HostMemory.m_h_HostWaitMsoExit);
				if(l_i_Result != MORPHO_OK)
					goto End;
				
				memset(&g_T_SharedMemory->m_T_MsoData,0,sizeof(g_T_SharedMemory->m_T_MsoData));
				
				//Find User ID
				l_ul_FieldIndex = 0;
				if(g_T_HostMemory.m_px_User == NULL)
				{
					l_i_Result = MORPHOERR_CMDE_ABORTED;
				}
				else
				{
					l_i_Result = g_T_HostMemory.m_px_User->GetField
						(
						l_ul_FieldIndex,
						l_ul_LenField,
						l_puc_DataField 
						);
				}
				if(l_i_Result != MORPHO_OK)
					goto End;
				
				memcpy(g_T_SharedMemory->m_T_MsoData.m_pwc_UserId,l_puc_DataField,l_ul_LenField);
				
				//Find Encryption Keys
				l_ul_FieldIndex = 1;
				if(g_T_HostMemory.m_px_User == NULL)
				{
					l_i_Result = MORPHOERR_CMDE_ABORTED;
				}
				else
				{
					l_i_Result = g_T_HostMemory.m_px_User->GetField
						(
						l_ul_FieldIndex,
						l_ul_LenField,
						l_puc_DataField 
						);
				}
				if(l_i_Result != MORPHO_OK)
					goto End;
				
				memcpy(g_T_SharedMemory->m_T_MsoData.m_pwc_UserKey,l_puc_DataField,l_ul_LenField);
				
				//Find Encryption Keys
				l_ul_FieldIndex = 2;
				if(g_T_HostMemory.m_px_User == NULL)
				{
					l_i_Result = MORPHOERR_CMDE_ABORTED;
				}
				else
				{
					l_i_Result = g_T_HostMemory.m_px_User->GetField
						(
						l_ul_FieldIndex,
						l_ul_LenField,
						l_puc_DataField 
						);
				}
				if(l_i_Result != MORPHO_OK)
					goto End;
				
				memcpy(g_T_SharedMemory->m_T_MsoData.m_pwc_UserLogon,l_puc_DataField,l_ul_LenField);
				
				for(i = 0;i<VI_NBAPPLI_MAX;i++)
				{
					l_ul_FieldIndex = i + 3;
					if(g_T_HostMemory.m_px_User == NULL)
					{
						l_i_Result = MORPHOERR_CMDE_ABORTED;
					}
					else
					{
						l_i_Result = g_T_HostMemory.m_px_User->GetField
							(
							l_ul_FieldIndex,
							l_ul_LenField,
							l_puc_DataField 
							);
					}
					if(l_i_Result != MORPHO_OK)
						goto End;
					
					memcpy(g_T_SharedMemory->m_T_MsoData.m_pwc_UserBase[i],l_puc_DataField,l_ul_LenField);
				}
				
End:	
				if(g_T_SharedMemory->m_b_AdminIdent)
				{
					if(l_i_Result == MORPHO_OK)
						g_T_SharedMemory->m_T_ResultAdminId = SW_OKHIT_MD;
					else if(l_i_Result == MORPHOERR_NO_HIT)
						g_T_SharedMemory->m_T_ResultAdminId = SW_NOHIT_MD;
					else if(l_i_Result == MORPHOERR_CMDE_ABORTED)
						g_T_SharedMemory->m_T_ResultAdminId = SW_ABORT_MD;
					else if(l_i_Result == (MORPHOERR_INTERNAL || MORPHOERR_PROTOCOLE || MORPHOERR_CONNECT || MORPHOERR_COM_NOT_OPEN))
					{
						g_T_SharedMemory->m_T_SWState.m_T_ComState	= MSO_COM_ERR;
						g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_ERR;
						g_T_SharedMemory->m_T_ResultAdminId = SW_ERRACT_MD;
					}
					else
					{
						g_T_SharedMemory->m_T_SWState.m_T_ComState	= MSO_COM_OK;
						g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_ERR;
						g_T_SharedMemory->m_T_ResultAdminId = SW_ERRACT_MD;
					}
					
					g_T_SharedMemory->m_b_AdminIdent = FALSE;
					PulseEvent(g_T_LocalMemory.m_h_AdminIdent);
				}
				else if(g_T_SharedMemory->m_b_LogonIdent)
				{
					if(l_i_Result == MORPHO_OK)
						g_T_SharedMemory->m_T_ResultLogonId = SW_OKHIT_MD;
					else if(l_i_Result == MORPHOERR_NO_HIT)
						g_T_SharedMemory->m_T_ResultLogonId = SW_NOHIT_MD;
					else if(l_i_Result == MORPHOERR_CMDE_ABORTED)
						g_T_SharedMemory->m_T_ResultLogonId = SW_ABORT_MD;
					else if(l_i_Result == (MORPHOERR_INTERNAL || MORPHOERR_PROTOCOLE || MORPHOERR_CONNECT || MORPHOERR_COM_NOT_OPEN))
					{
						g_T_SharedMemory->m_T_SWState.m_T_ComState	= MSO_COM_ERR;
						g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_ERR;
						g_T_SharedMemory->m_T_ResultLogonId = SW_ERRACT_MD;
					}
					else
					{
						g_T_SharedMemory->m_T_SWState.m_T_ComState	= MSO_COM_OK;
						g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_ERR;
						g_T_SharedMemory->m_T_ResultLogonId = SW_ERRACT_MD;
					}
					
					g_T_SharedMemory->m_b_LogonIdent = FALSE;
					PulseEvent(g_T_LocalMemory.m_h_LogonIdent);
				}
				else if(g_T_SharedMemory->m_b_DataIdent)
				{
					if(l_i_Result == MORPHO_OK)
						g_T_SharedMemory->m_T_ResultDataId = SW_OKHIT_MD;
					else if(l_i_Result == MORPHOERR_NO_HIT)
						g_T_SharedMemory->m_T_ResultDataId = SW_NOHIT_MD;
					else if(l_i_Result == MORPHOERR_CMDE_ABORTED)
						g_T_SharedMemory->m_T_ResultDataId = SW_ABORT_MD;
					else if(l_i_Result == (MORPHOERR_INTERNAL || MORPHOERR_PROTOCOLE || MORPHOERR_CONNECT || MORPHOERR_COM_NOT_OPEN))
					{
						g_T_SharedMemory->m_T_SWState.m_T_ComState	= MSO_COM_ERR;
						g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_ERR;
						g_T_SharedMemory->m_T_ResultDataId = SW_ERRACT_MD;
					}
					else
					{
						g_T_SharedMemory->m_T_SWState.m_T_ComState	= MSO_COM_OK;
						g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_ERR;
						g_T_SharedMemory->m_T_ResultDataId = SW_ERRACT_MD;
					}
					
					g_T_SharedMemory->m_b_DataIdent = FALSE;
					PulseEvent(g_T_LocalMemory.m_h_DataIdent);
				}
				else if(g_T_SharedMemory->m_b_AccessIdent)
				{
					if(l_i_Result == MORPHO_OK)
						g_T_SharedMemory->m_T_ResultAccessId = SW_OKHIT_MD;
					else if(l_i_Result == MORPHOERR_NO_HIT)
						g_T_SharedMemory->m_T_ResultAccessId = SW_NOHIT_MD;
					else if(l_i_Result == MORPHOERR_CMDE_ABORTED)
						g_T_SharedMemory->m_T_ResultAccessId = SW_ABORT_MD;
					else if(l_i_Result == (MORPHOERR_INTERNAL || MORPHOERR_PROTOCOLE || MORPHOERR_CONNECT || MORPHOERR_COM_NOT_OPEN))
					{
						g_T_SharedMemory->m_T_SWState.m_T_ComState	= MSO_COM_ERR;
						g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_ERR;
						g_T_SharedMemory->m_T_ResultAccessId = SW_ERRACT_MD;
					}
					else
					{
						g_T_SharedMemory->m_T_SWState.m_T_ComState	= MSO_COM_OK;
						g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_ERR;
						g_T_SharedMemory->m_T_ResultAccessId = SW_ERRACT_MD;
					}
					
					g_T_SharedMemory->m_b_AccessIdent = FALSE;
					PulseEvent(g_T_LocalMemory.m_h_AccessIdent);
				}
				
				if(g_T_SharedMemory->m_b_AdminIdent || g_T_SharedMemory->m_b_LogonIdent ||\
					g_T_SharedMemory->m_b_AccessIdent || g_T_SharedMemory->m_b_DataIdent)
				{
					SetEvent(g_T_LocalMemory.m_h_WaitIdent);
				}
		}
		}
		__except(EXCEPTION_EXECUTE_HANDLER ){}		
	}while(l_dw_EventRet != WAIT_OBJECT_0);
	return 0;
}

DWORD WINAPI CancelThreadProc
(
 LPVOID lpvParam
 )
{
	HANDLE		l_h_Events[2]	= {NULL};
	DWORD		l_dw_EventRet	= -1;
	
	do
	{
		__try
		{
			if(
				g_T_SharedMemory != NULL &&\
				g_T_HostMemory.m_px_Database != NULL && g_T_HostMemory.m_px_MorphoSmart != NULL &&\
				g_T_HostMemory.m_px_Image != NULL && g_T_HostMemory.m_px_User != NULL
				)
			{
				l_h_Events[0]		= g_T_LocalMemory.m_h_ExistSW;
				l_h_Events[1]		= g_T_LocalMemory.m_h_WaitCancel;
				
				l_dw_EventRet = WaitForMultipleObjects(2,l_h_Events,FALSE,INFINITE);
				
				ResetEvent(g_T_LocalMemory.m_h_WaitCancel);
				
				g_T_SharedMemory->m_b_AccessIdent	= FALSE;
				g_T_SharedMemory->m_b_AdminEnroll	= FALSE;
				g_T_SharedMemory->m_b_DataIdent 	= FALSE;
				g_T_SharedMemory->m_b_AdminIdent	= FALSE;
				g_T_SharedMemory->m_b_LogonIdent	= FALSE;
				
				g_T_SharedMemory->m_T_ResultAccessId = SW_ABORT_MD;
				g_T_SharedMemory->m_T_ResultLogonId  = SW_ABORT_MD;
				g_T_SharedMemory->m_T_ResultAdminId  = SW_ABORT_MD;
				g_T_SharedMemory->m_T_ResultAdminEn  = SW_ABORT_MD;
				g_T_SharedMemory->m_T_ResultDataId	 = SW_ABORT_MD;
				
				PulseEvent(g_T_LocalMemory.m_h_AccessIdent);
				PulseEvent(g_T_LocalMemory.m_h_LogonIdent);
				PulseEvent(g_T_LocalMemory.m_h_DataIdent);
				PulseEvent(g_T_LocalMemory.m_h_AdminIdent);
				PulseEvent(g_T_LocalMemory.m_h_AdminEnroll);
				
				if(g_T_HostMemory.m_px_MorphoSmart != NULL)
					g_T_HostMemory.m_px_MorphoSmart->CancelLiveAcquisition();
				
			}
		}
		__except(EXCEPTION_EXECUTE_HANDLER ){}
	}while(l_dw_EventRet != WAIT_OBJECT_0);
	return 0;
}

VOID SWCreateObject
(
 VOID
 )
{
	g_T_HostMemory.m_px_MorphoSmart 	= new	C_MORPHO_Device();
	g_T_HostMemory.m_px_Database		= new	C_MORPHO_Database();
	g_T_HostMemory.m_px_User			= new	C_MORPHO_User();
	g_T_HostMemory.m_px_Image			= new	C_MORPHO_Image(4);
}

VOID SWDeleteObject
(
 VOID
 )
{
	__try
	{
		SetEvent(g_T_LocalMemory.m_h_WaitCancel);
		WaitForSingleObject(g_T_HostMemory.m_h_HostWaitMsoExit,VI_TIMEOUT/2);
		if(
			g_T_HostMemory.m_px_Database != NULL && g_T_HostMemory.m_px_MorphoSmart != NULL &&\
			g_T_HostMemory.m_px_Image != NULL && g_T_HostMemory.m_px_User != NULL
			)
		{
			delete(g_T_HostMemory.m_px_MorphoSmart);
			delete(g_T_HostMemory.m_px_Database);
			delete(g_T_HostMemory.m_px_User);
			delete(g_T_HostMemory.m_px_Image);
			g_T_HostMemory.m_px_MorphoSmart = NULL;
			g_T_HostMemory.m_px_Database	= NULL;
			g_T_HostMemory.m_px_User		= NULL;
			g_T_HostMemory.m_px_Image		= NULL;
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
}

DWORD WINAPI SWOnThreadProc
(
 LPVOID lpvParam
 )
{
	HANDLE						l_h_Events[2]							= {NULL};
	DWORD						l_dw_EventRet							= -1;
	INT 						l_i_Result								= 0;
	ULONG						l_ul_nbUsedRecord						= 0;
	USHORT						l_us_fieldMaxSize						= 0;
	UCHAR						l_puc_fieldName[MORPHO_FIELD_NAME_LEN]	= {0};
	T_MORPHO_FIELD_ATTRIBUTE	l_uc_fieldAttribute ; 
	
	do
	{
		__try
		{
			l_h_Events[0]		= g_T_LocalMemory.m_h_ExistSW;
			l_h_Events[1]		= g_T_LocalMemory.m_h_WaitOn;
			
			l_dw_EventRet = WaitForMultipleObjects(2,l_h_Events,FALSE,INFINITE);
			
			if(l_dw_EventRet == WAIT_OBJECT_0)
				return 0;
			
			ResetEvent(g_T_LocalMemory.m_h_WaitOn);
			
			SWCreateObject();
			
			if(
				g_T_SharedMemory != NULL &&\
				g_T_HostMemory.m_px_Database != NULL && g_T_HostMemory.m_px_MorphoSmart != NULL &&\
				g_T_HostMemory.m_px_Image != NULL && g_T_HostMemory.m_px_User != NULL
				)
			{
				g_T_SharedMemory->m_i_DataCreateOrNo = VI_DATACREATED_INDEC;
				
				if(g_T_HostMemory.m_px_MorphoSmart == NULL)
					continue;
				
				g_T_HostMemory.m_px_MorphoSmart->CancelLiveAcquisition();
				
				/***************************************Mso Device****************************************/
				if(g_T_HostMemory.m_px_MorphoSmart == NULL)
					continue;
				l_i_Result = g_T_HostMemory.m_px_MorphoSmart->OpenDevice(VI_MSOUSBDEVICE_SERIAL);
				if(l_i_Result == MORPHO_OK)
				{
					g_T_SharedMemory->m_T_SWState.m_T_ComState	= MSO_COM_OK;
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_OK;
				}
				else
				{
					if(g_T_HostMemory.m_px_MorphoSmart == NULL)
						continue;
					l_i_Result = g_T_HostMemory.m_px_MorphoSmart->OpenDevice(VI_MSORS232DEVICE_SERIAL);
					if(l_i_Result == MORPHO_OK)
					{
						g_T_SharedMemory->m_T_SWState.m_T_ComState	= MSO_COM_OK;
						g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_OK;
					}
					else
					{
						g_T_SharedMemory->m_T_SWState.m_T_ComState	= MSO_COM_ERR;
						g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_ERR;
						PulseEvent(g_T_LocalMemory.m_h_SWOn);
						continue;
					}
				}
				
				/***************************************Mso DataBase**************************************/
				//Test existing data base
				if(g_T_HostMemory.m_px_MorphoSmart == NULL || g_T_HostMemory.m_px_Database == NULL)
					continue;
				l_i_Result = g_T_HostMemory.m_px_MorphoSmart->GetDatabase(0, *g_T_HostMemory.m_px_Database);
				if(l_i_Result == MORPHO_OK)
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_OK;
				else if(l_i_Result == MORPHOERR_BASE_NOT_FOUND)
				{
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_NOBASE;
					PulseEvent(g_T_LocalMemory.m_h_SWOn);
					continue;
				}
				else if(l_i_Result == (MORPHOERR_INTERNAL || MORPHOERR_PROTOCOLE || MORPHOERR_CONNECT || MORPHOERR_COM_NOT_OPEN))
				{
					g_T_SharedMemory->m_T_SWState.m_T_ComState	= MSO_COM_ERR;
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_ERR;
					PulseEvent(g_T_LocalMemory.m_h_SWOn);
					continue;
				}
				else
				{
					g_T_SharedMemory->m_T_SWState.m_T_ComState	= MSO_COM_OK;
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_ERR;
					PulseEvent(g_T_LocalMemory.m_h_SWOn);
					continue;
				}
				
				///Test existing User
				if(g_T_HostMemory.m_px_Database == NULL)
					continue;
				l_i_Result = g_T_HostMemory.m_px_Database->GetNbUsedRecord(g_T_HostMemory.m_ul_nbUsedRecord);
				if(l_i_Result == MORPHO_OK)
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_OK;
				else if(l_i_Result == MORPHOERR_BASE_NOT_FOUND)
				{
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_NOBASE;
					PulseEvent(g_T_LocalMemory.m_h_SWOn);
					continue;
				}
				else if(l_i_Result == (MORPHOERR_INTERNAL || MORPHOERR_PROTOCOLE || MORPHOERR_CONNECT || MORPHOERR_COM_NOT_OPEN))
				{
					g_T_SharedMemory->m_T_SWState.m_T_ComState	= MSO_COM_ERR;
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_ERR;
					PulseEvent(g_T_LocalMemory.m_h_SWOn);
					continue;
				}
				else
				{
					g_T_SharedMemory->m_T_SWState.m_T_ComState	= MSO_COM_OK;
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_ERR;
					PulseEvent(g_T_LocalMemory.m_h_SWOn);
					continue;
				}
				
				if(g_T_HostMemory.m_px_Database == NULL)
					continue;
				l_i_Result = g_T_HostMemory.m_px_Database->GetNbFreeRecord(g_T_HostMemory.m_ul_nbFreeRecord);
				if(l_i_Result == MORPHO_OK)
				{
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_OK;
				}
				else if(l_i_Result == MORPHOERR_BASE_NOT_FOUND)
				{
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_NOBASE;
					PulseEvent(g_T_LocalMemory.m_h_SWOn);
					continue;
				}
				else if(l_i_Result == (MORPHOERR_INTERNAL || MORPHOERR_PROTOCOLE || MORPHOERR_CONNECT || MORPHOERR_COM_NOT_OPEN))
				{
					g_T_SharedMemory->m_T_SWState.m_T_ComState	= MSO_COM_ERR;
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_ERR;
					PulseEvent(g_T_LocalMemory.m_h_SWOn);
					continue;
				}
				else
				{
					g_T_SharedMemory->m_T_SWState.m_T_ComState	= MSO_COM_OK;
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_ERR;
					PulseEvent(g_T_LocalMemory.m_h_SWOn);
					continue;
				}
				
				if(g_T_HostMemory.m_px_Database == NULL)
					continue;
				l_i_Result = g_T_HostMemory.m_px_Database->GetNbTotalRecord(g_T_HostMemory.m_ul_nbTotalRecord);
				if(l_i_Result == MORPHO_OK)
				{
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_OK;
				}
				else if(l_i_Result == MORPHOERR_BASE_NOT_FOUND)
				{
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_NOBASE;
					PulseEvent(g_T_LocalMemory.m_h_SWOn);
					continue;
				}
				else if(l_i_Result == (MORPHOERR_INTERNAL || MORPHOERR_PROTOCOLE || MORPHOERR_CONNECT || MORPHOERR_COM_NOT_OPEN))
				{
					g_T_SharedMemory->m_T_SWState.m_T_ComState	= MSO_COM_ERR;
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_ERR;
					PulseEvent(g_T_LocalMemory.m_h_SWOn);
					continue;
				}
				else
				{
					g_T_SharedMemory->m_T_SWState.m_T_ComState	= MSO_COM_OK;
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_ERR;
					PulseEvent(g_T_LocalMemory.m_h_SWOn);
					continue;
				}
				
				//Test DataBase Validité
				if(g_T_HostMemory.m_px_Database == NULL)
					continue;
				l_i_Result = g_T_HostMemory.m_px_Database->GetField
					(	
					1,
					l_uc_fieldAttribute, 
					l_us_fieldMaxSize,
					l_puc_fieldName);
				
				if(l_i_Result == MORPHO_OK)
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_OK;
				else if(l_i_Result == MORPHOERR_BASE_NOT_FOUND)
				{
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_NOBASE;
					PulseEvent(g_T_LocalMemory.m_h_SWOn);
					continue;
				}
				else if(l_i_Result == (MORPHOERR_INTERNAL || MORPHOERR_PROTOCOLE || MORPHOERR_CONNECT || MORPHOERR_COM_NOT_OPEN))
				{
					g_T_SharedMemory->m_T_SWState.m_T_ComState	= MSO_COM_ERR;
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_ERR;
					PulseEvent(g_T_LocalMemory.m_h_SWOn);
					continue;
				}
				else
				{
					g_T_SharedMemory->m_T_SWState.m_T_ComState	= MSO_COM_OK;
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_ERR;
					PulseEvent(g_T_LocalMemory.m_h_SWOn);
					continue;
				}
				
				if(memcmp(l_puc_fieldName,VC_DBVERSION_NAME,sizeof(l_puc_fieldName)) !=0)
				{
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_INVALIDE;
					PulseEvent(g_T_LocalMemory.m_h_SWOn);
					continue;
				}
				
				if(g_T_HostMemory.m_ul_nbFreeRecord == 0)
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_FULL;		
				else if(g_T_HostMemory.m_ul_nbUsedRecord == 0)
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_EMPTY;
				else
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_OK;
				
				PulseEvent(g_T_LocalMemory.m_h_SWOn);
				continue;
		}
		}
		__except(EXCEPTION_EXECUTE_HANDLER ){}
		}while(l_dw_EventRet != WAIT_OBJECT_0);
		return 0;
}

DWORD WINAPI SWOffThreadProc
(
 LPVOID lpvParam
 )
{
	HANDLE		l_h_Events[2]	= {NULL};
	DWORD		l_dw_EventRet	= -1;
	
	do
	{
		__try
		{
			if(
				g_T_SharedMemory != NULL &&\
				g_T_HostMemory.m_px_Database != NULL && g_T_HostMemory.m_px_MorphoSmart != NULL &&\
				g_T_HostMemory.m_px_Image != NULL && g_T_HostMemory.m_px_User != NULL
				)
			{
				
				l_h_Events[0]		= g_T_LocalMemory.m_h_ExistSW;
				l_h_Events[1]		= g_T_LocalMemory.m_h_WaitOff;
				
				l_dw_EventRet = WaitForMultipleObjects(2,l_h_Events,FALSE,INFINITE);
				
				g_T_SharedMemory->m_b_AccessIdent	= FALSE;
				g_T_SharedMemory->m_b_AdminEnroll	= FALSE;
				g_T_SharedMemory->m_b_DataIdent 	= FALSE;
				g_T_SharedMemory->m_b_AdminIdent	= FALSE;
				g_T_SharedMemory->m_b_LogonIdent	= FALSE;
				
				g_T_SharedMemory->m_T_ResultAccessId = SW_ABORT_MD;
				g_T_SharedMemory->m_T_ResultLogonId  = SW_ABORT_MD;
				g_T_SharedMemory->m_T_ResultAdminId  = SW_ABORT_MD;
				g_T_SharedMemory->m_T_ResultAdminEn  = SW_ABORT_MD;
				g_T_SharedMemory->m_T_ResultDataId	 = SW_ABORT_MD;
				
				PulseEvent(g_T_LocalMemory.m_h_AccessIdent);
				PulseEvent(g_T_LocalMemory.m_h_LogonIdent);
				PulseEvent(g_T_LocalMemory.m_h_DataIdent);
				PulseEvent(g_T_LocalMemory.m_h_AdminIdent);
				PulseEvent(g_T_LocalMemory.m_h_AdminEnroll);
				
				//g_T_HostMemory.m_px_MorphoSmart->CancelLiveAcquisition();
				//g_T_HostMemory.m_px_MorphoSmart->CloseDevice();
				
				SWDeleteObject();
				
				g_T_SharedMemory->m_i_DataCreateOrNo = 0;
				SetEvent(g_T_LocalMemory.m_h_SWOff);
				
				if(l_dw_EventRet == WAIT_OBJECT_0)
					return 0;
			}
		}
		__except(EXCEPTION_EXECUTE_HANDLER ){}
	}while(l_dw_EventRet != WAIT_OBJECT_0);
	return 0;
}

DWORD WINAPI UserThreadProc
(
 LPVOID lpvParam
 )
{
	HANDLE		l_h_Events[2]	= {NULL};
	DWORD		l_dw_EventRet	= -1;
	INT 		l_i_Result		= 0;
	
	do
	{
		__try
		{
			if(
				g_T_SharedMemory != NULL &&\
				g_T_HostMemory.m_px_Database != NULL && g_T_HostMemory.m_px_MorphoSmart != NULL &&\
				g_T_HostMemory.m_px_Image != NULL && g_T_HostMemory.m_px_User != NULL
				)
			{
				l_h_Events[0]		= g_T_LocalMemory.m_h_ExistSW;
				l_h_Events[1]		= g_T_LocalMemory.m_h_WaitAdminUser;
				
				l_dw_EventRet = WaitForMultipleObjects(2,l_h_Events,FALSE,INFINITE);
				
				if(l_dw_EventRet == WAIT_OBJECT_0)
					return 0;
				
				if(g_T_HostMemory.m_px_Database == NULL || g_T_HostMemory.m_px_User == NULL)
					continue;
				
				l_i_Result = g_T_HostMemory.m_px_Database->GetUser(VI_USERID_MAX*sizeof(WCHAR),g_T_SharedMemory->m_puc_UserID,*g_T_HostMemory.m_px_User);
				
				if(l_i_Result != MORPHO_OK)
				{
					g_T_SharedMemory->m_T_ResultAdminUser = SW_ERRACT_MD;
					PulseEvent(g_T_LocalMemory.m_h_AdminUser);
					continue;
				}
				
				//Remove User from DataBase
				if(g_T_HostMemory.m_px_User == NULL)
					continue;
				l_i_Result = g_T_HostMemory.m_px_User->DbDelete();
				if(l_i_Result != MORPHO_OK)
				{
					g_T_SharedMemory->m_T_ResultAdminUser = SW_ERRACT_MD;
					PulseEvent(g_T_LocalMemory.m_h_AdminUser);
					continue;
				}
				
				g_T_HostMemory.m_ul_nbFreeRecord++;
				g_T_HostMemory.m_ul_nbUsedRecord--;
				
				if(g_T_HostMemory.m_ul_nbUsedRecord == 0)
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_EMPTY;
				else
					g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_OK;
				
				g_T_SharedMemory->m_T_ResultAdminUser = SW_OKHIT_MD;
				PulseEvent(g_T_LocalMemory.m_h_AdminUser);
				continue;	
			}
		}
		__except(EXCEPTION_EXECUTE_HANDLER ){}
	}while(l_dw_EventRet != WAIT_OBJECT_0);
	return 0;
}


DWORD WINAPI PaintThreadProc
(
 LPVOID lpvParam
 )
{
	HANDLE							l_h_Events[2]			= {NULL};
	DWORD							l_dw_EventRet			= -1;
	CDC 							*l_p_Cdc				= NULL;
	RECT							l_cr_Rect				= {0};
	CRect							l_cr_CRect				= CRect(NULL); 
	
	do
	{	
		__try
		{
			if(
				g_T_SharedMemory != NULL &&\
				g_T_HostMemory.m_px_Database != NULL && g_T_HostMemory.m_px_MorphoSmart != NULL &&\
				g_T_HostMemory.m_px_Image != NULL && g_T_HostMemory.m_px_User != NULL
				)
			{
				l_h_Events[0]		= g_T_LocalMemory.m_h_ExistSW;
				l_h_Events[1]		= g_T_LocalMemory.m_h_WaitPaint;
				
				l_dw_EventRet = WaitForMultipleObjects(2,l_h_Events,FALSE,INFINITE);
				
				if(l_dw_EventRet == WAIT_OBJECT_0)
					return 0;
				
				if(g_T_SharedMemory->m_T_PcData.m_i_CurrentImage >= 1)
				{
					if(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_1 != NULL && ::IsWindow(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_1))
					{
						l_p_Cdc = CDC::FromHandle(::GetDC(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_1));
						::GetClientRect(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_1,&l_cr_Rect);
						l_cr_CRect = CRect(l_cr_Rect);
						g_T_HostMemory.m_px_Image->RefreshViewer(0,l_cr_CRect,l_p_Cdc);
						::ReleaseDC(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_1,l_p_Cdc->m_hDC);		
					}
					
					if(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_4 != NULL && ::IsWindow(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_4))
					{
						l_p_Cdc = CDC::FromHandle(::GetDC(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_4));
						::GetClientRect(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_4,&l_cr_Rect);
						l_cr_CRect = CRect(l_cr_Rect);
						g_T_HostMemory.m_px_Image->RefreshViewer(3,l_cr_CRect,l_p_Cdc);
						::ReleaseDC(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_4,l_p_Cdc->m_hDC);		
					}
				}
				if(g_T_SharedMemory->m_T_PcData.m_i_CurrentImage >= 2)
				{
					if(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_2 != NULL && ::IsWindow(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_2))
					{
						l_p_Cdc = CDC::FromHandle(::GetDC(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_2));
						::GetClientRect(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_2,&l_cr_Rect);
						l_cr_CRect = CRect(l_cr_Rect);
						g_T_HostMemory.m_px_Image->RefreshViewer(1,l_cr_CRect,l_p_Cdc);
						::ReleaseDC(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_2,l_p_Cdc->m_hDC);		
					}
				}
				if(g_T_SharedMemory->m_T_PcData.m_i_CurrentImage >= 3)
				{
					if(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_3 != NULL && ::IsWindow(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_3))
					{
						l_p_Cdc = CDC::FromHandle(::GetDC(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_3));
						::GetClientRect(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_3,&l_cr_Rect);
						l_cr_CRect = CRect(l_cr_Rect);
						g_T_HostMemory.m_px_Image->RefreshViewer(2,l_cr_CRect,l_p_Cdc);
						::ReleaseDC(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_3,l_p_Cdc->m_hDC);		
					}
				}	
			}
		}
		__except(EXCEPTION_EXECUTE_HANDLER ){}
	}while(l_dw_EventRet != WAIT_OBJECT_0);
	return 0;
}

DWORD WINAPI UpdateThreadProc
(
 LPVOID lpvParam
 )
{
	HANDLE			l_h_Events[3]									= {NULL};
	DWORD			l_dw_EventRet									= -1;
	INT 			l_i_Result										= 0;
	UCHAR			l_puc_UserId[VI_USERID_MAX*sizeof(WCHAR)]		= {NULL};
	UCHAR			l_uc_DataField[VI_DBFIELD_MAX*sizeof(WCHAR)]	= {NULL};
	ULONG			l_ul_FieldIndex 								= 0;
	ULONG			l_ul_LenField									= 0;
	
	do
	{
		__try
		{
			if(
				g_T_SharedMemory != NULL &&\
				g_T_HostMemory.m_px_Database != NULL && g_T_HostMemory.m_px_MorphoSmart != NULL &&\
				g_T_HostMemory.m_px_Image != NULL && g_T_HostMemory.m_px_User != NULL
				)
			{
				l_h_Events[0]		= g_T_LocalMemory.m_h_ExistSW;
				l_h_Events[1]		= g_T_LocalMemory.m_h_WaitUpdateAccess;
				l_h_Events[2]		= g_T_LocalMemory.m_h_WaitUpdateAdmin;
				
				l_dw_EventRet = WaitForMultipleObjects(3,l_h_Events,FALSE,INFINITE);
				
				if(l_dw_EventRet == WAIT_OBJECT_0)
					return 0;
				
				if(l_dw_EventRet == WAIT_OBJECT_0 + 1)
				{	
					memcpy(l_puc_UserId,g_T_SharedMemory->m_T_UpdateData.m_pwc_UserId,sizeof(l_puc_UserId));
					
					l_i_Result = g_T_HostMemory.m_px_Database->GetUser
						(
						VI_USERID_MAX*sizeof(WCHAR),
						l_puc_UserId,
						*g_T_HostMemory.m_px_User 
						);
					
					if(l_i_Result != MORPHO_OK)
					{
						g_T_SharedMemory->m_T_ResultAccessUp = SW_ERRACT_MD;
						PulseEvent(g_T_LocalMemory.m_h_AccessUpdate);
						continue;
					}
					
					l_ul_LenField	= VI_DBFIELD_MAX*sizeof(WCHAR);
					l_ul_FieldIndex = g_T_SharedMemory->m_T_UpdateData.m_i_FieldIndex;
					memset(l_uc_DataField,0,sizeof(l_uc_DataField));
					memcpy(l_uc_DataField,g_T_SharedMemory->m_T_UpdateData.m_pwc_Field,sizeof(g_T_SharedMemory->m_T_UpdateData.m_pwc_Field));
					
					l_i_Result = g_T_HostMemory.m_px_User->PutField
						(
						l_ul_FieldIndex,
						l_ul_LenField,
						l_uc_DataField	
						);
					if(l_i_Result != MORPHO_OK)
					{
						g_T_SharedMemory->m_T_ResultAccessUp = SW_ERRACT_MD;
						PulseEvent(g_T_LocalMemory.m_h_AccessUpdate);
						continue;
					}
					
					l_i_Result = g_T_HostMemory.m_px_User->DbUpdatePublicFields();
					
					if(l_i_Result != MORPHO_OK)
					{
						g_T_SharedMemory->m_T_ResultAccessUp = SW_ERRACT_MD;
						PulseEvent(g_T_LocalMemory.m_h_AccessUpdate);
						continue;
					}
					
					g_T_SharedMemory->m_T_ResultAccessUp = SW_OKHIT_MD;
					PulseEvent(g_T_LocalMemory.m_h_AccessUpdate);
					continue;	
				}
				if(l_dw_EventRet == WAIT_OBJECT_0 + 2)
				{	
					memcpy(l_puc_UserId,g_T_SharedMemory->m_T_UpdateData.m_pwc_UserId,sizeof(l_puc_UserId));
					
					l_i_Result = g_T_HostMemory.m_px_Database->GetUser
						(
						VI_USERID_MAX*sizeof(WCHAR),
						l_puc_UserId,
						*g_T_HostMemory.m_px_User
						);
					
					if(l_i_Result != MORPHO_OK)
					{
						g_T_SharedMemory->m_T_ResultAdminUp = SW_ERRACT_MD;
						PulseEvent(g_T_LocalMemory.m_h_AdminUpdate);
						continue;
					}
					
					l_ul_LenField	= VI_DBFIELD_MAX*sizeof(WCHAR);
					
					l_ul_FieldIndex = 2;
					memset(l_uc_DataField,0,sizeof(l_uc_DataField));
					memcpy(l_uc_DataField,g_T_SharedMemory->m_T_UpdateData.m_pwc_Field,sizeof(g_T_SharedMemory->m_T_UpdateData.m_pwc_Field));
					
					l_i_Result = g_T_HostMemory.m_px_User->PutField
						(
						l_ul_FieldIndex,
						l_ul_LenField,
						l_uc_DataField	
						);
					
					if(l_i_Result != MORPHO_OK)
					{
						g_T_SharedMemory->m_T_ResultAdminUp = SW_ERRACT_MD;
						PulseEvent(g_T_LocalMemory.m_h_AdminUpdate);
						continue;
					}
					
					l_i_Result = g_T_HostMemory.m_px_User->DbUpdatePublicFields();
					
					if(l_i_Result != MORPHO_OK)
					{
						g_T_SharedMemory->m_T_ResultAdminUp = SW_ERRACT_MD;
						PulseEvent(g_T_LocalMemory.m_h_AdminUpdate);
						continue;
					}
					
					g_T_SharedMemory->m_T_ResultAdminUp = SW_OKHIT_MD;
					PulseEvent(g_T_LocalMemory.m_h_AdminUpdate);
					continue;
				}
			}
		}
		__except(EXCEPTION_EXECUTE_HANDLER ){}
	}while(l_dw_EventRet != WAIT_OBJECT_0);
	return 0;
}

DWORD WINAPI DbThreadProc
(
 LPVOID lpvParam
 )
{
	HANDLE		l_h_Events[2]								= {NULL};
	DWORD		l_dw_EventRet								= -1;
	INT 		l_i_Result									= 0;
	ULONG		l_ul_indexField 							= 0;
	USHORT		l_ul_lenField								= 0;
	UCHAR		l_puc_dataField[MORPHO_FIELD_NAME_LEN]		= {NULL};
	
	do
	{	
		__try
		{
			if(
				g_T_SharedMemory != NULL &&\
				g_T_HostMemory.m_px_Database != NULL && g_T_HostMemory.m_px_MorphoSmart != NULL &&\
				g_T_HostMemory.m_px_Image != NULL && g_T_HostMemory.m_px_User != NULL
				)
			{
				l_h_Events[0]		= g_T_LocalMemory.m_h_ExistSW;
				l_h_Events[1]		= g_T_LocalMemory.m_h_WaitAdminDb;
				
				l_dw_EventRet = WaitForMultipleObjects(2,l_h_Events,FALSE,INFINITE);
				
				if(l_dw_EventRet == WAIT_OBJECT_0)
					return 0;
				
				if(g_T_SharedMemory->m_b_EraseDel)
				{	
					/*************************Destroy Data Base**************************/
					l_i_Result = g_T_HostMemory.m_px_Database->DbDelete
						(
						C_MORPHO_Database::T_MORPHO_TYPE_DELETION::MORPHO_DESTROY_BASE 
						);
					
					if(l_i_Result == MORPHO_OK)
						g_T_SharedMemory->m_T_SWState.m_T_DbState =  MSO_DB_NOBASE;
					else if(l_i_Result == MORPHOERR_BASE_NOT_FOUND)
						g_T_SharedMemory->m_T_SWState.m_T_DbState =  MSO_DB_NOBASE;
					else if(l_i_Result == (MORPHOERR_INTERNAL || MORPHOERR_PROTOCOLE || MORPHOERR_CONNECT || MORPHOERR_COM_NOT_OPEN))
					{
						g_T_SharedMemory->m_T_SWState.m_T_ComState =  MSO_COM_ERR;
						g_T_SharedMemory->m_T_SWState.m_T_DbState =  MSO_DB_ERR;
						PulseEvent(g_T_LocalMemory.m_h_AdminDb);
						continue;
					}
					else
					{
						g_T_SharedMemory->m_T_SWState.m_T_ComState =  MSO_COM_OK;
						g_T_SharedMemory->m_T_SWState.m_T_DbState =  MSO_DB_ERR;
						PulseEvent(g_T_LocalMemory.m_h_AdminDb);
						continue;
					}
				}
				
				l_ul_lenField = VI_DBFIELD_MAX*sizeof(WCHAR);
				
				/**********************Create Data Base***************************/
				//1er Field 	: Priv Version & PKey
				//Len			: 128
				//Name			: SWSP01
				memset(l_puc_dataField,0,sizeof(l_puc_dataField));
				memcpy(l_puc_dataField,VC_DBVERSION_NAME,MORPHO_FIELD_NAME_LEN);
				
				l_i_Result = g_T_HostMemory.m_px_Database->PutField
					(
					MORPHO_PRIVATE_FIELD, 
					l_ul_lenField,
					l_puc_dataField,
					l_ul_indexField
					);
				
				if(l_i_Result == MORPHO_OK)
					g_T_SharedMemory->m_T_SWState.m_T_DbState =  MSO_DB_NOBASE;
				else if(l_i_Result == MORPHOERR_BASE_NOT_FOUND)
					g_T_SharedMemory->m_T_SWState.m_T_DbState =  MSO_DB_NOBASE;
				else if(l_i_Result == (MORPHOERR_INTERNAL || MORPHOERR_PROTOCOLE || MORPHOERR_CONNECT || MORPHOERR_COM_NOT_OPEN))
				{
					g_T_SharedMemory->m_T_SWState.m_T_ComState =  MSO_COM_ERR;
					g_T_SharedMemory->m_T_SWState.m_T_DbState =  MSO_DB_ERR;
					PulseEvent(g_T_LocalMemory.m_h_AdminDb);
					continue;
				}
				else
				{
					g_T_SharedMemory->m_T_SWState.m_T_ComState =  MSO_COM_OK;
					g_T_SharedMemory->m_T_SWState.m_T_DbState =  MSO_DB_ERR;
					PulseEvent(g_T_LocalMemory.m_h_AdminDb);
					continue;
				}
				
				//2eme Field	: Private encoding key
				//Len			: 128
				//Name			: PLogon
				memset(l_puc_dataField,0,sizeof(l_puc_dataField));
				memcpy(l_puc_dataField,"PLogon",MORPHO_FIELD_NAME_LEN);
				
				l_i_Result = g_T_HostMemory.m_px_Database->PutField
					(
					MORPHO_PUBLIC_FIELD, 
					l_ul_lenField,
					l_puc_dataField,
					l_ul_indexField
					);
				
				if(l_i_Result == MORPHO_OK)
					g_T_SharedMemory->m_T_SWState.m_T_DbState =  MSO_DB_NOBASE;
				else if(l_i_Result == MORPHOERR_BASE_NOT_FOUND)
					g_T_SharedMemory->m_T_SWState.m_T_DbState =  MSO_DB_NOBASE;
				else if(l_i_Result == (MORPHOERR_INTERNAL || MORPHOERR_PROTOCOLE || MORPHOERR_CONNECT || MORPHOERR_COM_NOT_OPEN))
				{
					g_T_SharedMemory->m_T_SWState.m_T_ComState =  MSO_COM_ERR;
					g_T_SharedMemory->m_T_SWState.m_T_DbState =  MSO_DB_ERR;
					PulseEvent(g_T_LocalMemory.m_h_AdminDb);
					continue;
				}
				else
				{
					g_T_SharedMemory->m_T_SWState.m_T_ComState =  MSO_COM_OK;
					g_T_SharedMemory->m_T_SWState.m_T_DbState =  MSO_DB_ERR;
					PulseEvent(g_T_LocalMemory.m_h_AdminDb);
					continue;
				}
				
				//3eme Field	: Public Logon Field
				//Len			: 128
				//Name			: PAPP%d
				for(INT i = 0; i<VI_NBAPPLI_MAX;i++)
				{
					memset(l_puc_dataField,0,sizeof(l_puc_dataField));
					wsprintfA((CHAR *)l_puc_dataField,"PAPP%d",i+1);
					
					l_i_Result = g_T_HostMemory.m_px_Database->PutField
						(
						MORPHO_PUBLIC_FIELD, 
						l_ul_lenField,
						l_puc_dataField,
						l_ul_indexField
						);
					
					if(l_i_Result == MORPHO_OK)
						g_T_SharedMemory->m_T_SWState.m_T_DbState =  MSO_DB_NOBASE;
					else if(l_i_Result == MORPHOERR_BASE_NOT_FOUND)
						g_T_SharedMemory->m_T_SWState.m_T_DbState =  MSO_DB_NOBASE;
					else if(l_i_Result == (MORPHOERR_INTERNAL || MORPHOERR_PROTOCOLE || MORPHOERR_CONNECT || MORPHOERR_COM_NOT_OPEN))
					{
						g_T_SharedMemory->m_T_SWState.m_T_ComState =  MSO_COM_ERR;
						g_T_SharedMemory->m_T_SWState.m_T_DbState =  MSO_DB_ERR;
						PulseEvent(g_T_LocalMemory.m_h_AdminDb);
						continue;
					}
					else
					{
						g_T_SharedMemory->m_T_SWState.m_T_ComState =  MSO_COM_OK;
						g_T_SharedMemory->m_T_SWState.m_T_DbState =  MSO_DB_ERR;
						PulseEvent(g_T_LocalMemory.m_h_AdminDb);
						continue;
					}
				}
				
				l_i_Result = g_T_HostMemory.m_px_Database->DbCreate
					(
					VI_NB_RECORDS,
					VI_NB_FINGERS,
					MORPHO_PK_COMP
					);
				
				if(l_i_Result == MORPHO_OK)
					g_T_SharedMemory->m_T_SWState.m_T_DbState =  MSO_DB_EMPTY;
				else if(l_i_Result == MORPHOERR_BASE_NOT_FOUND)
					g_T_SharedMemory->m_T_SWState.m_T_DbState =  MSO_DB_NOBASE;
				else if(l_i_Result == (MORPHOERR_INTERNAL || MORPHOERR_PROTOCOLE || MORPHOERR_CONNECT || MORPHOERR_COM_NOT_OPEN))
				{
					g_T_SharedMemory->m_T_SWState.m_T_ComState =  MSO_COM_ERR;
					g_T_SharedMemory->m_T_SWState.m_T_DbState =  MSO_DB_ERR;
				}
				else
				{
					g_T_SharedMemory->m_T_SWState.m_T_ComState =  MSO_COM_OK;
					g_T_SharedMemory->m_T_SWState.m_T_DbState =  MSO_DB_ERR;
				}
				PulseEvent(g_T_LocalMemory.m_h_AdminDb);
				continue;
			}
		}
		__except(EXCEPTION_EXECUTE_HANDLER ){}
	}while(l_dw_EventRet != WAIT_OBJECT_0);
	return 0;
}

VOID SWInitImage
(
 VOID
 )
{
	if(g_T_HostMemory.m_px_Image != NULL)
	{
		g_T_HostMemory.m_px_Image->~C_MORPHO_Image();
		g_T_HostMemory.m_px_Image = new C_MORPHO_Image(4);
	}
}

DWORD WINAPI EnrollThreadProc
(
 LPVOID lpvParam
 )
{
	HANDLE		l_h_Events[2]									= {NULL};
	DWORD		l_dw_EventRet									= -1;
	ULONG		l_ul_CallbackMask								= 0;
	INT 		l_i_Result										= 0;
	USHORT		l_ul_lenField									= 0;
	UCHAR		l_puc_dataField[VI_DBFIELD_MAX*sizeof(WCHAR)]	= {NULL};
	UCHAR		l_puc_UserId[VI_USERID_MAX*sizeof(WCHAR)]		= {NULL};
	INT 		l_i_TimerRand									= 0;
	SYSTEMTIME	l_T_Timer										= {NULL};
	BOOL		l_b_ActionOK									= FALSE;
	HWND		l_h_Hwnd										= NULL;
	
	do
	{	
		__try
		{
			if(
				g_T_SharedMemory != NULL &&\
				g_T_HostMemory.m_px_Database != NULL && g_T_HostMemory.m_px_MorphoSmart != NULL &&\
				g_T_HostMemory.m_px_Image != NULL && g_T_HostMemory.m_px_User != NULL
				)
			{
				l_h_Events[0]		= g_T_LocalMemory.m_h_ExistSW;
				l_h_Events[1]		= g_T_LocalMemory.m_h_WaitEnroll;
				
				l_ul_CallbackMask	= MORPHO_CALLBACK_IMAGE_CMD|MORPHO_CALLBACK_ENROLLMENT_CMD|MORPHO_CALLBACK_COMMAND_CMD;
				
				l_dw_EventRet = WaitForMultipleObjects(2,l_h_Events,FALSE,INFINITE);
				
				if(l_dw_EventRet == WAIT_OBJECT_0)
					return 0;	
				
				for(INT j = 0; j<VI_NB_RECORDS;j++)
				{
					memset(l_puc_UserId,0,sizeof(l_puc_UserId));
					
					::GetLocalTime(&l_T_Timer);
					
					l_puc_UserId[0] = l_T_Timer.wMilliseconds;
					l_puc_UserId[1] = l_T_Timer.wSecond;
					l_puc_UserId[2] = l_T_Timer.wMinute;
					l_puc_UserId[3] = l_T_Timer.wHour;
					l_puc_UserId[4] = l_T_Timer.wDay;
					l_puc_UserId[5] = l_T_Timer.wYear;
					
					srand( (unsigned)time( NULL ));
					l_i_TimerRand = rand();
					srand( (unsigned)l_i_TimerRand);
					
					for(INT i = 0; i<VI_USERID_MAX*sizeof(WCHAR)-6; i++)
						l_puc_UserId[i+6] = (INT)(128*rand()/RAND_MAX - 128*rand()/RAND_MAX);
					
					l_i_Result = g_T_HostMemory.m_px_Database->DbQueryFirst
						(
						0,
						VI_USERID_MAX*sizeof(WCHAR),
						l_puc_UserId,								
						*g_T_HostMemory.m_px_User);
					
					if(l_i_Result == MORPHOERR_USER_NOT_FOUND)
					{
						l_b_ActionOK = TRUE;
						break;
					}
				}
				
				if(!l_b_ActionOK)
				{
					memset(l_puc_UserId,0,sizeof(l_puc_UserId));
					for(INT k = 0; k<VI_USERID_MAX*sizeof(WCHAR); k++)
					{
						srand( (unsigned)time( NULL ));
						l_i_TimerRand = rand();
						srand( (unsigned)l_i_TimerRand);
						
						l_puc_UserId[k] = (INT)(128*rand()/RAND_MAX - 128*rand()/RAND_MAX);
					}
					
					l_i_Result = g_T_HostMemory.m_px_Database->DbQueryFirst
						(
						0,
						VI_USERID_MAX*sizeof(WCHAR),
						l_puc_UserId,								
						*g_T_HostMemory.m_px_User
						);
					
					if(l_i_Result == MORPHOERR_USER_NOT_FOUND)
						l_b_ActionOK = TRUE;
				}
				
				if(!l_b_ActionOK)
				{
					g_T_SharedMemory->m_T_ResultAdminEn = SW_ERRACT_MD;
					PulseEvent(g_T_LocalMemory.m_h_AdminEnroll);
					Beep(BEEP_F_ERR,BEEP_D_ERR);
					continue;
				}
				
				l_i_Result = g_T_HostMemory.m_px_Database->GetUser
					(
					VI_USERID_MAX*sizeof(WCHAR),
					l_puc_UserId,								
					*g_T_HostMemory.m_px_User
					);
				
				if(l_i_Result != MORPHO_OK)
				{
					g_T_SharedMemory->m_T_ResultAdminEn = SW_ERRACT_MD;
					PulseEvent(g_T_LocalMemory.m_h_AdminEnroll);
					Beep(BEEP_F_ERR,BEEP_D_ERR);
					continue;
				}
				
				/**********************Create Data Base***************************/
				//1er Field 	: Priv Version & PKey
				//Len			: 128
				//Name			: SWSP01
				l_ul_lenField = sizeof(g_T_SharedMemory->m_T_PcData.m_pwc_UserKey);
				memset(l_puc_dataField,0,sizeof(l_puc_dataField));
				memcpy(l_puc_dataField,g_T_SharedMemory->m_T_PcData.m_pwc_UserKey,sizeof(g_T_SharedMemory->m_T_PcData.m_pwc_UserKey));
				
				l_i_Result = g_T_HostMemory.m_px_User->PutField
					(
					1, 
					l_ul_lenField,
					l_puc_dataField
					);
				
				if(l_i_Result != MORPHO_OK)
				{
					g_T_SharedMemory->m_T_ResultAdminEn = SW_ERRACT_MD;
					PulseEvent(g_T_LocalMemory.m_h_AdminEnroll);
					Beep(BEEP_F_ERR,BEEP_D_ERR);
					continue;
				}
				
				l_ul_lenField = sizeof(g_T_SharedMemory->m_T_PcData.m_pwc_UserLogon);
				memset(l_puc_dataField,0,sizeof(l_puc_dataField));
				memcpy(l_puc_dataField,g_T_SharedMemory->m_T_PcData.m_pwc_UserLogon,sizeof(g_T_SharedMemory->m_T_PcData.m_pwc_UserLogon));
				
				l_i_Result = g_T_HostMemory.m_px_User->PutField
					(
					2, 
					l_ul_lenField,
					l_puc_dataField
					);
				
				if(l_i_Result != MORPHO_OK)
				{
					g_T_SharedMemory->m_T_ResultAdminEn = SW_ERRACT_MD;
					PulseEvent(g_T_LocalMemory.m_h_AdminEnroll);
					Beep(BEEP_F_ERR,BEEP_D_ERR);
					continue;
				}
				
				l_b_ActionOK = TRUE;
				
				l_ul_lenField = VI_DBFIELD_MAX*sizeof(WCHAR);
				memset(l_puc_dataField,0,sizeof(l_puc_dataField));
				memcpy(l_puc_dataField,g_T_SharedMemory->m_T_PcData.m_pwc_Field,sizeof(g_T_SharedMemory->m_T_PcData.m_pwc_Field));
				
				for(INT i = 0; i<VI_NBAPPLI_MAX;i++)
				{				
					l_i_Result = g_T_HostMemory.m_px_User->PutField
						(
						i+3, 
						l_ul_lenField,
						l_puc_dataField
						);
					if(l_i_Result != MORPHO_OK)
						l_b_ActionOK = FALSE;
				}
				
				if(!l_b_ActionOK)
				{
					g_T_SharedMemory->m_T_ResultAdminEn = SW_ERRACT_MD;
					PulseEvent(g_T_LocalMemory.m_h_AdminEnroll);
					Beep(BEEP_F_ERR,BEEP_D_ERR);
					continue;
				}
				
				g_T_SharedMemory->m_T_PcData.m_i_CurrentImage = 1;
				
				SWInitImage();
				
				l_i_Result = g_T_HostMemory.m_px_User->Enroll
					(
					VS_TIMEOUT,
					VI_NB_FINGERS-1,
					MORPHO_PK_COMP,
					l_ul_CallbackMask,
					Enroll_Callback,
					NULL
					);
				
				g_T_SharedMemory->m_T_PcData.m_i_CurrentImage = 0;
				g_T_SharedMemory->m_b_AdminEnroll = FALSE;
				
				//priority for Enroll and set the data after
				if(l_i_Result == MORPHO_OK)
				{
					g_T_HostMemory.m_ul_nbFreeRecord--;
					g_T_HostMemory.m_ul_nbUsedRecord++;
					
					if(g_T_HostMemory.m_ul_nbFreeRecord == 0)
						g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_FULL;
					else
						g_T_SharedMemory->m_T_SWState.m_T_DbState = MSO_DB_OK;
					
					g_T_SharedMemory->m_T_ResultAdminEn = SW_OKHIT_MD;
					PulseEvent(g_T_LocalMemory.m_h_AdminEnroll);
					Beep(BEEP_F_OK,BEEP_D_OK);
					continue;
				}
				else if(l_i_Result == MORPHOERR_CMDE_ABORTED)
				{
					g_T_SharedMemory->m_T_ResultAdminEn = SW_ABORT_MD;
					PulseEvent(g_T_LocalMemory.m_h_AdminEnroll);
					Beep(BEEP_F_SHORT,BEEP_D_SHORT);
					continue;
				}
				else
				{
					g_T_SharedMemory->m_T_ResultAdminEn = SW_ERRACT_MD;
					PulseEvent(g_T_LocalMemory.m_h_AdminEnroll);
					Beep(BEEP_F_ERR,BEEP_D_ERR);
					continue;
				}
			}
		}
		__except(EXCEPTION_EXECUTE_HANDLER ){}
	}while(l_dw_EventRet != WAIT_OBJECT_0);
	return 0;
}


INT Enroll_Callback
(	 
 PVOID						i_pv_context,
 T_MORPHO_CALLBACK_COMMAND	i_i_command,
 PVOID						i_pv_param	
 )
{ 
	RECT							l_cr_Rect;
	CRect							l_cr_CRect; 
	BOOL							l_b_ActionOk		= FALSE;
	CDC 							*l_p_Cdc			= NULL;
	PUC 							l_puc_EnrollmentCmd = NULL;
	T_MORPHO_CALLBACK_IMAGE_STATUS	l_x_ImageStructure	= {NULL};
	
	__try
	{
		if(g_T_HostMemory.m_px_Image != NULL && g_T_SharedMemory != NULL)
		{
			/*********************Asynchronous Position Messages******************/
			if (i_i_command == MORPHO_CALLBACK_COMMAND_CMD)
			{
				switch(*(PI)i_pv_param)
				{
				case MORPHO_REMOVE_FINGER:
					{
						if(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1 != NULL && ::IsWindow(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1))
							::SendMessage(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1,WM_SETTEXT,0,(LPARAM)_T(VC_MSG_REMOVEFINGER));
						
						Beep(BEEP_F_SHORT,BEEP_D_SHORT);
						break;
					}
				case MORPHO_MOVE_NO_FINGER:
					{
						if(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1 != NULL && ::IsWindow(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1))
							::SendMessage(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1,WM_SETTEXT,0,(LPARAM)_T(""));
						
						break;
					}
				case MORPHO_LATENT:
					{
						if(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1 != NULL && ::IsWindow(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1))
							::SendMessage(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1,WM_SETTEXT,0,(LPARAM)_T(VC_MSG_LATENT));
						
						break;
					}
				case MORPHO_MOVE_FINGER_UP:
					{
						if(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1 != NULL && ::IsWindow(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1))
							::SendMessage(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1,WM_SETTEXT,0,(LPARAM)_T(VC_MSG_MOVEUP));
						
						break;
					}
				case MORPHO_MOVE_FINGER_DOWN:
					{
						if(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1 != NULL && ::IsWindow(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1))
							::SendMessage(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1,WM_SETTEXT,0,(LPARAM)_T(VC_MSG_MOVEDOWN));
						
						break;
					}
				case MORPHO_MOVE_FINGER_LEFT:
					{
						if(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1 != NULL && ::IsWindow(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1))
							::SendMessage(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1,WM_SETTEXT,0,(LPARAM)_T(VC_MSG_MOVELEFT));
						
						break;
					}
				case MORPHO_MOVE_FINGER_RIGHT:
					{
						if(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1 != NULL && ::IsWindow(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1))
							::SendMessage(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1,WM_SETTEXT,0,(LPARAM)_T(VC_MSG_MOVERIGHT));
						
						break;
					}
				case MORPHO_PRESS_FINGER_HARDER:
					{
						if(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1 != NULL && ::IsWindow(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1))
							::SendMessage(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1,WM_SETTEXT,0,(LPARAM)_T(VC_MSG_PRESSHEADER));
						
						break;
					}
					if(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1 != NULL && ::IsWindow(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1))
						::UpdateWindow(g_T_SharedMemory->m_T_PcData.m_h_hwndText_1);
				}
			}
			
			/*****************Asynchronous Command Messages*********************/	  
			if (i_i_command == MORPHO_CALLBACK_ENROLLMENT_CMD)
			{
				l_puc_EnrollmentCmd = (PUC)i_pv_param;		
				switch (l_puc_EnrollmentCmd[0])
				{
				case 1:
					switch (l_puc_EnrollmentCmd[2])
					{
					case 1:
						{
							if(g_T_SharedMemory->m_T_PcData.m_h_hwndText_2 != NULL && ::IsWindow(g_T_SharedMemory->m_T_PcData.m_h_hwndText_2))
							{
								g_T_SharedMemory->m_T_PcData.m_i_CurrentImage = 1;
								::SendMessage(g_T_SharedMemory->m_T_PcData.m_h_hwndText_2,WM_SETTEXT,0,(LPARAM)_T(VC_MSG_CAPTURE_1));
							}
							break;
						}
					case 2:
						{
							if(g_T_SharedMemory->m_T_PcData.m_h_hwndText_2 != NULL && ::IsWindow(g_T_SharedMemory->m_T_PcData.m_h_hwndText_2))
							{
								g_T_SharedMemory->m_T_PcData.m_i_CurrentImage = 2;
								::SendMessage(g_T_SharedMemory->m_T_PcData.m_h_hwndText_2,WM_SETTEXT,0,(LPARAM)_T(VC_MSG_CAPTURE_2));
							}
							break;
						}
					case 3:
						{
							if(g_T_SharedMemory->m_T_PcData.m_h_hwndText_2 != NULL && ::IsWindow(g_T_SharedMemory->m_T_PcData.m_h_hwndText_2))
							{
								g_T_SharedMemory->m_T_PcData.m_i_CurrentImage = 3;
								::SendMessage(g_T_SharedMemory->m_T_PcData.m_h_hwndText_2,WM_SETTEXT,0,(LPARAM)_T(VC_MSG_CAPTURE_3));	
							}
							break;
						}
						if(g_T_SharedMemory->m_T_PcData.m_h_hwndText_2 != NULL && ::IsWindow(g_T_SharedMemory->m_T_PcData.m_h_hwndText_2))
							::UpdateWindow(g_T_SharedMemory->m_T_PcData.m_h_hwndText_2);
					}
					break;			
				}					
			}
			
			/**************************Asynchronous Images***********************/
			if (i_i_command == MORPHO_CALLBACK_IMAGE_CMD)
			{
				memcpy(&l_x_ImageStructure.m_x_ImageHeader, (T_MORPHO_IMAGE_HEADER*)i_pv_param, sizeof(T_MORPHO_IMAGE_HEADER) );
				l_x_ImageStructure.m_puc_Image = (PUC)i_pv_param+sizeof(T_MORPHO_IMAGE_HEADER);
				
				if(g_T_SharedMemory->m_T_PcData.m_i_CurrentImage == 1)
				{
					if(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_1 != NULL && ::IsWindow(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_1))
					{
						l_p_Cdc = CDC::FromHandle(::GetDC(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_1));	
						::GetClientRect(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_1,&l_cr_Rect);
						l_cr_CRect = CRect(l_cr_Rect);
						
						g_T_HostMemory.m_px_Image->SetImage(	
							0,
							l_x_ImageStructure, 
							0,
							l_p_Cdc,
							l_cr_CRect
							);
						::ReleaseDC(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_1,l_p_Cdc->m_hDC);
					}
				}
				else if(g_T_SharedMemory->m_T_PcData.m_i_CurrentImage == 2)
				{
					if(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_2 != NULL && ::IsWindow(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_2))
					{
						l_p_Cdc = CDC::FromHandle(::GetDC(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_2));
						::GetClientRect(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_2,&l_cr_Rect);
						l_cr_CRect = CRect(l_cr_Rect);
						
						g_T_HostMemory.m_px_Image->SetImage(	
							1,
							l_x_ImageStructure, 
							0,
							l_p_Cdc,
							l_cr_CRect
							);
						::ReleaseDC(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_2,l_p_Cdc->m_hDC);
					}
				}
				else
				{
					if(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_3 != NULL && ::IsWindow(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_3))
					{
						l_p_Cdc = CDC::FromHandle(::GetDC(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_3));
						::GetClientRect(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_3,&l_cr_Rect);
						l_cr_CRect = CRect(l_cr_Rect);
						
						g_T_HostMemory.m_px_Image->SetImage(	
							2,
							l_x_ImageStructure, 
							0,
							l_p_Cdc,
							l_cr_CRect
							);
						::ReleaseDC(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_3,l_p_Cdc->m_hDC);
					}
				}
				
				if(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_4 != NULL && ::IsWindow(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_4))
				{
					l_p_Cdc = CDC::FromHandle(::GetDC(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_4));
					::GetClientRect(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_4,&l_cr_Rect);
					l_cr_CRect = CRect(l_cr_Rect);
					
					g_T_HostMemory.m_px_Image->SetImage(	
						3,
						l_x_ImageStructure, 
						0,
						l_p_Cdc,
						l_cr_CRect
						);
					::ReleaseDC(g_T_SharedMemory->m_T_PcData.m_h_hwndImage_4,l_p_Cdc->m_hDC);
				}
			}
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER ){}
	return 0;
}
