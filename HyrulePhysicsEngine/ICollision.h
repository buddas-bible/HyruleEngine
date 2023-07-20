#pragma once

namespace Hyrule
{
	struct Vector3D;


	namespace Physics
	{
		class ICollsion
		{
		public:
			ICollsion()	noexcept = default;
			virtual ~ICollsion() noexcept = default;

		public:
			virtual Vector3D Impulse() noexcept abstract;
			virtual Vector3D RelativeVelocity() noexcept abstract;
			virtual std::vector<Vector3D> Contacts() noexcept abstract;
			virtual Vector3D Contact(size_t) noexcept abstract;
			virtual size_t ContactCount() noexcept abstract;
			virtual Vector3D Normal() noexcept abstract;
		};
	}
}