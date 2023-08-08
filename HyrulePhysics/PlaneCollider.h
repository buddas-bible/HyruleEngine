#pragma once
#include "Collider.h"
#include "Shape.h"

namespace Hyrule
{
	namespace Physics
	{
		class AABB;
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
			virtual AABB GetAABB() override;
			virtual Vector3D FindFarthestPoint(const Vector3D&) override;
			virtual Face FindSupportFace(const Vector3D&) override;
			virtual Matrix3x3 GetInertiaTensor(float) noexcept override;
			virtual size_t GetType() noexcept override;
		};
	}
}

