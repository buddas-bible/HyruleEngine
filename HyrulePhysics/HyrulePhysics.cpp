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
		/// ���� ������Ʈ�� �̸�
		/// Ʈ������ ����
		/// �ݶ��̴� ������ �޾Ƽ� �ݶ��̴��� �����.
		/// </summary>
		ICollider* HyrulePhysics::AddCollider(const std::wstring& _name, COLLIDER_INFO* _colinfo)
		{
			auto obj = ObjectManager::GetInstance().GetObject(_name);

			if (obj == nullptr)
			{
				obj = ObjectManager::GetInstance().CreateObject(_name);
			}

			auto collider = this->CreateCollider(obj, _colinfo);

			return (ICollider*)collider;
		}

		/// <summary>
		/// ���� ������Ʈ �̸�
		/// Ʈ������ ������ �޾Ƽ� ��ü�� �����.
		/// </summary>
		IRigidBody* HyrulePhysics::AddRigidBody(const std::wstring& _name)
		{
			auto obj = ObjectManager::GetInstance().GetObject(_name);

			if (obj == nullptr)
			{
				obj = ObjectManager::GetInstance().CreateObject(_name);
			}

			if (obj->rigidbody != nullptr)
			{
				this->RemoveRigidBody(_name);
			}
				
			auto rigidbody = this->CreateRigidBody(obj);

			return (IRigidBody*)rigidbody;
		}

		/// <summary>
		/// ������Ʈ�� �ݶ��̴��� ������
		/// </summary>
		void HyrulePhysics::RemoveCollider(const std::wstring& _name, ICollider* _target)
		{
			auto obj = ObjectManager::GetInstance().GetObject(_name);

			if (obj == nullptr || _target == nullptr)
			{
				return;
			}

			obj->colliders.erase(remove(obj->colliders.begin(), obj->colliders.end(), _target));

			delete _target;

			// ������Ʈ�� ���� �ݶ��̴� ������ 0�̶��
			if (!obj->colliders.size() && obj->rigidbody == nullptr)
			{
				objectMap.erase(_name);
				objectList.erase(remove(objectList.begin(), objectList.end(), obj));
			}
		}

		/// <summary>
		/// ������Ʈ�� �ݶ��̴��� ������
		/// </summary>
		void HyrulePhysics::RemoveCollider(const std::wstring& _name, int _index)
		{
			auto obj = ObjectManager::GetInstance().GetObject(_name);

			if ( (obj == nullptr) || 
				 (_index < 0) || 
				((obj->colliders.size() -1) < _index))
			{
				return;
			}

			auto& collider = obj->colliders[_index];

			obj->colliders.erase(obj->colliders.begin() + _index);

			delete collider;

			// ������Ʈ�� ���� �ݶ��̴� ������ 0�̰�, ��ü�� ������ ������Ʈ�� ������.
			if (!obj->colliders.size() && obj->rigidbody == nullptr)
			{
				objectMap.erase(_name);
				objectList.erase(remove(objectList.begin(), objectList.end(), obj));
				obj = nullptr;
			}
		}

		/// <summary>
		/// ������Ʈ�� ���� ��ü�� ����
		/// </summary>
		void HyrulePhysics::RemoveRigidBody(const std::wstring& _name)
		{
			auto obj = ObjectManager::GetInstance().GetObject(_name);

			if (obj == nullptr)
			{
				return;
			}

			auto& rigidbody = obj->rigidbody;

			if (rigidbody == nullptr)
			{
				return;
			}

			delete rigidbody;

			// ������Ʈ�� ��ü�� �����µ� �ݶ��̴��� ������ ������Ʈ�� ������. 
			if (!obj->colliders.size())
			{
				objectMap.erase(_name);
				objectList.erase(remove(objectList.begin(), objectList.end(), obj));
				obj = nullptr;
			}
		}

		long HyrulePhysics::Initialize()
		{
			gravity = Hyrule::Vector3D(0.f, -9.81f, 0.f);

			return (long)0L;
		}

		/// <summary>
		/// �ݸ��� üũ
		/// </summary>
		void HyrulePhysics::CollisionDetection()
		{
			// �� �Լ��� ȣ��Ǳ� ���� �ݶ��̴����� ����TM�� ������Ʈ ���� ���̴�.
			// ���� TM�� ���� TM�� ���غ��� ������ �Ǿ�����
			// Ʈ�� �ȿ� �ִ� ������Ʈ�� ������Ű�� �ٽ� ����.
			// TM�� ������ �� ����.

			/// �켱 ������ ��Ʈ���� ������� �������� ����
			/// �迭�� ���� Ž������ �Ǵ���.
			if (useOctree)
			{
				/// ��Ʈ���� ��带 ������.
				/// ��� �ȿ� �����Ͱ� 0~1���� �н�.
				/// 2�� ~ 4�������� �׳� ��ȸ�ϸ鼭 �浹 ���� �Ϸ��� ��.
				/// 5�� �Ѿ�� �ڽ��� Ž��.

				Octree<Object, 4> octree;
				
			}
			else
			{
				for (size_t i = 0; i < objectList.size(); ++i)
				{
					for (size_t j = i + 1; j < objectList.size(); ++j)
					{
						// objectList[i];
					}
				}
			}
		}

		/// <summary>
		/// ��ü �ùķ��̼�
		/// </summary>
		void HyrulePhysics::CollisionResponse(const float _deltaTime)
		{
			/*
			���� ������ ������ ��ü�� Ʈ������ ������ ��� ������ ��� ������Ʈ�� �ؾ��ұ�?
			���� ������Ʈ�� �ޱ� ��, �켱 ���� Ʈ�������� ���� �޴´�.
			��ü �ùķ��̼��� ���ؼ� ���� Ʈ������ ������ ������ �ȴ�.
			�θ��� ���� Ʈ������ ������ ������� ���� Ʈ������ ������ ������Ʈ �Ѵ�.
			*/
		}

		/// <summary>
		/// ���� �ȿ� �ִ� ������Ʈ�� ���� ������
		/// </summary>
		void HyrulePhysics::WorldReset()
		{
			/*
			���� �������� �� ������ ������ �Ѵٰ� ���� ��.
			�� ��ȯ ��, ���� ���� �Լ��� ȣ���ϴ� ������ ���� ������ �ִ� ������Ʈ�� �����Ѵ�.
			
			���� ������ �� ������ ������Ʈ�� �����ϴ� ���� ��� �غ�������
			�̷��� ���� ������ ���������� �̿��� �� ���� �� �; �̷��� �ϱ�� �ߴ�.

			���� ���� ������ �� ������ ����ٰ� ���� ��,
			�� �������̽��� ���� �ܺο��� ���� �����ϰ� �ش� ����
			*/
		}

		void HyrulePhysics::Finalize()
		{
			/*
			
			*/
		}

		/// <summary>
		/// �߷� ���ӵ� ����
		/// </summary>
		void HyrulePhysics::SetWorldGravity(const Hyrule::Vector3D& _gravity)
		{
			this->gravity = _gravity;
		}

		/// <summary>
		/// �ݶ��̴��� ���� ������Ʈ�� ���� �ݶ��̴� ����Ʈ�� �߰���.
		/// </summary>
		Collider* HyrulePhysics::CreateCollider(Object* _obj, COLLIDER_INFO* _info)
		{
			Collider* collider = new Collider(*_info);
			
			_obj->colliders.push_back(collider);

			return collider;
		}

		/// <summary>
		/// ������Ʈ�� ��ü�� ����
		/// </summary>
		RigidBody* HyrulePhysics::CreateRigidBody(Object* _obj)
		{
			RigidBody* newRigidbody = new RigidBody;

			_obj->rigidbody = newRigidbody;

			return newRigidbody;
		}
	}
}