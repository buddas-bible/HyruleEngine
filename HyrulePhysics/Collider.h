#pragma once
#include "ICollider.h"

#include <vector>
#include <string>
#include "HyruleMath.h"

namespace Hyrule
{
	namespace Physics
	{
		class Object;
		class Shape;

		class Collider : public ICollider
		{
		public:
			Collider() noexcept = default;
			virtual ~Collider() noexcept = default;

		protected:
			Object* object;
			Shape* shape;

			Vector3D center;
			Vector3D size;
			bool isTrigger;
//			bool collided;

			Matrix3x3 inertia;
			Vector3D centerOfMass;

		public:
			virtual void SetWorldTransform(const Matrix4x4& _mat);

		public:
			virtual void SetTrigger(bool);
			virtual void SetSize(const Vector3D&);
			virtual void SetCenter(const Vector3D&);

		public:
			virtual std::wstring GetObjectName();
			virtual bool IsColliding();
			
		public:
			virtual Vector3D FindFarthestPoint(const Vector3D&) abstract;
		};
	}
}


/*
고민이 되네
버텍스


*/