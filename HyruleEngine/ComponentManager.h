#pragma once
#include <string>
#include <map>
#include <unordered_map>
#include <typeinfo>
#include "Singleton.h"

#define TYPE_NAME(name) #name


namespace Hyrule
{
	class Entity;
	class Component;

	class ComponentManager : public Singleton<ComponentManager>
	{
	private:
		class IComponentContainer
		{
		public:
			virtual ~IComponentContainer() = 0;

			virtual std::string GetTypeName() const = 0;
		};

		template <typename T>
		class ComponentContainer : public IComponentContainer
		{
			~ComponentContainer() override = default;

		public:
			std::string GetTypeName() const override
			{
				static std::string typeName{ decltype(T)};

				return typeName;
			}

			T* CreateComponent()
			{

			}

		private:
			std::vector<T> container;
		};

	public:
		using ComponentContainerRegistry = std::unordered_map<size_t, IComponentContainer*>;
		ComponentContainerRegistry componentContainerRegistry;
		
		template <typename T>
		ComponentContainer<T>* GetComponentContainer()
		{
			size_t componentID = typeid(T).hash_code();

			auto itr = componentContainerRegistry.find(componentID);
			ComponentContainer<T>* container = nullptr;

			if (itr == componentContainerRegistry.end())
			{
				container = new ComponentContainer<T>();
				componentContainerRegistry.insert(std::make_pair(componentID, container));
			}
			else
			{
				container = static_cast<ComponentContainer<T>*>(itr->second);
			}

			return container;
		}

		using EntityComponentMap = std::map<size_t, std::vector<size_t>*>;
		EntityComponentMap entityComponentMap;

		void EntityComponenetMapping(size_t _entityID, size_t componentID)
		{
			// 
			auto itr = entityComponentMap.find(_entityID);

			if (itr == entityComponentMap.end())
			{

			}

		}

		void EntityComponenetUnmapping(size_t _entityID, size_t _componentID)
		{
			auto itr = entityComponentMap.find(_entityID);

			std::vector<size_t>* entityContainer = nullptr;

			if (itr == entityComponentMap.end())
				return;

			entityContainer = itr->second;
			
			entityContainer->erase(std::ranges::find(*entityContainer, _componentID));
		}

		int* AddComponent(size_t _entityID)
		{
			const size_t componentID = typeid(int).hash_code();

			int* newComponent = new int();

			EntityComponenetMapping(_entityID, componentID);

			return newComponent;
		}

		int* GetComponent(size_t _entityID)
		{
			const size_t componentID = typeid(int).hash_code();


		}

		void RemoveComponent(Entity*)
		{

		}
	};
}