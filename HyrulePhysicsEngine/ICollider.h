#pragma once

namespace Hyrule
{
	struct Vector3D;

	namespace Physics
	{
		class ICollider
		{
		public:
			ICollider() noexcept = default;
			virtual ~ICollider() noexcept = default;

		public:
			virtual void SetTrigger(bool) abstract;
			virtual void SetSize(const Vector3D&) abstract;
			virtual void SetCenter(const Vector3D&) abstract;
			virtual bool IsColliding() abstract;

		};
	}
}