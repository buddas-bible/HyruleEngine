#include "HBoxCollider.h"

#include "ICollider.h"
#include "HTransform.h"
#include "HEntity.h"
#include "PhysicsSystem.h"
#include "PHYSICALLYOBJECT_INFO.h"

namespace hyrule
{
	HBoxCollider::HBoxCollider(HEntity* _gameObject) : 
		HCollider(_gameObject)
	{
		Physics::COLLIDER_INFO info;
		info.shapeInfo.shapeType = Physics::BOX;
		collider = PhysicsSystem::Instance()->CreateCollider(entity->GetName(), &info);
	}

	HBoxCollider::~HBoxCollider()
	{

	}

	void HBoxCollider::SetTrigger(bool _trigger)
	{
		collider->SetTrigger(_trigger);
	}

	void HBoxCollider::SetSize(const Vector3D& _size)
	{
		size = _size;
	}

	void HBoxCollider::SetCenter(const Vector3D& _center)
	{
		center = _center;
	}

	bool HBoxCollider::isCollision()
	{
		return collider->isCollision();
	}

	void HBoxCollider::PrePhysicsUpdate()
	{
		collider->SetTransform(
			center,
			size,
			entity->GetTransform()->GetWorldPosition(),
			entity->GetTransform()->GetWorldQuaternion(),
			entity->GetTransform()->GetWorldScale()
		);
	}

	void HBoxCollider::PhysicsUpdate()
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

	void HBoxCollider::LatePhysicsUpdate()
	{

	}

	void HBoxCollider::Update()
	{

	}

	void HBoxCollider::OnEnable()
	{
		collider->OnEnable();
	}

	void HBoxCollider::OnDisable()
	{
		collider->OnDisable();
	}

	void HBoxCollider::OnDestroy()
	{
		collider->OnDestroy();
	}
}