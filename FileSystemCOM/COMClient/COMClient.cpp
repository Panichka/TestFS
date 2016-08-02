// COMClient.cpp : Defines the entry point for the console application.
//
#include <memory>
#include <exception>
#include <functional>
#include <future>
#include <vector>
#include <iostream>
#include <string>

#include <windows.h>
#include <unknwn.h>

#include <GUIDS.h>
#include <FSInterface.h>

template <class T>
struct Releasable
{
   Releasable() = delete;
   Releasable(const Releasable&) = delete;
   void operator=(const Releasable&) = delete;

   Releasable(std::function<HRESULT(T*)>&& init)
   {
      HRESULT result = init(Ptr);
      if (FAILED(result))
         throw result;
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

int main()
{
   try
   {
      CoInitializer::Create();

      /*
      Releasable<IClassFactory> ifactory([](IClassFactory* ifactoryPtr)
      {
         return CoGetClassObject(CLSID_FS, CLSCTX_INPROC_SERVER, nullptr, IID_IClassFactory, (LPVOID *)&ifactoryPtr);
      });

      Releasable<IFileSystem> ifs([&ifactory](IFileSystem* ifsPtr)
      {
         return ifactory.Ptr->CreateInstance(nullptr, IID_FS, (LPVOID *)&ifsPtr);
      });
      */

      Releasable<IFileSystem> ifs([](IFileSystem* ifsPtr)
      {
         return CoCreateInstance(CLSID_FS, 0, CLSCTX_INPROC_SERVER, IID_FS, (LPVOID *)&ifsPtr);
      });

      ULONG rootHandle;
      if (SUCCEEDED(ifs.Ptr->Root(&rootHandle)))
      {
         std::vector<std::future<void>> futures;

         /*----------------------------------- create dirs recursivly ------------------------------------*/
         auto createDirFuture = std::async(std::launch::async, [rootHandle, &ifs]
         {
            auto childCount = 1000u;
            auto nestingDepth = 10u;
            std::vector<std::future<HRESULT>> futures(std::powf(childCount, nestingDepth)); //no reallocations for async push_back

            std::function<void(ULONG, ULONG)> func = [&ifs, &futures, &func, childCount](ULONG handle, ULONG depth)
            {
               for (auto index = 0u; index < childCount; ++index)
               {
                  auto ftr = std::async(std::launch::deferred, [&ifs, &futures, &func, index, handle, depth]() -> HRESULT
                  {
                     ULONG created;
                     auto result = ifs.Ptr->CreateDirectory(handle, std::to_wstring(index).c_str(), &created);

                     if ((1u < depth) && SUCCEEDED(result))
                        func(created, depth - 1);

                     return result;
                  });

                  futures.push_back(std::move(ftr));
               }
            };

            func(rootHandle, nestingDepth);

            auto index = 0u;
            std::for_each(futures.begin(), futures.end(), [&index](std::future<HRESULT> & future)
            {
               if (SUCCEEDED(future.get()))
               {
                  auto i = index;
                  std::string path("");

                  while (0 != i)
                  {
                     path = "/" + std::to_string(i % 1000) + path;
                     i = i / 1000;
                  }

                  path = "/" + std::to_string(i) + path;
                  std::cout << path << '\n';
               }

               ++index;
            });
         });

         futures.push_back(std::move(createDirFuture));

         /*----------------------------------- create and write files recursivly ------------------------------------*/
         //
         /*----------------------------------- delete some entities recursivly --------------------------------------*/
         //

         std::for_each(futures.begin(), futures.end(), [](std::future<void> & fut)
         {
            fut.wait();
         });
      }
   }
   catch(const HRESULT& result)
   {
      std::cout << "Some initialization step failed with code \n" << result;
      std::getchar();
      return -1;
   }

   std::getchar();
   return 0;
}

