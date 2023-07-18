#pragma once

namespace Hyrule
{
	struct Vector3D;
	struct Matrix4x4;
	struct COLLIDER_INFO;

	namespace Physics
	{
		class ICollider
		{
		public:
			ICollider() noexcept = default;
			virtual ~ICollider() noexcept = default;

		public:
			virtual void OnDisable() noexcept abstract;
			virtual void OnEnable() noexcept abstract;

		public:
			/// <summary>
			/// ���� �������κ��� Ʈ������ ������ ����.
			/// </summary>
			virtual void SetWorldTransform(const Matrix4x4&) abstract;

			virtual void SetTrigger(bool) abstract;
			virtual void SetSize(const Vector3D&) abstract;
			virtual void SetCenter(const Vector3D&) abstract;

			// virtual std::wstring GetObjectName() abstract;
			// virtual bool IsColliding() abstract;
		};
	}
}