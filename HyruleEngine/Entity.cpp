#include "Entity.h"

#include "Transform.h"
#include "Scene.h"

namespace Hyrule
{
	Entity::Entity(const std::wstring& _name, Scene* _scene) :
		scene(_scene)
	{
		// 게임 오브젝트는 트랜스폼을 가지고 태어남
		this->transform = this->AddComponent<Transform>();
	}

	Scene* Entity::GetScene()
	{
		return scene;
	}

	Transform* Entity::GetTransform()
	{
		return transform;
	}

	const std::string& Entity::GetTag()
	{
		return this->tag;
	}

	void Entity::SetTag(const std::string& _tag)
	{
		this->tag = std::move(_tag);
	}

	void Entity::SetActive(bool _active)
	{
		if (_active && !activeSelf)
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

	bool Entity::Activated()
	{
		return this->activeSelf;
	}

	void Entity::OnDisable()
	{
		for (auto& e : components)
		{
			// e.second->OnDisable();
		}
		activeSelf = false;
	}

	void Entity::OnEnable()
	{
		for (auto& e : components)
		{
			// e.second->OnEnable();
		}
		activeSelf = true;
	}

	void Entity::Awake()
	{
		for (auto& e : components)
		{
			// e.second->Awake();
		}
	}

	void Entity::Start()
	{
		for (auto& e : components)
		{
			// e.second->Start();
		}
	}

	void Entity::FixedUpdate()
	{
		for (auto& e : components)
		{
			// e.second->FixedUpdate();
		}
	}

	void Entity::Update()
	{
		for (auto& e : components)
		{
			// e.second->Update();
		}
	}

	void Entity::LateUpdate()
	{
		for (auto& e : components)
		{
			// e.second->LateUpdate();
		}
	}

	void Entity::OnDestroy()
	{
		for (auto& e : components)
		{
			// e.second->OnDestroy();
			// delete e.second;
		}

		components.clear();
	}
}