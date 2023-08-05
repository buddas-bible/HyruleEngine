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
			std::vector<Collider*> colliders;					// 활성화된 콜라이더
			std::vector<RigidBody*> rigidBodies;				// 시뮬레이션 예정인 강체

		private:
			std::queue<Collider*> ToDestroyCollider;
			std::queue<RigidBody*> ToDestroyRigidBody;

			Octree_v2<Collider*> octree;

		public:
			ICollider* CreateCollider(const std::wstring&, COLLIDER_INFO*);	// 오브젝트에 콜라이더를 추가함.
			IRigidBody* CreateRigidBody(const std::wstring&);					// 오브젝트에 강체를 추가함

			void RemoveCollider(const std::wstring&, Collider*&);			// 콜라이더 포인터를 받아서 삭제
			void RemoveCollider(const std::wstring&, ICollider*&);			// 콜라이더 포인터를 받아서 삭제
			void RemoveCollider(const std::wstring&, int);					// 콜라이더 인덱스를 받아서 삭제
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
			Collider* AddCollider(Object*, COLLIDER_INFO*);						// 콜라이더를 만듬
			RigidBody* AddRigidBody(Object*);									// 강체를 만듬

			Object* GetObject(const std::wstring&);
			Object* CreateObject(const std::wstring&);
			void RemoveObject(const std::wstring&);
		};
	}
}

