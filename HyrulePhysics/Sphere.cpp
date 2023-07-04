#include "Sphere.h"

#include "HyruleMath.h"

namespace Hyrule
{
	namespace Physics
	{

		Sphere::Sphere()
		{
			type = ShapeType::SPHERE;
		}

		Sphere::~Sphere()
		{

		}

		int Sphere::GetShapeType()
		{
			return (int)this->type;
		}

		Hyrule::Vector3D Sphere::GetCenterOfMess()
		{

		}

		Hyrule::Matrix3x3 Sphere::GetInertiaTensor(float _mess)
		{
			return Matrix3x3
			{

			};
		}

		void Sphere::CalculateCenterOfMessAndInertiaTensor(float _mess)
		{
		}

		void Sphere::Subexpressions(float, float, float, float&, float&, float&, float&, float&, float&)
		{

		}

	}

}
