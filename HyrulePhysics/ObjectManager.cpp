#include "ObjectManager.h"

#include "Object.h"

namespace Hyrule
{
	namespace Physics
	{
		Object* ObjectManager::GetObject(const std::wstring& _name)
		{
			Object* obj = nullptr;

			auto itr = objectMap.find(_name);
			
			if (itr == objectMap.end())
			{
				obj = CreateObject(_name);
			}
			else
			{
				obj = itr->second;
			}

			return obj;
		}

		Object* ObjectManager::CreateObject(const std::wstring& _name)
		{
			Object* obj = new Object(_name);
			objectMap[_name] = obj;
			return obj;
		}

		ObjectManager& ObjectManager::GetInstance()
		{
			static ObjectManager* instance = nullptr;

			if (!instance)
			{
				instance = new ObjectManager;
			}

			return *instance;
		}

	}
}