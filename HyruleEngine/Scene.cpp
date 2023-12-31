#include "Scene.h"

#include "GameObject.h"
#include "Camera.h"

namespace Hyrule
{
	Scene::Scene(const std::wstring& _name) noexcept :
		name(_name), gameObjecs(), mainCamera()
	{
		SceneManager::GetInstance().AddScene(_name, this);

		GameObject* camera = CreateGameObject(L"Camera");
		mainCamera = camera->AddComponent<Camera>();
	}

	std::wstring Scene::GetName() noexcept
	{
		return this->name;
	}

	GameObject* Scene::CreateGameObject(const std::wstring& _name)
	{
		auto itr = gameObjecs.find(_name);

		if (itr != gameObjecs.end())
		{
			return itr->second;
		}

		GameObject* newObejct = new GameObject(_name, this);
		gameObjecs.insert(make_pair(_name, newObejct));

		return newObejct;
	}

	GameObject* Scene::CreateGameObject(const std::wstring& _name, GameObject* _parent)
	{
		GameObject* newObejct = CreateGameObject(_name);
		gameObjecs[_name] = newObejct;
		newObejct->SetParent(newObejct);

		return newObejct;
	}

	std::map<std::wstring, GameObject*>& Scene::SceneObjects()
	{
		return this->gameObjecs;
	}

	std::queue<GameObject*>& Scene::ActivatedQueue()
	{
		return this->objectsToDeactivate;
	}

	std::queue<GameObject*>& Scene::DeactivatedQueue()
	{
		return this->objectsToActivate;
	}

	std::queue<GameObject*>& Scene::DestroyedQueue()
	{
		return this->objectsToDestroy;
	}

	Camera* Scene::GetMainCamera()
	{
		return this->mainCamera;
	}

	void Scene::SetMainCamera(Camera* _camera)
	{
		this->mainCamera = _camera;
	}

	void Scene::AddActivatedQueue(GameObject* _object)
	{
		this->objectsToActivate.push(_object);
	}

	void Scene::AddDeactivatedQueue(GameObject* _object)
	{
		this->objectsToDeactivate.push(_object);
	}

	void Scene::AddDestroyedQueue(GameObject* _object)
	{
		this->objectsToDestroy.push(_object);
	}

	void Scene::Initialize() noexcept
	{
		if (!objectsToActivate.empty())
		{
			for (auto i = 0; i < objectsToActivate.size(); i++)
			{
				auto e{ objectsToActivate.front() };

				if (e != nullptr)
				{
					delete e;
				}

				objectsToActivate.pop();
			}
		}
		if (!objectsToDestroy.empty())
		{
			auto e{ objectsToDestroy.front() };

			if (e != nullptr)
			{
				delete e;
			}

			objectsToDestroy.pop();
		}
		if (!objectsToDeactivate.empty())
		{
			auto e{ objectsToDeactivate.front() };

			if (e != nullptr)
			{
				delete e;
			}

			objectsToDeactivate.pop();
		}
	}

	void Scene::Destroy(GameObject* _gameObject) noexcept
	{
		this->objectsToDestroy.push(_gameObject);
	}

	void Scene::Clear() noexcept
	{
		for (auto& e: gameObjecs)
		{
			e.second->OnDestroy();
		}
	}
}
