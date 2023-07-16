#pragma once


namespace Hyrule
{
	class GameObject;
	class Camera;

	class IScene
	{
	public:
		IScene() noexcept = default;
		virtual ~IScene() noexcept = default;

	protected:
		virtual GameObject* CreateGameObject(const std::wstring&) abstract;

	public:
		virtual  std::wstring GetName() noexcept abstract;
		virtual  GameObject* AddGameObject(const std::wstring&) abstract;
		virtual  GameObject* AddGameObject(const std::wstring&, GameObject*) abstract;
		virtual  std::map<std::wstring, GameObject*>& GetGameObjectList() abstract;

		virtual Camera* GetMainCamera() abstract;

		virtual void Load() noexcept abstract;
		virtual void Clear() noexcept abstract;
	};


}