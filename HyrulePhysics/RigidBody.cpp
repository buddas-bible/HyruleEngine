#include "RigidBody.h"



namespace Hyrule
{





	void RigidBody::AddForce(const Vector3D& _force) noexcept
	{
		this->force += _force;
	}

	void RigidBody::AddTorque(const Vector3D& _torque) noexcept
	{
		this->torque += _torque;
	}

#pragma region GetSet
	void RigidBody::SetMess(const float _mess) noexcept
	{
		this->mess = _mess;
	}

	float RigidBody::GetMess() const noexcept
	{
		return this->mess;
	}

	void RigidBody::SetVelocity(const Vector3D& _velo) noexcept
	{
		this->velocity = _velo;
	}

	Vector3D RigidBody::GetVelocity() const noexcept
	{
		return this->velocity;
	}

	void RigidBody::SetAccleration(const Vector3D& _accel) noexcept
	{
		this->accleration = _accel;
	}

	Vector3D RigidBody::GetAccleration() const noexcept
	{
		return this->accleration;
	}

	void RigidBody::SetAngularVelocity(const Vector4D& _angularVelo) noexcept
	{
		this->angularVelocity = _angularVelo;
	}

	Vector4D RigidBody::GetAngularVelocity() const noexcept
	{
		return this->angularVelocity;
	}

	bool RigidBody::isSleeping() const noexcept
	{
		return this->sleep;
	}

	void RigidBody::isSleeping(const bool _sleep) noexcept
	{
		this->sleep = _sleep;
	}

	bool RigidBody::isKinematic() const noexcept
	{
		return this->kinematic;
	}

	void RigidBody::isKinematic(const bool _kinematic) noexcept
	{
		this->kinematic = _kinematic;
	}
#pragma endregion GetSet
}