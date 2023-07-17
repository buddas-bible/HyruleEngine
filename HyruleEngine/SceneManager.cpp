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
		sceneMap[_name] = _scene;
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
		// current를 비활성화
		if (currentScene != nullptr)
		{
			currentScene->Clear();
		}

		currentScene = sceneMap[_name];
		currentScene->Load();
	}

	void SceneManager::LoadScene(IScene* _scene) noexcept
	{
		// current를 비활성화
		if (currentScene != nullptr)
		{
			currentScene->Clear();
		}

		currentScene = _scene;
		currentScene->Load();
	}

	void SceneManager::ClearScene()
	{
		currentScene->Clear();
	}



	void SceneManager::Initalization()
	{
		if (first == true)
		{

		}
		else
		{
			// 우선 모든 오브젝트는 기본이 활성 상태.
			// Start에서 비활성화
			for (size_t i = 0; i < currentScene->ActivatedQueue().size(); i++)
			{
				auto obj = currentScene->ActivatedQueue().front();
				obj->Awake();
				currentScene->AddActivatedQueue(obj);
				currentScene->ActivatedQueue().pop();
			}

			for (size_t i = 0; i < currentScene->ActivatedQueue().size(); i++)
			{
				currentScene->ActivatedQueue().front()->OnEnable();
				currentScene->ActivatedQueue().pop();
			}
		}
	}

	void SceneManager::OnDisable()
	{
		for (auto& e : currentScene->GetSceneObjectList())
		{
			e.second->OnDisable();
		}
	}

	void SceneManager::OnEnable()
	{
		for (auto& e : currentScene->GetSceneObjectList())
		{
			e.second->OnEnable();
		}
	}

	void SceneManager::Awake()
	{
		for (auto& e : currentScene->GetSceneObjectList())
		{
			e.second->Awake();
		}
	}

	void SceneManager::Start()
	{
		for (auto& e : currentScene->GetActivtedObject())
		{
			e->Start();
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
		for (auto& e : currentScene->GetActivtedObject())
		{
			e->FixedUpdate();
		}
	}

	void SceneManager::Update()
	{
		for (auto& e : currentScene->GetActivtedObject())
		{
			e->Update();
		}
	}

	void SceneManager::LateUpdate()
	{
		for (auto& e : currentScene->GetActivtedObject())
		{
			e->LateUpdate();
		}
	}

	void SceneManager::OnDestroy()
	{
		for (auto& e : currentScene->GetSceneObjectList())
		{
			e.second->OnDestroy();
		}
	}

	void SceneManager::Decommissioning()
	{
		// 우선 모든 오브젝트는 기본이 활성 상태.
		// Start에서 비활성화
		for (size_t i = 0; i < currentScene->DeactivatedQueue().size(); i++)
		{
			currentScene->DeactivatedQueue().front()->OnDisable();
			currentScene->ActivatedQueue().pop();
		}

		for (size_t i = 0; i < currentScene->DestroyedQueue().size(); i++)
		{
			currentScene->DestroyedQueue().front()->OnDestroy();
			currentScene->DestroyedQueue().pop();
		}
	}
}