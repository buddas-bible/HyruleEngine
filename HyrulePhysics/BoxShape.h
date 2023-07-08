#pragma once
#include "Shape.h"

#include <vector>
#include "HyruleMath.h"

namespace Hyrule
{
	namespace Physics
	{
		class BoxShape : public Shape
		{
		public:
			BoxShape() noexcept;
			~BoxShape() noexcept = default;

		private:
			float length;
			std::vector<Vector3D> points{
				{ -0.5f, -0.5f, -0.5f }, { -0.5f, -0.5f, 0.5f },
				{ -0.5f, -0.5f, -0.5f }, { -0.5f, -0.5f, -0.5f },
				{ -0.5f, -0.5f, -0.5f }, { -0.5f, -0.5f, -0.5f },
				{ -0.5f, -0.5f, -0.5f }, { -0.5f, -0.5f, -0.5f }
			};
			std::vector<size_t> index{
				{}, {}, {}, {}, {}
			};

		public:
			int GetShapeType();
			float GetLength();
		};
	}
}

