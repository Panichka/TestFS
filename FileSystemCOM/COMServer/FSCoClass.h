#ifndef __vfs__COMInterfaceImpl_h__
#define __vfs__COMInterfaceImpl_h__

#include "FSInterface.h"

class FileSystem : public IFileSystem
{
public:
	FileSystem() = default;
   FileSystem(const FileSystem&) = delete;
   void operator=(const FileSystem&) = delete;
	virtual ~FileSystem() = default;

   // IUnknown methods
   STDMETHOD(QueryInterface)(REFIID riid, LPVOID *ppv) override;
   STDMETHOD_(ULONG, AddRef)() override;
   STDMETHOD_(ULONG, Release)() override;

	// IFileSystem methods
   STDMETHOD(Create)(LPCSTR inPath, LPVOID outHandle) override;
   STDMETHOD(Open)(LPVOID inHandle) override;
   STDMETHOD(Close)(LPVOID inHandle) override;
   STDMETHOD(Delete)(LPVOID inHandle) override;

   STDMETHOD(Find)(LPCSTR inPath, LPVOID outHandle) override;

   STDMETHOD(List)(LPCSTR inPath, LPCSTR* outEntries) override;

   STDMETHOD(GetSize)(LPCSTR inPath, ULONG* outEntrySize) override;

   STDMETHOD(Read)(LPVOID inHandle, LPVOID outBuffer, ULONG size) override;
   STDMETHOD(Write)(LPVOID inHandle, const LPVOID outBuffer, ULONG size) override;

private:
   ULONG m_refCounter;
};

#endif // __vfs__COMInterfaceImpl_h__
