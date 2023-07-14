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
			SphereCollider(COLLIDER_INFO*) noexcept;
			virtual ~SphereCollider() noexcept = default;

		public:
			virtual Vector3D FindFarthestPoint(const Vector3D&) override;
		};
	}
}