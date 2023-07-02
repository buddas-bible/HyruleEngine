#include "RigidBody.h"

#include "Object.h"
#include "Collider.h"

namespace Hyrule
{
	namespace Physics
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
			Vector3D dw = _contact.Cross(_impulse) * invInertiaTensor;
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

		/// <summary>
		/// 관성 텐서 계산
		/// </summary>
		void RigidBody::CalculateInertiaTensor()
		{
			object->colliders[0];
			// 일단 콜라이더 1개만이라도 관성 텐서를 구해보도록 하자...
			// 그리고 강체가 복수의 콜라이더를 가진다고 했을 땐
			// 또 고민해볼 점이 많다.....
			// 질량 중심을 옮겨야 한다는 점.
			// 관성 텐서를 계산하는 부분이 막막하다...
			// 대략 예상이 가는 점은..
			// 다면체의 면의 노말 방향을 보고 그 사면체의 부피에서 뺼지 더할지를 판단하고?
			// (질량 중심이 외각에 있기 때문에)
			// 
			// 이런다고 될까?
			// 
			// for (auto& e : object->colliders)
			// {
			// 	
			// }
		}

#pragma region GetSet
		void RigidBody::SetMess(const float _mess) noexcept
		{
			if (_mess == 0.f)
			{
				this->invMess = 0.f;
			}
			else
			{
				this->invMess = 1 / _mess;
			}

			/// SetMess를 시도하면
			/// inertia Tensor를 새로 구하도록 해야함.

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

		void RigidBody::SetAngularVelocity(const Vector3D& _angular) noexcept
		{
			this->angularVelocity = _angular;
		}

		Vector3D RigidBody::GetAngularVelocity() const noexcept
		{
			return angularVelocity;
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
}