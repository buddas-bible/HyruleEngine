#pragma once
#include "Collider.h"
#include "Shape.h"

namespace Hyrule
{
	namespace Physics
	{
		class AABB;
		struct SHAPE_INPO;
		struct COLLIDER_INFO;

		class ConvexCollider : public Collider
		{
		public:
			ConvexCollider() noexcept = delete;
			ConvexCollider(Object*, COLLIDER_INFO*) noexcept;
			virtual ~ConvexCollider() noexcept = default;

		private:
			std::shared_ptr<ConvexShape> shape;

		public:
			virtual AABB GetAABB() override;
			virtual Vector3D FindFarthestPoint(const Vector3D&) override;
			virtual Face FindSupportFace(const Vector3D&) override;
			virtual Matrix3x3 GetInertiaTensor(float) noexcept override;
			virtual size_t GetType() noexcept override;
		};
	}
}