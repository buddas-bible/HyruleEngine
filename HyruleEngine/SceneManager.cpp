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

	void SceneManager::AddScene(const std::wstring& _name, Scene*& _scene) noexcept
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
		// current�� ��Ȱ��ȭ
		// currentScene

		// �ش� ���� Ȱ��ȭ ��Ű�� ���� ���� �ٲ�
		// sceneMap[_name]
		// currentScene = sceneMap[_name];
	}

	void SceneManager::LoadScene(Scene*& _scene) noexcept
	{
		// current�� ��Ȱ��ȭ
		// currentScene

		// �ش� ���� Ȱ��ȭ ��Ű�� ���� ���� �ٲ�
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