#pragma once
#include "Collider.h"
#include "Shape.h"

namespace Hyrule
{
	namespace Physics
	{
		struct COLLIDER_INFO;

		class BoxCollider : public Collider
		{
		public:
			BoxCollider() noexcept = delete;
			BoxCollider(Object*, COLLIDER_INFO*) noexcept;
			virtual ~BoxCollider() noexcept = default;

		private:
			std::shared_ptr<BoxShape> shape;

		public:
			virtual Vector3D FindFarthestPoint(const Vector3D&) override;
			virtual Face FindSupportFace(const Vector3D&) override;
		};
	}
}
