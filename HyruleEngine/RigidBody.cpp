#include "Entity.h"
#include "Transform.h"
#include "Scene.h"

#include "Vector3D.h"
#include "IRigidBody.h"

#include "PhysicsSystem.h"
#include "InputSystem.h"

#include "RigidBody.h"

namespace Hyrule
{
	RigidBody::RigidBody(Entity* _gameObject) :
		Component(_gameObject), iRigidBody()
	{
		iRigidBody = PhysicsSystem::Instance()->CreateRigidBody(gameObject->GetName());
	}

	void RigidBody::AddForce(const Hyrule::Vector3D& _force) const
	{
		iRigidBody->AddForce(_force);
	}

	void RigidBody::AddTorque(const Hyrule::Vector3D& _torque) const
	{
		iRigidBody->AddTorque(_torque);
	}

	void RigidBody::SetMass(const float _mess)
	{
		iRigidBody->SetMass(_mess);
	}

	float RigidBody::GetMass() const
	{
		return iRigidBody->GetMass();
	}

	void RigidBody::SetVelocity(const Hyrule::Vector3D& _velo)
	{
		iRigidBody->SetVelocity(_velo);
	}

	Vector3D RigidBody::GetVelocity() const
	{
		return iRigidBody->GetVelocity();
	}

	void RigidBody::SetAngularVelocity(const Hyrule::Vector3D& _angularVelo)
	{
		iRigidBody->SetAngularVelocity(_angularVelo);
	}

	Vector3D RigidBody::GetAngularVelocity() const
	{
		return iRigidBody->GetAngularVelocity();
	}

	bool RigidBody::isSleeping() const
	{
		return iRigidBody->IsAwake();
	}

	bool RigidBody::IsKinematic() const
	{
		return false;
	}

	void RigidBody::SetKinematic(const bool)
	{

	}

	void RigidBody::LatePhysicsUpdate()
	{
		Vector3D pos{ iRigidBody->ApplyPosition() };
		Quaternion rot{ iRigidBody->ApplyQuaternion()};

		auto parent = gameObject->GetTransform()->GetParent();

		if (parent != nullptr)
		{
			pos *= parent->GetWorldMatrix().Inverse();
			rot = parent->GetWorldQuaternion().Inverse() * rot;
		}

		gameObject->GetTransform()->SetLocalPosition(pos);;
		gameObject->GetTransform()->SetLocalQuaternion(rot.Normalized());
	}

	void RigidBody::Update()
	{
		if (InputSystem::Instance().KeyDown('P'))
		{
			gameObject->GetTransform()->SetLocalPosition(position);
			gameObject->GetTransform()->SetLocalQuaternion(rotation);
		}
	}

	//void RigidBody::OnEnable()
	//{
	//	iRigidBody->OnEnable();
	//}

	//void RigidBody::OnDisable()
	//{
	//	iRigidBody->OnDisable();
	//}

	//void RigidBody::OnDestroy()
	//{
	//	iRigidBody->OnDestroy();
	//}
}