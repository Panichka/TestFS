#include <functional>
#include <climits>

#include <windows.h>
#include <comdef.h>

#include "GUIDs.h"
#include "FSCoClass.h"
#include "FSController.h"
#include "FSExceptions.h"

FileSystem::FileSystem()
   : m_controller(std::make_unique<NFileSystem::Controller>())
{}

STDMETHODIMP FileSystem::QueryInterface(REFIID riid, LPVOID *ppv)
{
	*ppv = nullptr;
	if(IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_FS))
	{
		*ppv = static_cast<IFileSystem*>(this);
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
         switch (error.Code)
         {
         case ErrorCode::InternalError:
         case ErrorCode::AlreadyExists:
         case ErrorCode::DoesNotExists:
         case ErrorCode::IsLocked:
         default:
            return E_FAIL;
         }         
      }
      catch (...)
      {
         return E_FAIL;
      }
   }
}

STDMETHODIMP FileSystem::CreateFile(LPOLESTR inPath)
{
   return CatchAll([this, inPath]()
   {
      m_controller->Create(NFileSystem::Path(inPath), NFileSystem::Entity::Category::File);
   });
}

STDMETHODIMP FileSystem::CreateDirectory(LPOLESTR inPath)
{
   return CatchAll([this, inPath]()
   {
      m_controller->Create(NFileSystem::Path(inPath), NFileSystem::Entity::Category::Directory);
   });
}

STDMETHODIMP FileSystem::Delete(ULONG inHandle)
{
   return CatchAll([this, inHandle]()
   {
      m_controller->Delete(inHandle);
   });
}

STDMETHODIMP FileSystem::Exists(LPOLESTR inPath)
{
   return CatchAll([this, inPath]()
   {
      m_controller->Exists(NFileSystem::Path(inPath));
   });
}

STDMETHODIMP FileSystem::List(ULONG inHandle, SAFEARR_BSTR outEntities)
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

STDMETHODIMP FileSystem::GetSize(ULONG inHandle, ULONG* outEntitySize)
{
   return CatchAll([this, inHandle, outEntitySize]()
   {
      if (nullptr == outEntitySize)
         throw InterfaceError(E_INVALIDARG);

      *outEntitySize =
         CastIfNoOverflow(m_controller->Size(inHandle));
   });
}

STDMETHODIMP FileSystem::Read(ULONG inHandle, ULONG Count, BYTE_SIZEDARR* outBuffer)
{
   return CatchAll([this, inHandle, Count, &outBuffer]()
   {
      if (nullptr == outBuffer)
         throw InterfaceError(E_INVALIDARG);

      auto readResult = m_controller->Read(inHandle, Count);
      if (!readResult.first)
         throw InterfaceError(E_UNEXPECTED);
      
      outBuffer->clSize = CastIfNoOverflow(readResult.second);
      outBuffer->pData = readResult.first.get();
      readResult.first.release();
   });
}

STDMETHODIMP FileSystem::Write(ULONG inHandle, BYTE_SIZEDARR inBuffer)
{
   return CatchAll([this, inHandle, &inBuffer]()
   {
      if (0u == inBuffer.clSize)
         return;

      if (nullptr == inBuffer.pData)
         throw InterfaceError(E_INVALIDARG);

      m_controller->Write(inHandle, inBuffer.pData, inBuffer.clSize);
   });
}
