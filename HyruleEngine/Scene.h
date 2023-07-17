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
		std::wstring name;								// �� �̸�
		std::map<std::wstring, GameObject*> gameObjecs;	// ���� �ִ� ��� ������Ʈ

	protected:
		std::vector<GameObject*> activatedObject;		// Ȱ��ȭ�� ������Ʈ
		std::queue<GameObject*> objectsToDestroy;		// ������Ʈ �ı�
		std::queue<GameObject*> objectsToActivate;		// ������Ʈ Ȱ��ȭ
		std::queue<GameObject*> objectsToDeactivate;	// ������Ʈ ��Ȱ��ȭ

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
���� ���� ������Ʈ�� ������ ����.
�� ������

*/