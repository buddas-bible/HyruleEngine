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
			virtual ~ICollision() = default;

		public:
			virtual ICollider* Collider() abstract;
			virtual void* UserData() abstract;
			virtual std::wstring InstanceID() abstract;
			virtual std::wstring Tag() abstract;
			virtual Vector3D Impulse() abstract;
			virtual std::vector<Vector3D> Contacts() abstract;
			virtual Vector3D Contact(size_t) abstract;
			virtual size_t ContactCount() abstract;
			virtual Vector3D Normal() abstract;
		};
	}
}