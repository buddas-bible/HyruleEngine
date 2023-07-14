#pragma once
#include "Collider.h"

namespace Hyrule
{
	namespace Physics
	{
		struct COLLIDER_INFO;

		class ConvexCollider : public Collider
		{
		public:
			ConvexCollider() noexcept = default;
			ConvexCollider(COLLIDER_INFO*) noexcept;
			virtual ~ConvexCollider() noexcept = default;

		public:
			virtual Vector3D FindFarthestPoint(const Vector3D&) override;
		};
	}
}