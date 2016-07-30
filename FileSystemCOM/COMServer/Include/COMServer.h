#ifdef COMSERVER_EXPORTS
#define COMSERVER_EXPORTS __declspec(dllexport)
#else
#define COMSERVER_EXPORTS __declspec(dllimport)
#endif

#include <objbase.h>

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppvOut);
STDAPI DllCanUnloadNow(void);
STDAPI DllRegisterServer(void);
STDAPI DllUnregisterServer(void);

