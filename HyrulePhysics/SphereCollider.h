#pragma once
#include "Collider.h"

namespace Hyrule
{
	namespace Physics
	{
		class AABB;
		struct COLLIDER_INFO;

		class SphereCollider : public Collider
		{
		public:
			SphereCollider() noexcept = delete;
			SphereCollider(Object*, COLLIDER_INFO*) noexcept;
			virtual ~SphereCollider() noexcept = default;

		public:
			virtual AABB GetAABB() override;
			virtual Vector3D FindFarthestPoint(const Vector3D&) override;
			virtual Face FindSupportFace(const Vector3D&) override;
			virtual Matrix3x3 GetInertiaTensor(float) noexcept override;
		};
	}
}