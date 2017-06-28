/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jul 25 09:23:34 2003
 */
/* Compiler settings for W:\PC\Outils\SW Product Suite\SW Data\SWData_DLL\src\SWData.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __SWData_i_h__
#define __SWData_i_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDLSWData_FWD_DEFINED__
#define __IDLSWData_FWD_DEFINED__
typedef interface IDLSWData IDLSWData;
#endif 	/* __IDLSWData_FWD_DEFINED__ */


#ifndef __DLLSWData_FWD_DEFINED__
#define __DLLSWData_FWD_DEFINED__

#ifdef __cplusplus
typedef class DLLSWData DLLSWData;
#else
typedef struct DLLSWData DLLSWData;
#endif /* __cplusplus */

#endif 	/* __DLLSWData_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IDLSWData_INTERFACE_DEFINED__
#define __IDLSWData_INTERFACE_DEFINED__

/* interface IDLSWData */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IDLSWData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8AB81E71-CB2F-11D3-8D3B-AC2F34F1FA3C")
    IDLSWData : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IDLSWDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDLSWData __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDLSWData __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDLSWData __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDLSWData __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDLSWData __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDLSWData __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDLSWData __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IDLSWDataVtbl;

    interface IDLSWData
    {
        CONST_VTBL struct IDLSWDataVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDLSWData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDLSWData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDLSWData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDLSWData_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDLSWData_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDLSWData_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDLSWData_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDLSWData_INTERFACE_DEFINED__ */



#ifndef __DLSWDataLib_LIBRARY_DEFINED__
#define __DLSWDataLib_LIBRARY_DEFINED__

/* library DLSWDataLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_DLSWDataLib;

EXTERN_C const CLSID CLSID_DLLSWData;

#ifdef __cplusplus

class DECLSPEC_UUID("8AB81E72-CB2F-11D3-8D3B-AC2F34F1FA3C")
DLLSWData;
#endif
#endif /* __DLSWDataLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
