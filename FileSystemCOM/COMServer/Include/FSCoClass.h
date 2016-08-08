#ifndef __vfs__COMInterfaceImpl_h__
#define __vfs__COMInterfaceImpl_h__

#include "ReferenceCounter.h"
#include "FSInterface.h"
#include "FSController.h"

class FileSystem : public IFileSystem
{
public:
	FileSystem();
   FileSystem(const FileSystem&) = delete;
   void operator=(const FileSystem&) = delete;
	virtual ~FileSystem() = default;

   // IUnknown methods
   STDMETHOD(QueryInterface)(REFIID riid, LPVOID *ppv) override;
   STDMETHOD_(ULONG, AddRef)() override;
   STDMETHOD_(ULONG, Release)() override;

	// IFileSystem methods
   STDMETHOD(Root)(ULONGLONG* outRootHandle) const override;
   STDMETHOD(CreateFile)(ULONGLONG inLocationHandle, LPCOLESTR inName, ULONGLONG* outCreatedHandle) override;
   STDMETHOD(CreateDirectory)(ULONGLONG inLocationHandle, LPCOLESTR inName, ULONGLONG* outCreatedHandle) override;
   STDMETHOD(Delete)(ULONGLONG inHandle) override;

   STDMETHOD(Exists)(ULONGLONG inLocationHandle, LPCOLESTR inName, BOOL* outResult) const override;
   STDMETHOD(List)(ULONGLONG inHandle, LPOLESTR** outEntities, ULONGLONG* outCount) const override;

   STDMETHOD(GetName)(ULONGLONG inHandle, LPOLESTR* outName) const override;
   STDMETHOD(GetSize)(ULONGLONG inHandle, ULONGLONG* outEntitySize) const override;
   STDMETHOD(GetHandle)(ULONGLONG inLocationHandle, LPCOLESTR inName, ULONGLONG* outHandle) const override;

   STDMETHOD(IsDirectory)(ULONGLONG inHandle, BOOL* outIsDir) const override;
   STDMETHOD(IsDirectoryByName)(ULONGLONG inLocationHandle, LPCOLESTR inName, BOOL* outIsDir) const override;

   STDMETHOD(IsFile)(ULONGLONG inHandle, BOOL* outIsDir) const override;
   STDMETHOD(IsFileByName)(ULONGLONG inLocationHandle, LPCOLESTR inName, BOOL* outIsDir) const override;

   STDMETHOD(Read)(ULONGLONG inHandle, ULONGLONG inCount, ULONGLONG inFromPosition, LPBYTE outBuffer, ULONGLONG* outReadCount) const override;
   STDMETHOD(Write)(ULONGLONG inHandle, ULONGLONG inCount, ULONGLONG inToPosition, LPBYTE inBuffer) override;

private:
   NFileSystem::EntityHandle Convert(ULONGLONG comHandle) const;
   ULONGLONG Convert(NFileSystem::EntityHandle implHandle) const;

   NCOMServer::ReferenceCounter m_refCounter;
   NFileSystem::Controller m_controller;
};

#endif // __vfs__COMInterfaceImpl_h__
