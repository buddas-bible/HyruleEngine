#pragma once
#include <map>
#include <string>

namespace Hyrule
{
	class GameObject;

	class Scene
	{
	public:
		Scene() noexcept;
		Scene(const std::wstring&) noexcept;
		~Scene() noexcept = default;

	private:
		std::wstring name;							// 씬 이름
		std::map<std::wstring, GameObject*> gameObjectList;	// 
		GameObject* CreateGameObject(const std::wstring&);

	public:
		std::wstring GetName() noexcept;
		GameObject* AddGameObject(const std::wstring&);
		GameObject* AddGameObject(const std::wstring&, GameObject*);


	};
}


/*
씬은 게임 오브젝트를 가지고 있음.
씬 단위로

*/