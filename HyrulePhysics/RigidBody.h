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

			virtual const Vector3D& ApplyPosition() noexcept override;
			virtual const Quaternion& ApplyQuaternion() noexcept override;

			virtual void OnEnable() noexcept override;
			virtual void OnDisable() noexcept override;
			virtual void OnDestroy() noexcept override;
			
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
			float mass{ 10.f };									// ����
			float invMass{ 1 / 10.f };							// �� ����
			Vector3D velocity;									// �ӵ�
			Vector3D angularVelocity;							// ���ӵ�

			// Vector3D deltaVelocity;
			// Vector3D deltaAngularVelocity;

			float dfriction{ 0.1f };							// ����
			float sfriction{ 0.2f };							// ����
			float restitution{ 0.2f };							// �ݹ߰��
			Matrix3x3 inertiaTensor{ Matrix3x3::Identity() };	// �����ټ�
			Matrix3x3 invInertiaTensor{ Matrix3x3::Identity() };// �������ټ�

			float linerDamping{ 0.4f };
			float angularDamping{ 0.4f };

			bool sleep{ false };						// ������ �ִ� �����ΰ�?
			bool kinematic;								// �ٸ� ��ü���� �ܷ��� ���� �� �ִ°�?
			bool useGravity{ true };					// �߷¿� ������ �޴°�?
			bool freezePos[3];
			bool freezeRot[3];

		private:
			Vector3D force;						// ��
			Vector3D torque;					// ��ũ

			bool tensorUpdate{ false };
			float accumulate{};

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
			virtual void SetMass(const float) noexcept override;
			virtual float GetMass() const noexcept override;

			virtual void SetVelocity(const Hyrule::Vector3D&) noexcept override;
			virtual Hyrule::Vector3D GetVelocity() const noexcept override;

			virtual void SetAngularVelocity(const Hyrule::Vector3D&) noexcept override;
			virtual Hyrule::Vector3D GetAngularVelocity() const noexcept override;

			virtual void WakeUp() noexcept override;
			virtual bool IsAwake() const noexcept override;
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
