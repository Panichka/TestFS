#include "COMServer.h"
#include "ClassFactory.h"
#include "GUIDs.h"
#include "Registrar.h"

ULONG instCounter = 0ul;
HANDLE g_module;

BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    switch (dwReason)
	{
		case DLL_PROCESS_ATTACH: 
			g_module = hInstance;
			break;

		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }

    return TRUE;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppvOut)
{
	*ppvOut = NULL;
    if (IsEqualIID(rclsid, CLSID_FS))
    {
       auto factory = new ClassFactory(instCounter);
       auto result = factory->QueryInterface(riid, ppvOut);
	   factory->Release();
	   return result;
    }

    return CLASS_E_CLASSNOTAVAILABLE;
}

STDAPI DllCanUnloadNow(void)
{
	//if < 0 ??
    return 0l == InterlockedXor(reinterpret_cast<unsigned long long*>(&instCounter), 0ul) ? S_OK : S_FALSE;
}

STDAPI DllRegisterServer(void)
{
	DllRegistrar registrar;
	char path [MAX_PATH];
	GetModuleFileName(static_cast<HMODULE>(g_module), path, MAX_PATH);
	return registrar.RegisterObject(CLSID_FS, "VirtualFileSystemLib", "VirtualFileSystemObj", path) ?
      S_OK : S_FALSE;
}

STDAPI DllUnregisterServer(void)
{
	DllRegistrar registrar;
	return registrar.UnRegisterObject(CLSID_FS, "VirtualFileSystemLib", "VirtualFileSystemObj") ?
      S_OK : S_FALSE;
}

