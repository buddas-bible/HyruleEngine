#include "RigidBody.h"

#include "Object.h"
#include "Collider.h"
#include "ObjectManager.h"

#include <iostream>
#include "HyrulePhysics.h"

namespace Hyrule
{
	namespace Physics
	{
		RigidBody::RigidBody(Object* _object) noexcept : 
			object(_object)
		{}

		bool RigidBody::isActive()
		{
			return this->activate;
		}

		Object* RigidBody::GetObject()
		{
			return this->object;
		}

		std::wstring RigidBody::GetObjectName() noexcept
		{
			return this->object->GetName();
		}

		const Hyrule::Vector3D& RigidBody::ApplyPosition() noexcept
		{
			return object->GetPosition();
		}

		const Hyrule::Quaternion& RigidBody::ApplyQuaternion() noexcept
		{
			return object->GetRotation();
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
			return this->invMass;
		}

		Vector3D RigidBody::GetPosition() noexcept
		{
			if (object)
			{
				return object->GetPosition();
			}
			else
			{
				return Vector3D();
			}
		}

		void RigidBody::SetPosition(const Vector3D& _pos) noexcept
		{
			if (invMass == 0.f)
			{
				return;
			}

			if (object)
			{
				// WakeUp();
				object->GetPosition() = _pos;
			}
		}

		float RigidBody::GetStaticFriction() noexcept
		{
			return this->sfriction;
		}

		float RigidBody::GetDynamicFriction() noexcept
		{
			return this->dfriction;
		}

		float RigidBody::GetRestitution() noexcept
		{
			return this->restitution;
		}

		Hyrule::Matrix3x3 RigidBody::GetInvInertia() noexcept
		{
			if (!tensorUpdate)
			{
				this->CalculateInertiaTensor();
				tensorUpdate = true;
			}

			return this->invInertiaTensor;
		}

		void RigidBody::ApplyImpulse(const Vector3D& _impulse, const Vector3D& _contact) noexcept
		{
			if (this->activate == false || this->invMass == 0.f)
			{
				return;
			}

			// 선형 운동
			// 충격량 = (F * dt) = (m * a * dt) = (m * dV) = dP
			// dV = 충격량 / m
			Vector3D dV{ _impulse * this->invMass };
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
			Vector3D rXdP{ _contact.Cross(_impulse) };
			Vector3D dw{ rXdP * this->GetInvInertia() };
			this->angularVelocity += dw;
		}

		void RigidBody::ComputeVelocity(Vector3D _gravity, float _dt) noexcept
		{
			if (this->invMass == 0.f)
			{
				return;
			}

			// 힘을 속력으로 변환
			this->velocity += (this->force + _gravity * useGravity * mass) * invMass * _dt;
			this->angularVelocity += (this->torque * this->GetInvInertia()) * _dt;
			
			// 감쇠
			// this->velocity *= 1.f / (1.f + 0.f * _dt);
			// this->angularVelocity *= 1.f / (1.f + 0.f * _dt);
			this->velocity *= std::exp(-(linerDamping) * _dt);
			this->angularVelocity *= std::exp(-(angularDamping) * _dt);

			this->force = Vector3D::Zero();
			this->torque = Vector3D::Zero();
		}

		void RigidBody::ComputePosition(float _dt) noexcept
		{
			if (invMass == 0.f)
			{
				return;
			}

			Vector3D& position{ object->GetPosition() };
			Quaternion& rotation{ object->GetRotation() };

			Vector3D dV{ velocity * _dt };
 			position += dV;

			Vector3D dW{ angularVelocity * _dt };
			float angle = dW.Length();
			if (angle > (PI<float> / 2) / _dt)
			{
				angle = (PI<float> / 2) / _dt;
			}

			rotation = ToQuaternion(dW.Normalized(), dW.Length()) * rotation;
			rotation.Normalize();
		}

		void RigidBody::AddForce(const Vector3D& _force) noexcept
		{
			// WakeUp();
			this->force += _force;
		}

		void RigidBody::AddTorque(const Vector3D& _torque) noexcept
		{
			// WakeUp();
			this->torque += _torque;
		}

		/// <summary>
		/// 콜라이더가 가진 Shape으로 관성 텐서 계산
		/// </summary>
		void RigidBody::CalculateInertiaTensor(float _mass)
		{
			if (object != nullptr)
			{
				inertiaTensor = object->GetInertiaTensor(_mass);
				invInertiaTensor = inertiaTensor.Inverse();
				centerOfMass = object->GetCenterOfMess();
			}
		}

		void RigidBody::CalculateInertiaTensor()
		{
			CalculateInertiaTensor(this->mass);
		}

		/// <summary>
		/// 텐서 회전
		/// </summary>
		Matrix3x3 RigidBody::GetInertia()
		{
			if (!tensorUpdate)
			{
				CalculateInertiaTensor();
				tensorUpdate = true;
			}

			return this->inertiaTensor;
		}

#pragma region GetSet
		void RigidBody::SetMass(const float _mass) noexcept
		{
			if (_mass == 0.f)
			{
				this->invMass = 0.f;
			}
			else
			{
				this->invMass = 1 / _mass;
			}

			/// SetMess를 시도하면
			/// inertia Tensor를 새로 구하도록 해야함.
			tensorUpdate = false;
			this->mass = _mass;
		}

		float RigidBody::GetMass() const noexcept
		{
			return this->mass;
		}

		void RigidBody::SetVelocity(const Vector3D& _velo) noexcept
		{
			if (invMass == 0.f)
			{
				velocity = Vector3D();
				return;
			}

			// WakeUp();
			this->velocity = _velo;
		}

		Vector3D RigidBody::GetVelocity() const noexcept
		{
			return this->velocity;
		}

		void RigidBody::SetAngularVelocity(const Vector3D& _angular) noexcept
		{
			if (invMass == 0.f)
			{
				angularVelocity = Vector3D();
				return;
			}

			// WakeUp();
			this->angularVelocity = _angular;
		}

		Vector3D RigidBody::GetAngularVelocity() const noexcept
		{
			return this->angularVelocity;
		}

		bool RigidBody::IsAwake() const noexcept
		{
			// 표면에서 물체가 반복적인 충돌을 하게 되면
			// 속력에 한계가 있을텐데
			// thresold를 설정해서 thresold에 도달하면 타이머를 재기 시작함.
			// 2~3초라는 설정 시간이 흐르게 되면 Sleep 상태가 되어서 물리 연산을 쉰다.
			return !this->sleep;
		}

		void RigidBody::WakeUp() noexcept
		{
			this->sleep = false;
		}

#pragma endregion GetSet

		RigidBody* NonRigidBody::nonRigidBody = nullptr;

		void NonRigidBody::Init()
		{
			if (NonRigidBody::nonRigidBody == nullptr)
			{
				nonRigidBody = new RigidBody;
			}

			nonRigidBody->SetMass(0.f);
		}
	}
}