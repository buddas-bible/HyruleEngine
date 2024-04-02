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
			Collision() = default;
			virtual ~Collision() = default;

		public:
			ICollider* collider;
			void* userData;
			std::wstring instanceID;
			std::wstring tag;
			Vector3D impulse;
			std::vector<Vector3D> contactPoints;
			Vector3D normal;

		public:
			virtual ICollider* Collider() override;
			virtual void* UserData() override;
			virtual std::wstring InstanceID() override;
			virtual std::wstring Tag() override;
			virtual Vector3D Impulse() override;
			virtual std::vector<Vector3D> Contacts() override;
			virtual Vector3D Contact(size_t) override;
			virtual size_t ContactCount() override;
			virtual Vector3D Normal() override;
		};
	}
}