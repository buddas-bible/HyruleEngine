#pragma once
#include <map>
#include <string>
#include "IScene.h"
#include "SceneManager.h"

namespace Hyrule
{
	class GameObject;
	class Camera;

	template <typename SceneType>
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

	private:
		std::wstring name;							// 씬 이름
		std::map<std::wstring, GameObject*> gameObjecs;	// 

	public:
		virtual std::wstring GetName() noexcept final
		{
			return name;
		}
		virtual std::map<std::wstring, GameObject*>& GetGameObjectList() final
		{
			return gameObjecs;
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

		virtual Camera* GetMainCamera() final
		{
			return this->mainCamera;
		}
		virtual void SetMainCamera(Camera* _camera) final
		{
			this->mainCamera = _camera;
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

	private:
		Camera* mainCamera;
	};
}


/*
씬은 게임 오브젝트를 가지고 있음.
씬 단위로

*/