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
			Matrix3x3 inertiaTensor{ Matrix3x3::Identity() };	// 관성텐서
			Matrix3x3 invInertiaTensor{ Matrix3x3::Identity() };// 역관성텐서

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
