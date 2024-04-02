#pragma once
#include <map>
#include <string>
#include <vector>
#include <queue>

namespace Hyrule
{
	class Entity;
	class Camera;

	class IScene
	{
	public:
		IScene() = default;
		virtual ~IScene() = default;

	public:
		virtual  std::wstring GetName() abstract;
		virtual  Entity* CreateGameObject(const std::wstring&) abstract;
		virtual  Entity* CreateGameObject(const std::wstring&, Entity*) abstract;
		virtual  std::map<std::wstring, Entity*>& SceneObjects() abstract;
		// virtual std::vector<GameObject*>& GetActivtedObject() abstract;
		virtual std::queue<Entity*>& ActivatedQueue() abstract;
		virtual std::queue<Entity*>& DeactivatedQueue() abstract;
		virtual std::queue<Entity*>& DestroyedQueue() abstract;

		virtual Camera* GetMainCamera() abstract;
		virtual void SetMainCamera(Camera* _camera) abstract;

		virtual void AddActivatedQueue(Entity*) abstract;
		virtual void AddDeactivatedQueue(Entity*) abstract;
		virtual void AddDestroyedQueue(Entity*) abstract;
		
		virtual void Initialize() abstract;
		virtual void Load() abstract;
		virtual void Destroy(Entity*) abstract;
		virtual void Clear() abstract;
	};


}