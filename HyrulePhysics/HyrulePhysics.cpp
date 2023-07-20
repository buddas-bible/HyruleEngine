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

			return (long)0L;
		}

		/// <summary>
		/// 콜리전 체크
		/// </summary>
		void HyrulePhysics::CollisionDetection()
		{
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
			// CollisionSystem::GJKCollisionDetection();
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

		/// <summary>
		/// 월드 안에 있는 오브젝트를 전부 삭제함
		/// </summary>
		// void HyrulePhysics::WorldReset()
		// {
			/*
			게임 엔진에서 씬 단위로 관리를 한다고 했을 때.
			씬 전환 시, 월드 리셋 함수를 호출하는 것으로 물리 엔진에 있는 오브젝트를 정리한다.
			
			물리 엔진도 씬 단위로 오브젝트를 관리하는 것을 고민 해보았지만
			이러는 편이 오히려 직관적으로 이용할 수 있을 듯 싶어서 이렇게 하기로 했다.

			만약 물리 엔진도 씬 단위로 만든다고 했을 때,
			씬 인터페이스를 만들어서 외부에서 씬을 생성하고 해당 씬에
			*/
			// 트리, 
		// }

		void HyrulePhysics::Finalize()
		{
			/*
			
			*/
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