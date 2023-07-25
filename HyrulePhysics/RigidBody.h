#pragma once
#include "IRigidBody.h"

#include "HyruleMath.h"
#include <string>

namespace Hyrule
{
	namespace Physics
	{
		struct Object;


		class RigidBody : public IRigidBody
		{
		public:
			RigidBody() noexcept = default;
			RigidBody(Object*) noexcept;
			virtual ~RigidBody() noexcept = default;

		private:
			Object* object;
			bool activate;

		public:
			bool isActive();
			Object* GetObject();
			std::wstring GetObjectName() noexcept;
			virtual void OnEnable() noexcept override;
			virtual void OnDisable() noexcept override;
			virtual void OnDestroy() noexcept override;
			
		private:
			// Vector3D position;
			// Quaternion rotation{ 1.f, 0.f, 0.f, 0.f };

		private:
			/// <summary>
			/// ���⼭ �����ǰ� �����̼��� Ʈ������ �����ε�
			/// ��� �� ������ ����غ�����
			/// 
			/// Ʈ������ ������ ������ ���·� ������ ������?
			/// ��� ������Ʈ �޴°� �����ϰ�
			/// ������ �޾ƿ��°�...?
			/// </summary>
			Vector3D centerOfMass;
			float mess{ 10.f };							// ����
			float invMess{ 1 / 10.f };					// �� ����
			Vector3D velocity;							// �ӵ�
			Vector3D angularVelocity;					// ���ӵ�
			float dfriction{ 0.1f };					// ����
			float sfriction{ 0.2f };					// ����
			float restitution{ 0.2f };					// �ݹ߰��
			Matrix3x3 inertiaTensor;					// �����ټ�
			Matrix3x3 invInertiaTensor;					// �������ټ�

			bool sleep;									// ������ �ִ� �����ΰ�?
			bool kinematic;								// �ٸ� ��ü���� �ܷ��� ���� �� �ִ°�?
			bool useGravity;							// �߷¿� ������ �޴°�?
			bool freezePos[3];
			bool freezeRot[3];

		private:
			Vector3D force;						// ��
			Vector3D torque;					// ��ũ

		public:
			float GetInvMass() noexcept;
			Vector3D GetPosition() noexcept;
			void SetPosition(const Vector3D&) noexcept;
			float GetStaticFriction() noexcept;
			float GetDynamicFriction() noexcept;
			float GetRestitution() noexcept;
			Matrix3x3 GetInvInertia() noexcept;

		public:
			void ApplyImpulse(const Hyrule::Vector3D&, const Hyrule::Vector3D&) noexcept;
			void ComputeVelocity(Vector3D _gravity, float) noexcept;
			void ComputePosition(float) noexcept;
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

			virtual Matrix4x4 Apply() noexcept override;
#pragma endregion GetSet
		};

		class NonRigidBody
		{
		public:
			static RigidBody* nonRigidBody;

			static void Init();
		};
	}
}
