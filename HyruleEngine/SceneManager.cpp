#include "SceneManager.h"
#include "Scene.h"

#include "GameObject.h"

namespace Hyrule
{
	SceneManager::~SceneManager() noexcept
	{

	}

	SceneManager& SceneManager::GetInstance() noexcept
	{
		static SceneManager instance;

		return instance;
	}

	void SceneManager::AddScene(Scene*& _scene) noexcept
	{
		sceneMap[_scene->GetName()] = _scene;
	}

	void SceneManager::RemoveScene(const std::wstring& _name) noexcept
	{
		auto e = sceneMap[_name];
		delete e;

		sceneMap.erase(_name);
	}

	void SceneManager::RemoveScene(Scene*& _scene) noexcept
	{
		_scene->GetName();
	}

	void SceneManager::LoadScene(const std::wstring& _name) noexcept
	{
		// current를 비활성화
		if (currentScene)
		{
			currentScene->ClearScene();
		}

		currentScene = sceneMap[_name];

		// 해당 씬을 활성화 시키고 현재 씬을 바꿈
		// sceneMap[_name]
		// currentScene = sceneMap[_name];
	}

	void SceneManager::LoadScene(Scene*& _scene) noexcept
	{
		// current를 비활성화
		if (currentScene)
		{
			currentScene->ClearScene();
		}

		currentScene = _scene;
		// 해당 씬을 활성화 시키고 현재 씬을 바꿈
		// sceneMap[_name]
		// currentScene = sceneMap[_name];
	}

	void SceneManager::ClearScene()
	{
		currentScene->ClearScene();
	}

	void SceneManager::Start()
	{
		for (auto& e : currentScene->GetGameObjectList())
		{
			e.second->Start();
		}
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

	void SceneManager::LastUpdate()
	{
		for (auto& e : currentScene->GetGameObjectList())
		{
			e.second->LastUpdate();
		}
	}
}