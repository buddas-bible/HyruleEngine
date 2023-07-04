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
			~BoxShape();

			virtual int GetShapeType() override;
			virtual Vector3D GetCenterOfMess() override;
			virtual Matrix3x3 GetInertiaTensor(float) override;
			virtual void CalculateCenterOfMessAndInertiaTensor(float) override;

		private:
			Matrix3x3 inertia;
			Vector3D centerOfMess;

			// std::vector<Face*> face;
									// �ﰢ���� �̷�� ���� ���� �븻�� �����ϰ� ������
									// ���� �ټ��� ����ϱ� �ξ� ������ ���̴�.
									// ��� �޸𸮸� ������ �԰� �ɵ�
									// ����غ� ������ �ִ�.



		private:


			void Subexpressions(
				float, float, float,
				float&, float&, float&,
				float&, float&, float&);
		};
	}
}

