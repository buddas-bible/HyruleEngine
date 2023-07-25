#include "RigidBody.h"

#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"

#include "Vector3D.h"
#include "IRigidBody.h"

#include "PhysicsSystem.h"

namespace Hyrule
{
	RigidBody::RigidBody(GameObject* _gameObject) noexcept :
		Component(_gameObject), rigidbody()
	{
		rigidbody = PhysicsSystem::GetInstance().CreateRigidBody(gameObject->GetName());
	}

	void RigidBody::AddForce(const Hyrule::Vector3D& _force) const noexcept
	{
		rigidbody->AddForce(_force);
	}

	void RigidBody::AddTorque(const Hyrule::Vector3D& _torque) const noexcept
	{
		rigidbody->AddTorque(_torque);
	}

	void RigidBody::SetMess(const float _mess) noexcept
	{
		rigidbody->SetMess(_mess);
	}

	float RigidBody::GetMess() const noexcept
	{
		return rigidbody->GetMess();
	}

	void RigidBody::SetVelocity(const Hyrule::Vector3D& _velo) noexcept
	{
		rigidbody->SetVelocity(_velo);
	}

	Vector3D RigidBody::GetVelocity() const noexcept
	{
		return rigidbody->GetVelocity();
	}

	void RigidBody::SetAngularVelocity(const Hyrule::Vector3D& _angularVelo) noexcept
	{
		rigidbody->SetAngularVelocity(_angularVelo);
	}

	Vector3D RigidBody::GetAngularVelocity() const noexcept
	{
		return rigidbody->GetAngularVelocity();
	}

	bool RigidBody::isSleeping() const noexcept
	{
		return rigidbody->isSleeping();
	}

	bool RigidBody::isKinematic() const noexcept
	{
		return false;
	}

	void RigidBody::isKinematic(const bool) noexcept
	{

	}

	void RigidBody::PrePhysicsUpdate()
	{

	}

	void RigidBody::PhysicsUpdate()
	{

	}

	void RigidBody::LatePhysicsUpdate()
	{
		Matrix4x4 matrix = rigidbody->Apply();
		Matrix4x4 parent{ gameObject->GetTransform()->GetParentWorldMatrix() };
		matrix /= parent;	// ºÎ¸ðÀÇ ¿ªÇà·ÄÀ» °öÇØ¼­ ·ÎÄÃÀ» »Ì¾Æ³¿

		Vector3D pos;
		Quaternion rot;
		Vector3D scl;
		Decompose(matrix, pos, rot, scl);

		gameObject->GetTransform()->SetLocalPosition(pos);;
		gameObject->GetTransform()->SetLocalQuaternion(rot);
 		gameObject->GetTransform()->SetLocalPosition(scl);
	}

	void RigidBody::Update()
	{
	}

	void RigidBody::OnEnable()
	{
		rigidbody->OnEnable();
	}

	void RigidBody::OnDisable()
	{
		rigidbody->OnDisable();
	}

	void RigidBody::OnDestroy()
	{
		rigidbody->OnDestroy();
	}
}