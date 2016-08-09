#include <boost/filesystem.hpp>
#include "FSController.h"

struct ControllerFixture
{
   ControllerFixture()
      : Internal(std::make_unique<NFileSystem::Controller>())
   { }

   ~ControllerFixture()
   {
      boost::filesystem::remove(boost::filesystem::current_path() /= "fs.rawdata");
   }

   std::shared_ptr<NFileSystem::Controller> Internal;
};

template<NFileSystem::EntityCategory category>
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

	std::weak_ptr<NFileSystem::Controller> WeakInternal;
   NFileSystem::EntityHandle Root;
   NFileSystem::EntityHandle Entity;
	std::wstring Name;
   NFileSystem::EntityCategory Category = category;
};
