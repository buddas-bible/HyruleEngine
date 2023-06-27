#include "SceneManager.h"
#include "Scene.h"

namespace Hyrule
{
	SceneManager::~SceneManager() noexcept
	{

	}

	SceneManager* SceneManager::GetInstance()
	{
		static SceneManager* instance = nullptr;

		if (instance == nullptr)
		{
			instance = new SceneManager;
		}

		return instance;
	}

	void SceneManager::AddScene(const std::wstring& _name, Scene*& _scene)
	{
		sceneMap[_name] = _scene;
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
		// currentScene

		// 해당 씬을 활성화 시키고 현재 씬을 바꿈
		// sceneMap[_name]
		// currentScene = sceneMap[_name];
	}

	void SceneManager::LoadScene(Scene*& _scene) noexcept
	{
		// current를 비활성화
		// currentScene

		// 해당 씬을 활성화 시키고 현재 씬을 바꿈
		// sceneMap[_name]
		// currentScene = sceneMap[_name];
	}
}