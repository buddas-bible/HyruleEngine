#include "Scene.h"

#include "Entity.h"
#include "Camera.h"

namespace Hyrule
{
	Scene::Scene(const std::wstring& _name) :
		name(_name), gameObjecs(), mainCamera()
	{
		SceneManager::GetInstance().AddScene(_name, this);

		Entity* camera = CreateGameObject(L"Camera");
		mainCamera = camera->AddComponent<Camera>();
	}

	std::wstring Scene::GetName()
	{
		return this->name;
	}

	Entity* Scene::CreateGameObject(const std::wstring& _name)
	{
		auto itr = gameObjecs.find(_name);

		if (itr != gameObjecs.end())
		{
			return itr->second;
		}

		Entity* newObejct = new Entity(_name, this);
		gameObjecs.insert(make_pair(_name, newObejct));

		return newObejct;
	}

	Entity* Scene::CreateGameObject(const std::wstring& _name, Entity* _parent)
	{
		Entity* newObejct = CreateGameObject(_name);
		gameObjecs[_name] = newObejct;
		newObejct->SetParent(newObejct);

		return newObejct;
	}

	std::map<std::wstring, Entity*>& Scene::SceneObjects()
	{
		return this->gameObjecs;
	}

	std::queue<Entity*>& Scene::ActivatedQueue()
	{
		return this->objectsToDeactivate;
	}

	std::queue<Entity*>& Scene::DeactivatedQueue()
	{
		return this->objectsToActivate;
	}

	std::queue<Entity*>& Scene::DestroyedQueue()
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

	void Scene::AddActivatedQueue(Entity* _object)
	{
		this->objectsToActivate.push(_object);
	}

	void Scene::AddDeactivatedQueue(Entity* _object)
	{
		this->objectsToDeactivate.push(_object);
	}

	void Scene::AddDestroyedQueue(Entity* _object)
	{
		this->objectsToDestroy.push(_object);
	}

	void Scene::Initialize()
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

	void Scene::Destroy(Entity* _gameObject)
	{
		this->objectsToDestroy.push(_gameObject);
	}

	void Scene::Clear()
	{
		for (auto& e: gameObjecs)
		{
			e.second->OnDestroy();
		}
	}
}
