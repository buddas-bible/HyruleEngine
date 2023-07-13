#include "ConvexShape.h"

#include "HyruleMath.h"

namespace Hyrule
{
	namespace Physics
	{
		ConvexShape::ConvexShape() noexcept : Shape(), points(), index(), length()
		{
			type = ShapeType::POLYHEDRON;
		}

		int ConvexShape::GetShapeType()
		{
			return (int)this->type;
		}

		float ConvexShape::GetLength()
		{
			return this->length;
		}
	}
}
