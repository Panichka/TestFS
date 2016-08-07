// COMClient.cpp : Defines the entry point for the console application.
//
#include <memory>
#include <exception>
#include <functional>
#include <future>
#include <vector>
#include <iostream>
#include <string>
#include <assert.h>

#include <windows.h>
#include <unknwn.h>

#include <GUIDS.h>
#include <FSInterface.h>

namespace
{
   template <class T>
   struct Releasable
   {
      Releasable() = delete;
      Releasable(const Releasable&) = delete;
      void operator=(const Releasable&) = delete;

      Releasable(std::function<std::pair<HRESULT, T*>()>&& init)
      {
         auto result = init();
         if (FAILED(result.first))
            throw result.first;

         assert(Ptr = result.second);
      }

      ~Releasable()
      {
         Ptr->Release();
      }

      T* Ptr = nullptr;
   };

   struct CoInitializer
   {
      static void Create()
      {
         static CoInitializer init;
      }

   private:
      CoInitializer()
      {
         HRESULT result = CoInitializeEx(0, COINIT_MULTITHREADED);
         if (FAILED(result))
            throw result;
      }

      ~CoInitializer()
      {
         CoUninitialize();
      }
   };

   template <uint32_t nestingDepth>
   uint32_t CountRecursivly(uint32_t childCount)
   {
      return CountRecursivly<nestingDepth - 1>(childCount) + std::powf(childCount, nestingDepth);
   }

   template <>
   uint32_t CountRecursivly<1>(uint32_t childCount)
   {
      return childCount;
   }
}

int main()
{
   try
   {
      CoInitializer::Create();

      /*
      Releasable<IClassFactory> ifactory([](IClassFactory* ifactoryPtr)
      {
         return CoGetClassObject(CLSID_FS, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER, nullptr, IID_IClassFactory, (LPVOID *)&ifactoryPtr);
      });

      Releasable<IFileSystem> ifs([&ifactory](IFileSystem* ifsPtr)
      {
         return ifactory.Ptr->CreateInstance(nullptr, IID_FS, (LPVOID *)&ifsPtr);
      });
      */

      /*----------------------------------- create dirs recursivly ------------------------------------*/
      auto createDir = []()
      {
         Releasable<IFileSystem> ifs([]()
         {
            IFileSystem* ifsPtr = nullptr;
            return std::make_pair(CoCreateInstance(CLSID_FS, 0, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER, IID_FS, (LPVOID *)&ifsPtr), ifsPtr);
         });

         ULONG rootHandle;
         if (FAILED(ifs.Ptr->Root(&rootHandle)))
            return;

         const uint32_t childCount = 2u;
         const uint32_t nestingDepth = 3u;

         std::vector<std::future<std::pair<HRESULT, std::wstring>>> futures;
         futures.reserve(CountRecursivly<nestingDepth>(childCount)); //no reallocations for async push_back

         std::function<void(ULONG, uint32_t, const std::wstring&)> func =
            [&ifs, &futures, &func, childCount](ULONG handle, uint32_t depth, const std::wstring& path)
         {
            for (auto index = 0u; index < childCount; ++index)
            {
               auto ftr = std::async(std::launch::deferred, [&ifs, &futures, &func, index, handle, depth, path]()
               {
                  ULONG created;
                  std::wstring relativePath(1u, L'a' + index);
 
                  auto result = std::make_pair<HRESULT, std::wstring>(
                     ifs.Ptr->CreateDirectory(handle, relativePath.c_str(), &created), path + L"/" + relativePath);

                  if ((1u < depth) && SUCCEEDED(result.first))
                     func(created, depth - 1, result.second);

                  return result;
               });

               futures.push_back(std::move(ftr));
            }
         };

         func(rootHandle, nestingDepth, L"");

         auto it = futures.begin();
         while(it != futures.end())
         {
            auto result = it->get();

            if (FAILED(result.first))
               std::wcout << L"FAILED: " << result.second << L'\n';

            ++it;
         }
      };

      createDir();
      /*----------------------------------- list root recursivly -------------------------------------------------*/
      auto listDirFuture = std::async(std::launch::async, []()
      {
         Releasable<IFileSystem> ifs([]()
         {
            IFileSystem* ifsPtr = nullptr;
            return std::make_pair(CoCreateInstance(CLSID_FS, 0, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER, IID_FS, (LPVOID *)&ifsPtr), ifsPtr);
         });

         ULONG rootHandle;
         if (FAILED(ifs.Ptr->Root(&rootHandle)))
            return;

         std::function<void(ULONG, std::wstring&&)> func = [&ifs, &func](ULONG dirHandle, std::wstring&& dirPath)
         {
            LPOLESTR* names = nullptr;
            ULONG count;
            ifs.Ptr->List(dirHandle, &names, &count);

            for (ULONG index = 0u; index < count; ++index)
            {
               auto path = dirPath + L"/" + names[index];
               std::wcout << L'\t' << path << L'\n';

               ULONG handle;
               if (SUCCEEDED(ifs.Ptr->GetHandle(dirHandle, names[index], &handle)))
               {
                  BOOL isDir = false;
                  if (SUCCEEDED(ifs.Ptr->IsDirectory(handle, &isDir)) && isDir)
                     func(handle, std::move(path));
               }
            }
         };

         std::cout << "LIST ROOT: \n";
         func(rootHandle, L"");
      });


      std::vector<std::future<void>> futures;
      futures.push_back(std::move(listDirFuture));
      /*----------------------------------- create and write files recursivly ------------------------------------*/
      //
      /*----------------------------------- delete some entities recursivly --------------------------------------*/
      //

      std::for_each(futures.begin(), futures.end(), [](std::future<void> & fut)
      {
         fut.get();
      });
   }
   catch (std::future_error& e)
   {
      std::cout << "Future throws" << e.what() << '\n';
      std::getchar();
      return -1;
   }
   catch (const HRESULT& result)
   {
      std::cout << "Some initialization step failed with code \n" << result;
      std::getchar();
      return -1;
   }

   std::getchar();
   return 0;
}

