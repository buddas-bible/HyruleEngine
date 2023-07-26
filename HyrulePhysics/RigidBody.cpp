#include "RigidBody.h"

#include "Object.h"
#include "Collider.h"
#include "ObjectManager.h"

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

			// ���� �
			// ��ݷ� = (F * dt) = (m * a * dt) = (m * dV) = dP
			// dV = ��ݷ� / m
			Vector3D dV = _impulse * this->invMass;
			this->velocity += dV;

			// ȸ�� �
			// t = Ia = r X F
			// 
			// �纯�� dt ����
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
			if (this->activate == false || this->invMass == 0.f)
			{
				return;
			}

			if (this->useGravity == true)
			{
				this->velocity += _gravity * _dt;
			}

			// ���� �ӷ����� ��ȯ
			this->velocity += (this->force * this->invMass) * _dt;
			this->angularVelocity += (this->torque * this->invInertiaTensor) * _dt;
			
			// ����
			this->velocity *= std::exp(-0.1 * _dt);
			this->angularVelocity *= std::exp(-0.1 * _dt);

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

			position += this->velocity * _dt;

			rotation *= ToQuaternion(
				this->angularVelocity.Normalized(), 
				this->angularVelocity.Length() * _dt
			);
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
			if (object != nullptr)
			{
				inertiaTensor = object->GetInertiaTensor(_mess);
				invInertiaTensor = inertiaTensor.Inverse();
				centerOfMass = object->GetCenterOfMess();
			}
		}

		void RigidBody::CalculateInertiaTensor()
		{
			CalculateInertiaTensor(this->mass);
		}

		/// <summary>
		/// �ټ� ȸ��
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

			/// SetMess�� �õ��ϸ�
			/// inertia Tensor�� ���� ���ϵ��� �ؾ���.
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

			this->angularVelocity = _angular;
		}

		Vector3D RigidBody::GetAngularVelocity() const noexcept
		{
			return this->angularVelocity;
		}

		bool RigidBody::isSleeping() const noexcept
		{
			// ǥ�鿡�� ��ü�� �ݺ����� �浹�� �ϰ� �Ǹ�
			// �ӷ¿� �Ѱ谡 �����ٵ�
			// thresold�� �����ؼ� thresold�� �����ϸ� Ÿ�̸Ӹ� ��� ������.
			// 2~3�ʶ�� ���� �ð��� �帣�� �Ǹ� Sleep ���°� �Ǿ ���� ������ ����.
			return this->sleep;
		}

		void RigidBody::isSleeping(const bool _sleep) noexcept
		{
			this->sleep = _sleep;
		}

		Hyrule::Matrix4x4 RigidBody::Apply() noexcept
		{
			return object->GetWorldTM();
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