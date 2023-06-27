#pragma once
#include "IRigidBody.h"
#include "HyruleMath.h"

namespace Hyrule
{
	class Collider;
	class Transform;

	class RigidBody : public IRigidBody
	{
	public:
		RigidBody() noexcept = default;
		virtual ~RigidBody() noexcept = default;

	private:
		// Collider* collider;
		Transform* transform;

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
		Vector3D velocity;					// 속도
		Vector3D angularVelocity;			// 각속도
		float dfriction;					// 마찰
		float sfriction;					// 마찰
		float restitution;					// 반발계수
		Matrix3x3 inertiaTensor;			// 관성텐서
		Matrix3x3 invInertiaTensor;			// 역관성텐서

		bool sleep;							// 잠지고 있는 상태인가?
		bool kinematic;
		bool gravityEnabled;

	private:
		Vector3D force;						// 힘
		Vector3D torque;					// 토크

	public:
		void AddImpulse(const Vector3D&, const Vector3D&) noexcept;
		virtual void AddForce(const Vector3D&) noexcept override;
		virtual void AddTorque(const Vector3D&) noexcept override;

#pragma region GetSet
	public:
		virtual void SetMess(const float) noexcept override;
		virtual float GetMess() const noexcept override;

		virtual void SetVelocity(const Vector3D&) noexcept override;
		virtual Vector3D GetVelocity() const noexcept override;

		virtual void SetAngularVelocity(const Vector3D&) noexcept override;
		virtual Vector3D GetAngularVelocity() const noexcept override;

		virtual bool isSleeping() const noexcept override;
		virtual void isSleeping(const bool) noexcept override;

		virtual bool isKinematic() const noexcept override;
		virtual void isKinematic(const bool) noexcept override;
#pragma endregion GetSet
	};
}
