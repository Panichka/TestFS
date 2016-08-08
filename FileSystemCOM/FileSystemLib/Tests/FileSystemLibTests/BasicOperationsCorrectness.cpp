#define BOOST_TEST_MODULE ExampleTestModule
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "FSController.h"

using namespace boost;
using namespace boost::unit_test;
using namespace NFileSystem;

BOOST_AUTO_TEST_SUITE(FileSystemLibTestSuite)

struct ControllerFixture
{
   ControllerFixture()
      : Internal(std::make_unique<Controller>())
   { }

   ~ControllerFixture()
   {
	   filesystem::remove(boost::filesystem::current_path() /= "fs.rawdata");
   }

   std::shared_ptr<Controller> Internal;
};

BOOST_FIXTURE_TEST_CASE(FSInitialization, ControllerFixture)
{
   BOOST_REQUIRE(filesystem::exists(boost::filesystem::current_path() /= "fs.rawdata"));
   
   EntityHandle root;
   BOOST_CHECK_NO_THROW(root = Internal->Root());

   BOOST_CHECK(Internal->Count() >= 1);
}

BOOST_FIXTURE_TEST_CASE(CreateNewAndOpenExisting, ControllerFixture)
{
   auto root = Internal->Root();

   auto beforeCreation = Internal->Count();
   auto name = std::to_wstring(std::rand());
   auto created = Internal->Create(root, name, EntityCategory::File);
   auto afterCreation = Internal->Count();

   BOOST_CHECK(afterCreation - beforeCreation == 1);

   auto opened = Internal->Create(root, name, EntityCategory::File);
   auto afterOpen = Internal->Count();

   BOOST_CHECK(afterOpen == afterCreation);
   BOOST_CHECK(opened == created);
}

BOOST_FIXTURE_TEST_CASE(SaveStructureAfterShutDown, ControllerFixture)
{
   auto root = Internal->Root();

   auto fileName = std::to_wstring(std::rand());
   auto file = Internal->Create(root, fileName, EntityCategory::File);

   auto dirName = std::to_wstring(std::rand());
   auto dir = Internal->Create(root, dirName, EntityCategory::Directory);

   auto nestedFileName = std::to_wstring(std::rand());
   auto nestedFile = Internal->Create(dir, nestedFileName, EntityCategory::File);

   auto nestedDirName = std::to_wstring(std::rand());
   auto nestedDir = Internal->Create(dir, nestedDirName, EntityCategory::Directory);

   Internal.reset();
   Internal = std::make_unique<Controller>();

   root = Internal->Root();

   BOOST_CHECK(Internal->Exists(root, fileName));
   BOOST_CHECK(Internal->Category(root, fileName) == EntityCategory::File);
   
   BOOST_CHECK(Internal->Exists(root, dirName));
   BOOST_CHECK(Internal->Category(root, dirName) == EntityCategory::Directory);

   dir = Internal->Create(root, dirName, EntityCategory::Directory);

   BOOST_CHECK(Internal->Exists(dir, nestedFileName));
   BOOST_CHECK(Internal->Category(dir, nestedFileName) == EntityCategory::File);

   BOOST_CHECK(Internal->Exists(dir, nestedDirName));
   BOOST_CHECK(Internal->Category(dir, nestedDirName) == EntityCategory::Directory);
}

BOOST_FIXTURE_TEST_CASE(SaveDataAfterShutDown, ControllerFixture)
{
   auto root = Internal->Root();

   auto fileName = std::to_wstring(std::rand());
   auto file = Internal->Create(root, fileName, EntityCategory::File);

   uint8_t data[] = "abcdefg";
   BOOST_CHECK_NO_THROW(Internal->Write(file, data, sizeof(data)));

   Internal.reset();
   Internal = std::make_unique<Controller>();

   root = Internal->Root();
   file = Internal->Create(root, fileName, EntityCategory::File);

   BOOST_CHECK(Internal->Size(file) == sizeof(data));

   ManagedArray readResult;
   BOOST_CHECK_NO_THROW(readResult = Internal->Read(file, sizeof(data)));

   BOOST_CHECK(readResult.second = sizeof(data));
   BOOST_CHECK(0 == memcmp(readResult.first.get(), data, readResult.second));
}

template<EntityCategory category>
struct ControllerWithEntity : private ControllerFixture
{
	ControllerWithEntity()
		: ControllerFixture()
		, WeakInternal(Internal)
	{
		Root = Internal->Root();
		Name = std::to_wstring(std::rand());
		Entity = Internal->Create(Root, Name, category);
	}

	std::weak_ptr<Controller> WeakInternal;
	EntityHandle Root;
	EntityHandle Entity;
	std::wstring Name;
	EntityCategory Category = category;
};

BOOST_FIXTURE_TEST_CASE(ReadAndWriteWithOffset, ControllerWithEntity<EntityCategory::File>)
{
	auto Internal = WeakInternal.lock();

	uint8_t data[] = "abcdefg";
	Internal->Write(Entity, data, sizeof(data));
	Internal->Write(Entity, data, sizeof(data), sizeof(data));

	BOOST_CHECK(Internal->Size(Entity) == 2 * sizeof(data));
	
	uint8_t sample[] = "abcdefg\0abcdefg";
	auto readResult = Internal->Read(Entity, sizeof(sample));

	BOOST_CHECK(readResult.second = sizeof(sample));
	BOOST_CHECK(0 == memcmp(readResult.first.get(), sample, readResult.second));

	readResult = Internal->Read(Entity, sizeof(data), sizeof(data));

	BOOST_CHECK(readResult.second = sizeof(data));
	BOOST_CHECK(0 == memcmp(readResult.first.get(), data, readResult.second));
}

BOOST_FIXTURE_TEST_CASE(SimpleGetters, ControllerWithEntity<EntityCategory::File>)
{
   auto Internal = WeakInternal.lock();

   BOOST_CHECK_EQUAL(0u, Internal->Size(Entity));
   BOOST_CHECK(Name == Internal->Name(Entity));
   BOOST_CHECK(Category == Internal->Category(Entity));
   BOOST_CHECK_EQUAL(2u, Internal->Count());

   uint8_t data[] = "abcdefg";
   Internal->Write(Entity, data, sizeof(data));
   BOOST_CHECK_EQUAL(sizeof(data), Internal->Size(Entity));
}

BOOST_AUTO_TEST_SUITE_END()