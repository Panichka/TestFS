#include <stdio.h>
#include "Registrar.h"

namespace NCOMServer
{
   namespace
   {
      BOOL SetInRegistry(HKEY rootKey, LPCSTR subKey, LPCSTR keyName, LPCSTR keyValue)
      {
         HKEY hKeyResult;
         DWORD dwDisposition;
         if (RegCreateKeyEx(rootKey, subKey, 0, nullptr, REG_OPTION_NON_VOLATILE,
            KEY_WRITE, nullptr, &hKeyResult, &dwDisposition) != ERROR_SUCCESS)
            return FALSE;

         auto dataLength = strlen(keyValue);
         if (dataLength > MAXDWORD)
            return FALSE;

         auto retVal = RegSetValueEx(hKeyResult, keyName, 0, REG_SZ,
            reinterpret_cast<const BYTE *>(keyValue), static_cast<DWORD>(dataLength));

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

         auto strLength = wcslen(pOleStr);
         if (strLength > MAXINT)
            return false;

         auto bytesConv = ::WideCharToMultiByte(CP_ACP, 0, pOleStr, static_cast<int>(strLength), strCLSID, MAX_PATH, nullptr, nullptr);
         CoTaskMemFree(pOleStr);

         strCLSID[bytesConv] = '\0';
         return 0 != bytesConv;
      }
   }

   bool RegisterObject(REFIID riid, LPCSTR libId, LPCSTR classId, LPCSTR path)
   {
      if (0 == strlen(classId))
         return false;

      char strCLSID[MAX_PATH];
      if (!StrFromCLSID(riid, strCLSID))
         return false;

      char buffer[MAX_PATH];
      auto SetInReg = [&buffer](LPCSTR value,  const char * format, ...)
      {
         va_list args;
         va_start(args, format);
         vsprintf_s(buffer, MAX_PATH, format, args);
         return TRUE == SetInRegistry(HKEY_CLASSES_ROOT, buffer, "", value);
      };

      auto firstStr = 0 == strlen(libId) ? classId : libId;

      if (!SetInReg(firstStr, "%s.%s\\CLSID", firstStr, classId))
         return false;

      char classStr[MAX_PATH];
      sprintf_s(classStr, MAX_PATH, "%s classStr", classId);
      if (!SetInReg(classStr, "CLSID\\%s", strCLSID))
         return false;

      sprintf_s(classStr, MAX_PATH, "%s.%s", libId, classId);
      strcat_s(buffer, "\\ProgId");
      if (!SetInReg(classStr, ""))
         return false;

      return SetInReg(path, "CLSID\\%s\\InProcServer32", strCLSID);
   }

   bool UnRegisterObject(REFIID riid, LPCSTR libId, LPCSTR classId)
   {
      char strCLSID[MAX_PATH];
      if (!StrFromCLSID(riid, strCLSID))
         return false;

      char buffer[MAX_PATH];
      auto DelFromReg = [&buffer](const char * format, ...)
      {
         va_list args;
         va_start(args, format);
         vsprintf_s(buffer, MAX_PATH, format, args);
         return TRUE == DelFromRegistry(HKEY_CLASSES_ROOT, buffer);
      };

      return
         DelFromReg("CLSID\\%s\\InProcServer32", strCLSID) &&
         DelFromReg("%s.%s\\CLSID", libId, classId) &&
         DelFromReg("%s.%s", libId, classId) &&
         DelFromReg("CLSID\\%s\\ProgId", strCLSID) &&
         DelFromReg("CLSID\\%s", strCLSID);
   }
} // namespace NCOMServer