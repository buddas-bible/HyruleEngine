#pragma once
#include "Shape.h"

#include <vector>
#include "HyruleMath.h"

namespace Hyrule
{
	namespace Physics
	{
		class PlaneShape : public Shape
		{
		public:
			PlaneShape() noexcept;
			~PlaneShape() noexcept = default;

		private:
			float length;						// AABB 크기를 잡기 위해서..

			std::vector<Vector3D> points{
				{ -5.f, 0.f, -5.f }, { -5.f, 0.f, 5.f },
				{ 5.f, 0.f, 5.f }, { 5.f, 0.f, -5.f },
			};

			std::vector<size_t> index{
				0, 1, 2,
				0, 2, 3,
			};

		public:
			int GetShapeType();
			float GetLength();
		};
	}
}

