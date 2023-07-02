#include "RigidBody.h"

#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"

#include "Vector3D.h"
#include "IRigidBody.h"

namespace Hyrule
{
	RigidBody::RigidBody(GameObject* _gameObject) noexcept :
		Component(_gameObject), rigidbody()
	{
		
	}

	void RigidBody::LinkRigidBody()
	{
		auto g = gameObject->GetName();
		auto s = gameObject->GetScene()->GetName();

		// 여기서 씬 이름과 오브젝트 이름을 넘겨주고
		// 해당 오브젝트의 리지드바디를 받아서?
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

	Hyrule::Vector3D RigidBody::GetVelocity() const noexcept
	{
		return rigidbody->GetVelocity();
	}

	void RigidBody::SetAngularVelocity(const Hyrule::Vector3D& _angularVelo) noexcept
	{
		rigidbody->SetAngularVelocity(_angularVelo);
	}

	Hyrule::Vector3D RigidBody::GetAngularVelocity() const noexcept
	{
		return rigidbody->GetAngularVelocity();
	}

	bool RigidBody::isSleeping() const noexcept
	{
		return rigidbody->isSleeping();
	}

	void RigidBody::isSleeping(const bool) noexcept
	{

	}

	bool RigidBody::isKinematic() const noexcept
	{
		return false;
	}

	void RigidBody::isKinematic(const bool) noexcept
	{

	}
}