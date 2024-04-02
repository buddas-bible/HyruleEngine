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
������, ���� ���� ������Ʈ���� ��� �� ���ΰ�..
������ ���̺귯���� �����س��´ٸ�
������ ���� ����ü ���� �� ��� �� ���ΰ�..
������ ���̴� ����ü�� �������̽��� ���� ������ AddForce��簡.. ������
���� ���� �Լ��� �����ϴ� ������� �ؾ��ϳ�..




*/