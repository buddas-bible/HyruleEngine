#pragma once
#include "Collider.h"
#include "Shape.h"

namespace Hyrule
{
	namespace Physics
	{
		class AABB;
		struct COLLIDER_INFO;

		class SphereCollider : public Collider
		{
		public:
			SphereCollider() = delete;
			SphereCollider(Object*, COLLIDER_INFO*);
			virtual ~SphereCollider() = default;

		public:
			virtual Vector3D GetPosition() override;
			virtual Quaternion GetRotation() override;
			virtual Vector3D GetScale() override;
			virtual float GetLength() override;

			virtual Matrix4x4 GetLocalTM() override;
			virtual Matrix4x4 GetWorldTM() override;
			virtual Vector3D GetSize() override;
			virtual Vector3D GetCenter() override;

			virtual AABB GetAABB() override;
			virtual Vector3D FindFarthestPoint(const Vector3D&) override;
			virtual Face FindSupportFace(const Vector3D&) override;
			virtual Matrix3x3 GetInertiaTensor(float) override;
			virtual size_t GetType() override;
		};
	}
}