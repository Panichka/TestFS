#ifndef __vfs__FSInterface_h__
#define __vfs__FSInterface_h__

struct IFileSystem : IUnknown
{
   STDMETHOD(Root)(ULONG* outRootHandle) const = 0;

	STDMETHOD(CreateFile)(ULONG inLocationHandle, LPOLESTR inName, ULONG* outCreatedHandle) = 0;
   STDMETHOD(CreateDirectory)(ULONG inLocationHandle, LPOLESTR inName, ULONG* outCreatedHandle) = 0;
	STDMETHOD(Delete)(ULONG inHandle) = 0;

	STDMETHOD(Exists)(ULONG inLocationHandle, LPOLESTR inName, BOOL* outResult) const = 0;
	STDMETHOD(List)(ULONG inHandle, SAFEARR_BSTR outEntities) const = 0;

   STDMETHOD(GetName)(ULONG inHandle, LPOLESTR outName) const = 0;
	STDMETHOD(GetSize)(ULONG inHandle, ULONG* outEntitySize) const = 0;

	STDMETHOD(Read)(ULONG inHandle, ULONG Count, BYTE_SIZEDARR* outBuffer) const = 0;
	STDMETHOD(Write)(ULONG inHandle, BYTE_SIZEDARR inBuffer) = 0;
};

#endif // __vfs__FSInterface_h__