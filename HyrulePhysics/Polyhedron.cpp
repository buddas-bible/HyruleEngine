#include "Polyhedron.h"

#include "HyruleMath.h"

namespace Hyrule
{
	namespace Physics
	{

		Polyhedron::Polyhedron() : Shape(), points(), index(), length()
		{
			type = ShapeType::POLYHEDRON;
		}

		int Polyhedron::GetShapeType()
		{
			return (int)this->type;
		}

		float Polyhedron::GetLength()
		{
			return this->length;
		}
	}
}
