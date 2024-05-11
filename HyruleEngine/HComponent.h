#pragma once
#include <type_traits>
#include <string>
#include "HEntity.h"

namespace hyrule
{
	class HEntity;
	class HTransform;

	class HComponent;

	template <typename _Ty>
	concept componentType = std::is_base_of_v<HComponent, _Ty>;

	class HComponent : public HObject
	{
	protected:
		HComponent() = delete;
		HComponent(HEntity* _gameObject);
		~HComponent() override = default;

	public:
		HEntity* entity;
		HTransform* transform;
		const char* tag;

	public:
		bool CompareTag(const std::string& _tag);

		HComponent* GetComponent(const std::string& _component);

		template <componentType _comTy>
		HComponent* GetComponent();

		template <componentType _comTy>
		void GetComponents(HComponent*, unsigned int size);
	};

	template <componentType _comTy>
	HComponent* HComponent::GetComponent()
	{
		entity->GetComponent<_comTy>();
	}

	template <componentType _comTy>
	void HComponent::GetComponents(HComponent* _p, unsigned int size)
	{
		entity->GetComponents<_comTy>(_p, size);
	}
}


/*
������, ���� ���� ������Ʈ���� ��� �� ���ΰ�..
������ ���̺귯���� �����س��´ٸ�
������ ���� ����ü ���� �� ��� �� ���ΰ�..
������ ���̴� ����ü�� �������̽��� ���� ������ AddForce��簡.. ������
���� ���� �Լ��� �����ϴ� ������� �ؾ��ϳ�..




*/