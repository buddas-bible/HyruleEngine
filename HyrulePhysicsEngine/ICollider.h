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
			/// 게임 엔진으로부터 트랜스폼 정보를 받음.
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