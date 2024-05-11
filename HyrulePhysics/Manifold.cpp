#include "Manifold.h"

#include <vector>
#include "Object.h"
#include "RigidBody.h"
#include "Collider.h"

namespace hyrule
{
	namespace Physics
	{
		Manifold::Manifold(Collider*& _A, Collider*& _B)
			: A(_A), B(_B),
			normal{}, depth{},
			contactPoints{},
			impulse{}
		{}


// 		Manifold::Manifold(const Manifold& _other) :
// 			A(_other.A), B(_other.B),
// 			normal(_other.normal),
// 			depth(_other.depth),
// 			contactPoints(_other.contactPoints),
// 			simplex(_other.simplex)
// 		{}

		RigidBody* Manifold::RigidBodyA()
		{
			auto rigidA = A->GetRigidBody();

			if (rigidA == nullptr)
			{
				return NonRigidBody::nonRigidBody;
			}

			return rigidA;
		}

		RigidBody* Manifold::RigidBodyB()
		{
			auto rigidB = B->GetRigidBody();

			if (rigidB == nullptr)
			{
				return NonRigidBody::nonRigidBody;
			}

			return rigidB;
		}


		Vector3D Manifold::PositionA()
		{
			return A->GetPosition();
		}

		Vector3D Manifold::PositionB()
		{
			return B->GetPosition();
		}


		void Manifold::Apply()
		{
			A->AddCollisionInfo(B, *this);
			B->AddCollisionInfo(A, *this);
		}


		void Manifold::SetSimplex(const Simplex& _simplex)
		{
			this->simplex = _simplex;
		}

		Simplex& Manifold::GetSimplex()
		{
			return simplex;
		}


		void Manifold::Clear()
		{

		}


		Collider* Manifold::GetColliderA()
		{
			return this->A;
		}

		Collider* Manifold::GetColliderB()
		{
			return this->B;
		}


		void Manifold::SetColliderA(Collider* _collider)
		{
			this->A = _collider;
		}

		void Manifold::SetColliderB(Collider* _collider)
		{
			this->B = _collider;
		}

		void Manifold::AddImpulse(const Vector3D& _impulse)
		{
			impulse += impulse;
		}

		hyrule::Vector3D Manifold::GetImpulse()
		{
			return impulse;
		}

		Vector3D Manifold::GetNormal() const
		{
			return this->normal;
		}

		void Manifold::SetNormal(const Vector3D& _normal)
		{
			this->normal = _normal;
		}


		float Manifold::GetDepth() const
		{
			return this->depth;
		}

		void Manifold::SetDepth(float _depth)
		{
			this->depth = _depth;
		}


		const std::vector<Vector3D>& Manifold::GetContactPoints() const
		{
			return contactPoints;
		}

		void Manifold::AddContactPoint(const Vector3D& point)
		{
			contactPoints.push_back(point);
		}
	}
}