#pragma once
#include "ICollider.h"

#include <vector>
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

			Matrix3x3 inertia;
			Vector3D centerOfMass;

		public:
			virtual void SetWorldTransformMatrix(const Matrix4x4&) override;
			
			virtual void SetTrigger(bool) override;
			virtual void SetSize(const Vector3D&) override;
			virtual void SetCenter(const Vector3D&) override;

			virtual bool IsColliding() override;
		};
	}
}


/*
고민이 되네
버텍스


*/