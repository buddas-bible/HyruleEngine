#pragma once


namespace Hyrule
{
	struct Vector3D;
	struct Vector4D;
	struct Matrix4x4;

	namespace Physics
	{
		class IRigidBody
		{
		public:
			IRigidBody() noexcept = default;
			virtual ~IRigidBody() noexcept = default;

		public:
			virtual void OnEnable() noexcept abstract;
			virtual void OnDisable() noexcept abstract;
			virtual void OnDestroy() noexcept abstract;

		public:
			virtual void AddForce(const Hyrule::Vector3D&) noexcept abstract;
			virtual void AddTorque(const Hyrule::Vector3D&) noexcept abstract;

			/// <summary>
			/// 외부에서 물리량을 조절하고 싶을 때.
			/// </summary>
			virtual void SetMess(const float) noexcept abstract;					// 질량
			virtual float GetMess() const noexcept abstract;

			virtual void SetVelocity(const Hyrule::Vector3D&) noexcept abstract;
			virtual Hyrule::Vector3D GetVelocity() const noexcept abstract;

			virtual void SetAngularVelocity(const Hyrule::Vector3D&) noexcept abstract;
			virtual Hyrule::Vector3D GetAngularVelocity() const noexcept abstract;

			virtual bool isSleeping() const noexcept abstract;
			virtual void isSleeping(const bool) noexcept abstract;

			/// <summary>
			/// 강체 시뮬레이션으로 변화된 월드 트랜프폼 정보
			/// </summary>
			virtual Matrix4x4 Apply() noexcept abstract;
		};
	}
}