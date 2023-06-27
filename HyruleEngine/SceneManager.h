#pragma once
#include <map>
#include <string>

namespace Hyrule
{
	class Scene;

	class SceneManager
	{
	private:
		SceneManager() noexcept = default;
		~SceneManager() noexcept;

	private:
		Scene* currentScene;
		std::map<std::wstring, Scene*> sceneMap;

	public:
		static SceneManager* GetInstance() noexcept;

		void AddScene(const std::wstring&, Scene*&) noexcept;
		void RemoveScene(const std::wstring&) noexcept;
		void RemoveScene(Scene*&) noexcept;

		void LoadScene(const std::wstring&);
		void LoadScene(Scene*&);
	};
}
