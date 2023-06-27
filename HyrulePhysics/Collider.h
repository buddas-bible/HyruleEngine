#pragma once
#include "ICollider.h"

#include <vector>
#include "HyruleMath.h"

namespace Hyrule
{
	class Transform;

	class Collider
	{
	public:
		Collider() noexcept = default;
		~Collider() noexcept = default;

	private:
		Transform* transform;

		// 메쉬 정보를 어떻게 할까...
		std::vector<Vector3D> vertex;
		std::vector<int> index;

		void GetWorldTransform();
	};

}


/*
고민이 되네
버텍스


*/