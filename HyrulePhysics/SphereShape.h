#pragma once
#include "Shape.h"

#include <vector>
#include "HyruleMath.h"

namespace Hyrule
{
	namespace Physics
	{
		class SphereShape : public Shape
		{
		public:
			SphereShape() noexcept;
			~SphereShape() noexcept = default;

		private:
			float length;

		public:
			int GetShapeType();
			float GetLength();
		};
	}
}

