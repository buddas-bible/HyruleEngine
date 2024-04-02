#pragma once


namespace Hyrule
{
	struct Vector3D;
	struct Vector4D;
	struct Quaternion;
	struct Matrix4x4;

	namespace Physics
	{
		class IRigidBody
		{
		public:
			IRigidBody() = default;
			virtual ~IRigidBody() = default;

		public:
			virtual const Vector3D& ApplyPosition() abstract;
			virtual const Quaternion& ApplyQuaternion() abstract;

			virtual void OnEnable() abstract;
			virtual void OnDisable() abstract;
			virtual void OnDestroy() abstract;

		public:
			virtual void AddForce(const Hyrule::Vector3D&) abstract;
			virtual void AddTorque(const Hyrule::Vector3D&) abstract;

			/// <summary>
			/// 외부에서 물리량을 조절하고 싶을 때.
			/// </summary>
			virtual void SetMass(const float) abstract;					// 질량
			virtual float GetMass() const abstract;

			virtual void SetVelocity(const Hyrule::Vector3D&) abstract;
			virtual Hyrule::Vector3D GetVelocity() const abstract;

			virtual void SetAngularVelocity(const Hyrule::Vector3D&) abstract;
			virtual Hyrule::Vector3D GetAngularVelocity() const abstract;

			virtual void WakeUp() abstract;
			virtual bool IsAwake() const abstract;
		};
	}
}