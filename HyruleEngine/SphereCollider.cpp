#include "SphereCollider.h"

#include "ICollider.h"
#include "Transform.h"
#include "GameObject.h"

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

	void SphereCollider::SetTrigger(bool _trigger)
	{
		collider->SetTrigger(_trigger);
	}

	void SphereCollider::SetSize(const Vector3D& _size)
	{
		collider->SetSize(_size);
	}

	void SphereCollider::SetCenter(const Vector3D& _center)
	{
		collider->SetSize(_center);
	}

	void SphereCollider::FixedUpdate()
	{
		// gameObject->GetComponent<Transform>()
		// collider->SetWorldTransform();
	}

	void SphereCollider::OnEnable()
	{

	}

	void SphereCollider::OnDisable()
	{

	}

	void SphereCollider::OnDestroy()
	{

	}

	// 	bool SphereCollider::IsColliding()
	// 	{
	// 		return collider->IsColliding();
	// 	}
}
