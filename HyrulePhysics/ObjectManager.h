#pragma once
 #include "Manager.h"

#include <string>
#include <map>
#include <vector>

namespace Hyrule
{
	struct Matrix4x4;

	namespace Physics
	{
		class Object;

		class ObjectManager : public Manager<ObjectManager>
		{
		public:
			ObjectManager() noexcept = default;
			~ObjectManager() noexcept = default;
			ObjectManager(const ObjectManager&) = delete;
			void operator=(const ObjectManager&) = delete;

		private:
			std::map<std::wstring, Object*> objectMap;

		public:
			Object*& GetObject(const std::wstring&);
			Object*& CreateObject(const std::wstring&);
		};
	}
}

