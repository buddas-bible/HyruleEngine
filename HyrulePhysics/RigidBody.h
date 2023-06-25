#pragma once
#include "IRigidBody.h"
#include "HyruleMath.h"

namespace Hyrule
{
	class Collider;

	class RigidBody : public IRigidBody
	{
	public:
		RigidBody() noexcept = default;
		virtual ~RigidBody() noexcept = default;

	private:
		Collider* collider;

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
		Vector3D position;					// 위치
		Vector3D velocity;					// 속도
		Vector3D accleration;				// 가속도
		Quaternion rotation;				// 각도
		Vector4D angularVelocity;			// 각속도
		Vector4D angularAcceleration;		// 각가속도
		// float friction;						// 마찰
		// float damping						// 감쇠
		float restitution;					// 반발계수
		bool sleep;							// 잠지고 있는 상태인가?
		bool kinematic;
		bool gravityEnabled;

	private:
		Vector3D force;						// 힘
		Vector3D torque;					// 토크

	public:
		virtual void AddForce(const Vector3D&) noexcept override;
		virtual void AddTorque(const Vector3D&) noexcept override;

#pragma region GetSet
	public:
		virtual void SetMess(const float) noexcept override;
		virtual float GetMess() const noexcept override;

		virtual void SetLinerDampping(const float) noexcept override;
		virtual float GetLinerDampping() const noexcept override;

		virtual void SetAngularDampping(const float) noexcept override;
		virtual float GetAngularDampping() const noexcept override;

		virtual void SetVelocity(const Vector3D&) noexcept override;
		virtual Vector3D GetVelocity() const noexcept override;

		virtual void SetAccleration(const Vector3D&) noexcept override;
		virtual Vector3D GetAccleration() const noexcept override;

		virtual void SetAngularVelocity(const Vector4D&) noexcept override;
		virtual Vector4D GetAngularVelocity() const noexcept override;

		virtual bool isSleeping() const noexcept override;
		virtual void isSleeping(const bool) noexcept override;

		virtual bool isKinematic() const noexcept override;
		virtual void isKinematic(const bool) noexcept override;
#pragma endregion GetSet
	};
}
