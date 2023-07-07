#include "SphereShape.h"

#include "HyruleMath.h"

namespace Hyrule
{
	namespace Physics
	{
		SphereShape::SphereShape() : Shape(), length()
		{
			type = ShapeType::SPHERE;
		}

		int SphereShape::GetShapeType()
		{
			return (int)this->type;
		}

		float SphereShape::GetLength()
		{
			return this->length;
		}
	}
}
