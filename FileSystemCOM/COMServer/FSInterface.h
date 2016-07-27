#ifndef __vfs__FSInterface_h__
#define __vfs__FSInterface_h__

struct IFileSystem : IUnknown
{
	STDMETHOD(CreateFile)(LPOLESTR inPath)PURE;
   STDMETHOD(CreateDirectory)(LPOLESTR inPath)PURE;
	STDMETHOD(Delete)(ULONG inHandle)PURE;

	STDMETHOD(Exists)(LPOLESTR inPath)PURE;
	
	STDMETHOD(List)(ULONG inHandle, SAFEARR_BSTR outEntities)PURE;

	STDMETHOD(GetSize)(ULONG inHandle, ULONG* outEntitySize)PURE;

	STDMETHOD(Read)(ULONG inHandle, ULONG Count, BYTE_SIZEDARR* outBuffer)PURE;
	STDMETHOD(Write)(ULONG inHandle, BYTE_SIZEDARR inBuffer)PURE;
};

#endif // __vfs__FSInterface_h__