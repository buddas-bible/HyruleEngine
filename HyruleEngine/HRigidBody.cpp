#include "HEntity.h"
#include "HTransform.h"
#include "Scene.h"

#include "Vector3D.h"
#include "IRigidBody.h"

#include "PhysicsSystem.h"
#include "InputSystem.h"

#include "HRigidBody.h"

namespace hyrule
{
	HRigidBody::HRigidBody(HEntity* _gameObject) :
		HComponent(_gameObject), iRigidBody()
	{
		iRigidBody = PhysicsSystem::Instance()->CreateRigidBody(entity->GetName());
	}

	void HRigidBody::AddForce(const hyrule::Vector3D& _force) const
	{
		iRigidBody->AddForce(_force);
	}

	void HRigidBody::AddTorque(const hyrule::Vector3D& _torque) const
	{
		iRigidBody->AddTorque(_torque);
	}

	void HRigidBody::SetMass(const float _mess)
	{
		iRigidBody->SetMass(_mess);
	}

	float HRigidBody::GetMass() const
	{
		return iRigidBody->GetMass();
	}

	void HRigidBody::SetVelocity(const hyrule::Vector3D& _velo)
	{
		iRigidBody->SetVelocity(_velo);
	}

	Vector3D HRigidBody::GetVelocity() const
	{
		return iRigidBody->GetVelocity();
	}

	void HRigidBody::SetAngularVelocity(const hyrule::Vector3D& _angularVelo)
	{
		iRigidBody->SetAngularVelocity(_angularVelo);
	}

	Vector3D HRigidBody::GetAngularVelocity() const
	{
		return iRigidBody->GetAngularVelocity();
	}

	bool HRigidBody::isSleeping() const
	{
		return iRigidBody->IsAwake();
	}

	bool HRigidBody::IsKinematic() const
	{
		return false;
	}

	void HRigidBody::SetKinematic(const bool)
	{

	}

	//void HRigidBody::LatePhysicsUpdate()
	//{
	//	Vector3D pos{ iRigidBody->ApplyPosition() };
	//	Quaternion rot{ iRigidBody->ApplyQuaternion()};

	//	auto parent = entity->GetTransform()->GetParent();

	//	if (parent != nullptr)
	//	{
	//		pos *= parent->GetWorldMatrix().Inverse();
	//		rot = parent->GetWorldQuaternion().Inverse() * rot;
	//	}

	//	entity->GetTransform()->SetLocalPosition(pos);;
	//	entity->GetTransform()->SetLocalQuaternion(rot.Normalized());
	//}

	//void HRigidBody::Update()
	//{
	//	if (InputSystem::Instance().KeyDown('P'))
	//	{
	//		entity->GetTransform()->SetLocalPosition(position);
	//		entity->GetTransform()->SetLocalQuaternion(rotation);
	//	}
	//}

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