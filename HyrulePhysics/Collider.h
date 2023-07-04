#pragma once
#include "ICollider.h"

#include <vector>
#include "HyruleMath.h"

namespace Hyrule
{
	namespace Physics
	{
		class Object;
		class Shape;

		class Collider : public ICollider
		{
		public:
			Collider() noexcept = default;
			~Collider() noexcept = default;

		private:
			Object* object;
			Shape* shape;

		public:
			Matrix3x3 GetInertiaTensor(float) noexcept;
			Vector3D GetCenterOfMess() noexcept;
		};
	}
}


/*
고민이 되네
버텍스


*/