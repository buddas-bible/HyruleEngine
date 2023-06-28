#pragma once
#include "ICollider.h"

#include <vector>
#include "HyruleMath.h"

namespace Hyrule
{
	namespace Physics
	{
		class Transform;
		class RigidBody;

		class Collider : public ICollider
		{
		public:
			Collider() noexcept = default;
			~Collider() noexcept = default;

		private:
			RigidBody* rigidbody;
			Transform* transform;

			// 메쉬 정보를 어떻게 할까...
			std::vector<Vector3D> vertex;
			std::vector<int> index;

			void GetWorldTransform();
		};
	}
}


/*
고민이 되네
버텍스


*/