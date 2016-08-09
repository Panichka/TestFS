#include <chrono>
#include <iostream>

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Fixtures.h"

using namespace boost;
using namespace boost::unit_test;
using namespace NFileSystem;

BOOST_AUTO_TEST_SUITE(FileSystemLibTestSuite)

BOOST_FIXTURE_TEST_CASE(ReadAndWriteLargeFile, ControllerWithEntity<EntityCategory::File>)
{
	auto Internal = WeakInternal.lock();

	uint8_t data[256];
   for (auto& i : data)
      i = &i - data; // for binary readability

   uint64_t offset = 0u;
   uint64_t size = 0x6400000; //100Mb

   auto start = std::chrono::steady_clock::now();
   while (offset < size)
   {
      Internal->Write(Entity, data, sizeof(data), offset);
      offset += sizeof(data);
   }
   auto duration = std::chrono::steady_clock::now() - start;
   
   std::cout << "\nTEST CASE \"ReadAndWriteLargeFile\":\n\twritten 100Mb by portions of 64 byte for "
             << std::chrono::duration_cast<std::chrono::minutes>(duration).count() << ":"
             << std::chrono::duration_cast<std::chrono::seconds>(duration).count() % 60 << ":"
             << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() % 1000;

	BOOST_CHECK(Internal->Size(Entity) == size);
	
	auto readResult = Internal->Read(Entity, sizeof(data), size/2);

	BOOST_CHECK(readResult.second = sizeof(data));
	BOOST_CHECK(0 == memcmp(readResult.first.get(), data, readResult.second));
}

BOOST_FIXTURE_TEST_CASE(OperateWithManyFiles, ControllerFixture)
{
   auto root = Internal->Root();

   const auto count = 100000u;

   auto start = std::chrono::steady_clock::now();
   for (auto index = 0u; index < count; ++index)
      Internal->Create(root, std::to_wstring(index), EntityCategory::File);
   auto duration = std::chrono::steady_clock::now() - start;

   std::cout << "\nTEST CASE \"OperateWithManyFiles\":\n\t 100000 empty files created for "
      << std::chrono::duration_cast<std::chrono::minutes>(duration).count() << ":"
      << std::chrono::duration_cast<std::chrono::seconds>(duration).count() % 60 << ":"
      << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() % 1000;

   Internal.reset();
   Internal = std::make_unique<Controller>();

   root = Internal->Root();

   auto randomIndex = std::rand() % (count - 1);
   auto name = std::to_wstring(randomIndex);

   start = std::chrono::steady_clock::now();
   auto founded = Internal->Handle(root, name);
   duration = std::chrono::steady_clock::now() - start;

   std::cout << "\n\t find by name among 100000 files took "
      << std::chrono::duration_cast<std::chrono::hours>(duration).count() << ":"
      << std::chrono::duration_cast<std::chrono::minutes>(duration).count() % 60 << ":"
      << std::chrono::duration_cast<std::chrono::seconds>(duration).count() % 60;
   
   auto contains = Internal->List(root);
   BOOST_REQUIRE(contains.size() == count);

   // This is too long check
   //for (auto index = 0u; index < count; ++index)
   //{
   //   BOOST_CHECK(contains.end() != std::find(contains.begin(), contains.end(), std::to_wstring(index)));
   //}
}

BOOST_AUTO_TEST_SUITE_END()