#pragma once
#include "Manager.h"

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <queue>
// #include "Octree.h"
#include "Octree_v2.h"

namespace Hyrule
{
	struct Matrix4x4;

	namespace Physics
	{
		class Object;

		class ICollider;
		class Collider;

		class IRigidBody;
		class RigidBody;

		class SphereCollider;
		class BoxCollider;
		class PlaneCollider;
		class SphereCollider;


		struct COLLIDER_INFO;

		class ObjectManager : public Manager<ObjectManager>
		{
		public:
			ObjectManager() noexcept;
			~ObjectManager() noexcept = default;
			ObjectManager(const ObjectManager&) = delete;
			void operator=(const ObjectManager&) = delete;

		private:
			std::map<std::string, Object*> objectMap;
			std::vector<Collider*> colliders;					// Ȱ��ȭ�� �ݶ��̴�
			std::vector<RigidBody*> rigidBodies;				// �ùķ��̼� ������ ��ü

		private:
			std::queue<Collider*> ToDestroyCollider;
			std::queue<RigidBody*> ToDestroyRigidBody;

			Octree_v2<Collider*> octree;

		public:
			ICollider* CreateCollider(const std::string&, COLLIDER_INFO*);	// ������Ʈ�� �ݶ��̴��� �߰���.
			IRigidBody* CreateRigidBody(const std::string&);					// ������Ʈ�� ��ü�� �߰���

			void RemoveCollider(const std::string&, Collider*&);			// �ݶ��̴� �����͸� �޾Ƽ� ����
			void RemoveCollider(const std::string&, ICollider*&);			// �ݶ��̴� �����͸� �޾Ƽ� ����
			void RemoveCollider(const std::string&, int);					// �ݶ��̴� �ε����� �޾Ƽ� ����
			void RemoveRigidBody(const std::string&);

			std::vector<Collider*>& GetColliders() noexcept;
			std::vector<RigidBody*>& GetRigidbodies() noexcept;

			std::vector<Collider*> QctreeQuery(Collider*) noexcept;
			std::vector<Collider*> QctreeQuery(const Ray&) noexcept;
			std::vector<Collider*> QctreeQuery(const Segment&) noexcept;
			void OctreeClear() noexcept;
			void OctreeResearch(Collider*);

		public:
			void AddRemoveQueue(Collider*);
			void AddRemoveQueue(RigidBody*);
			void RemoveQueue();

		private:
			Collider* AddCollider(Object*, COLLIDER_INFO*);						// �ݶ��̴��� ����
			RigidBody* AddRigidBody(Object*);									// ��ü�� ����

			Object* GetObject(const std::string&);
			Object* CreateObject(const std::string&);
			void RemoveObject(const std::string&);
		};
	}
}

