

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Tue Aug 09 13:44:54 2016
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
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Root( 
            /* [in] */ ULONGLONG *outRootHandle) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CreateFile( 
            /* [in] */ ULONGLONG inLocationHandle,
            /* [in] */ LPCOLESTR inName,
            /* [retval][out] */ ULONGLONG *outCreatedHandle) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CreateDirectory( 
            /* [in] */ ULONGLONG inLocationHandle,
            /* [in] */ LPCOLESTR inName,
            /* [retval][out] */ ULONGLONG *outCreatedHandle) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Delete( 
            /* [in] */ ULONGLONG inHandle) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Exists( 
            /* [in] */ ULONGLONG inLocationHandle,
            /* [in] */ LPCOLESTR inName,
            /* [retval][out] */ BOOL *outResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE List( 
            /* [in] */ ULONGLONG inHandle,
            /* [out] */ LPOLESTR **outEntities,
            /* [out] */ ULONGLONG *outCount) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetName( 
            /* [in] */ ULONGLONG inHandle,
            /* [retval][out] */ LPOLESTR *outName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetSize( 
            /* [in] */ ULONGLONG inHandle,
            /* [retval][out] */ ULONGLONG *outEntitySize) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetHandle( 
            /* [in] */ ULONGLONG inLocationHandle,
            /* [in] */ LPCOLESTR inName,
            /* [retval][out] */ ULONGLONG *outHandle) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE IsDirectory( 
            /* [in] */ ULONGLONG inHandle,
            /* [retval][out] */ BOOL *outIsDir) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE IsDirectoryByName( 
            /* [in] */ ULONGLONG inLocationHandle,
            /* [in] */ LPCOLESTR inName,
            /* [retval][out] */ BOOL *outIsDir) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE IsFile( 
            /* [in] */ ULONGLONG inHandle,
            /* [retval][out] */ BOOL *outIsFile) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE IsFileByName( 
            /* [in] */ ULONGLONG inLocationHandle,
            /* [in] */ LPCOLESTR inName,
            /* [retval][out] */ BOOL *outIsFile) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Read( 
            /* [in] */ ULONGLONG inHandle,
            /* [in] */ ULONGLONG inCount,
            /* [in] */ ULONGLONG inFromPosition,
            /* [out] */ BYTE *outBuffer,
            /* [out] */ ULONGLONG *outReadCount) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Write( 
            /* [in] */ ULONGLONG inHandle,
            /* [in] */ ULONGLONG inCount,
            /* [in] */ ULONGLONG inToPosition,
            /* [in] */ BYTE *inBuffer) = 0;
        
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
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Root )( 
            IFileSystem * This,
            /* [in] */ ULONGLONG *outRootHandle);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CreateFile )( 
            IFileSystem * This,
            /* [in] */ ULONGLONG inLocationHandle,
            /* [in] */ LPCOLESTR inName,
            /* [retval][out] */ ULONGLONG *outCreatedHandle);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CreateDirectory )( 
            IFileSystem * This,
            /* [in] */ ULONGLONG inLocationHandle,
            /* [in] */ LPCOLESTR inName,
            /* [retval][out] */ ULONGLONG *outCreatedHandle);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Delete )( 
            IFileSystem * This,
            /* [in] */ ULONGLONG inHandle);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Exists )( 
            IFileSystem * This,
            /* [in] */ ULONGLONG inLocationHandle,
            /* [in] */ LPCOLESTR inName,
            /* [retval][out] */ BOOL *outResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *List )( 
            IFileSystem * This,
            /* [in] */ ULONGLONG inHandle,
            /* [out] */ LPOLESTR **outEntities,
            /* [out] */ ULONGLONG *outCount);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IFileSystem * This,
            /* [in] */ ULONGLONG inHandle,
            /* [retval][out] */ LPOLESTR *outName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetSize )( 
            IFileSystem * This,
            /* [in] */ ULONGLONG inHandle,
            /* [retval][out] */ ULONGLONG *outEntitySize);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetHandle )( 
            IFileSystem * This,
            /* [in] */ ULONGLONG inLocationHandle,
            /* [in] */ LPCOLESTR inName,
            /* [retval][out] */ ULONGLONG *outHandle);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *IsDirectory )( 
            IFileSystem * This,
            /* [in] */ ULONGLONG inHandle,
            /* [retval][out] */ BOOL *outIsDir);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *IsDirectoryByName )( 
            IFileSystem * This,
            /* [in] */ ULONGLONG inLocationHandle,
            /* [in] */ LPCOLESTR inName,
            /* [retval][out] */ BOOL *outIsDir);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *IsFile )( 
            IFileSystem * This,
            /* [in] */ ULONGLONG inHandle,
            /* [retval][out] */ BOOL *outIsFile);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *IsFileByName )( 
            IFileSystem * This,
            /* [in] */ ULONGLONG inLocationHandle,
            /* [in] */ LPCOLESTR inName,
            /* [retval][out] */ BOOL *outIsFile);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Read )( 
            IFileSystem * This,
            /* [in] */ ULONGLONG inHandle,
            /* [in] */ ULONGLONG inCount,
            /* [in] */ ULONGLONG inFromPosition,
            /* [out] */ BYTE *outBuffer,
            /* [out] */ ULONGLONG *outReadCount);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Write )( 
            IFileSystem * This,
            /* [in] */ ULONGLONG inHandle,
            /* [in] */ ULONGLONG inCount,
            /* [in] */ ULONGLONG inToPosition,
            /* [in] */ BYTE *inBuffer);
        
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


#define IFileSystem_Root(This,outRootHandle)	\
    ( (This)->lpVtbl -> Root(This,outRootHandle) ) 

#define IFileSystem_CreateFile(This,inLocationHandle,inName,outCreatedHandle)	\
    ( (This)->lpVtbl -> CreateFile(This,inLocationHandle,inName,outCreatedHandle) ) 

#define IFileSystem_CreateDirectory(This,inLocationHandle,inName,outCreatedHandle)	\
    ( (This)->lpVtbl -> CreateDirectory(This,inLocationHandle,inName,outCreatedHandle) ) 

#define IFileSystem_Delete(This,inHandle)	\
    ( (This)->lpVtbl -> Delete(This,inHandle) ) 

#define IFileSystem_Exists(This,inLocationHandle,inName,outResult)	\
    ( (This)->lpVtbl -> Exists(This,inLocationHandle,inName,outResult) ) 

#define IFileSystem_List(This,inHandle,outEntities,outCount)	\
    ( (This)->lpVtbl -> List(This,inHandle,outEntities,outCount) ) 

#define IFileSystem_GetName(This,inHandle,outName)	\
    ( (This)->lpVtbl -> GetName(This,inHandle,outName) ) 

#define IFileSystem_GetSize(This,inHandle,outEntitySize)	\
    ( (This)->lpVtbl -> GetSize(This,inHandle,outEntitySize) ) 

#define IFileSystem_GetHandle(This,inLocationHandle,inName,outHandle)	\
    ( (This)->lpVtbl -> GetHandle(This,inLocationHandle,inName,outHandle) ) 

#define IFileSystem_IsDirectory(This,inHandle,outIsDir)	\
    ( (This)->lpVtbl -> IsDirectory(This,inHandle,outIsDir) ) 

#define IFileSystem_IsDirectoryByName(This,inLocationHandle,inName,outIsDir)	\
    ( (This)->lpVtbl -> IsDirectoryByName(This,inLocationHandle,inName,outIsDir) ) 

#define IFileSystem_IsFile(This,inHandle,outIsFile)	\
    ( (This)->lpVtbl -> IsFile(This,inHandle,outIsFile) ) 

#define IFileSystem_IsFileByName(This,inLocationHandle,inName,outIsFile)	\
    ( (This)->lpVtbl -> IsFileByName(This,inLocationHandle,inName,outIsFile) ) 

#define IFileSystem_Read(This,inHandle,inCount,inFromPosition,outBuffer,outReadCount)	\
    ( (This)->lpVtbl -> Read(This,inHandle,inCount,inFromPosition,outBuffer,outReadCount) ) 

#define IFileSystem_Write(This,inHandle,inCount,inToPosition,inBuffer)	\
    ( (This)->lpVtbl -> Write(This,inHandle,inCount,inToPosition,inBuffer) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFileSystem_INTERFACE_DEFINED__ */



#ifndef __COMServerLib_LIBRARY_DEFINED__
#define __COMServerLib_LIBRARY_DEFINED__

/* library COMServerLib */
/* [version][uuid] */ 


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


