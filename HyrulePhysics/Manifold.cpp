#include "Manifold.h"

#include <vector>
#include "Object.h"
#include "RigidBody.h"
#include "Collider.h"

namespace Hyrule
{
	namespace Physics
	{
		Manifold::Manifold(Collider*& _A, Collider*& _B) noexcept
			: A(_A), B(_B),
			normal{}, tangent{}, depth{},
			contactPoints{},
			contactNormal{}, friction{},
			collided{ false }
		{}

		Manifold::~Manifold() noexcept
		{
			if (simplex != nullptr)
			{
				delete simplex;
				simplex = nullptr;
			}
		}

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

		void Manifold::SetSimplex(Simplex* _simplex)
		{
			this->simplex = _simplex;
		}

		Simplex& Manifold::GetSimplex()
		{
			return *simplex;
		}

		void Manifold::Clear()
		{
			if (simplex != nullptr)
			{
				delete simplex;
				simplex = nullptr;
			}
		}

		Collider* Manifold::GetColliderA()
		{
			return this->A;
		}

		Collider* Manifold::GetColliderB()
		{
			return this->B;
		}

		Vector3D Manifold::GetNormal() const noexcept
		{
			return this->normal;
		}

		void Manifold::SetNormal(const Vector3D& _normal) noexcept
		{
			this->normal = _normal;
		}

		Vector3D Manifold::GetTangent() const noexcept
		{
			return this->tangent;
		}

		void Manifold::SetTangent(const Vector3D& _tangent) noexcept
		{
			this->tangent = _tangent;
		}

		Vector3D Manifold::GetContactNormal() const noexcept
		{
			return this->contactNormal;
		}

		void Manifold::SetContactNormal(const Vector3D& _contactNormal) noexcept
		{
			this->contactNormal = _contactNormal;
		}

		float Manifold::GetDepth() const noexcept
		{
			return this->depth;
		}

		void Manifold::SetDepth(float _depth) noexcept
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