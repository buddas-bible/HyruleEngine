#include "MeshCollider.h"

#include "ICollider.h"

namespace Hyrule
{

	MeshCollider::MeshCollider(GameObject* _gameObject) noexcept : 
		Collider(_gameObject)
	{

	}

	MeshCollider::~MeshCollider() noexcept
	{

	}

	void MeshCollider::SetTrigger(bool _trigger)
	{
		collider->SetTrigger(_trigger);
	}

	void MeshCollider::SetSize(const Vector3D& _size)
	{
		collider->SetSize(_size);
	}

	void MeshCollider::SetCenter(const Vector3D& _center)
	{
		collider->SetSize(_center);
	}

	void MeshCollider::FixedUpdate()
	{

	}

	void MeshCollider::OnEnable()
	{

	}

	void MeshCollider::OnDisable()
	{

	}

	void MeshCollider::OnDestroy()
	{

	}

// 	bool MeshCollider::IsColliding()
// 	{
// 		return collider->IsColliding();
// 	}
}
