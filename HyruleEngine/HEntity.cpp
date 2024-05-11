#include "HEntity.h"

#include "HTransform.h"
#include "Scene.h"

namespace hyrule
{
	HEntity::HEntity(const std::wstring& _name, Scene* _scene) :
		scene(_scene)
	{
		// 게임 오브젝트는 트랜스폼을 가지고 태어남
		this->transform = this->AddComponent<HTransform>();
	}

	Scene* HEntity::GetScene()
	{
		return scene;
	}

	HTransform* HEntity::GetTransform()
	{
		return transform;
	}

	const std::string& HEntity::GetTag()
	{
		return this->tag;
	}

	void HEntity::SetTag(const std::string& _tag)
	{
		this->tag = std::move(_tag);
	}

	void HEntity::SetActive(bool _active)
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

	bool HEntity::Activated()
	{
		return this->activeSelf;
	}

	void HEntity::OnDisable()
	{
		for (auto& e : components)
		{
			// e.second->OnDisable();
		}
		activeSelf = false;
	}

	void HEntity::OnEnable()
	{
		for (auto& e : components)
		{
			// e.second->OnEnable();
		}
		activeSelf = true;
	}

	void HEntity::Awake()
	{
		for (auto& e : components)
		{
			// e.second->Awake();
		}
	}

	void HEntity::Start()
	{
		for (auto& e : components)
		{
			// e.second->Start();
		}
	}

	void HEntity::FixedUpdate()
	{
		for (auto& e : components)
		{
			// e.second->FixedUpdate();
		}
	}

	void HEntity::Update()
	{
		for (auto& e : components)
		{
			// e.second->Update();
		}
	}

	void HEntity::LateUpdate()
	{
		for (auto& e : components)
		{
			// e.second->LateUpdate();
		}
	}

	void HEntity::OnDestroy()
	{
		for (auto& e : components)
		{
			// e.second->OnDestroy();
			// delete e.second;
		}

		components.clear();
	}
}