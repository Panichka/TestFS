#ifndef __vfs__Registrar_h__
#define __vfs__Registrar_h__

#include <windows.h>

class DllRegistrar
{
public:
	DllRegistrar() = default;
   bool RegisterObject(REFIID riid, LPCSTR libId, LPCSTR classId, LPCSTR path);
   bool UnRegisterObject(REFIID riid, LPCSTR libId, LPCSTR classId);

   BOOL SetInRegistry(HKEY rootKey, LPCSTR subKey, LPCSTR keyName, LPCSTR keyValue);
   BOOL DelFromRegistry(HKEY rootKey, LPCTSTR subKey);
};

#endif // __vfs__Registrar_h__