#pragma once
#include "Shape.h"

#include <vector>
#include "HyruleMath.h"

namespace Hyrule
{
	namespace Physics
	{
		class Sphere : public Shape
		{
		public:
			Sphere() noexcept = default;
			virtual ~Sphere() noexcept = default;

		private:
			float length;

		public:
			virtual int GetShapeType() override;
			virtual float GetLength() override;
		};
	}
}

