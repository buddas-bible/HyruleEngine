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

	}

	void MeshCollider::PrePhysicsUpdate()
	{
		collider->SetTransform(
			gameObject->GetTransform()->GetWorldPosition(),
			gameObject->GetTransform()->GetWorldQuaternion(),
			gameObject->GetTransform()->GetWorldScale()
		);
	}

	void MeshCollider::PhysicsUpdate()
	{
		if (isCollision() == true || isColliding == false)
		{
			gameObject->OnCollisionEnter();
		}
		else if (isCollision() == true || isColliding == true)
		{
			gameObject->OnCollisionStay();
		}
		else if (isCollision() == false || isColliding == true)
		{
			gameObject->OnCollisionExit();
		}

		isColliding = this->isCollision();
	}

	void MeshCollider::LatePhysicsUpdate()
	{

	}

	void MeshCollider::Update()
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
		collider->OnDestroy();
	}

// 	bool MeshCollider::IsColliding()
// 	{
// 		return collider->IsColliding();
// 	}
}
