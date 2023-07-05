#include "BoxShape.h"


namespace Hyrule
{
	namespace Physics
	{
		BoxShape::BoxShape() : Shape(), length()
		{
			this->type = ShapeType::BOX;
		}

		int BoxShape::GetShapeType()
		{
			return (int)this->type;
		}

		float BoxShape::GetLength()
		{
			return this->length;
		}
	}
}
