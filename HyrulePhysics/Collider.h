#pragma once
#include "ICollider.h"

#include <vector>
#include <string>
#include "HyruleMath.h"
#include "ICollision.h"

namespace Hyrule
{
	namespace Physics
	{
		class Object;
		class Shape;
		struct Vertex;
		struct Edge;
		struct Face;
		class ICollision;
		class Manifold;
		class RigidBody;
		class AABB;

		class Collider : public ICollider
		{
		public:
			Collider() noexcept = delete;
			Collider(Object*) noexcept;
			virtual ~Collider() noexcept = default;

		protected:
			Object* object;

			std::wstring tag;
			std::wstring layer;

			void* userData;

			Vector3D prePos;
			Quaternion preRot;
			Vector3D preScl;

			// 콜라이더 중심과 크기를 바꿀 일이 없다고 생각하자....
			Vector3D center;
			Vector3D size;
			bool isTrigger;
			bool activate;
			std::vector<ICollision*> collisionInfo;

			Matrix3x3 inertia;
			Vector3D centerOfMass;

			bool collied;

		public:
			Object* GetObject();
			RigidBody* GetRigidBody();
			void CollisionInfoClear();
			bool hasRigidBody();
			bool isActive();
			void SetCollied(bool);

			virtual Vector3D GetCenterOfMass() noexcept final;
			virtual Matrix3x3 GetInertiaTensor(float) noexcept abstract;
			// virtual void Subexpressions(float, float, float, float&, float&, float&, float&, float&, float&) final;
			virtual AABB GetAABB() abstract;

		public:
			virtual Vector3D GetPosition() abstract;
			virtual Quaternion GetRotation() abstract;
			virtual Vector3D GetScale() abstract;
			virtual float GetLength() abstract;

		public:
			void AddCollisionInfo(Collider*, Manifold&);

			virtual bool isCollision() noexcept final;
			virtual void OnEnable() noexcept final;
			virtual void OnDisable() noexcept final;
			virtual void OnDestroy() noexcept final;
			virtual std::vector<ICollision*> GetCollisionInfo() noexcept final;

		public:
			virtual void SetTransform(
				const Vector3D&, const Vector3D&,
				const Vector3D&, const Quaternion&, const Vector3D&) noexcept final;

		public:
			virtual Matrix4x4 GetLocalTM() abstract;
			virtual Matrix4x4 GetWorldTM() abstract;

			virtual Vector3D GetSize() abstract;
			virtual Vector3D GetCenter() abstract;
			
			virtual bool GetTrigger() final;
			virtual void SetTrigger(bool) final;

			//
		public:
			virtual std::wstring GetObjectName() final;
			
			// 충돌 관련
		public:
			virtual size_t GetType() noexcept abstract;
			virtual Vector3D FindFarthestPoint(const Vector3D&) abstract;
			virtual Face FindSupportFace(const Vector3D&) abstract;
		};
	}
}


/*
고민이 되네
버텍스


*/