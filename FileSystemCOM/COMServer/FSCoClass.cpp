#include <functional>
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
   NFileSystem::Path BSTRToPath(BSTR pathStr)
   {
      _bstr_t wrapper(pathStr, false);
      std::unique_ptr<const wchar_t> raw(static_cast<const wchar_t*>(wrapper));
      wrapper.Detach();

      return NFileSystem::Path(raw.get());
   }

   BSTR wstringToBSTR(const std::wstring& str)
   {
      _bstr_t wrapper(str.c_str());
      return wrapper.Detach();
   }

   ULONG CastIfNoOverflow(size_t value)
   {
      constexpr ULONG maxULong = ULONG(0) - 1;
      if (value > maxULong)
         throw std::overflow_error("msg is not used");

      return static_cast<ULONG>(value);
   }

   HRESULT CatchAll(const std::function<void()>& action)
   {
      try
      {
         action();
         return S_OK;
      }
      catch (...)
      {
         return S_FALSE;
      }
   }
}

STDMETHODIMP FileSystem::CreateFile(BSTR inPath)
{
   return CatchAll([this, inPath]()
   {
      m_controller->Create(BSTRToPath(inPath), NFileSystem::Entity::Category::File);
   });
}

STDMETHODIMP FileSystem::CreateDirectory(BSTR inPath)
{
   return CatchAll([this, inPath]()
   {
      m_controller->Create(BSTRToPath(inPath), NFileSystem::Entity::Category::Directory);
   });
}

STDMETHODIMP FileSystem::Delete(BSTR inPath)
{
   return CatchAll([this, inPath]()
   {
      m_controller->Delete(BSTRToPath(inPath));
   });
}

STDMETHODIMP FileSystem::Exists(BSTR inPath)
{
   return CatchAll([this, inPath]()
   {
      m_controller->Exists(BSTRToPath(inPath));
   });
}

STDMETHODIMP FileSystem::List(BSTR inPath, SAFEARR_BSTR outEntities)
{
   return CatchAll([this, inPath, &outEntities]()
   {
      auto entities = m_controller->List(BSTRToPath(inPath));
      
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

STDMETHODIMP FileSystem::GetSize(BSTR inPath, ULONG* outEntitySize)
{
   return CatchAll([this, inPath, outEntitySize]()
   {
      if (nullptr == outEntitySize)
         throw std::runtime_error("msg is not used");

      *outEntitySize =
         CastIfNoOverflow(m_controller->Size(BSTRToPath(inPath)));
   });
}

STDMETHODIMP FileSystem::Read(BSTR inPath, ULONG Count, BYTE_SIZEDARR* outBuffer)
{
   return CatchAll([this, inPath, Count, &outBuffer]()
   {
      if (nullptr == outBuffer)
         throw std::runtime_error("msg is not used");

      auto readResult = m_controller->Read(BSTRToPath(inPath), Count);
      if (!readResult.first)
         throw std::runtime_error("msg is not used");
      
      outBuffer->clSize = CastIfNoOverflow(readResult.second);
      outBuffer->pData = readResult.first.get();
      readResult.first.release();
   });
} 
STDMETHODIMP FileSystem::Write(BSTR inPath, BYTE_SIZEDARR inBuffer)
{
   return CatchAll([this, inPath, &inBuffer]()
   {
      if (0u == inBuffer.clSize)
         return;

      if (nullptr == inBuffer.pData)
         throw std::runtime_error("msg is not used");

      m_controller->Write(BSTRToPath(inPath),
         inBuffer.pData, inBuffer.clSize);
   });
}
