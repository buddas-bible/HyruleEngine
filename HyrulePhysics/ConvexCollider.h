#pragma once
#include "Collider.h"
#include "Shape.h"

namespace Hyrule
{
	namespace Physics
	{
		struct COLLIDER_INFO;

		class ConvexCollider : public Collider
		{
		public:
			ConvexCollider() noexcept = delete;
			ConvexCollider(COLLIDER_INFO*) noexcept;
			virtual ~ConvexCollider() noexcept = default;

		public:
			virtual Vector3D FindFarthestPoint(const Vector3D&) override;
			virtual Face FindSupportFace(const Vector3D&) override;
		};
	}
}