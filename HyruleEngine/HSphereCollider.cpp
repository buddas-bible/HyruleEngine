#include "HSphereCollider.h"

#include "ICollider.h"
#include "HTransform.h"
#include "HEntity.h"
#include "PhysicsSystem.h"
#include "PHYSICALLYOBJECT_INFO.h"

namespace hyrule
{
	HSphereCollider::HSphereCollider(HEntity* _gameObject) : 
		HCollider(_gameObject)
	{
		Physics::COLLIDER_INFO info;
		info.shapeInfo.shapeType = Physics::SPHERE;
		collider = PhysicsSystem::Instance().CreateCollider(entity->GetName(), &info);
	}

	HSphereCollider::~HSphereCollider()
	{

	}

	void HSphereCollider::SetTrigger(bool _trigger)
	{
		collider->SetTrigger(_trigger);
	}

	void HSphereCollider::SetSize(const Vector3D& _size)
	{
		size = _size;
	}

	void HSphereCollider::SetCenter(const Vector3D& _center)
	{
		center = _center;
	}

	bool HSphereCollider::isCollision()
	{
		return collider->isCollision();
	}

	void HSphereCollider::PrePhysicsUpdate()
	{
		collider->SetTransform(
			center,
			size,
			entity->GetTransform()->GetWorldPosition(),
			entity->GetTransform()->GetWorldQuaternion(),
			entity->GetTransform()->GetWorldScale()
		);
	}

	void HSphereCollider::PhysicsUpdate()
	{
		bool curr{ isCollision() };

		if (curr == true && isColliding == false)
		{
			entity->OnCollisionEnter();
		}
		else if (curr == true && isColliding == true)
		{
			entity->OnCollisionStay();
		}
		else if (curr == false && isColliding == true)
		{
			entity->OnCollisionExit();
		}

		isColliding = curr;
	}

	void HSphereCollider::LatePhysicsUpdate()
	{

	}

	void HSphereCollider::Update()
	{

	}

	void HSphereCollider::OnEnable()
	{
		collider->OnEnable();
	}

	void HSphereCollider::OnDisable()
	{
		collider->OnDisable();
	}

	void HSphereCollider::OnDestroy()
	{
		collider->OnDestroy();
	}
}
