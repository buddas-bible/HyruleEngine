#include "Collider.h"

#include "Object.h"
#include <string>

#include "ObjectManager.h"
#include "Collision.h"
#include "Manifold.h"

namespace Hyrule
{
	namespace Physics
	{
		Collider::Collider(Object* _obj) noexcept : 
			object(_obj),
			center(), size(0.5f, 0.5f, 0.5f), isTrigger(false),
			inertia(), centerOfMass(), activate(true), collied(false),
			type()
		{}

		Vector3D Collider::GetPosition()
		{
			return object->GetPosition();
		}

		Quaternion Collider::GetRotation()
		{
			return object->GetRotation();
		}

		Vector3D Collider::GetScale()
		{
			return object->GetScale();
		}

		float Collider::GetLength()
		{
			Vector3D scl{ object->GetScale() };

			float x = scl.x * 0.5f;
			float y = scl.y * 0.5f;
			float z = scl.z * 0.5f;

			return std::sqrtf(x * x + y * y + z * z);
		}

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
			for (auto& e : collisionInfo)
			{
				delete e;
			}

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

		void Collider::Subexpressions(float w0, float w1, float w2, float& f0, float& f1, float& f2, float& g0, float& g1, float& g2)
		{
			auto w0Plusw1 = w0 + w1;
			f0 = w0Plusw1 + w2;

			auto w0Sqrt = w0 * w0;
			auto temp2 = w0Sqrt + (w1 * w0Plusw1);
			f1 = temp2 + (w2 * f0);
			f2 = (w0 * w0Sqrt) + (w1 * temp2) + (w2 * f1);

			g0 = f1 + w0 * (f0 + w0);
			g1 = f1 + w1 * (f0 + w1);
			g2 = f1 + w2 * (f0 + w2);
		}

		ColliderType Collider::GetType()
		{
			return type;
		}

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

		std::vector<ICollision*> Collider::GetCollisionInfo() noexcept
		{
			return collisionInfo;
		}

		void Collider::AddCollisionInfo(Collider* _collider, Manifold& _manifold)
		{
			Collision* collision = new Collision();
			collision->collider = _collider;
			collision->contactPoints = _manifold.GetContactPoints();
			collision->normal = _manifold.GetNormal();

			collisionInfo.push_back(collision);
		}

		void Collider::SetTransform(const Vector3D& _pos, const Quaternion& _rot, const Vector3D& _scl) noexcept
		{
			if (prePos == _pos && preRot == _rot && preScl == _scl)
			{
				return;
			}

			this->prePos = _pos;
			this->preRot = _rot;
			this->preScl = _scl;
			this->object->SetPosition(_pos);
			this->object->SetRotation(_rot);
			this->object->SetScale(_scl);
			ObjectManager::GetInstance().OctreeResearch(this);
		}

		void Collider::SetTrigger(bool _trigger)
		{
			this->isTrigger = _trigger;
		}

		void Collider::SetSize(const Vector3D& _size)
		{
			this->size = _size;
		}

		void Collider::SetCenter(const Vector3D& _center)
		{
			this->center = _center;
		}

		std::wstring Collider::GetObjectName()
		{
			return this->object->GetName();
		}
	}
}
