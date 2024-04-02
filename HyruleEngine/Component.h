#pragma once
#include <type_traits>
#include <string>
#include "Entity.h"

namespace Hyrule
{
	class Entity;
	class Transform;

	class Component;
	template <typename T>
	concept componentType = std::is_base_of_v<Component, T>;

	class Component : public Object
	{
	protected:
		Component() = delete;
		Component(Entity* _gameObject);
		~Component() override = default;

	public:
		Entity* gameObject;
		Transform* transform;
		const char* tag;

	public:
		bool CompareTag(const std::string&);

		Component* GetComponent(const std::string&);

		template <componentType Type>
		Component* GetComponent();

		template <componentType Type>
		void GetComponents(Component*, unsigned int size);
	};

	template <componentType Type>
	Component* Component::GetComponent()
	{
		gameObject->GetComponent<Type>();
	}

	template <componentType Type>
	void Component::GetComponents(Component* _p, unsigned int size)
	{
		gameObject->GetComponents<Type>(_p, size);
	}
}


/*
렌더러, 물리 관련 컴포넌트들을 어떻게 할 것인가..
물리를 라이브러리로 구분해놓는다면
물리에 들어가는 구조체 같은 건 어떻게 할 것인가..
물리에 쓰이는 구조체도 인터페이스로 따로 빼놓고 AddForce라든가.. 같은건
관련 수학 함수는 공유하는 방식으로 해야하나..




*/