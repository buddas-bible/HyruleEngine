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
			// �ϴ� �ݶ��̴� 1���� ���� ���� �ټ� ���
			inertiaTensor = object->GetInertiaTensor(_mess);
			invInertiaTensor = inertiaTensor.Inverse();
			centerOfMess = object->GetCenterOfMess();
			// �ϴ� �ݶ��̴� 1�����̶� ���� �ټ��� ���غ����� ����...
			// �׸��� ��ü�� ������ �ݶ��̴��� �����ٰ� ���� ��
			// �� ����غ� ���� ����.....
			// ���� �߽��� �Űܾ� �Ѵٴ� ��.
			// ���� �ټ��� ����ϴ� �κ��� �����ϴ�...
			// �뷫 ������ ���� ����..
			// �ٸ�ü�� ���� �븻 ������ ���� �� ���ü�� ���ǿ��� �E�� �������� �Ǵ��ϰ�?
			// (���� �߽��� �ܰ��� �ֱ� ������)
			// 
			// �̷��ٰ� �ɱ�?
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
			return inertiaTensor;
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
#pragma endregion GetSet
	}
}