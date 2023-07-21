#include "BoxCollider.h"

#include "ICollider.h"
#include "Transform.h"
#include "GameObject.h"
#include "PhysicsSystem.h"
#include "PHYSICALLYOBJECT_INFO.h"

namespace Hyrule
{
	BoxCollider::BoxCollider(GameObject* _gameObject) noexcept : 
		Collider(_gameObject)
	{
		Physics::COLLIDER_INFO info;
		info.shapeInfo.shapeType = Physics::BOX;
		collider = PhysicsSystem::GetInstance().CreateCollider(gameObject->GetName(), &info);
	}

	BoxCollider::~BoxCollider() noexcept
	{

	}

	void BoxCollider::SetTrigger(bool _trigger)
	{
		collider->SetTrigger(_trigger);
	}

	void BoxCollider::SetSize(const Vector3D& _size)
	{
		collider->SetSize(_size);
	}

	void BoxCollider::SetCenter(const Vector3D& _center)
	{
		collider->SetSize(_center);
	}

	bool BoxCollider::isCollision() noexcept
	{
		return collider->isCollision();
	}

	void BoxCollider::FixedUpdate()
	{
		collider->SetWorldTransform(gameObject->GetTransform()->GetWorldMatrix());
	}

	void BoxCollider::Update()
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

	void BoxCollider::OnEnable()
	{
		collider->OnEnable();
	}

	void BoxCollider::OnDisable()
	{
		collider->OnDisable();
	}

	void BoxCollider::OnDestroy()
	{
		collider->OnDestroy();
	}

// 	bool BoxCollider::IsColliding()
// 	{
// 		return collider->IsColliding();
// 	}
}