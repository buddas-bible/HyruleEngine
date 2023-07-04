#pragma once


namespace Hyrule
{
	struct Vector3D;
	struct Vector4D;

	namespace Physics
	{
		class IRigidBody
		{
		public:
			IRigidBody() noexcept = default;
			virtual ~IRigidBody() noexcept = default;

		public:
			virtual void AddForce(const Hyrule::Vector3D&) noexcept abstract;
			virtual void AddTorque(const Hyrule::Vector3D&) noexcept abstract;

			/// <summary>
			/// �ܺο��� �������� �����ϰ� ���� ��.
			/// </summary>
			virtual void SetMess(const float) noexcept abstract;					// ����
			virtual float GetMess() const noexcept abstract;

			virtual void SetVelocity(const Hyrule::Vector3D&) noexcept abstract;
			virtual Hyrule::Vector3D GetVelocity() const noexcept abstract;

			virtual void SetAngularVelocity(const Hyrule::Vector3D&) noexcept abstract;
			virtual Hyrule::Vector3D GetAngularVelocity() const noexcept abstract;

			virtual bool isSleeping() const noexcept abstract;
			virtual void isSleeping(const bool) noexcept abstract;
		};
	}
}