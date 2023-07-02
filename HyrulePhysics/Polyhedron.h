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


			Face* face;				// 삼각형을 이루는 점과 그의 노말을 저장하고 있으면
									// 관성 텐서를 계산하기 훨씬 수월할 것이다.
									// 대신 메모리를 오지게 먹게 될듯
									// 고민해볼 여지가 있다.
		};
	}
}

