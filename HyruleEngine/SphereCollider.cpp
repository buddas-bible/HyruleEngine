#include "SphereCollider.h"

#include "ICollider.h"

namespace Hyrule
{
	SphereCollider::SphereCollider(GameObject* _gameObject) noexcept : 
		Collider(_gameObject)
	{
		// ���⼭ ������ ������ �ݶ��̴� �߰��� ��û��.
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

	bool SphereCollider::IsColliding()
	{
		return collider->IsColliding();
	}
}
