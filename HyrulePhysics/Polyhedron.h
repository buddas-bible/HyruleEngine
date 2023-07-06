#pragma once
#include "Shape.h"

#include <vector>
#include "HyruleMath.h"

namespace Hyrule 
{
	namespace Physics 
	{
		class Face;

		class Polyhedron : public Shape
		{
		public:
			Polyhedron() noexcept = default;
			virtual ~Polyhedron() noexcept = default;

		private:
			float length;						// AABB 크기를 잡기 위해서..

			std::vector<Vector3D> points;
			std::vector<size_t> index;

		public:
			virtual int GetShapeType() override;
			virtual float GetLength() override;
		};
	}
}

