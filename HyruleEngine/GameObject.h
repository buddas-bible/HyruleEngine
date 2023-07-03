#pragma once

#include <string>
#include <vector>

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
		std::wstring tag;					// �±�
		std::wstring name;					// �̸�

		std::vector<Component*> components;	// ������Ʈ ����Ʈ
		Transform* transform;				// Ʈ������
		
		// ����Ƽ������ ���� ������Ʈ�� ���� ������ �� �־��µ�...
		Scene* scene;						// ���� ���Ե� ��..
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

		// newComponent = dynamic_cast<Component>(newComponent);

		if (newComponent == nullptr)
		{
			throw("������Ʈ ���� ����");
		}

		return (component*)newComponent;
	}

	template <typename component>
	component* GameObject::GetComponent()
	{
		for (auto e : components)
		{
			// �� ��� �ۿ� ���°ɱ�?
			auto pointer = dynamic_cast<component*>(e);

			if (pointer != nullptr)
			{
				return e;
			}
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

		components.push_back(newComponent);
		return newComponent;
	}
}