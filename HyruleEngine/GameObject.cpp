#include "GameObject.h"

#include "Transform.h"

namespace Hyrule
{
	GameObject::GameObject(const std::wstring& _name, Scene* _scene) :
		name(_name), scene(_scene)
	{
		// 게임 오브젝트는 트랜스폼을 가지고 태어남
		this->transform = this->AddComponent<Transform>();
	}

	const std::wstring& GameObject::GetName()
	{
		return this->name;
	}

	void GameObject::SetName(const std::wstring& _name)
	{
		this->name = _name;
	}

	const std::wstring& GameObject::GetTag()
	{
		return this->tag;
	}

	void GameObject::SetTag(const std::wstring& _tag)
	{
		this->tag = _tag;
	}

	Scene* GameObject::GetScene()
	{
		return scene;
	}


	Transform* GameObject::GetTransform()
	{
		return transform;
	}

	void GameObject::Start()
	{
		for (auto& e : components)
		{
			e.second->Start();
		}
	}

	void GameObject::Update()
	{
		for (auto& e : components)
		{
			e.second->Update();
		}
	}

	void GameObject::FixedUpdate()
	{
		for (auto& e : components)
		{
			e.second->FixedUpdate();
		}
	}

	void GameObject::LastUpdate()
	{
		for (auto& e : components)
		{
			e.second->LastUpdate();
		}
	}

	void GameObject::Render()
	{
		for (auto& e : components)
		{
			e.second->Render();
		}
	}

	void GameObject::OnCollisionEnter()
	{
		for (auto& e : components)
		{
			e.second->OnCollisionEnter();
		}
	}

	void GameObject::OnCollisionStay()
	{
		for (auto& e : components)
		{
			e.second->OnCollisionStay();
		}
	}

	void GameObject::OnCollisionExit()
	{
		for (auto& e : components)
		{
			e.second->OnCollisionExit();
		}
	}

	void GameObject::OnDestroy()
	{
		for (auto& e : components)
		{
			e.second->OnDestroy();
			delete e.second;
			components.erase(e.first);
		}
	}
}