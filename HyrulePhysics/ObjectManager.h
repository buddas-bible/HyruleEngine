#pragma once
#include "Manager.h"

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <queue>

namespace Hyrule
{
	struct Matrix4x4;

	namespace Physics
	{
		class Object;

		class ICollider;
		class Collider;
		class SphereCollider;
		class BoxCollider;
		class PlaneCollider;
		class SphereCollider;

		class IRigidBody;
		class RigidBody;

		struct COLLIDER_INFO;

		class ObjectManager : public Manager<ObjectManager>
		{
		public:
			ObjectManager() noexcept = default;
			~ObjectManager() noexcept = default;
			ObjectManager(const ObjectManager&) = delete;
			void operator=(const ObjectManager&) = delete;

		private:
			std::map<std::wstring, Object*> objectMap;
			std::vector<Collider*> colliders;		// Ȱ��ȭ�� �ݶ��̴�
			std::vector<RigidBody*> rigidBodies;				// �ùķ��̼� ������ ��ü

		public:
			ICollider* CreateCollider(const std::wstring&, COLLIDER_INFO*);	// ������Ʈ�� �ݶ��̴��� �߰���.
			IRigidBody* CreateRigidBody(const std::wstring&);					// ������Ʈ�� ��ü�� �߰���

			void RemoveCollider(const std::wstring&, Collider*&);			// �ݶ��̴� �����͸� �޾Ƽ� ����
			void RemoveCollider(const std::wstring&, ICollider*&);			// �ݶ��̴� �����͸� �޾Ƽ� ����
			void RemoveCollider(const std::wstring&, int);					// �ݶ��̴� �ε����� �޾Ƽ� ����
			void RemoveRigidBody(const std::wstring&);

			std::vector<Collider*>& GetColliders() noexcept;
			std::vector<RigidBody*>& GetRigidbodies() noexcept;

		private:
			Collider* AddCollider(Object*, COLLIDER_INFO*);						// �ݶ��̴��� ����
			RigidBody* AddRigidBody(Object*);									// ��ü�� ����

			Object* GetObject(const std::wstring&);
			Object* CreateObject(const std::wstring&);
			void RemoveObject(const std::wstring&);
		};
	}
}

