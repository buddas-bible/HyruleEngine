#pragma once
// #include "IManager.h"

#include <string>
#include <map>
#include <vector>

namespace Hyrule
{
	struct Matrix4x4;

	namespace Physics
	{
		class Object;

		class ObjectManager//  : public IManager<ObjectManager>
		{
		public:
			ObjectManager() noexcept = default;
			~ObjectManager() noexcept = default;
			ObjectManager(const ObjectManager&) = delete;
			void operator=(const ObjectManager&) = delete;

		private:
			std::map<std::wstring, Object*> objectMap;
			// std::vector<Object*>			

		public:
			static ObjectManager& GetInstance();

			Object* GetObject(const std::wstring&);
			Object* CreateObject(const std::wstring&);
		};
	}
}

