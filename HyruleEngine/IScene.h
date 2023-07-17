#pragma once
#include <map>
#include <string>
#include <vector>
#include <queue>

namespace Hyrule
{
	class GameObject;
	class Camera;

	class IScene
	{
	public:
		IScene() noexcept = default;
		virtual ~IScene() noexcept = default;

	public:
		virtual  std::wstring GetName() noexcept abstract;
		virtual  GameObject* CreateGameObject(const std::wstring&) abstract;
		virtual  GameObject* CreateGameObject(const std::wstring&, GameObject*) abstract;
		virtual  std::map<std::wstring, GameObject*>& GetSceneObjectList() abstract;
		virtual std::vector<GameObject*>& GetActivtedObject() abstract;
		virtual std::queue<GameObject*>& ActivatedQueue() abstract;
		virtual std::queue<GameObject*>& DeactivatedQueue() abstract;
		virtual std::queue<GameObject*>& DestroyedQueue() abstract;

		virtual Camera* GetMainCamera() abstract;
		virtual void SetMainCamera(Camera* _camera) abstract;

		virtual void AddActivatedQueue(GameObject*) abstract;
		virtual void AddDeactivatedQueue(GameObject*) abstract;
		virtual void AddDestroyedQueue(GameObject*) abstract;

		virtual void Load() noexcept abstract;
		virtual void Clear() noexcept abstract;
	};


}