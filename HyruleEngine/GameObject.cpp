#include "GameObject.h"

#include "Transform.h"
#include "Scene.h"

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

	void GameObject::SetParent(GameObject* _parent)
	{
		this->transform->SetParent(_parent->transform);
	}

	void GameObject::SetActive(bool _active)
	{
		if (_active == true && activeSelf == false)
		{
			scene->AddActivatedQueue(this);
			for (auto& e : transform->Getchildren())
			{
				e->gameObject->SetActive(_active);
			}
		}
		else if (_active == false && activeSelf == true)
		{
			scene->AddDeactivatedQueue(this);
			for (auto& e : transform->Getchildren())
			{
				e->gameObject->SetActive(_active);
			}
		}
	}

	bool GameObject::Activated()
	{
		return this->activeSelf;
	}

	void GameObject::OnDisable()
	{
		for (auto& e : components)
		{
			e.second->OnDisable();
		}
		activeSelf = false;
	}

	void GameObject::OnEnable()
	{
		for (auto& e : components)
		{
			e.second->OnEnable();
		}
		activeSelf = true;
	}

	void GameObject::Awake()
	{
		for (auto& e : components)
		{
			e.second->Awake();
		}
	}

	void GameObject::Start()
	{
		for (auto& e : components)
		{
			e.second->Start();
		}
	}

	void GameObject::FixedUpdate()
	{
		for (auto& e : components)
		{
			e.second->FixedUpdate();
		}
	}

	void GameObject::PrePhysicsUpdate()
	{
		for (auto& e : components)
		{
			e.second->PrePhysicsUpdate();
		}
	}

	void GameObject::PhysicsUpdate()
	{
		for (auto& e : components)
		{
			e.second->PhysicsUpdate();
		}
	}

	void GameObject::LatePhysicsUpdate()
	{
		for (auto& e : components)
		{
			e.second->LatePhysicsUpdate();
		}
	}

	void GameObject::Update()
	{
		for (auto& e : components)
		{
			e.second->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (auto& e : components)
		{
			e.second->LateUpdate();
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
		}

		components.clear();
	}
}