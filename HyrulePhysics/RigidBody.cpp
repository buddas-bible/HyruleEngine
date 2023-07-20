#include "RigidBody.h"

#include "Object.h"
#include "Collider.h"

namespace Hyrule
{
	namespace Physics
	{
		bool RigidBody::isActive()
		{
			return this->activate;
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

		}

		void RigidBody::ApplyImpulse(const Vector3D& _impulse, const Vector3D& _contact) noexcept
		{
			if (activate == false || invMess == 0.f)
			{
				return;
			}

			// ���� �
			// ��ݷ� = (F * dt) = (m * a * dt) = (m * dV) = dP
			// dV = ��ݷ� / m
			Vector3D dV = _impulse * invMess;
			velocity = velocity + dV;

			// ȸ�� �
			// t = Ia = r X F
			// 
			// �纯�� dt ����
			// t * dt = (r X F * dt) = (r X m * a * dt) = (r X m * dV) = r X dP
			// dL = (t * dt) = r X dP
			// dL = Ia * dt = I * dw
			// dw = dL / I
			// dw = (r X dP) / I
			Vector3D dw = _contact.Cross(_impulse) * invInertiaTensor;
			angularVelocity = angularVelocity + dw;
		}

		void RigidBody::ApplyForceAndTorque(Vector3D _gravity, float _dt) noexcept
		{
			if (activate == false || invMess == 0.f)
			{
				return;
			}

			if (useGravity == true)
			{
				this->velocity += _gravity * _dt;
			}

			this->velocity += this->force * this->invMess * _dt;
			this->force = Vector3D::Zero();

			this->angularVelocity += this->torque * this->invInertiaTensor * _dt;
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

		void RigidBody::ApplyVelocity(float _dt) noexcept
		{
			Vector3D dL{ velocity * _dt };

			Vector3D dW{ angularVelocity * _dt };

			// �� dW�� ũ�⸦ ����, ������ ������ �ؼ� �ఢ���� ��Ÿ�� �� ������?
			Matrix4x4 rot{ ToMatrix4(dW.Normalized(), dW.Length()) };
		}

// 		void RigidBody::ApplyAngularVelocity(float _dt) noexcept
// 		{
// 			Vector3D dW{ angularVelocity * _dt };
// 
// 			// �� dW�� ũ�⸦ ����, ������ ������ �ؼ� �ఢ���� ��Ÿ�� �� ������?
// 			Matrix4x4 rot{ ToMatrix4(dW.Normalized(), dW.Length()) };
// 		}

		void RigidBody::AddForce(const Vector3D& _force) noexcept
		{
			this->force += _force;
		}

		void RigidBody::AddTorque(const Vector3D& _torque) noexcept
		{
			this->torque += _torque;
		}

		/// <summary>
		/// �ݶ��̴��� ���� Shape���� ���� �ټ� ���
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
		/// �ټ� ȸ��
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

			/// SetMess�� �õ��ϸ�
			/// inertia Tensor�� ���� ���ϵ��� �ؾ���.
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

		Hyrule::Matrix4x4 RigidBody::Apply() const noexcept
		{
			return this->object->GetWorldTM();
		}
#pragma endregion GetSet
	}
}