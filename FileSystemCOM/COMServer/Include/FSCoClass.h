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
   STDMETHOD(Root)(ULONG* outRootHandle) const override;
   STDMETHOD(CreateFile)(ULONG inLocationHandle, LPCOLESTR inName, ULONG* outCreatedHandle) override;
   STDMETHOD(CreateDirectory)(ULONG inLocationHandle, LPCOLESTR inName, ULONG* outCreatedHandle) override;
   STDMETHOD(Delete)(ULONG inHandle) override;

   STDMETHOD(Exists)(ULONG inLocationHandle, LPCOLESTR inName, BOOL* outResult) const override;
   STDMETHOD(List)(ULONG inHandle, LPOLESTR* outEntities, ULONG* outCount) const override;

   STDMETHOD(GetName)(ULONG inHandle, LPOLESTR outName) const override;
   STDMETHOD(GetSize)(ULONG inHandle, ULONG* outEntitySize) const override;
   STDMETHOD(GetHandle)(ULONG inLocationHandle, LPCOLESTR inName, ULONG* outHandle) const override;

   STDMETHOD(IsDirectory)(ULONG inHandle, BOOL* outIsDir) const override;
   STDMETHOD(IsDirectoryByName)(ULONG inLocationHandle, LPCOLESTR inName, BOOL* outIsDir) const override;

   STDMETHOD(IsFile)(ULONG inHandle, BOOL* outIsDir) const override;
   STDMETHOD(IsFileByName)(ULONG inLocationHandle, LPCOLESTR inName, BOOL* outIsDir) const override;

   STDMETHOD(Read)(ULONG inHandle, ULONG inCount, ULONG inFromPosition, LPBYTE outBuffer, ULONG* outReadCount) const override;
   STDMETHOD(Write)(ULONG inHandle, ULONG inCount, ULONG inToPosition, LPBYTE inBuffer) override;

private:
   NFileSystem::EntityHandle Convert(ULONG comHandle) const;
   ULONG Convert(NFileSystem::EntityHandle implHandle) const;

   NCOMServer::ReferenceCounter m_refCounter;
   NFileSystem::Controller m_controller;
};

#endif // __vfs__COMInterfaceImpl_h__
