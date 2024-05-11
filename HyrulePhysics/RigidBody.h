#pragma once
#include "IRigidBody.h"

#include "HyruleMath.h"
#include <string>

namespace hyrule
{
	namespace Physics
	{
		struct Object;


		class RigidBody : public IRigidBody
		{
		public:
			RigidBody() = default;
			RigidBody(Object*);
			virtual ~RigidBody() = default;

		private:
			Object* object;
			bool activate;

		public:
			bool isActive();
			Object* GetObject();
			std::wstring GetObjectName();

			virtual const Vector3D& ApplyPosition() override;
			virtual const Quaternion& ApplyQuaternion() override;

			virtual void OnEnable() override;
			virtual void OnDisable() override;
			virtual void OnDestroy() override;
			
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
			Matrix3x3 inertiaTensor{ };	// �����ټ�
			Matrix3x3 invInertiaTensor{ };// �������ټ�

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
			float GetInvMass();

			Vector3D GetPosition();
			void SetPosition(const Vector3D&);

			float GetStaticFriction();
			float GetDynamicFriction();

			float GetRestitution();
			Matrix3x3 GetInvInertia();

		public:
			void ApplyImpulse(const hyrule::Vector3D&, const hyrule::Vector3D&);
			void ComputeVelocity(Vector3D _gravity, float);
			void ComputePosition(float);
			virtual void AddForce(const hyrule::Vector3D&) override;
			virtual void AddTorque(const hyrule::Vector3D&) override;

		private:
			void CalculateInertiaTensor(float);
			void CalculateInertiaTensor();
			Matrix3x3 GetInertia();

#pragma region GetSet
		public:
			virtual void SetMass(const float) override;
			virtual float GetMass() const override;

			virtual void SetVelocity(const hyrule::Vector3D&) override;
			virtual hyrule::Vector3D GetVelocity() const override;

			virtual void SetAngularVelocity(const hyrule::Vector3D&) override;
			virtual hyrule::Vector3D GetAngularVelocity() const override;

			virtual void WakeUp() override;
			virtual bool IsAwake() const override;
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
