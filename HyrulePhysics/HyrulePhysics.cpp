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
			auto& colliders = ObjectManager::GetInstance().GetColliders();

			/// ICollosion�� ���� Ŭ���� �ؾ���.
			for (auto& e : colliders)
			{
				e->SetCollied(false);
				e->CollisionInfoClear();
			}
			colliderTable.clear();
			collisionInfo.clear();


			auto& nodes{ ObjectManager::GetInstance().GetNodeContainer() };

			// ��Ʈ������ ���� �����̳ʸ� ��ȸ��.
			for (auto& e : nodes)
			{

				// ��� �ȿ� �ִ� �ݶ��̴��� üũ��
				for (auto itr = e.begin(); itr != e.end(); itr++)
				{
					for (auto itr2 = e.begin(); itr2 != e.end(); itr2++)
					{
						if (itr == itr2)
						{
							continue;
						}

						// �� �ݶ��̴��� �˻縦 �� ���� �ִ°�?
						auto colliderPair0{ std::make_pair(*itr, *itr2) };
						auto colliderPair1{ std::make_pair(*itr2, *itr) };

						if (colliderTable.count(colliderPair0) != 0 || colliderTable.count(colliderPair1) != 0)
						{
							continue;
						}

						// Ȱ��ȭ �Ǿ����� ������ �ѱ�
						if ((*itr2)->isActive() == false || (*itr)->isActive() == false)
						{
							continue;
						}

						Manifold manifold{ *itr, *itr2 };

						colliderTable.insert(std::make_pair(*itr, *itr2));

						if (CollisionSystem::GJKCollisionDetection(*itr, *itr2, manifold) == false)
						{
							continue;
						}

						/// �� �� �ϳ��� ������ �ٵ� ������ �ִٸ� EPA�� ���� ��Ų��.
						if ((*itr)->hasRigidBody() || (*itr2)->hasRigidBody())
						{
							collisionInfo.push_back(manifold);
							CollisionSystem::EPAComputePenetrationDepth(manifold);
						}

						/// ��ü�� ��� �ִ� �ݶ��̴��� �浹 ������ �ݶ��̴����� �Ѱ���� �Ѵ�.
						if ((*itr)->hasRigidBody() && (*itr2)->hasRigidBody())
						{
							manifold.Apply();
						}

						(*itr)->SetCollied(true);
						(*itr2)->SetCollied(true);
					}
				}
			}

			for (auto& e : collisionInfo)
			{
				e.Clear();
			}

			ObjectManager::GetInstance().NodeContainerClear();
		}

		/// <summary>
		/// ��ü �ùķ��̼�
		/// </summary>
		void HyrulePhysics::CollisionResponse(const float _deltaTime)
		{
			auto& rigidbodis = ObjectManager::GetInstance().GetRigidbodies();

			/// �ӷ� ���
			for (auto& e : rigidbodis)
			{
				e->ComputeVelocity(gravity, _deltaTime);
			}

			/// ��ü, �ݶ��̴� �浹 ����
			for (auto& e : collisionInfo)
			{
				// �浹

			}

			/// ���� �ӷ��� ��ġ, ������ ����
			for (auto& e : rigidbodis)
			{
				e->ComputePosition(_deltaTime);
			}

			/// �о
			for (auto& e : collisionInfo)
			{
				
			}
		}

		void HyrulePhysics::ApplyObjectDestroy()
		{
			ObjectManager::GetInstance().RemoveQueue();
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