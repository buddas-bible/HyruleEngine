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
			std::map<std::wstring, Object*> objectMap;
			std::vector<Collider*> colliders;					// Ȱ��ȭ�� �ݶ��̴�
			std::vector<RigidBody*> rigidBodies;				// �ùķ��̼� ������ ��ü

		private:
			std::queue<Collider*> ToDestroyCollider;
			std::queue<RigidBody*> ToDestroyRigidBody;

			Octree_v2<Collider*> octree;

		public:
			ICollider* CreateCollider(const std::wstring&, COLLIDER_INFO*);	// ������Ʈ�� �ݶ��̴��� �߰���.
			IRigidBody* CreateRigidBody(const std::wstring&);					// ������Ʈ�� ��ü�� �߰���

			void RemoveCollider(const std::wstring&, Collider*&);			// �ݶ��̴� �����͸� �޾Ƽ� ����
			void RemoveCollider(const std::wstring&, ICollider*&);			// �ݶ��̴� �����͸� �޾Ƽ� ����
			void RemoveCollider(const std::wstring&, int);					// �ݶ��̴� �ε����� �޾Ƽ� ����
			void RemoveRigidBody(const std::wstring&);

			std::vector<Collider*>& GetColliders() noexcept;
			std::vector<RigidBody*>& GetRigidbodies() noexcept;

			// std::vector<std::list<Collider*>>& GetNodeContainer() noexcept;
			// void NodeContainerClear() noexcept;
			std::vector<Collider*> QctreeQuery(Collider*) noexcept;
			void OctreeClear() noexcept;
			void OctreeResearch(Collider*);

		public:
			void AddRemoveQueue(Collider*);
			void AddRemoveQueue(RigidBody*);
			void RemoveQueue();

		private:
			Collider* AddCollider(Object*, COLLIDER_INFO*);						// �ݶ��̴��� ����
			RigidBody* AddRigidBody(Object*);									// ��ü�� ����

			Object* GetObject(const std::wstring&);
			Object* CreateObject(const std::wstring&);
			void RemoveObject(const std::wstring&);
		};
	}
}

