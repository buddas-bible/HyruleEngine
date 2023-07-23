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
			gravity = Hyrule::Vector3D(0.f, -9.81f, 0.f);
			Shapes::Initalize();
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
			colliderTable.clear();
			collisionInfo.clear();


			auto& nodes{ ObjectManager::GetInstance().GetNodeContainer() };

			// 옥트리에서 꺼낸 컨테이너를 순회함.
			for (auto& e : nodes)
			{

				// 노드 안에 있는 콜라이더만 체크함
				for (auto itr = e.begin(); itr != e.end(); itr++)
				{
					for (auto itr2 = e.begin(); itr2 != e.end(); itr2++)
					{
						if (itr == itr2)
						{
							continue;
						}

						// 두 콜라이더가 검사를 한 적이 있는가?
						auto colliderPair0{ std::make_pair(*itr, *itr2) };
						auto colliderPair1{ std::make_pair(*itr2, *itr) };

						if (colliderTable.count(colliderPair0) != 0 || colliderTable.count(colliderPair1) != 0)
						{
							continue;
						}

						// 활성화 되어있지 않으면 넘김
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

						/// 둘 중 하나라도 리지드 바디를 가지고 있다면 EPA를 실행 시킨다.
						if ((*itr)->hasRigidBody() || (*itr2)->hasRigidBody())
						{
							collisionInfo.push_back(manifold);
							CollisionSystem::EPAComputePenetrationDepth(manifold);
						}

						/// 강체를 들고 있는 콜라이더는 충돌 정보를 콜라이더에게 넘겨줘야 한다.
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
		/// 강체 시뮬레이션
		/// </summary>
		void HyrulePhysics::CollisionResponse(const float _deltaTime)
		{
			auto& rigidbodis = ObjectManager::GetInstance().GetRigidbodies();

			/// 속력 계산
			for (auto& e : rigidbodis)
			{
				e->ComputeVelocity(gravity, _deltaTime);
			}

			/// 강체, 콜라이더 충돌 대응
			for (auto& e : collisionInfo)
			{
				// 충돌

			}

			/// 계산된 속력을 위치, 각도에 적용
			for (auto& e : rigidbodis)
			{
				e->ComputePosition(_deltaTime);
			}

			/// 밀어냄
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
		/// 중력 가속도 설정
		/// </summary>
		void HyrulePhysics::SetWorldGravity(const Hyrule::Vector3D& _gravity)
		{
			this->gravity = _gravity;
		}
	}
}