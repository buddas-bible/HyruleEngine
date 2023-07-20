#include "HyrulePhysics.h"

#include "Collider.h"
#include "RigidBody.h"
#include "Object.h"
#include "Octree.h"

#include "PHYSICALLYOBJECT_INFO.h"
#include "ObjectManager.h"

namespace Hyrule
{
	namespace Physics
	{
		__declspec(dllexport) IPhysics* CreatePhysics()
		{
			return new Hyrule::Physics::HyrulePhysics;
		}

		/// <summary>
		/// ���� ������Ʈ�� �̸�
		/// Ʈ������ ����
		/// �ݶ��̴� ������ �޾Ƽ� �ݶ��̴��� �����.
		/// </summary>
		ICollider* HyrulePhysics::CreateCollider(const std::wstring& _name, COLLIDER_INFO* _colinfo)
		{
			return ObjectManager::GetInstance().CreateCollider(_name, _colinfo);
		}

		/// <summary>
		/// ���� ������Ʈ �̸�
		/// Ʈ������ ������ �޾Ƽ� ��ü�� �����.
		/// </summary>
		IRigidBody* HyrulePhysics::CreateRigidBody(const std::wstring& _name)
		{
			return ObjectManager::GetInstance().CreateRigidBody(_name);
		}

		std::vector<Manifold*> HyrulePhysics::GetCollisionData()
		{
			return std::vector<Manifold*>();
		}

		long HyrulePhysics::Initialize()
		{
			gravity = Hyrule::Vector3D(0.f, -9.81f, 0.f);

			return (long)0L;
		}

		/// <summary>
		/// �ݸ��� üũ
		/// </summary>
		void HyrulePhysics::CollisionDetection()
		{
			// CollisionSystem::GetInstance()
			// 
			// �� �Լ��� ȣ��Ǳ� ���� �ݶ��̴����� ����TM�� ������Ʈ ���� ���̴�.
			// ���� TM�� ���� TM�� ���غ��� ������ �Ǿ�����
			// Ʈ�� �ȿ� �ִ� ������Ʈ�� ������Ű�� �ٽ� ����.
			// TM�� ������ �� ����.

			/// �켱 ������ ��Ʈ���� ������� �������� ����
			/// �迭�� ���� Ž������ �Ǵ���.

			/// ��Ʈ���� ��带 ������.
			/// ��� �ȿ� �����Ͱ� 0~1���� �н�.
			/// 2�� ~ 4�������� �׳� ��ȸ�ϸ鼭 �浹 ���� �Ϸ��� ��.
			/// 5�� �Ѿ�� �ڽ��� Ž��.

			Octree<Object, 4> octree;
			// CollisionSystem::GJKCollisionDetection();
		}

		/// <summary>
		/// ��ü �ùķ��̼�
		/// </summary>
		void HyrulePhysics::CollisionResponse(const float _deltaTime)
		{
			/*
			���� ������ ������ ��ü�� Ʈ������ ������ ��� ������ ��� ������Ʈ�� �ؾ��ұ�?
			���� ������Ʈ�� �ޱ� ��, �켱 ���� Ʈ�������� ���� �޴´�.
			��ü �ùķ��̼��� ���ؼ� ���� Ʈ������ ������ ������ �ȴ�.
			�θ��� ���� Ʈ������ ������ ������� ���� Ʈ������ ������ ������Ʈ �Ѵ�.
			*/
		}

		/// <summary>
		/// ���� �ȿ� �ִ� ������Ʈ�� ���� ������
		/// </summary>
		// void HyrulePhysics::WorldReset()
		// {
			/*
			���� �������� �� ������ ������ �Ѵٰ� ���� ��.
			�� ��ȯ ��, ���� ���� �Լ��� ȣ���ϴ� ������ ���� ������ �ִ� ������Ʈ�� �����Ѵ�.
			
			���� ������ �� ������ ������Ʈ�� �����ϴ� ���� ��� �غ�������
			�̷��� ���� ������ ���������� �̿��� �� ���� �� �; �̷��� �ϱ�� �ߴ�.

			���� ���� ������ �� ������ ����ٰ� ���� ��,
			�� �������̽��� ���� �ܺο��� ���� �����ϰ� �ش� ����
			*/
			// Ʈ��, 
		// }

		void HyrulePhysics::Finalize()
		{
			/*
			
			*/
		}

		/// <summary>
		/// �߷� ���ӵ� ����
		/// </summary>
		void HyrulePhysics::SetWorldGravity(const Hyrule::Vector3D& _gravity)
		{
			this->gravity = _gravity;
		}
	}
}