#ifndef __vfs__COMInterfaceImpl_h__
#define __vfs__COMInterfaceImpl_h__

#include "FSInterface.h"
#include "ReferenceCounter.h"

namespace NFileSystem
{
   class Controller;
}

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
   STDMETHOD(CreateFile)(ULONG inLocationHandle, LPOLESTR inName, ULONG* outCreatedHandle) override;
   STDMETHOD(CreateDirectory)(ULONG inLocationHandle, LPOLESTR inName, ULONG* outCreatedHandle) override;
   STDMETHOD(Delete)(ULONG inHandle) override;

   STDMETHOD(Exists)(ULONG inLocationHandle, LPOLESTR inName, BOOL* outResult) const override;
   STDMETHOD(List)(ULONG inHandle, SAFEARR_BSTR outEntities) const override;

   STDMETHOD(GetName)(ULONG inHandle, LPOLESTR outName) const override;
   STDMETHOD(GetSize)(ULONG inHandle, ULONG* outEntitySize) const override;

   STDMETHOD(Read)(ULONG inHandle, ULONG inCount, ULONG inFromPosition, BYTE_SIZEDARR* outBuffer) const override;
   STDMETHOD(Write)(ULONG inHandle, ULONG inToPosition, BYTE_SIZEDARR inBuffer) override;

private:
   NCOMServer::ReferenceCounter m_refCounter;
   std::unique_ptr<NFileSystem::Controller> m_controller;
};

#endif // __vfs__COMInterfaceImpl_h__
