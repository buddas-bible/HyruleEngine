#pragma once
#include "Object.h"
#include <map>
#include <typeinfo>

namespace Hyrule
{
	class Component;
	class Transform;
	class Scene;

	class Entity final : public Object
	{
	public:
		Entity() = delete;
		Entity(const std::wstring& _name, Scene* _scene);
		~Entity() = default;

	private:
		Scene* scene;									// ���� ���Ե� ��..
		Transform* transform;							// Ʈ������
		
		std::string tag;								// �±�
		bool activeSelf{ true }; 

		std::map<size_t, Component*> components;	// ������Ʈ ����Ʈ

	public:
		Scene* GetScene();
		Transform* GetTransform();

		const std::string& GetTag();
		void SetTag(const std::string&);

	public:
		void SetActive(bool);
		bool Activated();

		void Awake();
		void OnEnable();

		void Start();
		void FixedUpdate();
		void Update();
		void LateUpdate();

		void OnDisable();
		void OnDestroy();

	public:
		template <typename component>
		component* CreateComponent();

		template <typename component>
		component* GetComponent();

		template <typename component>
		component* AddComponent();
	};

	template <typename component>
	component* Entity::CreateComponent()
	{
		Component* newComponent = dynamic_cast<Component*>(new component(this));

		if (newComponent == nullptr)
		{
			throw("������Ʈ ���� ����");
		}

		return (component*)newComponent;
	}

	template <typename component>
	component* Entity::GetComponent()
	{
		auto id = typeid(component).hash_code();

		auto itr = components.find(id);

		if (itr != components.end())
		{
			return static_cast<component*>(itr->second);
		}

		return nullptr;
	}

	template <typename component>
	component* Entity::AddComponent()
	{
		component* newComponent = ComponentManager::Instance()->AddComponent<component>(instanceID);

		if (newComponent == nullptr)
		{
			return nullptr;
		}

		components[typeid(newComponent).hash_code()] = newComponent;
		return newComponent;
	}
}