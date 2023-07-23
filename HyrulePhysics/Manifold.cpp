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
		{}

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

		/// <summary>
		/// 충돌 이벤트
		/// </summary>
//		void Manifold::CollisionEvent()
//		{
//			// A, B의 질량이 0이라면 운동을 하지 않음
// 			if (((A->GetInvMass() + B->GetInvMass()) - 0.f) <= 0.000001f)
// 			{
// 				A->SetVelocity({ 0.f, 0.f });
// 				B->SetVelocity({ 0.f, 0.f });
// 				return;
// 			}
// 
// 			this->sfriction = GetFriction(A->GetStaticFriction(), B->GetStaticFriction());
// 			this->dfriction = GetFriction(A->GetDynamicFriction(), B->GetDynamicFriction());
// 			this->e = GetRestitution(A->GetCOR(), B->GetCOR());
// 
// 			for (size_t i = 0; i < contactPoints.size(); i++)
// 			{
// 				// 질량 중심에서 충돌 지점까지의 벡터
// 				Vector3D AtoContactPoint = contactPoints[i] - A->GetPosition();
// 				Vector3D BtoContactPoint = contactPoints[i] - B->GetPosition();
// 
// 				// 상대속도
// 				Vector3D Av = A->GetVelocity() + Cross(A->GetAngularVelocity(), AtoContactPoint);
// 				Vector3D Bv = B->GetVelocity() + Cross(B->GetAngularVelocity(), BtoContactPoint);
// 				Vector3D Sv = Bv - Av;
// 
// 				// 충돌 지점에서 노말 방향으로의 상대 속도
// 				float Cv = Sv.Dot(normal);
// 
// 				if (Cv > 0.f)
// 				{
// 					return;
// 				}
// 
// 				/// 임펄스 공식의 분모 부분임.
// 				Vector3D AN = AtoContactPoint.Cross(normal);
// 				Vector3D BN = BtoContactPoint.Cross(normal);
// 				float invMass = A->GetInvMass() + B->GetInvMass();
// 				Matrix3x3 invInertia = (AN * AN) * A->GetInvInertia() + (BN * BN) * B->GetInvInertia();
// 				float numerator = invMass + invInertia;
// 
// 				float j = -(1.f + e) * Cv;
// 
// 				j /= numerator;
// 				j /= contactPoints.size();
// 
// 				Vector3D impulse = normal * j;
// 				A->ApplyImpulse(-1.f * impulse, AtoContactPoint);
// 				B->ApplyImpulse(impulse, BtoContactPoint);
// 
// 				/// 마찰
// 				Av = A->GetVelocity() + Cross(A->GetAngularVelocity(), AtoContactPoint);
// 				Bv = B->GetVelocity() + Cross(B->GetAngularVelocity(), BtoContactPoint);
// 				Sv = Bv - Av;
// 
// 				// 노말 방향의 상대속도를 구해서 상대속도에서 빼면 그에 수직인 벡터가 나옴
// 				// Vector3D tangent = tangentVector;
// 				Vector3D nSv = normal * Sv.Dot(normal);
// 				Vector3D tangent = (Sv - nSv).Normalize();
// 
// 				float jtangent = 1.f * Sv.Dot(tangent);
// 				jtangent /= numerator;
// 				jtangent /= contactPoints.size();
// 
// 				if (std::fabs(jtangent - 0.0f) <= 0.000001f)
// 				{
// 					return;
// 				}
// 
// 				Vector3D tangentImpulse;
// 				if (std::fabs(jtangent) < (j * sfriction))
// 				{
// 					tangentImpulse = tangent * jtangent * -1.f;
// 				}
// 				else
// 				{
// 					tangentImpulse = tangent * -1.f * j * dfriction;
// 				}
// 
// 				A->ApplyImpulse(-1.f * tangentImpulse, AtoContactPoint);
// 				B->ApplyImpulse(tangentImpulse, BtoContactPoint);
//			}
//		}
	}
}