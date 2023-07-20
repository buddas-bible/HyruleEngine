#pragma once
#include "Collider.h"
#include "Shape.h"

namespace Hyrule
{
	namespace Physics
	{
		struct COLLIDER_INFO;

		class PlaneCollider : public Collider
		{
		public:
			PlaneCollider() noexcept = delete;
			PlaneCollider(Object*, COLLIDER_INFO*) noexcept;
			virtual ~PlaneCollider() noexcept = default;

		private:
			std::shared_ptr<PlaneShape> shape;

		public:
			virtual Vector3D FindFarthestPoint(const Vector3D&) override;
			virtual Face FindSupportFace(const Vector3D&) override;
		};
	}
}

