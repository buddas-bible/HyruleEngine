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
			gravity = Hyrule::Vector3D(0.f, -1.81f, 0.f);
			Shapes::Initalize();
			NonRigidBody::Init();
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

			manifoldArray.clear();
			colliderTable.clear();


			// for (auto itr = colliders.begin(); itr != colliders.end(); itr++)
			// {
			// 	if ((*itr)->isActive() == false)
			// 		continue;
			// 
			// 	for (auto itr2 = std::next(itr); itr2 != colliders.end(); itr2++)
			// 	{
			// 		if ((*itr2)->isActive() == false)
			// 			continue;
			// 
			// 		auto colliderPair = std::minmax(*itr, *itr2);
			// 		if (colliderTable.count(colliderPair) != 0)
			// 			continue;
			// 
			// 		Manifold manifold{ *itr, *itr2 };
			// 
			// 		colliderTable.insert(colliderPair);
			// 
			// 		if (CollisionSystem::GJKCollisionDetection(*itr, *itr2, manifold))
			// 		{
			// 			/// �� �� �ϳ��� ������ �ٵ� ������ �ִٸ� EPA�� ���� ��Ų��.
			// 			if ((*itr)->hasRigidBody() || (*itr2)->hasRigidBody())
			// 			{
			// 				CollisionSystem::EPAComputePenetrationDepth(manifold);
			// 				manifoldArray.push_back(manifold);
			// 
			// 				/// ��ü�� ��� �ִ� �ݶ��̴��� �浹 ������ �ݶ��̴����� �Ѱ���� �Ѵ�.
			// 				if ((*itr)->hasRigidBody() && (*itr2)->hasRigidBody())
			// 				{
			// 					// �������� ã�ƾ���.
			// 					CollisionSystem::FindContactPoint(manifold);
			// 					manifold.Apply();
			// 				}
			// 
			// 				manifoldArray.push_back(manifold);
			// 			}
			// 
			// 			(*itr)->SetCollied(true);
			// 			(*itr2)->SetCollied(true);
			// 		}
			// 	}
			// }
				
			for (auto& e : colliders)
			{
				auto queryResult = ObjectManager::GetInstance().QctreeQuery(e);
				for (auto& test : queryResult)
				{
					if (e == test)
						continue;

					if (test->isActive() == false)
						continue;

					auto colliderPair = std::minmax(e, test);
					if (colliderTable.count(colliderPair) != 0)
						continue;

					Manifold manifold{ e, test };
					colliderTable.insert(colliderPair);

					if (CollisionSystem::GJKCollisionDetection(e, test, manifold))
					{
						/// �� �� �ϳ��� ������ �ٵ� ������ �ִٸ� EPA�� ���� ��Ų��.
						if (e->hasRigidBody() || test->hasRigidBody())
						{
							CollisionSystem::EPAComputePenetrationDepth(manifold);
							manifoldArray.push_back(manifold);

							/// ��ü�� ��� �ִ� �ݶ��̴��� �浹 ������ �ݶ��̴����� �Ѱ���� �Ѵ�.
							if (e->hasRigidBody() && test->hasRigidBody())
							{
								// �������� ã�ƾ���.
								CollisionSystem::FindContactPoint(manifold);
								manifold.Apply();
							}

							manifoldArray.push_back(manifold);
						}

						e->SetCollied(true);
						test->SetCollied(true);
					}
				}
			}

			// auto& nodes{ ObjectManager::GetInstance().GetNodeContainer() };
			// 
			// // ��Ʈ������ ���� �����̳ʸ� ��ȸ��.
			// for (auto& e : nodes)
			// {
			// 	// ��� �ȿ� �ִ� �ݶ��̴��� üũ��
			// 	for (auto itr = e.begin(); itr != e.end(); itr++)
			// 	{
			// 		if((*itr)->isActive() == false)
			// 			continue;
			// 
			// 		for (auto itr2 = std::next(itr); itr2 != e.end(); itr2++)
			// 		{
			// 			// Ȱ��ȭ �Ǿ����� ������ �ѱ�
			// 			if ((*itr2)->isActive() == false)
			// 				continue;
			// 
			// 			auto colliderPair = std::minmax(*itr, *itr2);
			// 			if (colliderTable.count(colliderPair) != 0)
			// 				continue;
			// 
			// 			Manifold manifold{ *itr, *itr2 };
			// 
			// 			colliderTable.insert(colliderPair);
			// 
			// 			if (CollisionSystem::GJKCollisionDetection(*itr, *itr2, manifold))
			// 			{
			// 				/// �� �� �ϳ��� ������ �ٵ� ������ �ִٸ� EPA�� ���� ��Ų��.
			// 				if ((*itr)->hasRigidBody() || (*itr2)->hasRigidBody())
			// 				{
			// 					CollisionSystem::EPAComputePenetrationDepth(manifold);
			// 					manifoldArray.push_back(manifold);
			// 
			// 					/// ��ü�� ��� �ִ� �ݶ��̴��� �浹 ������ �ݶ��̴����� �Ѱ���� �Ѵ�.
			// 					if ((*itr)->hasRigidBody() && (*itr2)->hasRigidBody())
			// 					{
			// 						// �������� ã�ƾ���.
			// 						CollisionSystem::FindContactPoint(manifold);
			// 						manifold.Apply();
			// 					}
			// 
			// 					manifoldArray.push_back(manifold);
			// 				}
			// 
			// 				(*itr)->SetCollied(true);
			// 				(*itr2)->SetCollied(true);
			// 			}
			// 		}
			// 	}
			// }
			// 
			// ObjectManager::GetInstance().NodeContainerClear();
		}

		/// <summary>
		/// ��ü �ùķ��̼�
		/// </summary>
		void HyrulePhysics::CollisionResponse(const float _deltaTime)
		{
			auto& rigidbodis = ObjectManager::GetInstance().GetRigidbodies();

			for (auto i = 0; i < 4; i++)
			{
				/// ��ü, �ݶ��̴� �浹 ����
				for (auto& e : manifoldArray)
				{
					// �浹
					CollisionSystem::ComputeImpulse(e);
				}
			}

			/// �ӷ� ���
			for (auto& e : rigidbodis)
			{
				e->ComputeVelocity(gravity, _deltaTime);
			}

			/// ���� �ӷ��� ��ġ, ������ ����
			for (auto& e : rigidbodis)
			{
				e->ComputePosition(_deltaTime);
			}

			/// �о
			for (auto& e : manifoldArray)
			{
				CollisionSystem::ResolveCollision(e);
			}
		}

		void HyrulePhysics::ApplyObjectDestroy()
		{
			ObjectManager::GetInstance().RemoveQueue();
		}

		void HyrulePhysics::Finalize()
		{
			
		}

		// 
		RaycastInfo* HyrulePhysics::Raycast(const Vector3D& _from, const Vector3D& _to)
		{
			return nullptr;

		}

		RaycastInfo* HyrulePhysics::Raycast(const Vector3D& _from, const Vector3D& _to, const std::string& _name)
		{
			return nullptr;
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