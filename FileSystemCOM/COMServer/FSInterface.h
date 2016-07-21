#ifndef __vfs__FSInterface_h__
#define __vfs__FSInterface_h__

struct IFileSystem : IUnknown
{
	STDMETHOD(CreateFile)(BSTR inPath)PURE;
   STDMETHOD(CreateDirectory)(BSTR inPath)PURE;
	STDMETHOD(Delete)(BSTR inPath)PURE;

	STDMETHOD(Exists)(BSTR inPath)PURE;
	
	STDMETHOD(List)(BSTR inPath, SAFEARR_BSTR outEntities)PURE;

	STDMETHOD(GetSize)(BSTR inPath, ULONG* outEntitySize)PURE;

	STDMETHOD(Read)(BSTR inPath, BYTE_SIZEDARR outBuffer)PURE;
	STDMETHOD(Write)(BSTR inPath, BYTE_SIZEDARR inBuffer)PURE;
};

#endif // __vfs__FSInterface_h__