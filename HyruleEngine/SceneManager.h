#pragma once
#include <map>
#include <string>

namespace Hyrule
{
	class IScene;

	class SceneManager
	{
	private:
		SceneManager() = default;
		~SceneManager() = default;
		SceneManager& operator= (const SceneManager&) = delete;
		SceneManager& operator= (SceneManager&&) = delete;

	private:
		IScene* currentScene;
		std::map<std::wstring, IScene*> sceneMap;
		bool first{ true };

	public:
		static SceneManager& GetInstance();

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
