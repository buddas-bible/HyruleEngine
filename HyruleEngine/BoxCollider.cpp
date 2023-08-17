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
		size = _size;
	}

	void BoxCollider::SetCenter(const Vector3D& _center)
	{
		center = _center;
	}

	bool BoxCollider::isCollision() noexcept
	{
		return collider->isCollision();
	}

	void BoxCollider::FixedUpdate()
	{

	}

	void BoxCollider::PrePhysicsUpdate()
	{
		collider->SetTransform(
			center,
			size,
			gameObject->GetTransform()->GetWorldPosition(),
			gameObject->GetTransform()->GetWorldQuaternion(),
			gameObject->GetTransform()->GetWorldScale()
		);
	}

	void BoxCollider::PhysicsUpdate()
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

	void BoxCollider::LatePhysicsUpdate()
	{

	}

	void BoxCollider::Update()
	{

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
}