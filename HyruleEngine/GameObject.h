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
		std::wstring tag;								// 태그
		std::wstring name;								// 이름

		std::map<unsigned int, Component*> components;	// 컴포넌트 리스트
		Transform* transform;							// 트랜스폼
		
		// 유니티에서는 게임 오브젝트가 씬에 접근할 수 있었는데...
		Scene* scene;									// 내가 포함된 씬..
														// 컴포넌트들이 게임 오브젝트를 통해서 씬 이름 같은걸 알아내나?

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
			throw("컴포넌트 생성 오류");
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