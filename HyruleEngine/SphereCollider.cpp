#include "SphereCollider.h"

#include "ICollider.h"
#include "Transform.h"
#include "Entity.h"
#include "PhysicsSystem.h"
#include "PHYSICALLYOBJECT_INFO.h"

namespace Hyrule
{
	SphereCollider::SphereCollider(Entity* _gameObject) : 
		Collider(_gameObject)
	{
		Physics::COLLIDER_INFO info;
		info.shapeInfo.shapeType = Physics::SPHERE;
		collider = PhysicsSystem::Instance().CreateCollider(gameObject->GetName(), &info);
	}

	SphereCollider::~SphereCollider()
	{

	}

	void SphereCollider::SetTrigger(bool _trigger)
	{
		collider->SetTrigger(_trigger);
	}

	void SphereCollider::SetSize(const Vector3D& _size)
	{
		size = _size;
	}

	void SphereCollider::SetCenter(const Vector3D& _center)
	{
		center = _center;
	}

	bool SphereCollider::isCollision()
	{
		return collider->isCollision();
	}

	void SphereCollider::PrePhysicsUpdate()
	{
		collider->SetTransform(
			center,
			size,
			gameObject->GetTransform()->GetWorldPosition(),
			gameObject->GetTransform()->GetWorldQuaternion(),
			gameObject->GetTransform()->GetWorldScale()
		);
	}

	void SphereCollider::PhysicsUpdate()
	{
		bool curr{ isCollision() };

		if (curr == true && isColliding == false)
		{
			gameObject->OnCollisionEnter();
		}
		else if (curr == true && isColliding == true)
		{
			gameObject->OnCollisionStay();
		}
		else if (curr == false && isColliding == true)
		{
			gameObject->OnCollisionExit();
		}

		isColliding = curr;
	}

	void SphereCollider::LatePhysicsUpdate()
	{

	}

	void SphereCollider::Update()
	{

	}

	void SphereCollider::OnEnable()
	{
		collider->OnEnable();
	}

	void SphereCollider::OnDisable()
	{
		collider->OnDisable();
	}

	void SphereCollider::OnDestroy()
	{
		collider->OnDestroy();
	}
}
