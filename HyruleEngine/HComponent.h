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
렌더러, 물리 관련 컴포넌트들을 어떻게 할 것인가..
물리를 라이브러리로 구분해놓는다면
물리에 들어가는 구조체 같은 건 어떻게 할 것인가..
물리에 쓰이는 구조체도 인터페이스로 따로 빼놓고 AddForce라든가.. 같은건
관련 수학 함수는 공유하는 방식으로 해야하나..




*/