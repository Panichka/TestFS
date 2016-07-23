#include "COMServer.h"
#include "ClassFactory.h"
#include "GUIDs.h"
#include "Registrar.h"

namespace
{
   NCOMServer::ReferenceCounter instCounter(0u);
   HANDLE g_module;
}

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
	*ppvOut = nullptr;
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
   return instCounter == 0u ? S_OK : S_FALSE;
}

STDAPI DllRegisterServer(void)
{
	char path [MAX_PATH];
	GetModuleFileName(static_cast<HMODULE>(g_module), path, MAX_PATH);
	return NCOMServer::RegisterObject(CLSID_FS, "VirtualFileSystemLib", "VirtualFileSystemObj", path) ?
      S_OK : S_FALSE;
}

STDAPI DllUnregisterServer(void)
{
	return NCOMServer::UnRegisterObject(CLSID_FS, "VirtualFileSystemLib", "VirtualFileSystemObj") ?
      S_OK : S_FALSE;
}

