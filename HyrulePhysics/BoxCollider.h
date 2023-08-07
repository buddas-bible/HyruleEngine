#pragma once
#include "Collider.h"
#include "Shape.h"

namespace Hyrule
{
	namespace Physics
	{
		struct COLLIDER_INFO;
		class AABB;

		class BoxCollider : public Collider
		{
		public:
			BoxCollider() noexcept = delete;
			BoxCollider(Object*, COLLIDER_INFO*) noexcept;
			virtual ~BoxCollider() noexcept = default;

		private:
			std::shared_ptr<BoxShape> shape;

		public:
			virtual AABB GetAABB() override;
			virtual Vector3D FindFarthestPoint(const Vector3D&) override;
			virtual Face FindSupportFace(const Vector3D&) override;
			virtual Matrix3x3 GetInertiaTensor(float) noexcept override;
			Vector3D ClosestPoint(const Vector3D& _point);
		};
	}
}
