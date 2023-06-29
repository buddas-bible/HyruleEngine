#include "Scene.h"

#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"

namespace Hyrule
{
	Scene::Scene(const std::wstring& _name) noexcept : 
		name(_name), gameObjectList(), mainCamera()
	{

	}

	std::wstring Scene::GetName() noexcept
	{
		return name;
	}

	GameObject* Scene::AddGameObject(const std::wstring& _name)
	{
		auto e = CreateGameObject(_name);

		gameObjectList[_name] = e;

		return e;
	}

	GameObject* Scene::AddGameObject(const std::wstring& _name, GameObject* _object)
	{
		auto e = CreateGameObject(_name);

		gameObjectList[_name] = e;

		return e;
	}

	std::map<std::wstring, GameObject*>& Scene::GetGameObjectList()
	{
		return gameObjectList;
	}

	void Scene::ClearScene()
	{
		for (auto& e : gameObjectList)
		{
			gameObjectList.erase(e.second->GetName());
			delete e.second;
		}

		gameObjectList.clear();
	}

	Camera* Scene::GetMainCamera()
	{
		return this->mainCamera;
	}

	GameObject* Scene::CreateGameObject(const std::wstring& _name)
	{
		auto e = gameObjectList[_name];

		if (e == nullptr)
		{
			return new GameObject(_name, this);
		}

		return e;
	}
}