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
			/// 여기서 포지션과 로테이션은 트렌스폼 정보인데
			/// 어떻게 할 것인지 고민해봐야함
			/// 
			/// 트랜스폼 정보를 포인터 형태로 가지고 있을까?
			/// 계속 업데이트 받는건 불편하고
			/// 참조로 받아오는건...?
			/// </summary>
			float mess;							// 질량
			float invMess;						// 역 질량
			Hyrule::Vector3D velocity;					// 속도
			Hyrule::Vector3D angularVelocity;			// 각속도
			float dfriction;					// 마찰
			float sfriction;					// 마찰
			float restitution;					// 반발계수
			Hyrule::Matrix3x3 inertiaTensor;			// 관성텐서
			Hyrule::Matrix3x3 invInertiaTensor;			// 역관성텐서

			bool sleep;							// 잠지고 있는 상태인가?
			bool kinematic;
			bool gravityEnabled;

		private:
			Hyrule::Vector3D force;						// 힘
			Hyrule::Vector3D torque;					// 토크

		public:
			void AddImpulse(const Hyrule::Vector3D&, const Hyrule::Vector3D&) noexcept;
			virtual void AddForce(const Hyrule::Vector3D&) noexcept override;
			virtual void AddTorque(const Hyrule::Vector3D&) noexcept override;

		private:
			void CalculateInertiaTensor();

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

			virtual bool isKinematic() const noexcept override;
			virtual void isKinematic(const bool) noexcept override;
#pragma endregion GetSet
		};
	}
}
