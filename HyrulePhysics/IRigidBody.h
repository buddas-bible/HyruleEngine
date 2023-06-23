#pragma once


namespace Hyrule
{
	class Vector3D;

	class IRigidBody
	{
	public:
		IRigidBody() noexcept = default;
		virtual ~IRigidBody() noexcept = default;

	public:
		/// <summary>
		/// 외부에서 물리량을 조절하고 싶을 때.
		/// </summary>
		virtual void SetMess(const float) noexcept abstract;				// 
		virtual float GetMess() const noexcept abstract;				// 

		virtual void SetLinerDampping(const float) noexcept abstract;
		virtual float GetLinerDampping() const noexcept abstract;

		virtual void SetAngularDampping(const float) noexcept abstract;
		virtual float GetAngularDampping() const noexcept abstract;

		virtual void SetVelocity(const Vector3D&) noexcept abstract;
		virtual Vector3D& GetVelocity() const noexcept abstract;

		virtual void SetAccelerator(const Vector3D&) noexcept abstract;
		virtual Vector3D& GetAccelerator() const noexcept abstract;

		virtual void SetAngularVelocity(const Vector3D&) noexcept abstract;
		virtual Vector3D& GetAngularVelocity() const noexcept abstract;

		virtual void AddForce(const Vector3D&) noexcept abstract;
		virtual void AddTorque(const Vector3D&) noexcept abstract;

		virtual bool isSleeping() const noexcept abstract;
		virtual void isSleeping(const bool) noexcept abstract;

		virtual bool isKinematic() const noexcept abstract;
		virtual void isKinematic(const bool) noexcept abstract;
	};
}