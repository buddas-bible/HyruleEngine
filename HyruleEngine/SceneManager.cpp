#include "SceneManager.h"
#include "IScene.h"

#include "GameObject.h"

namespace Hyrule
{
	SceneManager& SceneManager::GetInstance() noexcept
	{
		static SceneManager instance;

		return instance;
	}

	void SceneManager::AddScene(const std::wstring& _name, IScene* _scene) noexcept
	{
		sceneMap.insert(std::make_pair(_name, _scene));
	}

	void SceneManager::RemoveScene(const std::wstring& _name) noexcept
	{
		auto itr = sceneMap.find(_name);

		if (itr == sceneMap.end())
		{
			return;
		}

		sceneMap.erase(itr);
	}

	void SceneManager::RemoveScene(IScene*& _scene) noexcept
	{
		auto itr = sceneMap.find(_scene->GetName());

		if (itr == sceneMap.end())
		{
			return;
		}

		sceneMap.erase(itr);
	}

	void SceneManager::LoadScene(const std::wstring& _name) noexcept
	{
		// current�� ��Ȱ��ȭ
		this->ClearScene();

		currentScene = sceneMap[_name];
		currentScene->Load();
		first = true;
	}

	void SceneManager::LoadScene(IScene* _scene) noexcept
	{
		// current�� ��Ȱ��ȭ
		this->ClearScene();

		currentScene = _scene;
		currentScene->Load();
		first = true;
	}

	void SceneManager::ClearScene()
	{
		if (currentScene != nullptr)
		{
			currentScene->Clear();
		}
	}


	void SceneManager::Initalization()
	{
		if (first == true)
		{
			currentScene->Initialize();

			// Ȱ��ȭ ���� ������Ʈ�� �̺�Ʈ �Լ��� ȣ��
			for (auto& e : currentScene->SceneObjects())
			{
				if (e.second->Activated() != true)
					continue;
				e.second->Awake();
			}

			for (auto& e : currentScene->SceneObjects())
			{
				if (e.second->Activated() != true)
					continue;
				e.second->OnEnable();
			}

			for (auto& e : currentScene->SceneObjects())
			{
				if (e.second->Activated() != true)
					continue;
				e.second->Start();
			}

			first = false;
		}
		else
		{
			// ���� �����ӿ��� Ȱ��ȭ �� ������Ʈ���� �̺�Ʈ �Լ��� ȣ����.
			for (size_t i = 0; i < currentScene->ActivatedQueue().size(); i++)
			{
				auto obj = currentScene->ActivatedQueue().front();
				currentScene->AddActivatedQueue(obj);
				currentScene->ActivatedQueue().pop();

				obj->Awake();

				// Ȱ��ȭ�� ������Ʈ �迭�� ����.
				// currentScene->GetActivtedObject().push_back(obj);
			}

			for (size_t i = 0; i < currentScene->ActivatedQueue().size(); i++)
			{
				auto obj = currentScene->ActivatedQueue().front();
				currentScene->AddActivatedQueue(obj);
				currentScene->ActivatedQueue().pop();

				obj->OnEnable();
			}

			for (size_t i = 0; i < currentScene->ActivatedQueue().size(); i++)
			{
				currentScene->ActivatedQueue().front()->Start();
				currentScene->ActivatedQueue().pop();
			}
		}
	}

	void SceneManager::OnDisable()
	{
		for (auto& e : currentScene->SceneObjects())
		{
			e.second->OnDisable();
		}
	}

	void SceneManager::OnEnable()
	{
		for (auto& e : currentScene->SceneObjects())
		{
			e.second->OnEnable();
		}
	}

	void SceneManager::Awake()
	{
		for (auto& e : currentScene->SceneObjects())
		{
			e.second->Awake();
		}
	}

	void SceneManager::Start()
	{
		for (auto& e : currentScene->SceneObjects())
		{
			if (e.second->Activated() != true)
				continue;
			e.second->Start();
		}
	}

	void SceneManager::PhysicsUpdate()
	{
		// for (auto& e : currentScene->GetGameObjectList())
		// {
		// 	e->P();
		// }
	}

	void SceneManager::FixedUpdate()
	{
		for (auto& e : currentScene->SceneObjects())
		{
			if (e.second->Activated() != true)
				continue;
			e.second->FixedUpdate();
		}
	}

	void SceneManager::OnCollision()
	{
		for (auto& e : currentScene->SceneObjects())
		{
			if (e.second->Activated() != true)
				continue;
			e.second->OnCollisionEnter();
		}
	}

	void SceneManager::Update()
	{
		for (auto& e : currentScene->SceneObjects())
		{
			if (e.second->Activated() != true)
				continue;
			e.second->Update();
		}
	}

	void SceneManager::LateUpdate()
	{
		for (auto& e : currentScene->SceneObjects())
		{
			if (e.second->Activated() != true)
				continue;
			e.second->LateUpdate();
		}
	}

	void SceneManager::OnDestroy()
	{
		for (auto& e : currentScene->SceneObjects())
		{
			e.second->OnDestroy();
		}
	}

	void SceneManager::Decommissioning()
	{
		// ��Ȱ��ȭ �ϱ�� �� ������Ʈ ó�� 
		for (size_t i = 0; i < currentScene->DeactivatedQueue().size(); i++)
		{
			auto obj = currentScene->DeactivatedQueue().front();
			currentScene->ActivatedQueue().pop();

// 			auto itr = std::find(
// 				currentScene->GetActivtedObject().begin(), 
// 				currentScene->GetActivtedObject().end(), 
// 				obj
// 			);
// 
// 			currentScene->GetActivtedObject().erase(itr);
			
			obj->OnDisable();
		}

		// �ı��� ������Ʈ ó��
		for (size_t i = 0; i < currentScene->DestroyedQueue().size(); i++)
		{
			currentScene->DestroyedQueue().front()->OnDisable();
			currentScene->DestroyedQueue().front()->OnDestroy();
			currentScene->DestroyedQueue().pop();
		}
	}
}