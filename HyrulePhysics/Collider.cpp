#include "Collider.h"

#include "Object.h"
#include "RigidBody.h"
#include <string>

#include "ObjectManager.h"
#include "../HyrulePhysicsEngine/Collision.h"
#include "Manifold.h"

namespace Hyrule
{
    namespace Physics
    {
        Collider::Collider(Object* _obj) noexcept :
            object(_obj),
            center(), size(1.f, 1.f, 1.f), isTrigger(false),
            inertia(), centerOfMass(), activate(true), collied(false)
        {}

        Object* Collider::GetObject()
        {
            return object;
        }

        RigidBody* Collider::GetRigidBody()
        {
            return object->GetRigidBody();
        }

        void Collider::CollisionInfoClear()
        {
            collisionInfo.clear();
        }

        bool Collider::hasRigidBody()
        {
            return object->rigidbody != nullptr;
        }

        bool Collider::isActive()
        {
            return this->activate;
        }

        void Collider::SetCollied(bool _bool)
        {
            this->collied = _bool;
        }

        Vector3D Collider::GetCenterOfMass() noexcept
        {
            return centerOfMass;
        }

        // void Collider::Subexpressions(float w0, float w1, float w2, float& f0, float& f1, float& f2, float& g0, float& g1, float& g2)
        // {
        // 	auto w0Plusw1 = w0 + w1;
        // 	f0 = w0Plusw1 + w2;
        // 
        // 	auto w0Sqrt = w0 * w0;
        // 	auto temp2 = w0Sqrt + (w1 * w0Plusw1);
        // 	f1 = temp2 + (w2 * f0);
        // 	f2 = (w0 * w0Sqrt) + (w1 * temp2) + (w2 * f1);
        // 
        // 	g0 = f1 + w0 * (f0 + w0);
        // 	g1 = f1 + w1 * (f0 + w1);
        // 	g2 = f1 + w2 * (f0 + w2);
        // }

        bool Collider::isCollision() noexcept
        {
            return this->collied;
        }

        void Collider::OnEnable() noexcept
        {
            this->activate = true;
        }

        void Collider::OnDisable() noexcept
        {
            this->activate = false;
        }

        void Collider::OnDestroy() noexcept
        {
            ObjectManager::GetInstance().AddRemoveQueue(this);
        }

        std::vector<Hyrule::Physics::Collision>& Collider::GetCollisionInfo() noexcept
        {
            return collisionInfo;
        }

        void Collider::AddCollisionInfo(Collider* _collider, Manifold& _manifold)
        {
            Hyrule::Physics::Collision collision;
            collision.collider = _collider;
            collision.userData = _collider->userData;
            collision.tag = _collider->tag;
            collision.instanceID = _collider->GetInstaceID();
            collision.contactPoints = _manifold.GetContactPoints();
            collision.normal = _manifold.GetNormal();

            collisionInfo.push_back(collision);
        }

        void Collider::SetTransform(
            const Vector3D& _center, const Vector3D& _size,
            const Vector3D& _pos, const Quaternion& _rot, const Vector3D& _scl) noexcept
        {
            if (prePos == _pos && preRot == _rot && preScl == _scl &&
                center == _center && size == _size)
            {
                return;
            }

            if (preScl != _scl || size != _size)
            {
                if (hasRigidBody())
                {
                    object->GetRigidBody()->CalculateInertiaTensor();
                }
            }

            this->center = _center;
            this->size = _size;

            this->prePos = _pos;
            this->preRot = _rot;
            this->preScl = _scl;

            this->object->SetPosition(_pos);
            this->object->SetRotation(_rot);
            this->object->SetScale(_scl);
            ObjectManager::GetInstance().OctreeResearch(this);
        }


        void Collider::SetSize(const Vector3D& _size)
        {
            this->size = _size;
        }

        void Collider::SetCenter(const Vector3D& _center)
        {
            this->center = _center;
        }

        bool Collider::GetTrigger()
        {
            return isTrigger;
        }

        void Collider::SetTrigger(bool _trigger)
        {
            this->isTrigger = _trigger;
        }

        std::string Collider::GetInstaceID()
        {
            return this->object->GetName();
        }

        std::string Collider::GetTag()
        {
            return tag;
        }

        void* Collider::GetUserData()
        {
            return userData;
        }
    }
}
