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
		/// 게임 오브젝트의 이름
		/// 트랜스폼 정보
		/// 콜라이더 정보를 받아서 콜라이더를 만든다.
		/// </summary>
		ICollider* HyrulePhysics::CreateCollider(const std::wstring& _name, COLLIDER_INFO* _colinfo)
		{
			return ObjectManager::GetInstance().CreateCollider(_name, _colinfo);
		}

		/// <summary>
		/// 게임 오브젝트 이름
		/// 트랜스폼 정보를 받아서 강체를 만든다.
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
		/// 콜리전 체크
		/// </summary>
		void HyrulePhysics::CollisionDetection()
		{
			auto& colliders = ObjectManager::GetInstance().GetColliders();

			/// ICollosion을 전부 클리어 해야함.
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
			// 			/// 둘 중 하나라도 리지드 바디를 가지고 있다면 EPA를 실행 시킨다.
			// 			if ((*itr)->hasRigidBody() || (*itr2)->hasRigidBody())
			// 			{
			// 				CollisionSystem::EPAComputePenetrationDepth(manifold);
			// 				manifoldArray.push_back(manifold);
			// 
			// 				/// 강체를 들고 있는 콜라이더는 충돌 정보를 콜라이더에게 넘겨줘야 한다.
			// 				if ((*itr)->hasRigidBody() && (*itr2)->hasRigidBody())
			// 				{
			// 					// 접촉점도 찾아야함.
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
						/// 둘 중 하나라도 리지드 바디를 가지고 있다면 EPA를 실행 시킨다.
						if (e->hasRigidBody() || test->hasRigidBody())
						{
							CollisionSystem::EPAComputePenetrationDepth(manifold);
							manifoldArray.push_back(manifold);

							/// 강체를 들고 있는 콜라이더는 충돌 정보를 콜라이더에게 넘겨줘야 한다.
							if (e->hasRigidBody() && test->hasRigidBody())
							{
								// 접촉점도 찾아야함.
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
			// // 옥트리에서 꺼낸 컨테이너를 순회함.
			// for (auto& e : nodes)
			// {
			// 	// 노드 안에 있는 콜라이더만 체크함
			// 	for (auto itr = e.begin(); itr != e.end(); itr++)
			// 	{
			// 		if((*itr)->isActive() == false)
			// 			continue;
			// 
			// 		for (auto itr2 = std::next(itr); itr2 != e.end(); itr2++)
			// 		{
			// 			// 활성화 되어있지 않으면 넘김
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
			// 				/// 둘 중 하나라도 리지드 바디를 가지고 있다면 EPA를 실행 시킨다.
			// 				if ((*itr)->hasRigidBody() || (*itr2)->hasRigidBody())
			// 				{
			// 					CollisionSystem::EPAComputePenetrationDepth(manifold);
			// 					manifoldArray.push_back(manifold);
			// 
			// 					/// 강체를 들고 있는 콜라이더는 충돌 정보를 콜라이더에게 넘겨줘야 한다.
			// 					if ((*itr)->hasRigidBody() && (*itr2)->hasRigidBody())
			// 					{
			// 						// 접촉점도 찾아야함.
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
		/// 강체 시뮬레이션
		/// </summary>
		void HyrulePhysics::CollisionResponse(const float _deltaTime)
		{
			auto& rigidbodis = ObjectManager::GetInstance().GetRigidbodies();

			for (auto i = 0; i < 4; i++)
			{
				/// 강체, 콜라이더 충돌 대응
				for (auto& e : manifoldArray)
				{
					// 충돌
					CollisionSystem::ComputeImpulse(e);
				}
			}

			/// 속력 계산
			for (auto& e : rigidbodis)
			{
				e->ComputeVelocity(gravity, _deltaTime);
			}

			/// 계산된 속력을 위치, 각도에 적용
			for (auto& e : rigidbodis)
			{
				e->ComputePosition(_deltaTime);
			}

			/// 밀어냄
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
		/// 중력 가속도 설정
		/// </summary>
		void HyrulePhysics::SetWorldGravity(const Hyrule::Vector3D& _gravity)
		{
			this->gravity = _gravity;
		}
	}
}