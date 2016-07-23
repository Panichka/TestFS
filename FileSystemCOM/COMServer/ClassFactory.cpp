#include "ClassFactory.h"
#include "FSCoClass.h"

ClassFactory::ClassFactory(NCOMServer::ReferenceCounter& instCounter)
   : m_refCounter(1u)
   , m_lockCounter(instCounter)
{
   ++m_lockCounter;
}

ClassFactory::~ClassFactory()
{
   --m_lockCounter;
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
      *ppv = nullptr;
   }

   return result;
}

IFACEMETHODIMP_(ULONG) ClassFactory::AddRef()
{
   return ++m_refCounter;
}

IFACEMETHODIMP_(ULONG) ClassFactory::Release()
{
   auto counterValue = --m_refCounter;
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
   if (nullptr == pUnkOuter)
   {
      result = E_OUTOFMEMORY;

      auto fsObj = new FileSystem();
      if (nullptr == fsObj)
      {
         result = fsObj->QueryInterface(riid, ppv);
         fsObj->Release();
      }
   }

   return result;
}

IFACEMETHODIMP ClassFactory::LockServer(BOOL lock)
{
   lock ? ++m_lockCounter : --m_lockCounter;

   return S_OK;
}