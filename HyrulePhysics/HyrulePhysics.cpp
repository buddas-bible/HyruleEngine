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
#include "Ray.h"
#include "../HyrulePhysicsEngine/RaycastInfo.h"

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
		ICollider* HyrulePhysics::CreateCollider(const std::string& _name, COLLIDER_INFO* _colinfo)
		{
			return ObjectManager::GetInstance().CreateCollider(_name, _colinfo);
		}

		/// <summary>
		/// ���� ������Ʈ �̸�
		/// Ʈ������ ������ �޾Ƽ� ��ü�� �����.
		/// </summary>
		IRigidBody* HyrulePhysics::CreateRigidBody(const std::string& _name)
		{
			return ObjectManager::GetInstance().CreateRigidBody(_name);
		}

		long HyrulePhysics::Initialize()
		{
			gravity = Hyrule::Vector3D(0.f, -9.81f, 0.f);
			Shapes::Initalize();
			NonRigidBody::Init();

			return (long)0L;
		}

		/// <summary>
		/// �ݸ��� üũ
		/// </summary>
		void HyrulePhysics::CollisionDetection()
		{
			auto& colliders = ObjectManager::GetInstance().GetColliders();

			/// ICollosion�� ���� Ŭ���� �ؾ���.
			for (auto& e : colliders)
			{
				e->SetCollied(false);
				e->CollisionInfoClear();
			}

			manifoldArray.clear();
			colliderTable.clear();
				
			for (auto& e : colliders)
			{
                if (e->isActive() == false)
                    continue;

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

					if (CollisionSystem::CollisionDetection(e, test, manifold))
					{
						/// �� �� �ϳ��� ������ �ٵ� ������ �ִٸ� EPA�� ���� ��Ų��.
						if (e->hasRigidBody() || test->hasRigidBody())
						{
							CollisionSystem::FindContactPoint(manifold);

							manifoldArray.push_back(manifold);
						}

						e->SetCollied(true);
						test->SetCollied(true);
					}
				}
			}
		}

		/// <summary>
		/// ��ü �ùķ��̼�
		/// </summary>
		void HyrulePhysics::CollisionResponse(const float _deltaTime)
		{
			auto& rigidbodis = ObjectManager::GetInstance().GetRigidbodies();

			for (auto i = 0; i < 4; i++)
			{
				/// ��ü, �ݶ��̴� �浹 ����
				for (auto& e : manifoldArray)
				{
                    if (e.GetColliderA()->GetTrigger() || e.GetColliderB()->GetTrigger())
                        continue;

					// �浹
					CollisionSystem::ComputeImpulse(e);
				}
			}

			/// �ӷ� ���
			for (auto& e : rigidbodis)
			{
				if (e->isActive() == false || e->IsAwake() == false)
					continue;

				e->ComputeVelocity(gravity, _deltaTime);
			}

			/// ���� �ӷ��� ��ġ, ������ ����
			for (auto& e : rigidbodis)
			{
				if (e->isActive() == false || e->IsAwake() == false)
					continue;

				e->ComputePosition(_deltaTime);
			}

			/// �о
			for (auto& e : manifoldArray)
			{
                if (e.GetColliderA()->GetTrigger() || e.GetColliderB()->GetTrigger())
                    continue;

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

		bool HyrulePhysics::Raycast(const Vector3D& _from, const Vector3D& _to, RaycastInfo* _data)
		{
			Ray ray;
			ray.position = _from;
			ray.direction = _to;

			auto colliders{ ObjectManager::GetInstance().QctreeQuery(ray) };

			// Ʈ�� �ȿ��� �浹�� �ݶ��̴��� ����
			if (colliders.empty())
			{
				return false;
			}
			else
			{
                float minDist{ FLT_MAX };

				for (auto& e : colliders)
				{
                    Vector3D contact;
                    float dist;

					// �浹 �ϸ�? �浹 ��ġ�� ������ �����ص�.
					if (CollisionSystem::Raycast(ray, e, contact, dist))
					{
                        if (dist < minDist)
                        {
                            _data->collision = true;
                            _data->position = contact;
                            _data->instaceID = e->GetInstaceID();
                            _data->tag = e->GetTag();
                            _data->userData = e->GetUserData();
                        }
					}
				}

				return _data->collision;
			}
		}

        bool HyrulePhysics::Raycast(const Vector3D& _from, const Vector3D& _to, const float _length, RaycastInfo* _data)
		{
			Segment segment;
			segment.position = _from;
			segment.direction = _to;
			segment.length = _length;

			auto colliders{ ObjectManager::GetInstance().QctreeQuery(segment) };

            // Ʈ�� �ȿ��� �浹�� �ݶ��̴��� ����
            if (colliders.empty())
            {
                return false;
            }
            else
            {
                float minDist{ FLT_MAX };

                for (auto& e : colliders)
                {
                    Vector3D contact;
                    float dist;

                    // �浹 �ϸ�? �浹 ��ġ�� ������ �����ص�.
                    if (CollisionSystem::Raycast(segment, e, contact, dist))
                    {
                        if (dist < minDist)
                        {
                            _data->collision = true;
                            _data->position = contact;
                            _data->instaceID = e->GetInstaceID();
                            _data->tag = e->GetTag();
                            _data->userData = e->GetUserData();
                        }
                    }
                }

                return _data->collision;
            }
		}

		/// <summary>
		/// �߷� ���ӵ� ����
		/// </summary>
		void HyrulePhysics::SetWorldGravity(const Hyrule::Vector3D& _gravity)
		{
			this->gravity = _gravity;
		}
	}
}