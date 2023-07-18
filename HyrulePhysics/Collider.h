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
		struct Vertex;
		struct Edge;
		struct Face;

		class Collider : public ICollider
		{
		public:
			Collider() noexcept = default;
			virtual ~Collider() noexcept = default;

		protected:
			Object* object;

			Vector3D center{ 0.f, 0.f, 0.f };
			Vector3D size{ 0.5f, 0.5f, 0.5f };
			bool isTrigger{ false };

			Matrix3x3 inertia;
			Vector3D centerOfMass;

		public:
			virtual void OnDisable() noexcept override {};
			virtual void OnEnable() noexcept override {};

		public:
			virtual void SetWorldTransform(const Matrix4x4& _mat);

		public:
			virtual void SetTrigger(bool);
			virtual void SetSize(const Vector3D&);
			virtual void SetCenter(const Vector3D&);

		public:
			virtual std::wstring GetObjectName();
			
		public:
			virtual Vector3D FindFarthestPoint(const Vector3D&) abstract;
			virtual Face FindSupportFace(const Vector3D&) abstract;
		};
	}
}


/*
고민이 되네
버텍스


*/