#include "BoxShape.h"


namespace Hyrule
{
	namespace Physics
	{
		int BoxShape::GetShapeType()
		{
			return (int)this->type;
		}

		Vector3D BoxShape::GetCenterOfMess()
		{
			return centerOfMess;
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
