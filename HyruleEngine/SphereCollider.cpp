#include "SphereCollider.h"

#include "ICollider.h"
#include "Transform.h"
#include "GameObject.h"
#include "PhysicsSystem.h"
#include "PHYSICALLYOBJECT_INFO.h"

namespace Hyrule
{
	SphereCollider::SphereCollider(GameObject* _gameObject) noexcept : 
		Collider(_gameObject)
	{
		Physics::COLLIDER_INFO info;
		info.shapeInfo.shapeType = Physics::SPHERE;
		collider = PhysicsSystem::GetInstance().CreateCollider(gameObject->GetName(), &info);
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

	bool SphereCollider::isCollision() noexcept
	{
		return collider->isCollision();
	}

	void SphereCollider::FixedUpdate()
	{

	}

	void SphereCollider::PrePhysicsUpdate()
	{
		collider->SetTransform(
			gameObject->GetTransform()->GetWorldPosition(),
			gameObject->GetTransform()->GetWorldQuaternion(),
			gameObject->GetTransform()->GetWorldScale()
		);
	}

	void SphereCollider::PhysicsUpdate()
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

	// 	bool SphereCollider::IsColliding()
	// 	{
	// 		return collider->IsColliding();
	// 	}
}
