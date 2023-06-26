#include "RigidBody.h"

namespace Hyrule
{





	void RigidBody::AddImpulse(const Vector3D& _impulse, const Vector3D& _contact) noexcept
	{
		if (invMess == 0.f)
		{
			return;
		}

		// 선형 운동
		// 충격량 = (F * dt) = (m * a * dt) = (m * dV) = dP
		// dV = 충격량 / m
		Vector3D dV = _impulse * invMess;
		velocity = velocity + dV;

		// 회전 운동
		// t = Ia = r X F
		// 
		// 양변에 dt 곱함
		// t * dt = (r X F * dt) = (r X m * a * dt) = (r X m * dV) = r X dP
		// dL = (t * dt) = r X dP
		// dL = Ia * dt = I * dw
		// dw = dL / I
		// dw = (r X dP) / I
		Vector3D dw = Vector4D(_contact.Cross(_impulse) * inertiaTensor);
		angularVelocity = angularVelocity + dw;
	}

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