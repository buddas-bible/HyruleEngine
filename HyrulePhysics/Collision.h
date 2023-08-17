#pragma once
#include <string>
#include "ICollision.h"
#include "HyruleMath.h"

namespace Hyrule
{
	struct Vector3D;

	namespace Physics
	{
		class Collision : public ICollision
		{
		public:
			Collision() noexcept = default;
			virtual ~Collision() noexcept = default;

		public:
			ICollider* collider;
			void* userData;
			std::wstring instanceID;
			std::wstring tag;
			Vector3D impulse;
			std::vector<Vector3D> contactPoints;
			Vector3D normal;

		public:
			virtual ICollider* Collider() noexcept override;
			virtual void* UserData() noexcept override;
			virtual std::wstring InstanceID() noexcept override;
			virtual std::wstring Tag() noexcept override;
			virtual Vector3D Impulse() noexcept override;
			virtual std::vector<Vector3D> Contacts() noexcept override;
			virtual Vector3D Contact(size_t) noexcept override;
			virtual size_t ContactCount() noexcept override;
			virtual Vector3D Normal() noexcept override;
		};
	}
}