#include "RigidBody.h"

#include "Object.h"
#include "Collider.h"
#include "ObjectManager.h"

namespace Hyrule
{
	namespace Physics
	{
		bool RigidBody::isActive()
		{
			return this->activate;
		}

		Object* RigidBody::GetObject()
		{
			return object;
		}

		std::wstring RigidBody::GetObjectName() noexcept
		{
			return object->GetName();
		}

		void RigidBody::OnEnable() noexcept
		{
			this->activate = true;
		}

		void RigidBody::OnDisable() noexcept
		{
			this->activate = false;
		}

		void RigidBody::OnDestroy() noexcept
		{
			ObjectManager::GetInstance().AddRemoveQueue(this);
		}

		float RigidBody::GetInvMass() noexcept
		{
			return invMess;
		}

		float RigidBody::GetStaticFriction() noexcept
		{
			return sfriction;
		}

		float RigidBody::GetDynamicFriction() noexcept
		{
			return dfriction;
		}

		float RigidBody::GetRestitution() noexcept
		{
			return restitution;
		}

		Hyrule::Matrix3x3 RigidBody::GetInvInertia() noexcept
		{
			return invInertiaTensor;
		}

		void RigidBody::ApplyImpulse(const Vector3D& _impulse, const Vector3D& _contact) noexcept
		{
			if (activate == false || invMess == 0.f)
			{
				return;
			}

			// 선형 운동
			// 충격량 = (F * dt) = (m * a * dt) = (m * dV) = dP
			// dV = 충격량 / m
			Vector3D dV = _impulse * this->invMess;
			this->velocity += dV;

			// 회전 운동
			// t = Ia = r X F
			// 
			// 양변에 dt 곱함
			// t * dt = (r X F * dt) = (r X m * a * dt) = (r X m * dV) = r X dP
			// dL = (t * dt) = r X dP
			// dL = Ia * dt = I * dw
			// dw = dL / I
			// dw = (r X dP) / I
			Vector3D dw = _contact.Cross(_impulse) * this->invInertiaTensor;
			this->angularVelocity += dw;
		}

		void RigidBody::ComputeVelocity(Vector3D _gravity, float _dt) noexcept
		{
			if (this->activate == false || this->invMess == 0.f)
			{
				return;
			}

			if (this->useGravity == true)
			{
				this->velocity += _gravity * _dt;
			}

			this->velocity += (this->force * this->invMess) * _dt;
			this->angularVelocity += (this->torque * this->invInertiaTensor) * _dt;
			
			this->velocity *= std::exp(-0.1 * _dt);
			this->angularVelocity *= std::exp(-0.1 * _dt);

			this->force = Vector3D::Zero();
			this->torque = Vector3D::Zero();
		}

// 		void RigidBody::ApplyTorque(float _dt) noexcept
// 		{
// 			if (activate == false || invMess == 0.f)
// 			{
// 				return;
// 			}
// 
// 			this->angularVelocity += this->torque * this->invInertiaTensor * _dt;
// 			this->torque = Vector3D::Zero();
// 		}

		void RigidBody::ComputePosition(float _dt) noexcept
		{
			Vector3D dL{ this->velocity * _dt };
			position += dL;

			Vector3D dW{ this->angularVelocity * _dt };
			rotation *= ToQuaternion(dW);
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
		/// 콜라이더가 가진 Shape으로 관성 텐서 계산
		/// </summary>
		void RigidBody::CalculateInertiaTensor(float _mess)
		{
			inertiaTensor = object->GetInertiaTensor(_mess);
			invInertiaTensor = inertiaTensor.Inverse();
			centerOfMass = object->GetCenterOfMess();
		}

		void RigidBody::CalculateInertiaTensor()
		{
			CalculateInertiaTensor(this->mess);
		}

		/// <summary>
		/// 텐서 회전
		/// </summary>
		Matrix3x3 RigidBody::GetInertia()
		{
			return this->inertiaTensor;
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
			this->CalculateInertiaTensor(_mess);

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

		Hyrule::Matrix4x4 RigidBody::Apply() noexcept
		{
			auto mat{ ToTransformMatrix(position, rotation, 1.f) * this->object->GetWorldTM() };
			this->position = {};
			this->rotation = {};
			
			return mat;
		}
#pragma endregion GetSet
	}
}