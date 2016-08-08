#ifndef __vfs__FSInterface_h__
#define __vfs__FSInterface_h__

struct IFileSystem : IUnknown
{
   STDMETHOD(Root)(ULONGLONG* outRootHandle) const = 0;

	STDMETHOD(CreateFile)(ULONGLONG inLocationHandle, LPCOLESTR inName, ULONGLONG* outCreatedHandle) = 0;
   STDMETHOD(CreateDirectory)(ULONGLONG inLocationHandle, LPCOLESTR inName, ULONGLONG* outCreatedHandle) = 0;
	STDMETHOD(Delete)(ULONGLONG inHandle) = 0;

	STDMETHOD(Exists)(ULONGLONG inLocationHandle, LPCOLESTR inName, BOOL* outResult) const = 0;
   //! @note allocates memory for outEntities
   //! @retval E_INVALIDARG if outEntities is not null
	STDMETHOD(List)(ULONGLONG inHandle, LPOLESTR** outEntities, ULONGLONG* outCount) const = 0;

   //! @note allocates memory for outName
   //! @retval E_INVALIDARG if outName is not null
   STDMETHOD(GetName)(ULONGLONG inHandle, LPOLESTR* outName) const = 0;
	STDMETHOD(GetSize)(ULONGLONG inHandle, ULONGLONG* outEntitySize) const = 0;
   STDMETHOD(GetHandle)(ULONGLONG inLocationHandle, LPCOLESTR inName, ULONGLONG* outHandle) const = 0;

   STDMETHOD(IsDirectory)(ULONGLONG inHandle, BOOL* outIsDir) const = 0;
   STDMETHOD(IsDirectoryByName)(ULONGLONG inLocationHandle, LPCOLESTR inName, BOOL* outIsDir) const = 0;

   STDMETHOD(IsFile)(ULONGLONG inHandle, BOOL* outIsDir) const = 0;
   STDMETHOD(IsFileByName)(ULONGLONG inLocationHandle, LPCOLESTR inName, BOOL* outIsDir) const = 0;

	STDMETHOD(Read)(ULONGLONG inHandle, ULONGLONG inCount, ULONGLONG inFromPosition, LPBYTE outBuffer, ULONGLONG* outReadCount) const = 0;
	STDMETHOD(Write)(ULONGLONG inHandle, ULONGLONG inCount, ULONGLONG inToPosition, LPBYTE inBuffer) = 0;
};

#endif // __vfs__FSInterface_h__