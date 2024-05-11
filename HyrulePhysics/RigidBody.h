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
			/// 여기서 포지션과 로테이션은 트렌스폼 정보인데
			/// 어떻게 할 것인지 고민해봐야함
			/// 
			/// 트랜스폼 정보를 포인터 형태로 가지고 있을까?
			/// 계속 업데이트 받는건 불편하고
			/// 참조로 받아오는건...?
			/// </summary>
			Vector3D centerOfMass;
			float mass{ 10.f };									// 질량
			float invMass{ 1 / 10.f };							// 역 질량
			Vector3D velocity;									// 속도
			Vector3D angularVelocity;							// 각속도

			// Vector3D deltaVelocity;
			// Vector3D deltaAngularVelocity;

			float dfriction{ 0.1f };							// 마찰
			float sfriction{ 0.2f };							// 마찰
			float restitution{ 0.2f };							// 반발계수
			Matrix3x3 inertiaTensor{ };	// 관성텐서
			Matrix3x3 invInertiaTensor{ };// 역관성텐서

			float linerDamping{ 0.4f };
			float angularDamping{ 0.4f };

			bool sleep{ false };						// 잠지고 있는 상태인가?
			bool kinematic;								// 다른 물체에게 외력을 받을 수 있는가?
			bool useGravity{ true };					// 중력에 영향을 받는가?
			bool freezePos[3];
			bool freezeRot[3];

		private:
			Vector3D force;						// 힘
			Vector3D torque;					// 토크

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
