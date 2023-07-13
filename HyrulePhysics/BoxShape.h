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
			float length;						// AABB 크기를 잡기 위해서..
												// 일단 원점에서 정점 하나까지의 길이로 해놓고
												//

			std::vector<Vector3D> points{
				{ -0.5f, -0.5f, -0.5f }, { -0.5f, -0.5f, 0.5f },
				{ 0.5f, -0.5f, 0.5f }, { 0.5f, -0.5f, -0.5f },

				{ -0.5f, 0.5f, -0.5f }, { -0.5f, 0.5f, 0.5f },
				{-0.5f, 0.5f, -0.5f }, { 0.5f, 0.5f, 0.5f }
			};

			std::vector<size_t> index{
					1, 0, 3,		// 하
					1, 3, 2,

					0, 4, 7,		// 전
					0, 7, 3,

					4, 5, 6,		// 상
					4, 6, 7,

					3, 7, 6,		// 우
					3, 6, 2,

					2, 6, 5,		// 후
					2, 5, 1,

					1, 5, 4,		// 좌
					1, 4, 0,
			};

		public:
			int GetShapeType();
			float GetLength();
		};
	}
}

