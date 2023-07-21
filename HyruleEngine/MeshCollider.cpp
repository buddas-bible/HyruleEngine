#include "MeshCollider.h"

#include "ICollider.h"
#include "Transform.h"
#include "GameObject.h"

namespace Hyrule
{

	MeshCollider::MeshCollider(GameObject* _gameObject) noexcept : 
		Collider(_gameObject), collider()
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


	bool MeshCollider::isCollision() noexcept
	{
		return collider->isCollision();
	}

	void MeshCollider::FixedUpdate()
	{
		collider->SetWorldTransform(gameObject->GetTransform()->GetWorldMatrix());
	}

	void MeshCollider::Update()
	{
		if (isCollision() == true)
		{
			gameObject->OnCollisionEnter();
		}
		else
		{
			gameObject->OnCollisionExit();
		}
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
		collider->OnDestroy();
	}

// 	bool MeshCollider::IsColliding()
// 	{
// 		return collider->IsColliding();
// 	}
}
