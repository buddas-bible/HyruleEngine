#pragma once
#include "IRigidBody.h"

#include "HyruleMath.h"

namespace Hyrule
{
	namespace Physics
	{
		class Object;

		class RigidBody : public IRigidBody
		{
		public:
			RigidBody() noexcept = default;
			virtual ~RigidBody() noexcept = default;

		private:
			Object* object;

		private:
			/// <summary>
			/// ���⼭ �����ǰ� �����̼��� Ʈ������ �����ε�
			/// ��� �� ������ ����غ�����
			/// 
			/// Ʈ������ ������ ������ ���·� ������ ������?
			/// ��� ������Ʈ �޴°� �����ϰ�
			/// ������ �޾ƿ��°�...?
			/// </summary>
			Hyrule::Vector3D centerOfMess;
			float mess{ 10.f };							// ����
			float invMess{ 1 / 10.f };						// �� ����
			Hyrule::Vector3D velocity;					// �ӵ�
			Hyrule::Vector3D angularVelocity;			// ���ӵ�
			float dfriction;					// ����
			float sfriction;					// ����
			float restitution;					// �ݹ߰��
			Hyrule::Matrix3x3 inertiaTensor;			// �����ټ�
			Hyrule::Matrix3x3 invInertiaTensor;			// �������ټ�

			bool sleep;							// ������ �ִ� �����ΰ�?
			bool kinematic;						// �ٸ� ��ü���� �ܷ��� ���� �� �ִ°�?
			bool gravityEnabled;				// �߷¿� ������ �޴°�?

		private:
			Hyrule::Vector3D force;						// ��
			Hyrule::Vector3D torque;					// ��ũ

		public:
			void AddImpulse(const Hyrule::Vector3D&, const Hyrule::Vector3D&) noexcept;
			virtual void AddForce(const Hyrule::Vector3D&) noexcept override;
			virtual void AddTorque(const Hyrule::Vector3D&) noexcept override;

		private:
			void CalculateInertiaTensor(float);
			void CalculateInertiaTensor();
			Matrix3x3 GetInertia();

#pragma region GetSet
		public:
			virtual void SetMess(const float) noexcept override;
			virtual float GetMess() const noexcept override;

			virtual void SetVelocity(const Hyrule::Vector3D&) noexcept override;
			virtual Hyrule::Vector3D GetVelocity() const noexcept override;

			virtual void SetAngularVelocity(const Hyrule::Vector3D&) noexcept override;
			virtual Hyrule::Vector3D GetAngularVelocity() const noexcept override;

			virtual bool isSleeping() const noexcept override;
			virtual void isSleeping(const bool) noexcept override;
#pragma endregion GetSet
		};
	}
}
