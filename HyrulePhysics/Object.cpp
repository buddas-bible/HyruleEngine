#include "Object.h"

#include "HyruleMath.h"
#include "Transform.h"
#include "Collider.h"
#include "PHYSICALLYOBJECT_INFO.h"

namespace Hyrule
{
	namespace Physics
	{
		Object::Object(const std::wstring& _name/*, TRANSFORM_INFO* _info*/) noexcept
			: name(_name), /*transform(new Transform(_info)),*/
			rigidbody(), colliders()
		{

		}

		// Hyrule::Physics::Transform* Object::GetTransform()
		// {
		// 	return this->transform;
		// }

		// Matrix4x4 Object::GetLocalTM()
		// {
		// 	return transform->GetLocalTransform();
		// }

		Matrix3x3 Object::GetInertiaTensor(float _mess)
		{
			if (colliders.size())
			{
				// 아직은 하나만 할거임...
				// return colliders[0]->GetInertiaTensor(_mess);
			}

			return Matrix3x3();
		}

		Vector3D Object::GetCenterOfMess()
		{
			if (colliders.size())
			{
				// return colliders[0]->GetCenterOfMess();
			}

			return Vector3D();
		}


		void Object::CalculateCenterOfMassAndInertiaTensor(float _mass)
		{
		// 	// auto points = colliders[0].shape->
		// 
		// 	const float inv6 = 1 / 6;
		// 	const float inv24 = 1 / 24;
		// 	const float inv60 = 1 / 60;
		// 	const float inv120 = 1 / 120;
		// 
		// 	float intg[10] = {};
		// 	for (size_t triangle = 0; triangle < index.size(); triangle += 3)
		// 	{
		// 		// 삼각형 점을 가져옴
		// 		auto v0 = points[triangle];
		// 		auto v1 = points[triangle + 1];
		// 		auto v2 = points[triangle + 2];
		// 
		// 		// 삼각형의 변 벡터, 외적을 구함
		// 		auto a = v1 - v0;
		// 		auto b = v2 - v0;
		// 		auto aCrossb = a.Cross(b);
		// 
		// 		Vector3D f0, f1, f2;
		// 		Vector3D g0, g1, g2;
		// 
		// 		// 면 적분
		// 		Subexpressions(v0.x, v1.x, v2.x, f0.x, f1.x, f2.x, g0.x, g1.x, g2.x);
		// 		Subexpressions(v0.y, v1.y, v2.y, f0.y, f1.y, f2.y, g0.y, g1.y, g2.y);
		// 		Subexpressions(v0.z, v1.z, v2.z, f0.z, f1.z, f2.z, g0.z, g1.z, g2.z);
		// 
		// 		// 적분한 결과값을 저장함.
		// 		intg[0] += aCrossb.x * f0.x;
		// 
		// 		intg[1] += aCrossb.x * f1.x;
		// 		intg[2] += aCrossb.y * f1.y;
		// 		intg[3] += aCrossb.z * f1.z;
		// 
		// 		intg[4] += aCrossb.x * f2.x;
		// 		intg[5] += aCrossb.y * f2.y;
		// 		intg[6] += aCrossb.z * f2.z;
		// 
		// 		intg[7] += aCrossb.x * (v0.y * g0.x + v1.y * g1.x + v2.y * g2.x);
		// 		intg[8] += aCrossb.y * (v0.z * g0.y + v1.z * g1.y + v2.z * g2.y);
		// 		intg[9] += aCrossb.z * (v0.x * g0.z + v1.x * g1.z + v2.x * g2.z);
		// 	}
		// 
		// 	intg[0] *= inv6;
		// 
		// 	intg[1] *= inv24;
		// 	intg[2] *= inv24;
		// 	intg[3] *= inv24;
		// 
		// 	intg[4] *= inv60;
		// 	intg[5] *= inv60;
		// 	intg[6] *= inv60;
		// 
		// 	intg[7] *= inv120;
		// 	intg[8] *= inv120;
		// 	intg[9] *= inv120;
		// 
		// 	// 질량
		// 
		// 	// 질량을 따로 설정할 경우가 아니면 기본 값을 만들어냄.
		// 	float mass{};
		// 	//  if ()
		// 	//  {
		// 	mass = _mass;
		// 	//  }
		// 	//  else
		// 	 // {
		// 		// mass = intg[0];
		// 	//  }
		// 
		// 	// 질량 중심
		// 	this->centerOfMass = { intg[1], intg[2], intg[3] };
		// 	this->centerOfMass /= intg[0];
		// 
		// 	// 원점에 대한 관성
		// 	this->inertia.Ixx = intg[5] + intg[6];		// Ixx
		// 	this->inertia.Iyy = intg[4] + intg[6];		// Iyy
		// 	this->inertia.Izz = intg[4] + intg[5];		// Izz
		// 	this->inertia.Ixy = -intg[7];				// Ixy
		// 	this->inertia.Iyz = -intg[8];				// Iyz
		// 	this->inertia.Ixz = -intg[9];				// Ixz
		// 
		// 	// 질량 중심에 대한 관성
		// 	this->inertia.Ixx -= mass * (centerOfMass.y * centerOfMass.y + centerOfMass.z * centerOfMass.z);
		// 	this->inertia.Iyy -= mass * (centerOfMass.x * centerOfMass.x + centerOfMass.z * centerOfMass.z);
		// 	this->inertia.Izz -= mass * (centerOfMass.x * centerOfMass.x + centerOfMass.y * centerOfMass.y);
		// 
		// 	this->inertia.Ixy += mass * centerOfMass.x * centerOfMass.y;
		// 	this->inertia.Iyz += mass * centerOfMass.y * centerOfMass.z;
		// 	this->inertia.Ixz += mass * centerOfMass.y * centerOfMass.z;
		// 
		// 	// 텐서는 대칭 형태
		// 	this->inertia.Iyx = inertia.Ixy;
		// 	this->inertia.Izy = inertia.Iyz;
		// 	this->inertia.Izx = inertia.Ixz;
		}
	}
}