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
		template <typename component>
		component* CreateComponent();

		template <typename component>
		component* GetComponent();

		template <typename component>
		component* AddComponent();
	};

	template <typename component>
	component* GameObject::CreateComponent()
	{
		Component* newComponent = dynamic_cast<Component*>(new component(this));

		if (newComponent == nullptr)
		{
			throw("������Ʈ ���� ����");
		}

		return (component*)newComponent;
	}

	template <typename component>
	component* GameObject::GetComponent()
	{
		auto id = typeid(component).hash_code();

		auto pointer = components[id];

		if (pointer != nullptr)
		{
			return pointer;
		}

		return nullptr;
	}

	template <typename component>
	component* GameObject::AddComponent()
	{
		component* newComponent = CreateComponent<component>();

		if (newComponent == nullptr)
		{
			return nullptr;
		}

		components[typeid(newComponent).hash_code()] = newComponent;
		return newComponent;
	}
}