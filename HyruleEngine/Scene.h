#pragma once
#include <string>
#include <queue>
#include <map>
#include "IScene.h"
#include "SceneManager.h"
#include "GameObject.h"

namespace Hyrule
{
	class GameObject;
	class Camera;

	class Scene : public IScene
	{
	friend SceneManager;

	public:
		Scene(const std::wstring& _name) noexcept : 
			name(_name), gameObjecs(), mainCamera()
		{
			SceneManager::GetInstance().AddScene(_name, this);
		}
		virtual ~Scene() noexcept = default;

	protected:
		std::wstring name;								// �� �̸�
		std::map<std::wstring, GameObject*> gameObjecs;	// ���� �ִ� ��� ������Ʈ
		std::vector<GameObject*> activatedObject;		// Ȱ��ȭ�� ������Ʈ
		std::queue<GameObject*> objectsToDestroy;		// ������Ʈ �ı�
		std::queue<GameObject*> objectsToActivate;		// ������Ʈ Ȱ��ȭ
		std::queue<GameObject*> objectsToDeactivate;	// ������Ʈ ��Ȱ��ȭ

	public:
		virtual std::wstring GetName() noexcept final
		{
			return this->name;
		}
		virtual GameObject* CreateGameObject(const std::wstring& _name) final
		{
			auto itr = gameObjecs.find(_name);

			if (itr != gameObjecs.end())
			{
				return itr->second;
			}

			GameObject* newObejct = new GameObject(_name, this);
			gameObjecs[_name] = newObejct;

			return newObejct;
		}
		virtual GameObject* CreateGameObject(const std::wstring& _name, GameObject* _parent) final
		{
			GameObject* newObejct = CreateGameObject(_name);
			gameObjecs[_name] = newObejct;
			newObejct->SetParent(newObejct);

			return newObejct;
		}
		virtual std::map<std::wstring, GameObject*>& GetSceneObjectList() final
		{
			return gameObjecs;
		}
		virtual std::vector<GameObject*>& GetActivtedObject() final
		{
			return activatedObject;
		}
		virtual std::queue<GameObject*>& ActivatedQueue() final
		{
			return this->objectsToDeactivate;
		}
		virtual std::queue<GameObject*>& DeactivatedQueue() final
		{
			return this->objectsToActivate;
		}
		virtual std::queue<GameObject*>& DestroyedQueue() final
		{
			return this->objectsToDestroy;
		}

		virtual Camera* GetMainCamera() final
		{
			return this->mainCamera;
		}
		virtual void SetMainCamera(Camera* _camera) final
		{
			this->mainCamera = _camera;
		}
	
		virtual void AddActivatedQueue(GameObject* _object) final
		{
			this->objectsToActivate.push(_object);
		}
		virtual void AddDeactivatedQueue(GameObject* _object) final
		{
			this->objectsToDeactivate.push(_object);
		}
		virtual void AddDestroyedQueue(GameObject* _object) final
		{
			this->objectsToDestroy.push(_object);
		}

	public:
		virtual void Load() noexcept abstract;
		virtual void Clear() noexcept final
		{
			for (auto& e : gameObjecs)
			{
				delete e.second;
			}
			gameObjecs.clear();
		}

	protected:
		Camera* mainCamera;
	};
}


/*
���� ���� ������Ʈ�� ������ ����.
�� ������

*/