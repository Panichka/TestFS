#ifndef __vfs__ClassFactory_h__
#define __vfs__ClassFactory_h__

#include <unknwn.h>
#include <windows.h>
 
class ClassFactory : public IClassFactory
{
public:
   ClassFactory(ULONG& instCounter);
   ClassFactory(const ClassFactory&) = delete;
   void operator=(const ClassFactory&) = delete;

   // IUnknown
   IFACEMETHODIMP QueryInterface(REFIID riid, void **ppv);
   IFACEMETHODIMP_(ULONG) AddRef();
   IFACEMETHODIMP_(ULONG) Release();

   // IClassFactory
   IFACEMETHODIMP CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv);
   IFACEMETHODIMP LockServer(BOOL lock);

protected:
   virtual ~ClassFactory();

private:
   ULONG m_refCounter;
   ULONG& m_lockCounter;
};

#endif // __vfs__ClassFactory_h__
