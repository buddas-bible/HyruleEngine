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

		class Collider : public ICollider
		{
		public:
			Collider() noexcept = delete;
			Collider(Object*) noexcept;
			virtual ~Collider() noexcept = default;

		protected:
			Object* object;
			Matrix4x4 preTM;

			// �ݶ��̴� �߽ɰ� ũ�⸦ �ٲ� ���� ���ٰ� ��������....
			Vector3D center;
			Vector3D size;
			bool isTrigger;

			Matrix3x3 inertia;
			Vector3D centerOfMass;
			bool activate;

			bool collied;

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
			virtual bool isCollision() noexcept final;
			virtual void OnEnable() noexcept final;
			virtual void OnDisable() noexcept final;
			virtual void OnDestroy() noexcept final;
			virtual std::vector<ICollision*> GetCollisionInfo() noexcept final;

			void AddCollisionInfo(Collider*, Manifold&);

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
����� �ǳ�
���ؽ�


*/