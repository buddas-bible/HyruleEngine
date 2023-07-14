#pragma once
#include "Collider.h"

namespace Hyrule
{
	namespace Physics
	{
		struct COLLIDER_INFO;

		class PlaneCollider : public Collider
		{
		public:
			PlaneCollider() noexcept = default;
			PlaneCollider(COLLIDER_INFO*) noexcept;
			virtual ~PlaneCollider() noexcept = default;

		private:
			Collider::object;
			Collider::shape;

			Collider::center;
			Collider::size;
			Collider::isTrigger;

			Collider::inertia;
			Collider::centerOfMass;

		public:
			virtual Vector3D FindFarthestPoint(const Vector3D&) override;
		};
	}
}

