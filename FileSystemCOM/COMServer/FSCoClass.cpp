#include <windows.h>
#include "GUIDs.h"
#include "FSCoClass.h"

STDMETHODIMP FileSystem::QueryInterface(REFIID riid, LPVOID *ppv)
{
	*ppv = NULL;
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
   return InterlockedIncrement(&m_refCounter);
}

STDMETHODIMP_(ULONG) FileSystem::Release()
{
   auto counterValue = InterlockedDecrement(&m_refCounter);
   if (0l == counterValue)
      delete this;

   return counterValue;
}

STDMETHODIMP FileSystem::CreateFile(BSTR inPath)
{
	return S_OK;
}

STDMETHODIMP FileSystem::CreateDirectory(BSTR inPath)
{
   return S_OK;
}

STDMETHODIMP FileSystem::Delete(BSTR inPath)
{
	return S_OK;
}

STDMETHODIMP FileSystem::Exists(BSTR inPath)
{
	return S_OK;
}

STDMETHODIMP FileSystem::List(BSTR inPath, SAFEARR_BSTR outEntities)
{
	return S_OK;
}

STDMETHODIMP FileSystem::GetSize(BSTR inPath, ULONG* outEntitySize)
{
	return S_OK;
}

STDMETHODIMP FileSystem::Read(BSTR inPath, BYTE_SIZEDARR outBuffer)
{
	return S_OK;
}
STDMETHODIMP FileSystem::Write(BSTR inPath, BYTE_SIZEDARR inBuffer)
{
	return S_OK;
}
