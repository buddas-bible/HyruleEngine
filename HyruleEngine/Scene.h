#pragma once
#include <string>
#include <queue>
#include <map>
#include "IScene.h"
#include "SceneManager.h"
#include "Entity.h"

namespace Hyrule
{
	class Entity;
	class Camera;

	class Scene : public IScene
	{
	friend SceneManager;

	public:
		Scene(const std::wstring& _name);
		virtual ~Scene() = default;
		Scene& operator=(const Scene&) = delete;
		Scene& operator=(Scene&&) = delete;

	protected:
		std::wstring name;								// 씬 이름
		std::map<std::wstring, Entity*> gameObjecs;	// 씬에 있는 모든 오브젝트

	protected:
		std::queue<Entity*> objectsToDestroy;		// 오브젝트 파괴
		std::queue<Entity*> objectsToActivate;		// 오브젝트 활성화
		std::queue<Entity*> objectsToDeactivate;	// 오브젝트 비활성화

	public:
		virtual std::wstring GetName() final;
		virtual Entity* CreateGameObject(const std::wstring& _name) final;
		virtual Entity* CreateGameObject(const std::wstring& _name, Entity* _parent) final;
		virtual std::map<std::wstring, Entity*>& SceneObjects() final;
		virtual std::queue<Entity*>& ActivatedQueue() final;
		virtual std::queue<Entity*>& DeactivatedQueue() final;
		virtual std::queue<Entity*>& DestroyedQueue() final;

		virtual Camera* GetMainCamera() final;
		virtual void SetMainCamera(Camera* _camera) final;
	
		virtual void AddActivatedQueue(Entity* _object) final;
		virtual void AddDeactivatedQueue(Entity* _object) final;
		virtual void AddDestroyedQueue(Entity* _object) final;

	public:
		virtual void Initialize() final;
		virtual void Load() abstract;
		virtual void Destroy(Entity*) final;
		virtual void Clear() final;

	protected:
		Camera* mainCamera;
	};
}


/*
씬은 게임 오브젝트를 가지고 있음.
씬 단위로

*/