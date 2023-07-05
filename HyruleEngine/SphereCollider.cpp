#include "SphereCollider.h"


namespace Hyrule
{
	SphereCollider::SphereCollider(GameObject* _gameObject) noexcept : 
		Collider(_gameObject)
	{
		// 여기서 피직스 엔진에 콜라이더 추가를 요청함.
	}

	SphereCollider::~SphereCollider() noexcept
	{

	}

	void SphereCollider::SetTrigger(bool)
	{

	}

	void SphereCollider::SetSize(const Vector3D&)
	{
		collider->SetCenter()
	}

	void SphereCollider::SetCenter(const Vector3D&)
	{

	}

	bool SphereCollider::IsColliding()
	{
		return isColliding;
	}
}
