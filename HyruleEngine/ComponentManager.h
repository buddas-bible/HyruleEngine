#pragma once
#include "Singleton.h"
#include "InstanceID.h"

#include <string>
#include <map>
#include <unordered_map>
#include <typeinfo>
#include <memory>

#define TYPE_NAME(name) #name


namespace hyrule
{
	class HEntity;
	class HComponent;

	void StringSplit(std::string& _origin, std::string _tar)
	{
		auto itr = _origin.find(_tar);
		if (itr != std::string::npos)
		{
			_origin = _origin.substr(itr + _tar.size());
		}
	}

	class ComponentManager : public Singleton<ComponentManager>
	{
	private:
		class IComponentContainer
		{
		public:
			virtual ~IComponentContainer() = 0;

			virtual std::string GetTypeName() const = 0;
		};

		template <typename _Ty>
		class ComponentContainer : public IComponentContainer
		{
		public:
			friend class ComponentManager;

			using ComponenSharedPtr = std::shared_ptr<_Ty>;
			using ComponenWeakPtr = std::shared_ptr<_Ty>;
			
			std::string GetTypeName() override
			{
				static std::string typeName;

				if (typeName.empty())
				{
					std::string classString = "class ";
					std::string structString = "struct ";
					typeName = typeid(_Ty).name();
					StringSplit(typeName, classString);
					StringSplit(typeName, structString);
				}

				return typeName;
			}

			template <typename... Args>
			ComponenWeakPtr CreateComponent(Args&&... args)
			{
				auto newComponent = std::make_shared<_Ty>(std::forward<Args>(args)...);
				container.push_back(newComponent);
				return newComponent;
			}

		private:
			std::vector<ComponenSharedPtr> container;
		};

	public:
		using ComponentHash = size_t;
		using IContainerSharedPtr = std::shared_ptr<IComponentContainer>;
		template <typename _Ty> using ContainerWeakPtr = std::weak_ptr<ComponentContainer<_Ty>>;
		

		// 컴포넌트 해쉬 아이디와 컴포넌트 리스트 맵
		using ComponentContainerRegistry = std::unordered_map<ComponentHash, IContainerSharedPtr>;

		// 엔티티 아이디와 컴포넌트 아이디맵핑
		using EntityComponentMap = std::unordered_map<InstanceID, std::vector<ComponentID>>;

		// Component의 hash_code와 container
		ComponentContainerRegistry componentContainerRegistry;

		// Entity의 ID와 
		EntityComponentMap entityEngineComponentMap;
		EntityComponentMap entityUserComponentMap;
		
		template <typename _Ty>
		ContainerWeakPtr<_Ty> GetComponentContainer()
		{
			ComponentHash componentHash = typeid(_Ty).hash_code();

			auto itr = componentContainerRegistry.find(componentHash);

			std::shared_ptr<ComponentContainer<_Ty>> container;
			if (itr == componentContainerRegistry.end())
			{
				container = std::make_shared<ComponentContainer<_Ty>>();
				componentContainerRegistry.insert(std::make_pair(componentHash, container));
			}
			else
			{
				container = static_pointer_cast<ComponentContainer<_Ty>>(itr->second);
			}

			return container;
		}

		template <typename _Ty, typename... Args>
		std::weak_ptr<_Ty> CreateComponent(Args&&... args)
		{
			ContainerWeakPtr<_Ty> weakPtr = GetComponentContainer<_Ty>();
			std::weak_ptr<_Ty> result;
			if (!weakPtr.expired())
			{
				result = weakPtr.lock()->CreateComponent(std::forward<Args>(args)...);
			}
			return result;
		}

		template<typename _Ty>
		void EntityComponenetMapping(InstanceID _entityID)
		{
			_Ty* canCasting = dynamic_cast<MonoBehaviour>()

			const size_t componentID = typeid(_Ty).hash_code();
			entityComponentMap[_entityID].push_back(componentID);
		}

		//void EntityComponenetUnmapping(size_t _entityID, size_t _componentID)
		//{
		//	auto itr = entityComponentMap.find(_entityID);

		//	std::vector<size_t>* entityContainer = nullptr;

		//	if (itr == entityComponentMap.end())
		//		return;

		//	entityContainer = itr->second;
		//	
		//	entityContainer->erase(std::ranges::find(*entityContainer, _componentID));
		//}

		void EntityComponenetUnmapping(InstanceID _entityID, ComponentID _componentID)
		{
			auto itr = entityComponentMap.find(_entityID);
			if (entityComponentMap.contains(_entityID))
			{
				auto& components = itr->second;
				components.erase(std::remove(components.begin(), components.end(), _componentID), components.end());
			}
		}

		//int* AddComponent(size_t _entityID)
		//{
		//	const size_t componentID = typeid(int).hash_code();

		//	int* newComponent = new int();

		//	EntityComponenetMapping(_entityID, componentID);

		//	return newComponent;
		//}

		template<typename _Ty>
		std::weak_ptr<_Ty> AddComponent(InstanceID _entityID)
		{
			EntityComponenetMapping<_Ty>(_entityID);
			return new _Ty();
		}

		template<typename _Ty, typename... Args>
		std::shared_ptr<_Ty> AddComponent(const InstanceID& _entityID, Args&&... args)
		{
			EntityComponenetMapping<_Ty>(_entityID);
			return CreateComponent<_Ty>(std::forward<Args>(args)...);
		}

		//int* GetComponent(size_t _entityID)
		//{
		//	const size_t componentID = typeid(int).hash_code();


		//}

		template<typename _Ty>
		std::vector<size_t>* GetComponents(const InstanceID& _entityID)
		{
			auto itr = entityComponentMap.find(_entityID);
			if (itr != entityComponentMap.end())
			{
				return &itr->second;
			}

			return nullptr;
		}

		void RemoveComponent(const InstanceID& _entityID, const ComponentID& _componentID)
		{
			auto itr = entityComponentMap.find(_entityID);
			if (itr != entityComponentMap.end())
			{
				auto& components = itr->second;
				components.erase(
					std::remove(
						components.begin(), components.end(), _componentID), 
					components.end()
				);
			}
		}
	};
}