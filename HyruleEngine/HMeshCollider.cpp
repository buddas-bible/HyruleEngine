#include "HMeshCollider.h"

#include "ICollider.h"
#include "HTransform.h"
#include "HEntity.h"

namespace hyrule
{

	HMeshCollider::HMeshCollider(HEntity* _gameObject) : 
		HCollider(_gameObject), collider()
	{

	}

	HMeshCollider::~HMeshCollider()
	{

	}

	void HMeshCollider::SetTrigger(bool _trigger)
	{
		collider->SetTrigger(_trigger);
	}

	bool HMeshCollider::isCollision()
	{
		return collider->isCollision();
	}

	void HMeshCollider::PrePhysicsUpdate()
	{
		collider->SetTransform(
			center,
			size,
			entity->GetTransform()->GetWorldPosition(),
			entity->GetTransform()->GetWorldQuaternion(),
			entity->GetTransform()->GetWorldScale()
		);
	}

	void HMeshCollider::PhysicsUpdate()
	{
		if (isCollision() == true || isColliding == false)
		{
			entity->OnCollisionEnter();
		}
		else if (isCollision() == true || isColliding == true)
		{
			entity->OnCollisionStay();
		}
		else if (isCollision() == false || isColliding == true)
		{
			entity->OnCollisionExit();
		}

		isColliding = this->isCollision();
	}

	void HMeshCollider::LatePhysicsUpdate()
	{

	}

	void HMeshCollider::Update()
	{
	}

	void HMeshCollider::OnEnable()
	{
		collider->OnEnable();
	}

	void HMeshCollider::OnDisable()
	{
		collider->OnDisable();
	}

	void HMeshCollider::OnDestroy()
	{
		collider->OnDestroy();
	}

// 	bool MeshCollider::IsColliding()
// 	{
// 		return collider->IsColliding();
// 	}
}
