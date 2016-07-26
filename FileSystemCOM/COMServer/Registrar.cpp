#include "stdio.h"
#include "Registrar.h"

namespace NCOMServer
{
   namespace
   {
      BOOL SetInRegistry(HKEY rootKey, LPCSTR subKey, LPCSTR keyName, LPCSTR keyValue)
      {
         HKEY hKeyResult;
         DWORD dataLength;
         DWORD dwDisposition;
         if (RegCreateKeyEx(rootKey, subKey, 0, nullptr, REG_OPTION_NON_VOLATILE,
            KEY_WRITE, nullptr, &hKeyResult, &dwDisposition) != ERROR_SUCCESS)
            return FALSE;

         dataLength = strlen(keyValue);
         auto retVal = RegSetValueEx(hKeyResult, keyName, 0, REG_SZ, reinterpret_cast<const BYTE *>(keyValue), dataLength);
         RegCloseKey(hKeyResult);
         return retVal == ERROR_SUCCESS ? TRUE : FALSE;
      }

      BOOL DelFromRegistry(HKEY rootKey, LPCTSTR subKey)
      {
         return RegDeleteKey(rootKey, subKey) == ERROR_SUCCESS ? TRUE : FALSE;
      }

      bool StrFromCLSID(REFIID riid, LPSTR strCLSID)
      {
         LPOLESTR pOleStr = nullptr;

         if (FAILED(::StringFromCLSID(riid, &pOleStr)))
            return false;

         auto bytesConv = ::WideCharToMultiByte(CP_ACP, 0, pOleStr, static_cast<int>(wcslen(pOleStr)), strCLSID, MAX_PATH, nullptr, nullptr);
         CoTaskMemFree(pOleStr);

         strCLSID[bytesConv] = '\0';
         return bytesConv;
      }
   }

   bool RegisterObject(REFIID riid, LPCSTR libId, LPCSTR classId, LPCSTR path)
   {
      char strCLSID[MAX_PATH];
      char buffer[MAX_PATH];

      if (!strlen(classId))
         return false;

      if (!StrFromCLSID(riid, strCLSID))
         return false;

      if (!strlen(libId) && strlen(classId))
         sprintf_s(buffer, MAX_PATH, "%s.%s\\CLSID", classId, classId);
      else
         sprintf_s(buffer, MAX_PATH, "%s.%s\\CLSID", libId, classId);

      auto result = SetInRegistry(HKEY_CLASSES_ROOT, buffer, "", strCLSID);
      if (!result)
         return false;

      sprintf_s(buffer, MAX_PATH, "CLSID\\%s", strCLSID);

      char classStr[MAX_PATH];
      sprintf_s(classStr, MAX_PATH, "%s classStr", classId);
      if (!SetInRegistry(HKEY_CLASSES_ROOT, buffer, "", classStr))
         return false;

      sprintf_s(classStr, MAX_PATH, "%s.%s", libId, classId);
      strcat_s(buffer, "\\ProgId");
      if (!SetInRegistry(HKEY_CLASSES_ROOT, buffer, "", classStr))
         return false;

      sprintf_s(buffer, MAX_PATH, "CLSID\\%s\\InProcServer32", strCLSID);
      return SetInRegistry(HKEY_CLASSES_ROOT, buffer, "", path);
   }

   bool UnRegisterObject(REFIID riid, LPCSTR libId, LPCSTR classId)
   {
      char strCLSID[MAX_PATH];
      char buffer[MAX_PATH];

      if (!StrFromCLSID(riid, strCLSID))
         return false;

      sprintf_s(buffer, MAX_PATH, "CLSID\\%s\\InProcServer32", strCLSID);
      if (!DelFromRegistry(HKEY_CLASSES_ROOT, buffer))
         return false;

      sprintf_s(buffer, MAX_PATH, "%s.%s\\CLSID", libId, classId);
      if (!DelFromRegistry(HKEY_CLASSES_ROOT, buffer))
         return false;

      sprintf_s(buffer, MAX_PATH, "%s.%s", libId, classId);
      if (!DelFromRegistry(HKEY_CLASSES_ROOT, buffer))
         return false;

      sprintf_s(buffer, MAX_PATH, "CLSID\\%s\\ProgId", strCLSID);
      if (!DelFromRegistry(HKEY_CLASSES_ROOT, buffer))
         return false;

      sprintf_s(buffer, MAX_PATH, "CLSID\\%s", strCLSID);
      return DelFromRegistry(HKEY_CLASSES_ROOT, buffer);
   }
} // namespace NCOMServer