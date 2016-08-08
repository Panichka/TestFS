#ifndef __vfs__FSInterface_h__
#define __vfs__FSInterface_h__

//! @note All pointers must point to a valid memory address
//! if another is not specified in method notes
//!
//! All methods return S_OK if completed successfully.
//! If fail, error code may be E_INVALIDARG if invalid argument supplied for a method.
//! Also, it may return some of customer defined error codes:
//! 0x20000000 | 0, if an internal error occure
//! 0x20000000 | 1, if attempted to create entity that already exists with another cathegory (file or dir)
//! 0x20000000 | 2, if requested entity doesn't exists
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