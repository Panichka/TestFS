#include <functional>
#include <climits>

#include <windows.h>
#include <comdef.h>

#include "GUIDs.h"
#include "FSCoClass.h"
#include "FSExceptions.h"
#include <boost/optional.hpp>

FileSystem::FileSystem()
   : m_refCounter(1u)
   , m_controller()
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
   template <typename T>
   ULONG SafeCast(T value)
   {
      static_assert(sizeof(std::decay_t<T>) <= sizeof(ULONG), "unsafe conversion");
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

NFileSystem::EntityHandle FileSystem::Convert(ULONG comHandle) const
{
   if(m_controller.Count() <= comHandle)
      throw InterfaceError(E_INVALIDARG);

   auto result = m_controller.Root();
   std::advance(result, comHandle);
   return result;
}

ULONG FileSystem::Convert(NFileSystem::EntityHandle implHandle) const
{
   return SafeCast(std::distance(m_controller.Root(), implHandle));
}

STDMETHODIMP FileSystem::Root(ULONG* outRootHandle) const
{
   return CatchAll([this, outRootHandle]()
   {
      if (nullptr == outRootHandle)
         throw InterfaceError(E_INVALIDARG);

      *outRootHandle = SafeCast(Convert(m_controller.Root()));
   });
}

STDMETHODIMP FileSystem::CreateFile(ULONG inLocationHandle, LPCOLESTR inName, ULONG* outCreatedHandle)
{
   return CatchAll([this, inLocationHandle, inName, outCreatedHandle]()
   {
      if (nullptr == inName || nullptr == outCreatedHandle)
         throw InterfaceError(E_INVALIDARG);

      *outCreatedHandle = 
         Convert(m_controller.Create(Convert(inLocationHandle), inName, NFileSystem::EntityCategory::File));
   });
}

STDMETHODIMP FileSystem::CreateDirectory(ULONG inLocationHandle, LPCOLESTR inName, ULONG* outCreatedHandle)
{
   return CatchAll([this, inLocationHandle, inName, &outCreatedHandle]()
   {
      if (nullptr == inName || nullptr == outCreatedHandle)
         throw InterfaceError(E_INVALIDARG);

      *outCreatedHandle =
         Convert(m_controller.Create(Convert(inLocationHandle), inName, NFileSystem::EntityCategory::Directory));
   });
}

STDMETHODIMP FileSystem::Delete(ULONG inHandle)
{
   return CatchAll([this, inHandle]()
   {
      m_controller.Delete(Convert(inHandle));
   });
}

STDMETHODIMP FileSystem::Exists(ULONG inLocationHandle, LPCOLESTR inName, BOOL* outResult) const
{
   return CatchAll([this, inLocationHandle, inName, outResult]()
   {
      if (nullptr == inName || nullptr == outResult)
         throw InterfaceError(E_INVALIDARG);

      m_controller.Exists(Convert(inLocationHandle), inName);
   });
}

STDMETHODIMP FileSystem::List(ULONG inHandle, LPOLESTR* outEntities, ULONG* outCount) const
{
   return CatchAll([this, inHandle, &outEntities, &outCount]()
   {
      if (nullptr != outEntities || nullptr == outCount)
         throw InterfaceError(E_INVALIDARG);

      auto entities = m_controller.List(Convert(inHandle));

      *outCount = SafeCast(entities.size());
      std::unique_ptr<LPOLESTR[]> namesArray(new LPOLESTR[*outCount]);

      size_t index = 0u;
      for (const auto& item : entities)
      {
         auto nameLength = item.size() + 1;
         namesArray[index] = new std::wstring::value_type[nameLength];
         memcpy(namesArray[index], item.c_str(), sizeof(std::wstring::value_type) * nameLength);
         index++;
      }

      namesArray.release();
   });
}

STDMETHODIMP FileSystem::GetName(ULONG inHandle, LPOLESTR outName) const
{
   return CatchAll([this, inHandle, &outName]()
   {
      if (nullptr != outName)
         throw InterfaceError(E_INVALIDARG);

      auto name = m_controller.Name(Convert(inHandle));
      auto nameLength = name.size() + 1;
      outName = new std::wstring::value_type[nameLength];
      memcpy(outName, name.c_str(), sizeof(std::wstring::value_type) * nameLength);
   });
}

STDMETHODIMP FileSystem::GetSize(ULONG inHandle, ULONG* outEntitySize) const
{
   return CatchAll([this, inHandle, outEntitySize]()
   {
      if (nullptr == outEntitySize)
         throw InterfaceError(E_INVALIDARG);

      *outEntitySize = SafeCast(m_controller.Size(Convert(inHandle)));
   });
}

STDMETHODIMP FileSystem::GetHandle(ULONG inLocationHandle, LPCOLESTR inName, ULONG* outHandle) const
{
   return CatchAll([this, inLocationHandle, inName, &outHandle]()
   {
      if (nullptr == inName || nullptr == outHandle)
         throw InterfaceError(E_INVALIDARG);

      *outHandle = Convert(m_controller.Handle(Convert(inLocationHandle), inName));
   });
}

namespace
{
   template <class ...Args>
   bool CheckArgs(Args... )
   {
      return true;
   }

   template <>
   bool CheckArgs<ULONG, LPCOLESTR>(ULONG, LPCOLESTR inName)
   {
      return nullptr != inName;
   }

   template <class ...Args>
   HRESULT CheckEntityCategory(const NFileSystem::Controller& controller, NFileSystem::EntityCategory ctg, BOOL* result, Args... args)
   {
      return CatchAll([&controller, ctg, result, args...]()
      {
         if (nullptr == result || !CheckArgs(args...))
            throw InterfaceError(E_INVALIDARG);

         *result = ctg == controller.Category(args...) ? TRUE : FALSE;
      });
   }
}

STDMETHODIMP FileSystem::IsDirectory(ULONG inHandle, BOOL* outIsDir) const
{
   return CheckEntityCategory(m_controller, NFileSystem::EntityCategory::Directory, outIsDir, Convert(inHandle));
}

STDMETHODIMP FileSystem::IsDirectoryByName(ULONG inLocationHandle, LPCOLESTR inName, BOOL* outIsDir) const
{
   return CheckEntityCategory(m_controller, NFileSystem::EntityCategory::Directory, outIsDir, Convert(inLocationHandle), inName);
}

STDMETHODIMP FileSystem::IsFile(ULONG inHandle, BOOL* outIsFile) const
{
   return CheckEntityCategory(m_controller, NFileSystem::EntityCategory::File, outIsFile, Convert(inHandle));
}

STDMETHODIMP FileSystem::IsFileByName(ULONG inLocationHandle, LPCOLESTR inName, BOOL* outIsFile) const
{
   return CheckEntityCategory(m_controller, NFileSystem::EntityCategory::File, outIsFile, Convert(inLocationHandle), inName);
}

STDMETHODIMP FileSystem::Read(ULONG inHandle, ULONG inCount, ULONG inFromPosition, LPBYTE outBuffer, ULONG* outReadCount) const
{
   return CatchAll([this, inHandle, inCount, inFromPosition, &outBuffer, &outReadCount]()
   {
      if (0u == inCount)
         return;

      if (nullptr == outBuffer || nullptr == outReadCount)
         throw InterfaceError(E_INVALIDARG);

      auto readResult = m_controller.Read(Convert(inHandle), inCount, inFromPosition);
      if (!readResult.first)
         throw InterfaceError(E_UNEXPECTED);
      
      *outReadCount = SafeCast(readResult.second);
      memcpy(outBuffer, readResult.first.get(), readResult.second);
   });
}

STDMETHODIMP FileSystem::Write(ULONG inHandle, ULONG inCount, ULONG inToPosition, LPBYTE inBuffer)
{
   return CatchAll([this, inHandle, inCount, inToPosition, &inBuffer]()
   {
      if (0u == inCount)
         return;

      if (nullptr == inBuffer)
         throw InterfaceError(E_INVALIDARG);

      m_controller.Write(Convert(inHandle), inBuffer, inCount, inToPosition);
   });
}
