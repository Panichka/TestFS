#ifndef __vfs__Registrar_h__
#define __vfs__Registrar_h__

#include <windows.h>

namespace NCOMServer
{
   bool RegisterObject(REFIID riid, LPCSTR libId, LPCSTR classId, LPCSTR path);
   bool UnRegisterObject(REFIID riid, LPCSTR libId, LPCSTR classId);
} // namespace NCOMServer

#endif // __vfs__Registrar_h__