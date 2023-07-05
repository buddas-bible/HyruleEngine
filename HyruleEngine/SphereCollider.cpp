#include "SphereCollider.h"


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
