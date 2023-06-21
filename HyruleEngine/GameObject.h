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
		Component* components;	// 컴포넌트 배열
		Transform* transform;	// 트랜스폼
		GameObject* parent;		// 부모

		// std::wstring tag;		// 태그


	public:
		GameObject* GetParent();
		void SetParent(GameObject* _gameObject);

		template <typename component>
		component* GetComponent();
	};
}