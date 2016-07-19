#include "ClassFactory.h"
#include "FSCoClass.h"

ClassFactory::ClassFactory(ULONG& instCounter)
   : m_refCounter(1ul)
   , m_lockCounter(instCounter)
{
   InterlockedIncrement(&m_lockCounter);
}

ClassFactory::~ClassFactory()
{
   InterlockedDecrement(&m_lockCounter);
}

//
// IUnknown
//

IFACEMETHODIMP ClassFactory::QueryInterface(REFIID riid, void **ppv)
{
   HRESULT result = S_OK;

   if (IsEqualIID(IID_IUnknown, riid) ||
      //IsEqualIID(IID_IDispatch, riid) ||  // IDispatch is not implemented
      IsEqualIID(IID_IClassFactory, riid))
   {
      *ppv = static_cast<IUnknown *>(this);
      AddRef();
   }
   else
   {
      result = E_NOINTERFACE;
      *ppv = NULL;
   }

   return result;
}

IFACEMETHODIMP_(ULONG) ClassFactory::AddRef()
{
   return InterlockedIncrement(&m_refCounter);
}

IFACEMETHODIMP_(ULONG) ClassFactory::Release()
{
   auto counterValue = InterlockedDecrement(&m_refCounter);
   if (0l == counterValue)
      delete this;

   return counterValue;
}


// 
// IClassFactory
//

IFACEMETHODIMP ClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
   HRESULT result = CLASS_E_NOAGGREGATION;

   // aggregation is not implemented
   if (pUnkOuter == NULL)
   {
      result = E_OUTOFMEMORY;

      FileSystem *pSimpleObj = new FileSystem();
      if (pSimpleObj)
      {
         result = pSimpleObj->QueryInterface(riid, ppv);
         pSimpleObj->Release();
      }
   }

   return result;
}

IFACEMETHODIMP ClassFactory::LockServer(BOOL lock)
{
   lock ?
      InterlockedIncrement(&m_lockCounter) : InterlockedDecrement(&m_lockCounter);

   return S_OK;
}