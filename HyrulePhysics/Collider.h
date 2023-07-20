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
			Collider() noexcept = delete;
			Collider(Object*) noexcept;
			virtual ~Collider() noexcept = default;

		protected:
			Object* object;

			Vector3D center;
			Vector3D size;
			bool isTrigger;

			Matrix3x3 inertia;
			Vector3D centerOfMass;
			bool activate;

		public:
			bool isActive();
			virtual void OnEnable() noexcept final;
			virtual void OnDisable() noexcept final;
			virtual void OnDestroy() noexcept final;

		public:
			virtual void SetWorldTransform(const Matrix4x4& _mat) final;

		public:
			virtual void SetTrigger(bool) final;
			virtual void SetSize(const Vector3D&) final;
			virtual void SetCenter(const Vector3D&) final;

		public:
			virtual std::wstring GetObjectName() final;
			
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