#pragma once
#include "ICollider.h"

#include <vector>
#include "HyruleMath.h"

namespace Hyrule
{
	namespace Physics
	{
		class Object;

		class Collider : public ICollider
		{
		public:
			Collider() noexcept = default;
			~Collider() noexcept = default;

		private:
			Object* object;

			// 메쉬 정보를 어떻게 할까...
			std::vector<Hyrule::Vector3D> vertex;
			std::vector<int> index;
		};
	}
}


/*
고민이 되네
버텍스


*/