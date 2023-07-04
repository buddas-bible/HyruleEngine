#pragma once




#include <map>
#include <vector>
#include <string>
#include <typeinfo>

#include "RigidBody.h"

namespace Hyrule
{
	class Component;
	class RigidBody;

	class ComponentManager
	{
		class IComponentBox
		{
			IComponentBox();
			virtual ~IComponentBox() {}
			virtual std::wstring GetComponentName();
			virtual void DestroyComponent();
		};

		class ComponentBox
		{
			ComponentBox();
			virtual ~ComponentBox() {}
			virtual std::wstring GetComponentName();
			virtual void DestroyComponent();
		};

		// 컴포넌트 아이디와 그 컴포넌트들을 모아둔 리스트.
		std::map<unsigned int, std::vector<Component*>*> componentList;
	
	public:
		// template <typename T>
		std::vector<RigidBody*>* GetComponentList()
		{
			std::vector<RigidBody*>* result = nullptr;

			auto hash = typeid(RigidBody).hash_code();

			auto itr = this->componentList.find(hash);

			if (itr == componentList.end())
			{
				result = new std::vector<RigidBody*>();
				componentList[hash] = result;
			}
			else
			{
				result = static_cast<std::vector<int*>*>(itr->second);
			}

			return result;
		}
	};
}

