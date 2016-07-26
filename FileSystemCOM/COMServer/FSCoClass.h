#ifndef __vfs__COMInterfaceImpl_h__
#define __vfs__COMInterfaceImpl_h__

#include "FSInterface.h"
#include "ReferenceCounter.h"

namespace NFileSystem
{
   struct Controller;
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
   STDMETHOD(CreateFile)(BSTR inPath)override;
   STDMETHOD(CreateDirectory)(BSTR inPath)override;
   STDMETHOD(Delete)(BSTR inPath) override;

   STDMETHOD(Exists)(BSTR inPath) override;

   STDMETHOD(List)(BSTR inPath, SAFEARR_BSTR outEntities) override;

   STDMETHOD(GetSize)(BSTR inPath, ULONG* outEntitySize) override;

   STDMETHOD(Read)(BSTR inPath, ULONG Count, BYTE_SIZEDARR* outBuffer) override;
   STDMETHOD(Write)(BSTR inPath, BYTE_SIZEDARR inBuffer) override;

private:
   NCOMServer::ReferenceCounter m_refCounter;
   std::unique_ptr<NFileSystem::Controller> m_controller;
};

#endif // __vfs__COMInterfaceImpl_h__
