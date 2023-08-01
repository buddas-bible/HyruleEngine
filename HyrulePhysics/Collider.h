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
		enum class ColliderType : size_t
		{
			BOX = 10,
			SPHERE = 20,
			PLANE = 30,
			CONVEX = 40,
		};

		class Object;
		class Shape;
		struct Vertex;
		struct Edge;
		struct Face;
		class ICollision;
		class Manifold;
		class RigidBody;

		class Collider : public ICollider
		{
		public:
			Collider() noexcept = delete;
			Collider(Object*) noexcept;
			virtual ~Collider() noexcept = default;

		protected:
			Object* object;

			Vector3D prePos;
			Quaternion preRot;
			Vector3D preScl;

			// 콜라이더 중심과 크기를 바꿀 일이 없다고 생각하자....
			Vector3D center;
			Vector3D size;
			bool isTrigger;

			Matrix3x3 inertia;
			Vector3D centerOfMass;
			bool activate;

			bool collied;

			ColliderType type;

			std::vector<ICollision*> collisionInfo;

		public:
			Vector3D GetPosition();
			Quaternion GetRotation();
			float GetLength();

			Object* GetObject();
			RigidBody* GetRigidBody();
			void CollisionInfoClear();
			bool hasRigidBody();
			bool isActive();
			void SetCollied(bool);

			virtual Vector3D GetCenterOfMass() noexcept final;
			virtual Matrix3x3 GetInertiaTensor(float) noexcept abstract;
			virtual void Subexpressions(float, float, float, float&, float&, float&, float&, float&, float&) final;

		public:
			virtual ColliderType GetType() final;
			virtual bool isCollision() noexcept final;
			virtual void OnEnable() noexcept final;
			virtual void OnDisable() noexcept final;
			virtual void OnDestroy() noexcept final;
			virtual std::vector<ICollision*> GetCollisionInfo() noexcept final;

			void AddCollisionInfo(Collider*, Manifold&);

		public:
			virtual void SetTransform(const Vector3D&, const Quaternion&, const Vector3D&) noexcept final;

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