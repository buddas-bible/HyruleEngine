#pragma once
#include "Collider.h"

namespace Hyrule
{
	namespace Physics
	{
		struct COLLIDER_INFO;

		class SphereCollider : public Collider
		{
		public:
			SphereCollider() noexcept = delete;
			SphereCollider(COLLIDER_INFO*) noexcept;
			virtual ~SphereCollider() noexcept = default;

		public:
			virtual Vector3D FindFarthestPoint(const Vector3D&) override;
			virtual Face FindSupportFace(const Vector3D&) override;
		};
	}
}