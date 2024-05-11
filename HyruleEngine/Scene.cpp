#include "Scene.h"

#include "HEntity.h"
#include "HCamera.h"

namespace hyrule
{
	Scene::Scene(const std::wstring& _name) :
		name(_name), gameObjecs(), mainCamera()
	{
		SceneManager::Instance()->AddScene(_name, this);

		HEntity* camera = CreateGameObject(L"Camera");
		mainCamera = camera->AddComponent<HCamera>();
	}

	std::wstring Scene::GetName()
	{
		return this->name;
	}

	HEntity* Scene::CreateGameObject(const std::wstring& _name)
	{
		auto itr = gameObjecs.find(_name);

		if (itr != gameObjecs.end())
		{
			return itr->second;
		}

		HEntity* newObejct = new HEntity(_name, this);
		gameObjecs.insert(make_pair(_name, newObejct));

		return newObejct;
	}

	HEntity* Scene::CreateGameObject(const std::wstring& _name, HEntity* _parent)
	{
		HEntity* newObejct = CreateGameObject(_name);
		gameObjecs[_name] = newObejct;

		return newObejct;
	}

	std::map<std::wstring, HEntity*>& Scene::SceneObjects()
	{
		return this->gameObjecs;
	}

	std::queue<HEntity*>& Scene::ActivatedQueue()
	{
		return this->objectsToDeactivate;
	}

	std::queue<HEntity*>& Scene::DeactivatedQueue()
	{
		return this->objectsToActivate;
	}

	std::queue<HEntity*>& Scene::DestroyedQueue()
	{
		return this->objectsToDestroy;
	}

	HCamera* Scene::GetMainCamera()
	{
		return this->mainCamera;
	}

	void Scene::SetMainCamera(HCamera* _camera)
	{
		this->mainCamera = _camera;
	}

	void Scene::AddActivatedQueue(HEntity* _object)
	{
		this->objectsToActivate.push(_object);
	}

	void Scene::AddDeactivatedQueue(HEntity* _object)
	{
		this->objectsToDeactivate.push(_object);
	}

	void Scene::AddDestroyedQueue(HEntity* _object)
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

	void Scene::Destroy(HEntity* _gameObject)
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
