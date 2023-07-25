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
			/// 여기서 포지션과 로테이션은 트렌스폼 정보인데
			/// 어떻게 할 것인지 고민해봐야함
			/// 
			/// 트랜스폼 정보를 포인터 형태로 가지고 있을까?
			/// 계속 업데이트 받는건 불편하고
			/// 참조로 받아오는건...?
			/// </summary>
			Vector3D centerOfMass;
			float mess{ 10.f };							// 질량
			float invMess{ 1 / 10.f };					// 역 질량
			Vector3D velocity;							// 속도
			Vector3D angularVelocity;					// 각속도
			float dfriction{ 0.1f };					// 마찰
			float sfriction{ 0.2f };					// 마찰
			float restitution{ 0.2f };					// 반발계수
			Matrix3x3 inertiaTensor;					// 관성텐서
			Matrix3x3 invInertiaTensor;					// 역관성텐서

			bool sleep;									// 잠지고 있는 상태인가?
			bool kinematic;								// 다른 물체에게 외력을 받을 수 있는가?
			bool useGravity;							// 중력에 영향을 받는가?
			bool freezePos[3];
			bool freezeRot[3];

		private:
			Vector3D force;						// 힘
			Vector3D torque;					// 토크

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
