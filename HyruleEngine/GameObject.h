#pragma once

#include <string>
#include <map>
#include <typeinfo>

namespace Hyrule
{
	class Component;
	class Transform;
	class Scene;

	class GameObject
	{
	public:
		GameObject() = delete;
		GameObject(const std::wstring& _name, Scene* _scene);
		~GameObject() = default;

	private:
		std::wstring tag;								// �±�
		std::wstring name;								// �̸�

		std::map<unsigned int, Component*> components;	// ������Ʈ ����Ʈ
		Transform* transform;							// Ʈ������
		
		// ����Ƽ������ ���� ������Ʈ�� ���� ������ �� �־��µ�...
		Scene* scene;									// ���� ���Ե� ��..
														// ������Ʈ���� ���� ������Ʈ�� ���ؼ� �� �̸� ������ �˾Ƴ���?

	public:
		const std::wstring& GetName();
		void SetName(const std::wstring&);
		const std::wstring& GetTag();
		void SetTag(const std::wstring&);
		Scene* GetScene();

		Transform* GetTransform();

	public:
		void Start();
		void Update();
		void FixedUpdate();
		void LastUpdate();
		void Render();

		void OnCollisionEnter();
		void OnCollisionStay();
		void OnCollisionExit();

		void OnDestroy();

	public:
		template <typename ComponentType>
		ComponentType* CreateComponent();

		template <typename ComponentType>
		ComponentType* GetComponent();

		template <typename ComponentType>
		ComponentType* AddComponent();
	};

	template <typename ComponentType>
	ComponentType* GameObject::CreateComponent()
	{
		Component* newComponent = dynamic_cast<Component*>(new ComponentType(this));

		if (newComponent == nullptr)
		{
			throw("������Ʈ ���� ����");
		}

		return (ComponentType*)newComponent;
	}

	template <typename ComponentType>
	ComponentType* GameObject::GetComponent()
	{
		auto id = typeid(ComponentType).hash_code();

		auto itr = components.find(id);

		if (itr == components.end())
		{
			return nullptr;
		}

		return static_cast<ComponentType*>(itr->second);
	}

	template <typename ComponentType>
	ComponentType* GameObject::AddComponent()
	{
		ComponentType* newComponent = CreateComponent<ComponentType>();

		if (newComponent == nullptr)
		{
			return nullptr;
		}

		components[typeid(newComponent).hash_code()] = newComponent;
		return newComponent;
	}
}