#include "ObjectManager.h"

#include "Object.h"
#include "ICollider.h"
#include "Collider.h"
#include "IRigidBody.h"
#include "RigidBody.h"
#include "PHYSICALLYOBJECT_INFO.h"

#include "SphereCollider.h"
#include "BoxCollider.h"
#include "ConvexCollider.h"
#include "PlaneCollider.h"


namespace Hyrule
{
	namespace Physics
	{

		ICollider* ObjectManager::AddCollider(const std::wstring& _name, COLLIDER_INFO* _info)
		{
			Object* obj = this->GetObject(_name);

			if (obj == nullptr)
			{
				obj = this->CreateObject(_name);
			}

			Collider* collider = this->CreateCollider(obj, _info);

			return (ICollider*)collider;
		}


		IRigidBody* ObjectManager::AddRigidBody(const std::wstring& _name)
		{
			Object* obj = this->GetObject(_name);

			if (obj == nullptr)
			{
				obj = this->CreateObject(_name);
			}

			if (obj->rigidbody != nullptr)
			{
				this->RemoveRigidBody(_name);
			}

			RigidBody* rigidbody = this->CreateRigidBody(obj);

			return (IRigidBody*)rigidbody;
		}


		void ObjectManager::RemoveCollider(const std::wstring& _name, ICollider*& _target)
		{
			Object* obj = this->GetObject(_name);

			if (obj == nullptr || _target == nullptr)
			{
				return;
			}

			Collider* t = static_cast<Collider*>(_target);
			obj->RemoveCollider(t);

			// 오브젝트가 가진 콜라이더 개수가 0이라면
			if (obj->Empty())
			{
				this->RemoveObject(_name);
				delete obj;
				obj = nullptr;
			}
		}


		void ObjectManager::RemoveCollider(const std::wstring& _name, int _index)
		{
			Object* obj = this->GetObject(_name);

			if ((obj == nullptr) ||
				(_index < 0) ||
				((obj->colliders.size() - 1) < _index))
			{
				return;
			}

			obj->RemoveCollider(_index);
			// delete collider;

			// 오브젝트가 가진 콜라이더 개수가 0이고, 강체도 없으면 오브젝트를 삭제함.
			if (!obj->colliders.size() && obj->rigidbody == nullptr)
			{
				this->RemoveObject(_name);
				delete obj;
				obj = nullptr;
			}
		}


		void ObjectManager::RemoveRigidBody(const std::wstring& _name)
		{
			Object* obj = this->GetObject(_name);

			if (obj == nullptr)
			{
				return;
			}

			auto& rigidbody = obj->rigidbody;

			if (rigidbody.get() == nullptr)
			{
				return;
			}

			// delete rigidbody;

			// 오브젝트에 강체도 지웠는데 콜라이더도 없으면 오브젝트를 삭제함. 
			if (!obj->colliders.size())
			{
				this->RemoveObject(_name);
				delete obj;
				obj = nullptr;
			}
		}

		Collider* ObjectManager::CreateCollider(Object* _obj, COLLIDER_INFO* _info)
		{
			switch (_info->shapeInfo.shapeType)
			{
				case SPHERE:
					Collider* newCol = new SphereCollider(_info);
					break;
				case BOX:
					Collider* newCol = new BoxCollider(_info);
					break;
					// case CAPSULE:
					// 	Collider* newCol = new SphereCollider;
					// 	break;
				case CONVEX:
					Collider* newCol = new ConvexCollider(_info);
					break;
				case PLANE:
					Collider* newCol = new PlaneCollider(_info);
					break;
					// case MESH:
					// 	Collider* newCol = new MeshCollider;
					// 	break;
			}
			return NULL;
		}

		RigidBody* ObjectManager::CreateRigidBody(Object* _obj)
		{
			_obj->rigidbody = std::make_shared<RigidBody>();

			return _obj->rigidbody.get();
		}

		Object* ObjectManager::GetObject(const std::wstring& _name)
		{
			Object* obj = nullptr;

			auto itr = objectMap.find(_name);

			if (itr == objectMap.end())
			{
				obj = nullptr;
			}
			else
			{
				obj = itr->second;
			}

			return obj;
		}

		Object* ObjectManager::CreateObject(const std::wstring& _name)
		{
			Object* obj = new Object(_name);
			// std::unique_ptr<Object> obbj = std::make_unique<Object>(_name);
			objectMap[_name] = obj;

			return obj;
		}

		void ObjectManager::RemoveObject(const std::wstring& _name)
		{
			auto itr = objectMap.find(_name);

			if (itr == objectMap.end())
			{
				return;
			}

			objectMap.erase(itr);
		}
	}
}