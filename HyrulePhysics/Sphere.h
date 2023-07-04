#pragma once
#include "Shape.h"

#include <vector>
#include "HyruleMath.h"

namespace Hyrule
{
	namespace Physics
	{
		class Sphere : public Shape
		{
		public:
			Sphere();
			~Sphere();

			virtual int GetShapeType() override;
			virtual Vector3D GetCenterOfMess() override;
			virtual Matrix3x3 GetInertiaTensor(float) override;
			virtual void CalculateCenterOfMessAndInertiaTensor(float) override;

		private:
			float length;

			Matrix3x3 inertia;
			Vector3D centerOfMess;

			// std::vector<Face*> face;
									// 삼각형을 이루는 점과 그의 노말을 저장하고 있으면
									// 관성 텐서를 계산하기 훨씬 수월할 것이다.
									// 대신 메모리를 오지게 먹게 될듯
									// 고민해볼 여지가 있다.



		private:


			void Subexpressions(
				float, float, float,
				float&, float&, float&,
				float&, float&, float&);
		};
	}
}

