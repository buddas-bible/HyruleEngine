#pragma once
#include "Collider.h"
#include "Shape.h"

namespace Hyrule
{
	namespace Physics
	{
		struct COLLIDER_INFO;
		struct SHAPE_INPO;

		class ConvexCollider : public Collider
		{
		public:
			ConvexCollider() noexcept = delete;
			ConvexCollider(Object*, COLLIDER_INFO*) noexcept;
			virtual ~ConvexCollider() noexcept = default;

		private:
			std::shared_ptr<ConvexShape> shape;

		public:
			virtual Vector3D FindFarthestPoint(const Vector3D&) override;
			virtual Face FindSupportFace(const Vector3D&) override;
			virtual Matrix3x3 GetInertiaTensor(float) noexcept override;
		};
	}
}