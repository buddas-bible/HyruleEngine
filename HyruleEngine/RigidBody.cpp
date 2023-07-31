#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"

#include "Vector3D.h"
#include "IRigidBody.h"

#include "PhysicsSystem.h"

#include "RigidBody.h"

namespace Hyrule
{
	RigidBody::RigidBody(GameObject* _gameObject) noexcept :
		Component(_gameObject), iRigidBody()
	{
		iRigidBody = PhysicsSystem::GetInstance().CreateRigidBody(gameObject->GetName());
	}

	void RigidBody::AddForce(const Hyrule::Vector3D& _force) const noexcept
	{
		iRigidBody->AddForce(_force);
	}

	void RigidBody::AddTorque(const Hyrule::Vector3D& _torque) const noexcept
	{
		iRigidBody->AddTorque(_torque);
	}

	void RigidBody::SetMass(const float _mess) noexcept
	{
		iRigidBody->SetMass(_mess);
	}

	float RigidBody::GetMass() const noexcept
	{
		return iRigidBody->GetMass();
	}

	void RigidBody::SetVelocity(const Hyrule::Vector3D& _velo) noexcept
	{
		iRigidBody->SetVelocity(_velo);
	}

	Vector3D RigidBody::GetVelocity() const noexcept
	{
		return iRigidBody->GetVelocity();
	}

	void RigidBody::SetAngularVelocity(const Hyrule::Vector3D& _angularVelo) noexcept
	{
		iRigidBody->SetAngularVelocity(_angularVelo);
	}

	Vector3D RigidBody::GetAngularVelocity() const noexcept
	{
		return iRigidBody->GetAngularVelocity();
	}

	bool RigidBody::isSleeping() const noexcept
	{
		return iRigidBody->isSleeping();
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
		Vector3D pos{ iRigidBody->ApplyPosition() };
		Quaternion rot{ iRigidBody->ApplyQuaternion()};

		auto parent = gameObject->GetTransform()->GetParent();

		if (parent != nullptr)
		{
			pos *= parent->GetWorldMatrix().Inverse();
			rot *= parent->GetWorldQuaternion().Inverse();
		}

		gameObject->GetTransform()->SetLocalPosition(pos);;
		gameObject->GetTransform()->SetLocalQuaternion(rot.Normalized());
	}

	void RigidBody::Update()
	{
		Vector3D pos{ gameObject->GetTransform()->GetLocalPosition() };

		if (gameObject->GetTransform()->GetLocalPosition().x > 400.f)
		{
			gameObject->GetTransform()->SetLocalPosition({ pos.x - 400.f, pos.y, pos.z });
		}
		else if (gameObject->GetTransform()->GetLocalPosition().x < -400.f)
		{
			gameObject->GetTransform()->SetLocalPosition({ pos.x + 400.f, pos.y, pos.z });
		}
		if (gameObject->GetTransform()->GetLocalPosition().y > 400.f)
		{
			gameObject->GetTransform()->SetLocalPosition({ pos.x, pos.y - 400.f, pos.z });
		}
		else if (gameObject->GetTransform()->GetLocalPosition().y < -400.f)
		{
			gameObject->GetTransform()->SetLocalPosition({ pos.x, pos.y + 400.f, pos.z });
		}
		if (gameObject->GetTransform()->GetLocalPosition().z > 400.f)
		{
			gameObject->GetTransform()->SetLocalPosition({ pos.x, pos.y, pos.z - 400.f });
		}
		else if (gameObject->GetTransform()->GetLocalPosition().z < -400.f)
		{
			gameObject->GetTransform()->SetLocalPosition({ pos.x, pos.y, pos.z + 400.f });
 		}
	}

	void RigidBody::OnEnable()
	{
		iRigidBody->OnEnable();
	}

	void RigidBody::OnDisable()
	{
		iRigidBody->OnDisable();
	}

	void RigidBody::OnDestroy()
	{
		iRigidBody->OnDestroy();
	}
}