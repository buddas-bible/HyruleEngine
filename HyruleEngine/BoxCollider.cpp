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

	void BoxCollider::SetTrigger(bool)
	{

	}

	void BoxCollider::SetSize(const Vector3D&)
	{

	}

	void BoxCollider::SetCenter(const Vector3D&)
	{

	}

	bool BoxCollider::IsColliding()
	{
		return collider->IsColliding();
	}
}