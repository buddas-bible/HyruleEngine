#include "HyrulePhysics.h"

#include "Collider.h"
#include "RigidBody.h"
#include "Object.h"

namespace Hyrule
{
	namespace Physics
	{
		__declspec(dllexport) IPhysics* CreatePhysics()
		{
			return new Hyrule::Physics::HyrulePhysics;
		}

		__declspec(dllexport) void ReleasePhysics(IPhysics*& _physics)
		{
			if (_physics != nullptr)
			{
				delete _physics;
			}
		}

		ICollider* HyrulePhysics::AddCollider(const std::wstring& _name)
		{
			auto obj = this->GetObject(_name);

			auto collider = this->CreateCollider(obj);

			return (ICollider*)collider;
		}

		/// <summary>
		/// 오브젝트에 강체를 추가함.
		/// 오브젝트에 이미 강체가 있다면 강제를 삭제하고 새로 만듬.
		/// </summary>
		IRigidBody* HyrulePhysics::AddRigidBody(const std::wstring& _name)
		{
			auto obj = this->GetObject(_name);

			if (obj->rigidbody != nullptr)
			{
				this->RemoveRigidBody(_name);
			}
				
			auto rigidbody = this->CreateRigidBody(obj);

			return (IRigidBody*)rigidbody;
		}

		/// <summary>
		/// 오브젝트의 콜라이더를 삭제함
		/// </summary>
		void HyrulePhysics::RemoveCollider(const std::wstring& _name, ICollider* _target)
		{
			auto& obj = objectList[_name];

			if (obj == nullptr || _target == nullptr)
			{
				return;
			}

			obj->colliders.erase(remove(obj->colliders.begin(), obj->colliders.end(), _target));

			delete _target;
		}

		/// <summary>
		/// 오브젝트의 콜라이더를 삭제함
		/// </summary>
		void HyrulePhysics::RemoveCollider(const std::wstring& _name, int _index)
		{
			auto obj = objectList[_name];

			if ( (obj == nullptr) || 
				 (_index < 0) || 
				((obj->colliders.size() -1) < _index))
			{
				return;
			}

			auto& collider = obj->colliders[_index];

			obj->colliders.erase(obj->colliders.begin() + _index);

			delete collider;
		}

		/// <summary>
		/// 오브젝트가 가진 강체를 지움
		/// </summary>
		void HyrulePhysics::RemoveRigidBody(const std::wstring& _name)
		{
			auto obj = objectList[_name];

			if (obj == nullptr)
			{
				return;
			}

			auto& rigidbody = obj->rigidbody;

			delete rigidbody;
		}

		long HyrulePhysics::Initialize()
		{
			gravity = Hyrule::Vector3D(0.f, -9.81f, 0.f);

			return (long)0L;
		}

		/// <summary>
		/// 콜리전 체크
		/// </summary>
		void HyrulePhysics::CollisionCheck()
		{
			// 한 오브젝트가 복수의 콜라이더를 같는 경우
			// 자식 오브젝트가 콜라이더를 갖는 경우
			// 서로는 충돌 감지를 안함
			// Collision


			// 팔진 트리가 존재한다면 지우고 새로 만듬
			// 팔진 트리에 오브젝트를 다 꼴아 박았으면
			// 팔진 트리에서 Collider 배열의 모음을 받아서 하나씩 순회함.
			
			// 팔진 트리의 노드에서 반환할 Collider배열의 모음은 0~1은 걸러내고, 5 이상도 걸러낸다.
			// 한 노드 안에 5개의 콜라이더가 동시에 겹쳐져 있는 경우가 있을까...?
			// 이건 수치 조정으로 해결될 일이니...
			// 
			// 한 노드에 4개까지만 있다고 한다면 자식을 탐색하지 않고 본인의 배열을 뱉어낸다.
			// 4개끼리의 충돌 체크 정도는 더 파고들 이유가 없다고 생각됨.
			// 
			// 또한 콜라이더의 레이어를 나누면 좋겠지만 이건 나중으로 미루자

		}

		/// <summary>
		/// 강체 시뮬레이션
		/// </summary>
		void HyrulePhysics::RigidSimulation(const float _deltaTime)
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
		void HyrulePhysics::WorldReset()
		{
			/*
			게임 엔진에서 씬 단위로 관리를 한다고 했을 때.
			씬 전환 시, 월드 리셋 함수를 호출하는 것으로 물리 엔진에 있는 오브젝트를 정리한다.
			
			물리 엔진도 씬 단위로 오브젝트를 관리하는 것을 고민 해보았지만
			이러는 편이 오히려 직관적으로 이용할 수 있을 듯 싶어서 이렇게 하기로 했다.

			만약 물리 엔진도 씬 단위로 만든다고 했을 때,
			씬 인터페이스를 만들어서 외부에서 씬을 생성하고 해당 씬에
			*/
		}

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
			/*
			물리 시뮬레이션이 이뤄지는 세계의 중력 설정
			*/
			gravity = _gravity;
		}

		/// <summary>
		/// 오브젝트를 찾아서 반환함
		/// 없다면 만들어서 반환함
		/// </summary>
		Object* HyrulePhysics::GetObject(const std::wstring& _name)
		{
			auto obj = objectList[_name];

			if (obj == nullptr)
			{
				obj = new Object(_name);
				objectList[_name] = obj;
			}

			return obj;
		}

		/// <summary>
		/// 콜라이더를 만들어서 오브젝트가 가진 콜라이더 리스트에 추가함.
		/// </summary>
		Collider* HyrulePhysics::CreateCollider(Object* _obj)
		{
			/*
			우선 충돌 감지 때는 오브젝트 단위로 충돌 감지를 하려고 함.
			오브젝트
			*/
			// Collider* newCollider = new Collider;

			// _obj->colliders.push_back(newCollider);

			// return newCollider;

			return nullptr;
		}

		/// <summary>
		/// 오브젝트에 강체를 만듬
		/// </summary>
		RigidBody* HyrulePhysics::CreateRigidBody(Object* _obj)
		{
			RigidBody* newRigidbody = new RigidBody;

			_obj->rigidbody = newRigidbody;

			return newRigidbody;
		}
	}
}