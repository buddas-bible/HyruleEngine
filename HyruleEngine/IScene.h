#pragma once
#include <map>
#include <string>
#include <vector>
#include <queue>

namespace hyrule
{
	class HEntity;
	class HCamera;

	class IScene
	{
	public:
		IScene() = default;
		virtual ~IScene() = default;

	public:
		virtual  std::wstring GetName() abstract;
		virtual  HEntity* CreateGameObject(const std::wstring&) abstract;
		virtual  HEntity* CreateGameObject(const std::wstring&, HEntity*) abstract;
		virtual  std::map<std::wstring, HEntity*>& SceneObjects() abstract;
		// virtual std::vector<GameObject*>& GetActivtedObject() abstract;
		virtual std::queue<HEntity*>& ActivatedQueue() abstract;
		virtual std::queue<HEntity*>& DeactivatedQueue() abstract;
		virtual std::queue<HEntity*>& DestroyedQueue() abstract;

		virtual HCamera* GetMainCamera() abstract;
		virtual void SetMainCamera(HCamera* _camera) abstract;

		virtual void AddActivatedQueue(HEntity*) abstract;
		virtual void AddDeactivatedQueue(HEntity*) abstract;
		virtual void AddDestroyedQueue(HEntity*) abstract;
		
		virtual void Initialize() abstract;
		virtual void Load() abstract;
		virtual void Destroy(HEntity*) abstract;
		virtual void Clear() abstract;
	};


}