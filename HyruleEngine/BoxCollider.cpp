#include "BoxCollider.h"

#include "ICollider.h"

namespace Hyrule
{

	BoxCollider::BoxCollider(GameObject* _gameObject) noexcept : 
		Collider(_gameObject)
	{

	}

	BoxCollider::~BoxCollider() noexcept
	{

	}

	void BoxCollider::SetTrigger(bool _trigger)
	{
		collider->SetTrigger(_trigger);
	}

	void BoxCollider::SetSize(const Vector3D& _size)
	{
		collider->SetSize(_size);
	}

	void BoxCollider::SetCenter(const Vector3D& _center)
	{
		collider->SetSize(_center);
	}

// 	bool BoxCollider::IsColliding()
// 	{
// 		return collider->IsColliding();
// 	}
}