#include "Manifold.h"

#include <vector>
#include "Object.h"
#include "RigidBody.h"

namespace Hyrule
{
	namespace Physics
	{

		Manifold::Manifold(Collider*& _A, Collider*& _B) noexcept
			: A(_A), B(_B),
			normal{}, tangent{}, depth{},
			contactPoints{},
			contactNormal{},
			collided{ false }
		{

		}

		bool Manifold::IsColliding()
		{
			return this->collided;
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

		const std::vector<Hyrule::Vector3D>& Manifold::GetContactPoints() const
		{
			return contactPoints;
		}

		void Manifold::AddContactPoint(const Vector3D& point)
		{
			contactPoints.push_back(point);
		}

		/// <summary>
		/// 일단 2D때 했던 GJK를 그대로 옮겨옴
		/// </summary>
		void Manifold::CheckCollision()
		{
			// 임의의 방향 벡터
			Vector3D directionVec = Vector3D::Right();

			// 방향 벡터로부터 서포트 포인트를 구함
			// std::vector<Vector3D> simplex;

			// 원점
			Vector3D origin(0.f, 0.f, 0.f);
			Vector3D temp;

			size_t count = 0;

			while (true)
			{
				switch (simplex.size())
				{
					case 0:
					{
						// 서포트 포인트 A를 구함
						// simplex.push_back(GetSupportPoint(A, B, directionVec));
						directionVec = -directionVec;
					}
					break;

					case 1:
					{
						// 서포트 포인트 B를 구함
						Vector3D OA = simplex[0].Normalized();
						Vector3D AO = -OA;
						// simplex.push_back(GetSupportPoint(A, B, directionVec));

						// 서포트 포인트 B가 원점 너머에 있지 않으면 충돌하지 않음
						Vector3D OB = simplex[1].Normalized();

						if (OB.Dot(AO) < 0)
						{
							collided = false;
							return;
						}
					}
					break;

					case 2:
					{
						// 원점을 향한 방향 벡터를 구하기 위해서 삼중곱을 함
						Vector3D AB = simplex[1] - simplex[0];
						Vector3D AO = -simplex[0];
						directionVec = AB.Cross(AO).Cross(AB).Normalized();

						// AB 위에 원점이 있을 경우
						if (directionVec == origin)
						{
							directionVec = Vector3D(-AB.y, AB.x, 0.f).Normalized();
						}

						// 서포트 포인트 C를 구함
						// simplex.push_back(GetSupportPoint(A, B, directionVec));

						// 서포트 포인트 C가 원점 너머에 있지 않으면 충돌하지 않음
						Vector3D OC = simplex[2].Normalized();

						if (OC.Dot(directionVec) <= 0)
						{
							collided = false;
							return;
						}
					}
					break;

					case 3:
					{
						// 점이 중복된다면 리턴
						if ((simplex[0] == simplex[2]) || (simplex[0] == simplex[1]) || (simplex[1] == simplex[2]))
						{
							collided = false;
							return;
						}

						Vector3D CA = simplex[0] - simplex[2];
						Vector3D CB = simplex[1] - simplex[2];
						Vector3D CO = -simplex[2].Normalized();

						Vector3D nBC = CA.Cross(CB).Cross(CB).Normalized();
						Vector3D nAC = CB.Cross(CA).Cross(CA).Normalized();

						// AB에서 원점을 향해서 점을 찾기 시작한 것이니
						// nBC, nAC를 원점과 내적해서 각도가 제대로 나오는가 판단
						if (nBC.Dot(CO) <= 0 && nAC.Dot(CO) <= 0)
						{
							// 심플렉스 내부에 원점이 존재함

							// 현재 심플렉스 정보를 저장함
							// m_Simplex = simplex;
							// 
							// EPA(A, B);
							// 
							// FindContactPoint(manifold.normal, A, B);
							// manifold.tangentVector = Cross(manifold.normal, Vector3::Up).Normalized();
							collided = true;
							return;
						}

						if (nBC.Dot(CO) > 0)
						{
							// BC 영역 안에 원점이 존재함.
							directionVec = nBC;

							temp = simplex[0];
							// 점 A 삭제 및 배열을 당김
							simplex.erase(simplex.begin() + 0);
							count++;
							break;
						}
						else if (nAC.Dot(CO) > 0)
						{
							// AC 영역 안에 원점이 존재함.
							directionVec = nAC;

							temp = simplex[1];
							// 점 B 삭제 및 배열을 당김
							simplex.erase(simplex.begin() + 1);
							count++;
							break;
						}
					}
					break;
				}
			}

			collided = false;
			return;
		}

		/// <summary>
		/// 충돌 이벤트
		/// </summary>
		void Manifold::CollisionEvent()
		{
			// A, B의 질량이 0이라면 운동을 하지 않음
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
		}
	}
}