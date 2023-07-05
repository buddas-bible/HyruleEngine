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
			BoxShape();
			virtual ~BoxShape() noexcept = default;

		private:
			float length;

		public:
			virtual int GetShapeType() override;
			virtual float GetLength() override;
		};
	}
}

