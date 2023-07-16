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

	private:
		IScene* currentScene;
		std::map<std::wstring, IScene*> sceneMap;

	public:
		static SceneManager& GetInstance() noexcept;

		void AddScene(const std::wstring&, IScene*) noexcept;
		void RemoveScene(const std::wstring&) noexcept;
		void RemoveScene(IScene*&) noexcept;

		void LoadScene(const std::wstring&) noexcept;
		void LoadScene(IScene*&) noexcept;
		void ClearScene();

	public:
		void SceneStart();


		void Awake();
		void OnEnable();
		void Start();
		void PhysicsUpdate();
		void FixedUpdate();
		void Update();
		void LateUpdate();

		void OnDisable();

		void OnDestroy();
	};
}
