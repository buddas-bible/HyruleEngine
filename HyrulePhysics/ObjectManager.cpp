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

#include "Ray.h"

namespace Hyrule
{
	namespace Physics
	{

		ObjectManager::ObjectManager() noexcept : octree({ Vector3D(), 30000.f }, {Vector3D(), 100.f})
		{}

		ICollider* ObjectManager::CreateCollider(const std::string& _name, COLLIDER_INFO* _info)
		{
			Object* obj = this->GetObject(_name);

			if (obj == nullptr)
			{
				obj = this->CreateObject(_name);
			}

			Collider* collider = this->AddCollider(obj, _info);

			colliders.push_back(collider);
			octree.Insert(collider, collider->GetAABB());

			return (ICollider*)collider;
		}

		IRigidBody* ObjectManager::CreateRigidBody(const std::string& _name)
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

			RigidBody* rigidbody = this->AddRigidBody(obj);

			rigidBodies.push_back(rigidbody);

			return (IRigidBody*)rigidbody;
		}


		void ObjectManager::RemoveCollider(const std::string& _name, ICollider*& _target)
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

		void ObjectManager::RemoveCollider(const std::string& _name, int _index)
		{
			Object* obj = this->GetObject(_name);

			if ((obj == nullptr) ||
				(_index < 0) ||
				((obj->colliders.size() - 1) < _index))
			{
				return;
			}

			obj->RemoveCollider(_index);

			// 오브젝트가 가진 콜라이더 개수가 0이고, 강체도 없으면 오브젝트를 삭제함.
			if (obj->Empty())
			{
				this->RemoveObject(_name);
				delete obj;
				obj = nullptr;
			}
		}

		void ObjectManager::RemoveCollider(const std::string& _name, Collider*& _target)
		{
			Object* obj = this->GetObject(_name);

			if (obj == nullptr || _target == nullptr)
			{
				return;
			}

			obj->RemoveCollider(_target);

			// 오브젝트가 가진 콜라이더 개수가 0이라면
			if (obj->Empty())
			{
				this->RemoveObject(_name);
				delete obj;
				obj = nullptr;
			}
		}

		void ObjectManager::RemoveRigidBody(const std::string& _name)
		{
			Object* obj = this->GetObject(_name);

			if (obj == nullptr)
			{
				return;
			}

			obj->RemoveRigidBody();

			// 오브젝트에 강체도 지웠는데 콜라이더도 없으면 오브젝트를 삭제함. 
			if (obj->Empty())
			{
				this->RemoveObject(_name);
				delete obj;
				obj = nullptr;
			}
		}

		std::vector<Collider*>& ObjectManager::GetColliders() noexcept
		{
			return this->colliders;
		}

		// std::vector<std::list<Collider*>>& ObjectManager::GetNodeContainer() noexcept
		// {
		// 	return octree.GetDataList();
		// }

		// void ObjectManager::NodeContainerClear() noexcept
		// {
		// 	octree.DataListClear();
		// }

		std::vector<Collider*> ObjectManager::QctreeQuery(Collider* _collider) noexcept
		{
			// 지금은 딱 맞는 AABB로 하고 있지만
			// 이것도 연산이 좀 필요하다보니까
			// scale 값을 가지고 length를 구하고
			// 임의의 AABB를 구해보는게 어떨까
			// AABB aabb{ _collider->GetAABB() };

			return octree.Query(_collider->GetAABB());
		}

		std::vector<Collider*> ObjectManager::QctreeQuery(const Ray& _ray) noexcept
		{
			return octree.Query(_ray);
		}

        std::vector<Collider*> ObjectManager::QctreeQuery(const Segment& _segment) noexcept
        {
            return octree.Query(_segment);
        }

        void ObjectManager::OctreeClear() noexcept
		{
			octree.Clear();
		}

		void ObjectManager::OctreeResearch(Collider* _collider)
		{
			// 옥트리에 있는 콜라이더 지우고 다시 설정.
			octree.Remove(_collider);
			octree.Insert(_collider, _collider->GetAABB());
		}

		std::vector<RigidBody*>& ObjectManager::GetRigidbodies() noexcept
		{
			return this->rigidBodies;
		}

		void ObjectManager::AddRemoveQueue(Collider* _collider)
		{
			ToDestroyCollider.push(_collider);
		}

		void ObjectManager::AddRemoveQueue(RigidBody* _rigidbody)
		{
			ToDestroyRigidBody.push(_rigidbody);
		}

		void ObjectManager::RemoveQueue()
		{
			for (auto i = 0; i < ToDestroyCollider.size(); i++)
			{
				Collider* e{ ToDestroyCollider.front() };
				auto itr = std::find(colliders.begin(), colliders.end(), e);
				if (itr != colliders.end())
				{
					colliders.erase(itr);
				}
				octree.Remove(e);

				Object* obj{ e->GetObject() };
				obj->RemoveCollider(e);

				if (obj->Empty())
				{
					this->RemoveObject(obj->GetName());
					delete obj;
					obj = nullptr;
				}

				ToDestroyCollider.pop();
			}

			for (auto i = 0; i < ToDestroyRigidBody.size(); i++)
			{
				auto e{ ToDestroyRigidBody.front() };
				auto itr = std::find(rigidBodies.begin(), rigidBodies.end(), e);
				if (itr != rigidBodies.end())
				{
					rigidBodies.erase(itr);
				}

				auto obj{ e->GetObject() };
				obj->RemoveRigidBody();

				if (obj->Empty())
				{
					this->RemoveObject(obj->GetName());
					delete obj;
					obj = nullptr;
				}

				ToDestroyRigidBody.pop();	
			}
		}

		Collider* ObjectManager::AddCollider(Object* _obj, COLLIDER_INFO* _info)
		{
			Collider* newCollider = nullptr;

			switch (_info->shapeInfo.shapeType)
			{
				case SPHERE:
				{
					newCollider = new SphereCollider(_obj, _info);
				}
				break;

				case BOX:
				{
					newCollider = new BoxCollider(_obj, _info);
				}
				break;

					// case CAPSULE:
					// 	Collider* newCollider = new SphereCollider;
					// 	break;

				case CONVEX:
				{
					newCollider = new ConvexCollider(_obj, _info);
				}
				break;

				case PLANE:
				{
					newCollider = new PlaneCollider(_obj, _info);
				}
				break;

					// case MESH:
					// 	Collider* newCollider = new MeshCollider;
					// 	break;
			}

			return newCollider;
		}

		RigidBody* ObjectManager::AddRigidBody(Object* _obj)
		{
			_obj->rigidbody = new RigidBody(_obj);

			return _obj->rigidbody;
		}


		Object* ObjectManager::GetObject(const std::string& _name)
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

		Object* ObjectManager::CreateObject(const std::string& _name)
		{
			Object* obj = new Object(_name);
			// std::unique_ptr<Object> obbj = std::make_unique<Object>(_name);
			objectMap.insert(std::make_pair(_name, obj));

			return obj;
		}

		void ObjectManager::RemoveObject(const std::string& _name)
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