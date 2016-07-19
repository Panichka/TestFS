#ifndef __vfs__FSInterface_h__
#define __vfs__FSInterface_h__

#include <windows.h>

struct IFileSystem : IUnknown
{
	STDMETHOD(Create)(LPCSTR inPath, LPVOID outHandle)PURE;
	STDMETHOD(Open)(LPVOID inHandle)PURE;
	STDMETHOD(Close)(LPVOID inHandle)PURE;
	STDMETHOD(Delete)(LPVOID inHandle)PURE;

	STDMETHOD(Find)(LPCSTR inPath, LPVOID outHandle)PURE;
	
	STDMETHOD(List)(LPCSTR inPath, LPCSTR* outEntries)PURE;

	STDMETHOD(GetSize)(LPCSTR inPath, ULONG* outEntrySize)PURE;

	STDMETHOD(Read)(LPVOID inHandle, LPVOID outBuffer, ULONG size)PURE;
	STDMETHOD(Write)(LPVOID inHandle, const LPVOID outBuffer, ULONG size)PURE;
};

#endif // __vfs__FSInterface_h__