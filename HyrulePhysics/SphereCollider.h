#pragma once
#include "Collider.h"

namespace Hyrule
{
	namespace Physics
	{
		class SphereCollider : public Collider
		{
		public:
			SphereCollider(COLLIDER_INFO*) noexcept;
			virtual ~SphereCollider() noexcept = default;

		private:
			Collider::object;
			Collider::shape;

			Collider::center;
			Collider::size;
			Collider::isTrigger;

			Collider::inertia;
			Collider::centerOfMass;

		public:
			virtual void SetTrigger(bool) override;
			virtual void SetSize(const Vector3D&) override;
			virtual void SetCenter(const Vector3D&) override;

		public:
			virtual bool IsColliding() override;

		public:
			virtual Vector3D FindFarthestPoint(const Vector3D&) override;
		};
	}
}