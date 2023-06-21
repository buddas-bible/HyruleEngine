#pragma once

namespace Hyrule
{
	class Component;
	class Transform;

	class GameObject
	{
	public:
		GameObject() = default;
		~GameObject() = default;

	private:
		Component* components;	// ������Ʈ �迭
		Transform* transform;	// Ʈ������
		GameObject* parent;		// �θ�

		// std::wstring tag;		// �±�


	public:
		GameObject* GetParent();
		void SetParent(GameObject* _gameObject);

		template <typename component>
		component* GetComponent();
	};
}