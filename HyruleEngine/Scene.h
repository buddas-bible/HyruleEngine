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
		std::wstring name;								// �� �̸�
		std::map<std::wstring, HEntity*> gameObjecs;	// ���� �ִ� ��� ������Ʈ

	protected:
		std::queue<HEntity*> objectsToDestroy;		// ������Ʈ �ı�
		std::queue<HEntity*> objectsToActivate;		// ������Ʈ Ȱ��ȭ
		std::queue<HEntity*> objectsToDeactivate;	// ������Ʈ ��Ȱ��ȭ

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
���� ���� ������Ʈ�� ������ ����.
�� ������

*/