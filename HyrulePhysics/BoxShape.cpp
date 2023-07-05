#include "BoxShape.h"


namespace Hyrule
{
	namespace Physics
	{
		BoxShape::BoxShape()
		{
			this->type = ShapeType::BOX;
		}

		int BoxShape::GetShapeType()
		{
			return (int)this->type;
		}

		Vector3D BoxShape::GetCenterOfMess()
		{
			return centerOfMass;
		}

		Matrix3x3 BoxShape::GetInertiaTensor(float _mess)
		{
			return inertia;
		}

		void BoxShape::CalculateCenterOfMessAndInertiaTensor(float _mess)
		{
			// ���� * �� ���� ���� / 6 * ���� ���
		}
	}
}
