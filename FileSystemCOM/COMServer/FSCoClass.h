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
   STDMETHOD(CreateFile)(LPOLESTR inPath)override;
   STDMETHOD(CreateDirectory)(LPOLESTR inPath)override;
   STDMETHOD(Delete)(ULONG inHandle) override;

   STDMETHOD(Exists)(LPOLESTR inPath) override;

   STDMETHOD(List)(ULONG inHandle, SAFEARR_BSTR outEntities) override;

   STDMETHOD(GetSize)(ULONG inHandle, ULONG* outEntitySize) override;

   STDMETHOD(Read)(ULONG inHandle, ULONG Count, BYTE_SIZEDARR* outBuffer) override;
   STDMETHOD(Write)(ULONG inHandle, BYTE_SIZEDARR inBuffer) override;

private:
   NCOMServer::ReferenceCounter m_refCounter;
   std::unique_ptr<NFileSystem::Controller> m_controller;
};

#endif // __vfs__COMInterfaceImpl_h__
