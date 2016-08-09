

/* this ALWAYS GENERATED file contains the proxy stub code */


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

#if !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "COMServer_h.h"

#define TYPE_FORMAT_STRING_SIZE   43                                
#define PROC_FORMAT_STRING_SIZE   691                               
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _COMServer_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } COMServer_MIDL_TYPE_FORMAT_STRING;

typedef struct _COMServer_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } COMServer_MIDL_PROC_FORMAT_STRING;

typedef struct _COMServer_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } COMServer_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const COMServer_MIDL_TYPE_FORMAT_STRING COMServer__MIDL_TypeFormatString;
extern const COMServer_MIDL_PROC_FORMAT_STRING COMServer__MIDL_ProcFormatString;
extern const COMServer_MIDL_EXPR_FORMAT_STRING COMServer__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IFileSystem_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IFileSystem_ProxyInfo;



#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const COMServer_MIDL_PROC_FORMAT_STRING COMServer__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure Root */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 10 */	NdrFcShort( 0x24 ),	/* 36 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 16 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter outRootHandle */

/* 24 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 26 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 28 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 30 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 32 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 34 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateFile */

/* 36 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 38 */	NdrFcLong( 0x0 ),	/* 0 */
/* 42 */	NdrFcShort( 0x4 ),	/* 4 */
/* 44 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 46 */	NdrFcShort( 0x10 ),	/* 16 */
/* 48 */	NdrFcShort( 0x2c ),	/* 44 */
/* 50 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 52 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x0 ),	/* 0 */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter inLocationHandle */

/* 60 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 62 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 64 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter inName */

/* 66 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 68 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 70 */	NdrFcShort( 0x8 ),	/* Type Offset=8 */

	/* Parameter outCreatedHandle */

/* 72 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 74 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 76 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 78 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 80 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 82 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateDirectory */

/* 84 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 86 */	NdrFcLong( 0x0 ),	/* 0 */
/* 90 */	NdrFcShort( 0x5 ),	/* 5 */
/* 92 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 94 */	NdrFcShort( 0x10 ),	/* 16 */
/* 96 */	NdrFcShort( 0x2c ),	/* 44 */
/* 98 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 100 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 102 */	NdrFcShort( 0x0 ),	/* 0 */
/* 104 */	NdrFcShort( 0x0 ),	/* 0 */
/* 106 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter inLocationHandle */

/* 108 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 110 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 112 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter inName */

/* 114 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 116 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 118 */	NdrFcShort( 0x8 ),	/* Type Offset=8 */

	/* Parameter outCreatedHandle */

/* 120 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 122 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 124 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 126 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 128 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 130 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Delete */

/* 132 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 134 */	NdrFcLong( 0x0 ),	/* 0 */
/* 138 */	NdrFcShort( 0x6 ),	/* 6 */
/* 140 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 142 */	NdrFcShort( 0x10 ),	/* 16 */
/* 144 */	NdrFcShort( 0x8 ),	/* 8 */
/* 146 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 148 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 150 */	NdrFcShort( 0x0 ),	/* 0 */
/* 152 */	NdrFcShort( 0x0 ),	/* 0 */
/* 154 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter inHandle */

/* 156 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 158 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 160 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 162 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 164 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 166 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Exists */

/* 168 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 170 */	NdrFcLong( 0x0 ),	/* 0 */
/* 174 */	NdrFcShort( 0x7 ),	/* 7 */
/* 176 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 178 */	NdrFcShort( 0x10 ),	/* 16 */
/* 180 */	NdrFcShort( 0x24 ),	/* 36 */
/* 182 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 184 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 186 */	NdrFcShort( 0x0 ),	/* 0 */
/* 188 */	NdrFcShort( 0x0 ),	/* 0 */
/* 190 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter inLocationHandle */

/* 192 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 194 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 196 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter inName */

/* 198 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 200 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 202 */	NdrFcShort( 0x8 ),	/* Type Offset=8 */

	/* Parameter outResult */

/* 204 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 206 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 208 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 210 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 212 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 214 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure List */

/* 216 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 218 */	NdrFcLong( 0x0 ),	/* 0 */
/* 222 */	NdrFcShort( 0x8 ),	/* 8 */
/* 224 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 226 */	NdrFcShort( 0x10 ),	/* 16 */
/* 228 */	NdrFcShort( 0x2c ),	/* 44 */
/* 230 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 232 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 234 */	NdrFcShort( 0x0 ),	/* 0 */
/* 236 */	NdrFcShort( 0x0 ),	/* 0 */
/* 238 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter inHandle */

/* 240 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 242 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 244 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter outEntities */

/* 246 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 248 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 250 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter outCount */

/* 252 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 254 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 256 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 258 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 260 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 262 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetName */

/* 264 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 266 */	NdrFcLong( 0x0 ),	/* 0 */
/* 270 */	NdrFcShort( 0x9 ),	/* 9 */
/* 272 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 274 */	NdrFcShort( 0x10 ),	/* 16 */
/* 276 */	NdrFcShort( 0x8 ),	/* 8 */
/* 278 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 280 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 282 */	NdrFcShort( 0x0 ),	/* 0 */
/* 284 */	NdrFcShort( 0x0 ),	/* 0 */
/* 286 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter inHandle */

/* 288 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 290 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 292 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter outName */

/* 294 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 296 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 298 */	NdrFcShort( 0x1e ),	/* Type Offset=30 */

	/* Return value */

/* 300 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 302 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 304 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetSize */

/* 306 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 308 */	NdrFcLong( 0x0 ),	/* 0 */
/* 312 */	NdrFcShort( 0xa ),	/* 10 */
/* 314 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 316 */	NdrFcShort( 0x10 ),	/* 16 */
/* 318 */	NdrFcShort( 0x2c ),	/* 44 */
/* 320 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 322 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 324 */	NdrFcShort( 0x0 ),	/* 0 */
/* 326 */	NdrFcShort( 0x0 ),	/* 0 */
/* 328 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter inHandle */

/* 330 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 332 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 334 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter outEntitySize */

/* 336 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 338 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 340 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 342 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 344 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 346 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetHandle */

/* 348 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 350 */	NdrFcLong( 0x0 ),	/* 0 */
/* 354 */	NdrFcShort( 0xb ),	/* 11 */
/* 356 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 358 */	NdrFcShort( 0x10 ),	/* 16 */
/* 360 */	NdrFcShort( 0x2c ),	/* 44 */
/* 362 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 364 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 366 */	NdrFcShort( 0x0 ),	/* 0 */
/* 368 */	NdrFcShort( 0x0 ),	/* 0 */
/* 370 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter inLocationHandle */

/* 372 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 374 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 376 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter inName */

/* 378 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 380 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 382 */	NdrFcShort( 0x8 ),	/* Type Offset=8 */

	/* Parameter outHandle */

/* 384 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 386 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 388 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 390 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 392 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 394 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IsDirectory */

/* 396 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 398 */	NdrFcLong( 0x0 ),	/* 0 */
/* 402 */	NdrFcShort( 0xc ),	/* 12 */
/* 404 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 406 */	NdrFcShort( 0x10 ),	/* 16 */
/* 408 */	NdrFcShort( 0x24 ),	/* 36 */
/* 410 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 412 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 414 */	NdrFcShort( 0x0 ),	/* 0 */
/* 416 */	NdrFcShort( 0x0 ),	/* 0 */
/* 418 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter inHandle */

/* 420 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 422 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 424 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter outIsDir */

/* 426 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 428 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 430 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 432 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 434 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 436 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IsDirectoryByName */

/* 438 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 440 */	NdrFcLong( 0x0 ),	/* 0 */
/* 444 */	NdrFcShort( 0xd ),	/* 13 */
/* 446 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 448 */	NdrFcShort( 0x10 ),	/* 16 */
/* 450 */	NdrFcShort( 0x24 ),	/* 36 */
/* 452 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 454 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 456 */	NdrFcShort( 0x0 ),	/* 0 */
/* 458 */	NdrFcShort( 0x0 ),	/* 0 */
/* 460 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter inLocationHandle */

/* 462 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 464 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 466 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter inName */

/* 468 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 470 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 472 */	NdrFcShort( 0x8 ),	/* Type Offset=8 */

	/* Parameter outIsDir */

/* 474 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 476 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 478 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 480 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 482 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 484 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IsFile */

/* 486 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 488 */	NdrFcLong( 0x0 ),	/* 0 */
/* 492 */	NdrFcShort( 0xe ),	/* 14 */
/* 494 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 496 */	NdrFcShort( 0x10 ),	/* 16 */
/* 498 */	NdrFcShort( 0x24 ),	/* 36 */
/* 500 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 502 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 504 */	NdrFcShort( 0x0 ),	/* 0 */
/* 506 */	NdrFcShort( 0x0 ),	/* 0 */
/* 508 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter inHandle */

/* 510 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 512 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 514 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter outIsFile */

/* 516 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 518 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 520 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 522 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 524 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 526 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IsFileByName */

/* 528 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 530 */	NdrFcLong( 0x0 ),	/* 0 */
/* 534 */	NdrFcShort( 0xf ),	/* 15 */
/* 536 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 538 */	NdrFcShort( 0x10 ),	/* 16 */
/* 540 */	NdrFcShort( 0x24 ),	/* 36 */
/* 542 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 544 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 546 */	NdrFcShort( 0x0 ),	/* 0 */
/* 548 */	NdrFcShort( 0x0 ),	/* 0 */
/* 550 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter inLocationHandle */

/* 552 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 554 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 556 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter inName */

/* 558 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 560 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 562 */	NdrFcShort( 0x8 ),	/* Type Offset=8 */

	/* Parameter outIsFile */

/* 564 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 566 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 568 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 570 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 572 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 574 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Read */

/* 576 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 578 */	NdrFcLong( 0x0 ),	/* 0 */
/* 582 */	NdrFcShort( 0x10 ),	/* 16 */
/* 584 */	NdrFcShort( 0x28 ),	/* x86 Stack size/offset = 40 */
/* 586 */	NdrFcShort( 0x30 ),	/* 48 */
/* 588 */	NdrFcShort( 0x45 ),	/* 69 */
/* 590 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x6,		/* 6 */
/* 592 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 594 */	NdrFcShort( 0x0 ),	/* 0 */
/* 596 */	NdrFcShort( 0x0 ),	/* 0 */
/* 598 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter inHandle */

/* 600 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 602 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 604 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter inCount */

/* 606 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 608 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 610 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter inFromPosition */

/* 612 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 614 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 616 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter outBuffer */

/* 618 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 620 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 622 */	0x1,		/* FC_BYTE */
			0x0,		/* 0 */

	/* Parameter outReadCount */

/* 624 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 626 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 628 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 630 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 632 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 634 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Write */

/* 636 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 638 */	NdrFcLong( 0x0 ),	/* 0 */
/* 642 */	NdrFcShort( 0x11 ),	/* 17 */
/* 644 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 646 */	NdrFcShort( 0x49 ),	/* 73 */
/* 648 */	NdrFcShort( 0x8 ),	/* 8 */
/* 650 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x5,		/* 5 */
/* 652 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 654 */	NdrFcShort( 0x0 ),	/* 0 */
/* 656 */	NdrFcShort( 0x0 ),	/* 0 */
/* 658 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter inHandle */

/* 660 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 662 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 664 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter inCount */

/* 666 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 668 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 670 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter inToPosition */

/* 672 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 674 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 676 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter inBuffer */

/* 678 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 680 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 682 */	0x1,		/* FC_BYTE */
			0x0,		/* 0 */

	/* Return value */

/* 684 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 686 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 688 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const COMServer_MIDL_TYPE_FORMAT_STRING COMServer__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/*  4 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/*  6 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/*  8 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 10 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 12 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 14 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 16 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 18 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 20 */	NdrFcShort( 0x2 ),	/* Offset= 2 (22) */
/* 22 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 24 */	NdrFcShort( 0x2 ),	/* Offset= 2 (26) */
/* 26 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 28 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 30 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 32 */	NdrFcShort( 0xfffa ),	/* Offset= -6 (26) */
/* 34 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 36 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 38 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 40 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */

			0x0
        }
    };


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IFileSystem, ver. 0.0,
   GUID={0x5B26AF8D,0xEF23,0x4f1d,{0xA7,0x42,0x3C,0xC4,0xC2,0xF2,0x89,0x80}} */

#pragma code_seg(".orpc")
static const unsigned short IFileSystem_FormatStringOffsetTable[] =
    {
    0,
    36,
    84,
    132,
    168,
    216,
    264,
    306,
    348,
    396,
    438,
    486,
    528,
    576,
    636
    };

static const MIDL_STUBLESS_PROXY_INFO IFileSystem_ProxyInfo =
    {
    &Object_StubDesc,
    COMServer__MIDL_ProcFormatString.Format,
    &IFileSystem_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IFileSystem_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    COMServer__MIDL_ProcFormatString.Format,
    &IFileSystem_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(18) _IFileSystemProxyVtbl = 
{
    &IFileSystem_ProxyInfo,
    &IID_IFileSystem,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IFileSystem::Root */ ,
    (void *) (INT_PTR) -1 /* IFileSystem::CreateFile */ ,
    (void *) (INT_PTR) -1 /* IFileSystem::CreateDirectory */ ,
    (void *) (INT_PTR) -1 /* IFileSystem::Delete */ ,
    (void *) (INT_PTR) -1 /* IFileSystem::Exists */ ,
    (void *) (INT_PTR) -1 /* IFileSystem::List */ ,
    (void *) (INT_PTR) -1 /* IFileSystem::GetName */ ,
    (void *) (INT_PTR) -1 /* IFileSystem::GetSize */ ,
    (void *) (INT_PTR) -1 /* IFileSystem::GetHandle */ ,
    (void *) (INT_PTR) -1 /* IFileSystem::IsDirectory */ ,
    (void *) (INT_PTR) -1 /* IFileSystem::IsDirectoryByName */ ,
    (void *) (INT_PTR) -1 /* IFileSystem::IsFile */ ,
    (void *) (INT_PTR) -1 /* IFileSystem::IsFileByName */ ,
    (void *) (INT_PTR) -1 /* IFileSystem::Read */ ,
    (void *) (INT_PTR) -1 /* IFileSystem::Write */
};

const CInterfaceStubVtbl _IFileSystemStubVtbl =
{
    &IID_IFileSystem,
    &IFileSystem_ServerInfo,
    18,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    COMServer__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x800025b, /* MIDL Version 8.0.603 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _COMServer_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IFileSystemProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _COMServer_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IFileSystemStubVtbl,
    0
};

PCInterfaceName const _COMServer_InterfaceNamesList[] = 
{
    "IFileSystem",
    0
};


#define _COMServer_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _COMServer, pIID, n)

int __stdcall _COMServer_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_COMServer_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo COMServer_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _COMServer_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _COMServer_StubVtblList,
    (const PCInterfaceName * ) & _COMServer_InterfaceNamesList,
    0, /* no delegation */
    & _COMServer_IID_Lookup, 
    1,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_) */

