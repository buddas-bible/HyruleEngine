#pragma once
#include "Singleton.h"
#include <map>
#include <string>

namespace hyrule
{
	class IScene;

	class SceneManager : public Singleton<SceneManager>
	{
	private:
		IScene* currentScene;
		std::map<std::wstring, IScene*> sceneMap;
		bool first{ true };

	public:
		void AddScene(const std::wstring&, IScene*);
		void RemoveScene(const std::wstring&);
		void RemoveScene(IScene*&);

		void LoadScene(const std::wstring&);
		void LoadScene(IScene*);
		void UnloadScene();
		void ClearScene();

	public:
		void Initalization();

		void Awake();
		void OnEnable();
		void OnDisable();

		void Start();
		void FixedUpdate();

		void PrePhysicsUpdate();
		void PhysicsUpdate();
		void LatePhysicsUpdate();

		void OnCollision();

		void Update();
		void LateUpdate();

		void OnDestroy();
		void Decommissioning();
	};
}
