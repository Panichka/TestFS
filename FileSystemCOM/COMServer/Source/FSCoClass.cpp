#include <functional>
#include <climits>

#include <windows.h>
#include <comdef.h>

#include "GUIDs.h"
#include "FSCoClass.h"
#include "FSController.h"
#include "FSExceptions.h"
#include <boost/optional.hpp>

FileSystem::FileSystem()
   : m_refCounter(1u)
   , m_controller(std::make_unique<NFileSystem::Controller>())
{}

template <typename Interface>
boost::optional<Interface*> getInterface(FileSystem& object, REFIID iid, REFIID riid)
{
   if (IsEqualIID(iid, riid))
      return static_cast<Interface *>(&object);

   return boost::none;
}

STDMETHODIMP FileSystem::QueryInterface(REFIID riid, LPVOID *ppv)
{
   if (nullptr == ppv || nullptr != *ppv)
      return E_INVALIDARG;

   boost::optional<void*> result;
   if (
      (result = getInterface<IUnknown>(*this, IID_IUnknown, riid)) ||
      (result = getInterface<IFileSystem>(*this, IID_FS, riid))
      )
   {
      *ppv = result.get();
      AddRef();
      return S_OK;
   }

   return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) FileSystem::AddRef()
{
   return ++m_refCounter;
}

STDMETHODIMP_(ULONG) FileSystem::Release()
{
   auto counterValue = --m_refCounter;
   if (0u == counterValue)
      delete this;

   return counterValue;
}

namespace
{
   ULONG CastIfNoOverflow(size_t value)
   {
      if (value > ULONG_MAX)
         throw std::overflow_error("msg is not used");

      return static_cast<ULONG>(value);
   }

   struct InterfaceError
   {
      explicit InterfaceError(HRESULT code)
         : Code(code)
      {}

      HRESULT Code;
   };

   HRESULT CatchAll(const std::function<void()>& action)
   {
      try
      {
         action();
         return S_OK;
      }
      catch(const InterfaceError& error)
      {
	      return error.Code;
      }
      catch (const NFileSystem::Exception& error)
      {
         using namespace NFileSystem;

         const HRESULT CustomerDefinedError = 0x20000000;
         return CustomerDefinedError | static_cast<uint8_t>(error.Code);
      }
      catch (...)
      {
         return E_FAIL;
      }
   }
}

STDMETHODIMP FileSystem::Root(ULONG* outRootHandle) const
{
   return CatchAll([this, outRootHandle]()
   {
      if (nullptr == outRootHandle)
         throw InterfaceError(E_INVALIDARG);

      *outRootHandle =
         CastIfNoOverflow(m_controller->Root());
   });
}

STDMETHODIMP FileSystem::CreateFile(ULONG inLocationHandle, LPCOLESTR inName, ULONG* outCreatedHandle)
{
   return CatchAll([this, inLocationHandle, inName, outCreatedHandle]()
   {
      if (nullptr == inName || nullptr == outCreatedHandle)
         throw InterfaceError(E_INVALIDARG);

      *outCreatedHandle = 
         m_controller->Create(inLocationHandle, inName, NFileSystem::EntityCategory::File);
   });
}

STDMETHODIMP FileSystem::CreateDirectory(ULONG inLocationHandle, LPCOLESTR inName, ULONG* outCreatedHandle)
{
   return CatchAll([this, inLocationHandle, inName, &outCreatedHandle]()
   {
      if (nullptr == inName || nullptr == outCreatedHandle)
         throw InterfaceError(E_INVALIDARG);

      *outCreatedHandle =
         m_controller->Create(inLocationHandle, inName, NFileSystem::EntityCategory::Directory);
   });
}

STDMETHODIMP FileSystem::Delete(ULONG inHandle)
{
   return CatchAll([this, inHandle]()
   {
      m_controller->Delete(inHandle);
   });
}

STDMETHODIMP FileSystem::Exists(ULONG inLocationHandle, LPCOLESTR inName, BOOL* outResult) const
{
   return CatchAll([this, inLocationHandle, inName, outResult]()
   {
      if (nullptr == inName || nullptr == outResult)
         throw InterfaceError(E_INVALIDARG);

      m_controller->Exists(inLocationHandle, inName);
   });
}

STDMETHODIMP FileSystem::List(ULONG inHandle, SAFEARR_BSTR outEntities) const
{
   return CatchAll([this, inHandle, &outEntities]()
   {
      auto entities = m_controller->List(inHandle);
      
      outEntities.Size = CastIfNoOverflow(entities.size());
      outEntities.aBstr = new wireBSTR[outEntities.Size];
      ULONG index = 0u;
      for (const auto& item : entities)
      {
         auto& current = outEntities.aBstr[index++];
         current->fFlags = 0;
         current->clSize = CastIfNoOverflow(item.length());
         if (0u != current->clSize)
            memcpy(&current->asData, item.data(), sizeof(std::wstring::value_type) * current->clSize);
      }
   });
}

STDMETHODIMP FileSystem::GetName(ULONG inHandle, LPOLESTR outName) const
{
   return CatchAll([this, inHandle, &outName]()
   {
      if (nullptr != outName)
         delete []outName;

      auto name = m_controller->Name(inHandle);
      memcpy(outName, name.c_str(), sizeof(std::wstring::value_type) * name.size());
   });
}

STDMETHODIMP FileSystem::GetSize(ULONG inHandle, ULONG* outEntitySize) const
{
   return CatchAll([this, inHandle, outEntitySize]()
   {
      if (nullptr == outEntitySize)
         throw InterfaceError(E_INVALIDARG);

      *outEntitySize =
         CastIfNoOverflow(m_controller->Size(inHandle));
   });
}

STDMETHODIMP FileSystem::Read(ULONG inHandle, ULONG inCount, ULONG inFromPosition, BYTE_SIZEDARR* outBuffer) const
{
   return CatchAll([this, inHandle, inCount, inFromPosition, &outBuffer]()
   {
      if (0u == inCount)
         return;

      if (nullptr == outBuffer)
         throw InterfaceError(E_INVALIDARG);

      auto readResult = m_controller->Read(inHandle, inCount, inFromPosition);
      if (!readResult.first)
         throw InterfaceError(E_UNEXPECTED);
      
      outBuffer->clSize = CastIfNoOverflow(readResult.second);
      outBuffer->pData = readResult.first.get();
      readResult.first.release();
   });
}

STDMETHODIMP FileSystem::Write(ULONG inHandle, ULONG inToPosition, BYTE_SIZEDARR inBuffer)
{
   return CatchAll([this, inHandle, inToPosition, &inBuffer]()
   {
      if (0u == inBuffer.clSize)
         return;

      if (nullptr == inBuffer.pData)
         throw InterfaceError(E_INVALIDARG);

      m_controller->Write(inHandle, inBuffer.pData, inBuffer.clSize, inToPosition);
   });
}
