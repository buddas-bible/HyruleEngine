#include "MeshCollider.h"

#include "ICollider.h"

namespace Hyrule
{

	MeshCollider::MeshCollider(GameObject* _gameObject) noexcept : 
		Collider(_gameObject), isColliding(), collider()
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
		collider->OnEnable();
	}

	void MeshCollider::OnDisable()
	{
		collider->OnDisable();
	}

	void MeshCollider::OnDestroy()
	{
		// collider->OnD();
	}

// 	bool MeshCollider::IsColliding()
// 	{
// 		return collider->IsColliding();
// 	}
}
