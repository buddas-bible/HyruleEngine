#pragma once

namespace Hyrule
{
	struct Vector3D;
	struct Matrix4x4;

	namespace Physics
	{
		class ICollider
		{
		public:
			ICollider() noexcept = default;
			virtual ~ICollider() noexcept = default;

		public:
			/// <summary>
			/// ���� �������κ��� Ʈ������ ������ ����.
			/// 
			/// 
			/// </summary>
			virtual void SetWorldTransformMatrix(const Matrix4x4&) abstract;

			virtual void SetTrigger(bool) abstract;
			virtual void SetSize(const Vector3D&) abstract;
			virtual void SetCenter(const Vector3D&) abstract;
			virtual bool IsColliding() abstract;
		};
	}
}