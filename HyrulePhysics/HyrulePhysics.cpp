#include "HyrulePhysics.h"

#include "Collider.h"
#include "RigidBody.h"
#include "Object.h"
#include "Shape.h"
#include "Octree.h"

#include "PHYSICALLYOBJECT_INFO.h"
#include "ObjectManager.h"
#include "CollisionSystem.h"

#include "Manifold.h"
#include "Simplex.h"

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
			Shapes::Initalize();
			return (long)0L;
		}

		/// <summary>
		/// �ݸ��� üũ
		/// </summary>
		void HyrulePhysics::CollisionDetection()
		{
			CollisionSystem::GetInstance().Clear();

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

			auto& colliders = ObjectManager::GetInstance().GetColliders();
			for (auto i = 0; i < colliders.size() - 1; i++)
			{
				bool detect = CollisionSystem::GetInstance().GJKCollisionDetection(colliders[i], colliders[i + 1]);
				if (detect == true)
				{
					colliders[i]->SetCollied(true);
					colliders[i + 1]->SetCollied(true);
				}
				else
				{
					colliders[i]->SetCollied(false);
					colliders[i + 1]->SetCollied(false);
				}
			}

			CollisionSystem::GetInstance().EPAComputePenetrationDepth();
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

		void HyrulePhysics::Finalize()
		{
			
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