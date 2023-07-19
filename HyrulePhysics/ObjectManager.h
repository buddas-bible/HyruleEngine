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
			std::vector<Collider*> activatedCollider;		// Ȱ��ȭ�� �ݶ��̴�
			std::queue<RigidBody*> collision;				// �ùķ��̼� ������ ��ü

		public:
			ICollider* AddCollider(const std::wstring&, COLLIDER_INFO*);	// ������Ʈ�� �ݶ��̴��� �߰���.
			IRigidBody* AddRigidBody(const std::wstring&);					// ������Ʈ�� ��ü�� �߰���

			void RemoveCollider(const std::wstring&, ICollider*&);			// �ݶ��̴� �����͸� �޾Ƽ� ����
			void RemoveCollider(const std::wstring&, int);					// �ݶ��̴� �ε����� �޾Ƽ� ����
			void RemoveRigidBody(const std::wstring&);

		private:
			Collider* CreateCollider(Object*, COLLIDER_INFO*);						// �ݶ��̴��� ����
			RigidBody* CreateRigidBody(Object*);									// ��ü�� ����

			Object* GetObject(const std::wstring&);
			Object* CreateObject(const std::wstring&);
			void RemoveObject(const std::wstring&);
		};
	}
}

