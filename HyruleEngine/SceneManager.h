#pragma once
#include <map>
#include <string>

namespace Hyrule
{
	class IScene;

	class SceneManager
	{
	private:
		SceneManager() noexcept = default;
		~SceneManager() noexcept = default;
		SceneManager& operator= (const SceneManager&) noexcept = delete;
		SceneManager& operator= (SceneManager&&) noexcept = delete;

	private:
		IScene* currentScene;
		std::map<std::wstring, IScene*> sceneMap;
		bool first{ true };

	public:
		static SceneManager& GetInstance() noexcept;

		void AddScene(const std::wstring&, IScene*) noexcept;
		void RemoveScene(const std::wstring&) noexcept;
		void RemoveScene(IScene*&) noexcept;

		void LoadScene(const std::wstring&) noexcept;
		void LoadScene(IScene*) noexcept;
		void ClearScene();

	public:
		void Initalization();

		void Awake();
		void OnEnable();
		void OnDisable();

		void Start();
		void PhysicsUpdate();
		void FixedUpdate();

		void OnCollision();

		void Update();
		void LateUpdate();

		void OnDestroy();
		void Decommissioning();
	};
}
