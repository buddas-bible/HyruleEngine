#pragma once
#include <string>
#include <queue>
#include <map>
#include "IScene.h"
#include "SceneManager.h"
#include "HEntity.h"

namespace hyrule
{
	class HEntity;
	class HCamera;

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
		std::map<std::wstring, HEntity*> gameObjecs;	// 씬에 있는 모든 오브젝트

	protected:
		std::queue<HEntity*> objectsToDestroy;		// 오브젝트 파괴
		std::queue<HEntity*> objectsToActivate;		// 오브젝트 활성화
		std::queue<HEntity*> objectsToDeactivate;	// 오브젝트 비활성화

	public:
		virtual std::wstring GetName() final;
		virtual HEntity* CreateGameObject(const std::wstring& _name) final;
		virtual HEntity* CreateGameObject(const std::wstring& _name, HEntity* _parent) final;
		virtual std::map<std::wstring, HEntity*>& SceneObjects() final;
		virtual std::queue<HEntity*>& ActivatedQueue() final;
		virtual std::queue<HEntity*>& DeactivatedQueue() final;
		virtual std::queue<HEntity*>& DestroyedQueue() final;

		virtual HCamera* GetMainCamera() final;
		virtual void SetMainCamera(HCamera* _camera) final;
	
		virtual void AddActivatedQueue(HEntity* _object) final;
		virtual void AddDeactivatedQueue(HEntity* _object) final;
		virtual void AddDestroyedQueue(HEntity* _object) final;

	public:
		virtual void Initialize() final;
		virtual void Load() abstract;
		virtual void Destroy(HEntity*) final;
		virtual void Clear() final;

	protected:
		HCamera* mainCamera;
	};
}


/*
씬은 게임 오브젝트를 가지고 있음.
씬 단위로

*/