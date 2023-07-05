#include "Sphere.h"

#include "HyruleMath.h"

namespace Hyrule
{
	namespace Physics
	{
		Sphere::Sphere() : Shape(), length()
		{
			type = ShapeType::SPHERE;
		}

		int Sphere::GetShapeType()
		{
			return (int)this->type;
		}

		float Sphere::GetLength()
		{
			return this->length;
		}
	}
}
