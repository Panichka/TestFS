

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Tue Jul 19 16:00:44 2016
 */
/* Compiler settings for COMServer.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
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

#ifndef __COMServer_h_h__
#define __COMServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IFileSystem_FWD_DEFINED__
#define __IFileSystem_FWD_DEFINED__
typedef interface IFileSystem IFileSystem;

#endif 	/* __IFileSystem_FWD_DEFINED__ */


#ifndef __FileSystem_FWD_DEFINED__
#define __FileSystem_FWD_DEFINED__

#ifdef __cplusplus
typedef class FileSystem FileSystem;
#else
typedef struct FileSystem FileSystem;
#endif /* __cplusplus */

#endif 	/* __FileSystem_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IFileSystem_INTERFACE_DEFINED__
#define __IFileSystem_INTERFACE_DEFINED__

/* interface IFileSystem */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IFileSystem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5B26AF8D-EF23-4f1d-A742-3CC4C2F28980")
    IFileSystem : public IUnknown
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IFileSystemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFileSystem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFileSystem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFileSystem * This);
        
        END_INTERFACE
    } IFileSystemVtbl;

    interface IFileSystem
    {
        CONST_VTBL struct IFileSystemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFileSystem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFileSystem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFileSystem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFileSystem_INTERFACE_DEFINED__ */



#ifndef __COMServerLib_LIBRARY_DEFINED__
#define __COMServerLib_LIBRARY_DEFINED__

/* library COMServerLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_COMServerLib;

EXTERN_C const CLSID CLSID_FileSystem;

#ifdef __cplusplus

class DECLSPEC_UUID("438B8FDC-7DB8-4a3b-9814-931FDAB531DA")
FileSystem;
#endif
#endif /* __COMServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


