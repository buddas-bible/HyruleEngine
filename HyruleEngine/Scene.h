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
		std::wstring name;							// �� �̸�
		std::map<std::wstring, GameObject*> gameObjectList;	// 
		GameObject* CreateGameObject(const std::wstring&);

	public:
		std::wstring GetName() noexcept;
		GameObject* AddGameObject(const std::wstring&);
		GameObject* AddGameObject(const std::wstring&, GameObject*);


	};
}


/*
���� ���� ������Ʈ�� ������ ����.
�� ������

*/