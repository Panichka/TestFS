#ifndef __vfs__FSInterface_h__
#define __vfs__FSInterface_h__

struct IFileSystem : IUnknown
{
   STDMETHOD(Root)(ULONG* outRootHandle) const = 0;

	STDMETHOD(CreateFile)(ULONG inLocationHandle, LPCOLESTR inName, ULONG* outCreatedHandle) = 0;
   STDMETHOD(CreateDirectory)(ULONG inLocationHandle, LPCOLESTR inName, ULONG* outCreatedHandle) = 0;
	STDMETHOD(Delete)(ULONG inHandle) = 0;

	STDMETHOD(Exists)(ULONG inLocationHandle, LPCOLESTR inName, BOOL* outResult) const = 0;
   //! @note allocates memory for outEntities
   //! @retval E_INVALIDARG if outEntities is not null
	STDMETHOD(List)(ULONG inHandle, LPOLESTR** outEntities, ULONG* outCount) const = 0;

   //! @note allocates memory for outName
   //! @retval E_INVALIDARG if outName is not null
   STDMETHOD(GetName)(ULONG inHandle, LPOLESTR* outName) const = 0;
	STDMETHOD(GetSize)(ULONG inHandle, ULONG* outEntitySize) const = 0;
   STDMETHOD(GetHandle)(ULONG inLocationHandle, LPCOLESTR inName, ULONG* outHandle) const = 0;

   STDMETHOD(IsDirectory)(ULONG inHandle, BOOL* outIsDir) const = 0;
   STDMETHOD(IsDirectoryByName)(ULONG inLocationHandle, LPCOLESTR inName, BOOL* outIsDir) const = 0;

   STDMETHOD(IsFile)(ULONG inHandle, BOOL* outIsDir) const = 0;
   STDMETHOD(IsFileByName)(ULONG inLocationHandle, LPCOLESTR inName, BOOL* outIsDir) const = 0;

	STDMETHOD(Read)(ULONG inHandle, ULONG inCount, ULONG inFromPosition, LPBYTE outBuffer, ULONG* outReadCount) const = 0;
	STDMETHOD(Write)(ULONG inHandle, ULONG inCount, ULONG inToPosition, LPBYTE inBuffer) = 0;
};

#endif // __vfs__FSInterface_h__