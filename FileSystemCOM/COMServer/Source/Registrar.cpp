#include <stdio.h>
#include <list>
#include <utility>
#include "Registrar.h"

namespace NCOMServer
{
   namespace
   {
      using KeyValueList = std::list<std::pair<LPCSTR, LPCSTR>>;

      bool SetInRegistry(HKEY rootKey, LPCSTR subKey, const KeyValueList& newKeys)
      {
         HKEY hKeyResult;
         DWORD dwDisposition;
         if (RegCreateKeyEx(rootKey, subKey, 0, nullptr, REG_OPTION_NON_VOLATILE,
            KEY_WRITE, nullptr, &hKeyResult, &dwDisposition) != ERROR_SUCCESS)
            return false;
         
         auto retVal = ERROR_SUCCESS;
         for (const auto& item : newKeys)
         {
            auto dataLength = strlen(item.second);
            if (dataLength <= MAXDWORD)
               retVal = RegSetValueEx(hKeyResult, item.first, 0, REG_SZ,
                  reinterpret_cast<const BYTE *>(item.second), static_cast<DWORD>(dataLength));
            else
               retVal = FALSE;

            if (retVal != ERROR_SUCCESS)
               break;
         }

         RegCloseKey(hKeyResult);
         return retVal == ERROR_SUCCESS;
      }

      bool DelTreeFromRegistry(HKEY rootKey, LPCTSTR subKey)
      {
         HKEY hKeyResult;
         if (ERROR_SUCCESS == RegOpenKeyEx(rootKey, subKey, 0, DELETE | KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE | KEY_SET_VALUE, &hKeyResult))
         {
            auto result = ERROR_SUCCESS == RegDeleteTree(hKeyResult, nullptr);
            RegCloseKey(hKeyResult);
            return result && ERROR_SUCCESS == RegDeleteKey(rootKey, subKey);
         }

         return false;
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
      if(!libId || !classId || !path)
         return false;

      if (0 == strlen(classId))
         return false;

      char strCLSID[MAX_PATH];
      if (!StrFromCLSID(riid, strCLSID))
         return false;

      char buffer[MAX_PATH];
      auto SetInReg = [&buffer](const KeyValueList& pairs,  const char * format, ...)
      {
         va_list args;
         va_start(args, format);
         vsprintf_s(buffer, MAX_PATH, format, args);
         return TRUE == SetInRegistry(HKEY_CLASSES_ROOT, buffer, pairs);
      };

      const char* frendlyName = "class implements virual file system in single file";
      if (!SetInReg({ std::make_pair("", frendlyName) }, "CLSID\\%s", strCLSID))
         return false;

      char valueStr[MAX_PATH];
      sprintf_s(valueStr, MAX_PATH, "%s.%s", libId, classId);
      if (!SetInReg({ std::make_pair("", valueStr) }, "CLSID\\%s\\ProgId", strCLSID))
         return false;

      if (!SetInReg(
                     { std::make_pair("", path), std::make_pair("ThreadingModel", "Both") },
                     "CLSID\\%s\\InProcServer32",
                     strCLSID
         ))
         return false;

      auto firstStr = 0 == strlen(libId) ? classId : libId;
      return SetInReg({ std::make_pair("", strCLSID) }, "%s.%s\\CLSID", firstStr, classId);
   }

   bool UnRegisterObject(REFIID riid, LPCSTR libId, LPCSTR classId)
   {
      if (!libId || !classId)
         return false;

      char strCLSID[MAX_PATH];
      if (!StrFromCLSID(riid, strCLSID))
         return false;

      char buffer[MAX_PATH];

      sprintf_s(buffer, MAX_PATH, "%s.%s", libId, classId);
      bool result = DelTreeFromRegistry(HKEY_CLASSES_ROOT, buffer);

      sprintf_s(buffer, MAX_PATH, "CLSID\\%s", strCLSID);
      if (!result || !DelTreeFromRegistry(HKEY_CLASSES_ROOT, buffer))
         return false;

      return true;
   }
} // namespace NCOMServer