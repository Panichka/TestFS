#ifndef __vfs__ClassFactory_h__
#define __vfs__ClassFactory_h__

#include <unknwn.h>
#include <windows.h>

#include "ReferenceCounter.h"

class ClassFactory : public IClassFactory
{
public:
   static const NCOMServer::ReferenceCounter& InstanceCounter();

   ClassFactory();
   ClassFactory(const ClassFactory&) = delete;
   void operator=(const ClassFactory&) = delete;

   // IUnknown
   IFACEMETHODIMP QueryInterface(REFIID riid, void **ppv) override;
   IFACEMETHODIMP_(ULONG) AddRef() override;
   IFACEMETHODIMP_(ULONG) Release() override;

   // IClassFactory
   IFACEMETHODIMP CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv) override;
   IFACEMETHODIMP LockServer(BOOL lock) override;

protected:
   virtual ~ClassFactory();

private:
   NCOMServer::ReferenceCounter m_refCounter;
};

#endif // __vfs__ClassFactory_h__
