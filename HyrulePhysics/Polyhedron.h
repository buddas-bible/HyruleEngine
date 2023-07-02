#pragma once
#include "Shape.h"


namespace Hyrule 
{
	namespace Physics 
	{
		class Face;

		class Polyhedron : public Shape
		{
		public:
			virtual int GetShapeType() abstract;
			virtual Matrix3x3 GetInertiaTensor() abstract;


			Face* face;				// �ﰢ���� �̷�� ���� ���� �븻�� �����ϰ� ������
									// ���� �ټ��� ����ϱ� �ξ� ������ ���̴�.
									// ��� �޸𸮸� ������ �԰� �ɵ�
									// ����غ� ������ �ִ�.
		};
	}
}

