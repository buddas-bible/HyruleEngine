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

	void SceneManager::LoadScene(IScene*& _scene) noexcept
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



	void SceneManager::SceneStart()
	{

	}

	void SceneManager::OnDisable()
	{
		for (auto& e : currentScene->GetGameObjectList())
		{
			e.second->OnDisable();
		}
	}

	void SceneManager::OnEnable()
	{
		for (auto& e : currentScene->GetGameObjectList())
		{
			e.second->OnEnable();
		}
	}

	void SceneManager::Awake()
	{
		for (auto& e : currentScene->GetGameObjectList())
		{
			e.second->Awake();
		}
	}

	void SceneManager::Start()
	{
		for (auto& e : currentScene->GetGameObjectList())
		{
			e.second->Start();
		}
	}

	void SceneManager::PhysicsUpdate()
	{
		// for (auto& e : currentScene->GetGameObjectList())
		// {
		// 	e.second->P();
		// }
	}

	void SceneManager::FixedUpdate()
	{
		for (auto& e : currentScene->GetGameObjectList())
		{
			e.second->FixedUpdate();
		}
	}

	void SceneManager::Update()
	{
		for (auto& e : currentScene->GetGameObjectList())
		{
			e.second->Update();
		}
	}

	void SceneManager::LateUpdate()
	{
		for (auto& e : currentScene->GetGameObjectList())
		{
			e.second->LateUpdate();
		}
	}

	void SceneManager::OnDestroy()
	{
		for (auto& e : currentScene->GetGameObjectList())
		{
			e.second->OnDestroy();
		}
	}
}