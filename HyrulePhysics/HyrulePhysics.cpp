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
		/// 콜리전 체크
		/// </summary>
		void HyrulePhysics::CollisionDetection()
		{
			CollisionSystem::GetInstance().Clear();

			// CollisionSystem::GetInstance()
			// 
			// 이 함수가 호출되기 전에 콜라이더들은 월드TM을 업데이트 받을 것이다.
			// 이전 TM과 현재 TM을 비교해보고 변경이 되었으면
			// 트리 안에 있는 오브젝트를 삭제시키고 다시 넣음.
			// TM은 맵으로 할 예정.

			/// 우선 엔진이 옥트리를 사용할지 안할지에 따라서
			/// 배열을 전부 탐색할지 판단함.

			/// 옥트리의 노드를 구분함.
			/// 노드 안에 데이터가 0~1개면 패스.
			/// 2개 ~ 4개까지는 그냥 순회하면서 충돌 감지 하려고 함.
			/// 5개 넘어가면 자식을 탐색.

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
		/// 강체 시뮬레이션
		/// </summary>
		void HyrulePhysics::CollisionResponse(const float _deltaTime)
		{
			/*
			계층 구조를 가지는 강체는 트랜스폼 정보를 어떻게 가지고 어떻게 업데이트를 해야할까?
			물리 업데이트를 받기 전, 우선 월드 트랜스폼을 전달 받는다.
			강체 시뮬레이션을 통해서 월드 트랜스폼 정보가 변경이 된다.
			부모의 월드 트랜스폼 정보를 기반으로 로컬 트랜스폼 정보를 업데이트 한다.
			*/
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