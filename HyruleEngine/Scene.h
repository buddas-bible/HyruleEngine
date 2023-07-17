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
		Scene(const std::wstring& _name) noexcept;
		virtual ~Scene() noexcept = default;
		Scene& operator=(const Scene&) noexcept = delete;
		Scene& operator=(Scene&&) noexcept = delete;

	protected:
		std::wstring name;								// 씬 이름
		std::map<std::wstring, GameObject*> gameObjecs;	// 씬에 있는 모든 오브젝트

	protected:
		std::vector<GameObject*> activatedObject;		// 활성화된 오브젝트
		std::queue<GameObject*> objectsToDestroy;		// 오브젝트 파괴
		std::queue<GameObject*> objectsToActivate;		// 오브젝트 활성화
		std::queue<GameObject*> objectsToDeactivate;	// 오브젝트 비활성화

	public:
		virtual std::wstring GetName() noexcept final;
		virtual GameObject* CreateGameObject(const std::wstring& _name) final;
		virtual GameObject* CreateGameObject(const std::wstring& _name, GameObject* _parent) final;
		virtual std::map<std::wstring, GameObject*>& GetSceneObjectList() final;
		virtual std::vector<GameObject*>& GetActivtedObject() final;
		virtual std::queue<GameObject*>& ActivatedQueue() final;
		virtual std::queue<GameObject*>& DeactivatedQueue() final;
		virtual std::queue<GameObject*>& DestroyedQueue() final;

		virtual Camera* GetMainCamera() final;
		virtual void SetMainCamera(Camera* _camera) final;
	
		virtual void AddActivatedQueue(GameObject* _object) final;
		virtual void AddDeactivatedQueue(GameObject* _object) final;
		virtual void AddDestroyedQueue(GameObject* _object) final;

	public:
		virtual void Initialize() noexcept final;
		virtual void Load() noexcept abstract;
		virtual void Destroy(GameObject*) noexcept final;
		virtual void Clear() noexcept final;

	protected:
		Camera* mainCamera;
	};
}


/*
씬은 게임 오브젝트를 가지고 있음.
씬 단위로

*/