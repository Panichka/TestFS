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

STDMETHODIMP FileSystem::Create(LPCSTR inPath, PVOID outHandle)
{
	return S_OK;
}

STDMETHODIMP FileSystem::Open(PVOID inHandle)
{
	return S_OK;
}

STDMETHODIMP FileSystem::Close(PVOID inHandle)
{
	return S_OK;
}

STDMETHODIMP FileSystem::Delete(PVOID inHandle)
{
	return S_OK;
}

STDMETHODIMP FileSystem::Find(LPCSTR inPath, PVOID outHandle)
{
	return S_OK;
}

STDMETHODIMP FileSystem::List(LPCSTR inPath, LPCSTR* outEntries)
{
	return S_OK;
}

STDMETHODIMP FileSystem::GetSize(LPCSTR inPath, ULONG* outEntrySize)
{
	return S_OK;
}

STDMETHODIMP FileSystem::Read(PVOID inHandle, PVOID outBuffer, ULONG size)
{
	return S_OK;
}
STDMETHODIMP FileSystem::Write(PVOID inHandle, const PVOID outBuffer, ULONG size)
{
	return S_OK;
}
