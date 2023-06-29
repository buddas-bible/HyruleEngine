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
			return new Physics::HyrulePhysics;
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
			gravity = 9.81f;

			return (long)0L;
		}

		/// <summary>
		/// 콜리전 체크
		/// </summary>
		void HyrulePhysics::CollisionCheck()
		{

		}

		/// <summary>
		/// 강체 시뮬레이션
		/// </summary>
		void HyrulePhysics::RigidSimulation(const float _deltaTime)
		{

		}

		/// <summary>
		/// 월드 안에 있는 오브젝트를 전부 삭제함
		/// </summary>
		void HyrulePhysics::WorldReset()
		{

		}

		void HyrulePhysics::Finalize()
		{

		}

		void HyrulePhysics::SetGravity(float)
		{

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
			Collider* newCollider = new Collider;

			_obj->colliders.push_back(newCollider);

			return newCollider;
		}

		/// <summary>
		/// 오브젝트에 강체를 만듬
		/// </summary>
		/// <param name="_obj"></param>
		/// <returns></returns>
		RigidBody* HyrulePhysics::CreateRigidBody(Object* _obj)
		{
			RigidBody* newRigidbody = new RigidBody;

			_obj->rigidbody = newRigidbody;

			return newRigidbody;
		}
	}
}