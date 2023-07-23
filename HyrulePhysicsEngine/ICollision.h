#pragma once
#include <vector>

namespace Hyrule
{
	struct Vector3D;

	namespace Physics
	{
		class ICollider;

		class ICollision
		{
		public:
			ICollision()	noexcept = default;
			virtual ~ICollision() noexcept = default;

		public:
			virtual ICollider* Collider() noexcept abstract;
			virtual Vector3D Impulse() noexcept abstract;
			virtual std::vector<Vector3D> Contacts() noexcept abstract;
			virtual Vector3D Contact(size_t) noexcept abstract;
			virtual size_t ContactCount() noexcept abstract;
			virtual Vector3D Normal() noexcept abstract;
		};
	}
}