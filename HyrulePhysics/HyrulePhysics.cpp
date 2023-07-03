#include "HyrulePhysics.h"

#include "Collider.h"
#include "RigidBody.h"
#include "Object.h"
#include "Octree.h"

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
		/// ������Ʈ�� ��ü�� �߰���.
		/// ������Ʈ�� �̹� ��ü�� �ִٸ� ������ �����ϰ� ���� ����.
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
		/// ������Ʈ�� �ݶ��̴��� ������
		/// </summary>
		void HyrulePhysics::RemoveCollider(const std::wstring& _name, ICollider* _target)
		{
			auto& obj = objectMap[_name];

			if (obj == nullptr || _target == nullptr)
			{
				return;
			}

			obj->colliders.erase(remove(obj->colliders.begin(), obj->colliders.end(), _target));

			delete _target;
		}

		/// <summary>
		/// ������Ʈ�� �ݶ��̴��� ������
		/// </summary>
		void HyrulePhysics::RemoveCollider(const std::wstring& _name, int _index)
		{
			auto obj = objectMap[_name];

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
		/// ������Ʈ�� ���� ��ü�� ����
		/// </summary>
		void HyrulePhysics::RemoveRigidBody(const std::wstring& _name)
		{
			auto obj = objectMap[_name];

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
		/// �ݸ��� üũ
		/// </summary>
		void HyrulePhysics::CollisionCheck()
		{
			// �� ������Ʈ�� ������ �ݶ��̴��� ���� ���
			// �ڽ� ������Ʈ�� �ݶ��̴��� ���� ���
			// ���δ� �浹 ������ ����
			// Collision

			/// �켱 ������ ��Ʈ���� ������� �������� ����
			/// �迭�� ���� Ž������ �Ǵ���.
			if (useOctree)
			{
				/// ��Ʈ���� ��带 ������.
				/// ��� �ȿ� �����Ͱ� 0~1���� �н�.
				/// 2�� ~ 4�������� �׳� ��ȸ�ϸ鼭 �浹 ���� �Ϸ��� ��.
				/// 5�� �Ѿ�� �ڽ��� Ž��.
				/// 
				/// 

				static Octree<Object, 4> octree;
				
			}
			else
			{
				for (size_t i = 0; i < objectList.size(); ++i)
				{
					for (size_t j = i + 1; j < objectList.size(); ++j)
					{
						objectList[i];
					}
				}
			}
		}

		/// <summary>
		/// ��ü �ùķ��̼�
		/// </summary>
		void HyrulePhysics::RigidSimulation(const float _deltaTime)
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
			/*
			���� �ùķ��̼��� �̷����� ������ �߷� ����
			*/
			gravity = _gravity;
		}

		/// <summary>
		/// ������Ʈ�� ã�Ƽ� ��ȯ��
		/// ���ٸ� ���� ��ȯ��
		/// </summary>
		Object* HyrulePhysics::GetObject(const std::wstring& _name)
		{
			auto obj = objectMap[_name];

			if (obj == nullptr)
			{
				obj = new Object(_name);
				objectMap[_name] = obj;
				objectList.push_back(obj);
			}

			return obj;
		}

		/// <summary>
		/// �ݶ��̴��� ���� ������Ʈ�� ���� �ݶ��̴� ����Ʈ�� �߰���.
		/// </summary>
		Collider* HyrulePhysics::CreateCollider(Object* _obj)
		{
			/*
			�켱 �浹 ���� ���� ������Ʈ ������ �浹 ������ �Ϸ��� ��.
			������Ʈ
			*/
			// Collider* newCollider = new Collider;

			// _obj->colliders.push_back(newCollider);

			// return newCollider;

			return nullptr;
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