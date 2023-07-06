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
		/// �ϴ� 2D�� �ߴ� GJK�� �״�� �Űܿ�
		/// </summary>
		void Manifold::CheckCollision()
		{
			// ������ ���� ����
			Vector3D directionVec = Vector3D::Right();

			// ���� ���ͷκ��� ����Ʈ ����Ʈ�� ����
			// std::vector<Vector3D> simplex;

			// ����
			Vector3D origin(0.f, 0.f, 0.f);
			Vector3D temp;

			size_t count = 0;

			while (true)
			{
				switch (simplex.size())
				{
					case 0:
					{
						// ����Ʈ ����Ʈ A�� ����
						// simplex.push_back(GetSupportPoint(A, B, directionVec));
						directionVec = -directionVec;
					}
					break;

					case 1:
					{
						// ����Ʈ ����Ʈ B�� ����
						Vector3D OA = simplex[0].Normalized();
						Vector3D AO = -OA;
						// simplex.push_back(GetSupportPoint(A, B, directionVec));

						// ����Ʈ ����Ʈ B�� ���� �ʸӿ� ���� ������ �浹���� ����
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
						// ������ ���� ���� ���͸� ���ϱ� ���ؼ� ���߰��� ��
						Vector3D AB = simplex[1] - simplex[0];
						Vector3D AO = -simplex[0];
						directionVec = AB.Cross(AO).Cross(AB).Normalized();

						// AB ���� ������ ���� ���
						if (directionVec == origin)
						{
							directionVec = Vector3D(-AB.y, AB.x, 0.f).Normalized();
						}

						// ����Ʈ ����Ʈ C�� ����
						// simplex.push_back(GetSupportPoint(A, B, directionVec));

						// ����Ʈ ����Ʈ C�� ���� �ʸӿ� ���� ������ �浹���� ����
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
						// ���� �ߺ��ȴٸ� ����
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

						// AB���� ������ ���ؼ� ���� ã�� ������ ���̴�
						// nBC, nAC�� ������ �����ؼ� ������ ����� �����°� �Ǵ�
						if (nBC.Dot(CO) <= 0 && nAC.Dot(CO) <= 0)
						{
							// ���÷��� ���ο� ������ ������

							// ���� ���÷��� ������ ������
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
							// BC ���� �ȿ� ������ ������.
							directionVec = nBC;

							temp = simplex[0];
							// �� A ���� �� �迭�� ���
							simplex.erase(simplex.begin() + 0);
							count++;
							break;
						}
						else if (nAC.Dot(CO) > 0)
						{
							// AC ���� �ȿ� ������ ������.
							directionVec = nAC;

							temp = simplex[1];
							// �� B ���� �� �迭�� ���
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
		/// �浹 �̺�Ʈ
		/// </summary>
		void Manifold::CollisionEvent()
		{
			// A, B�� ������ 0�̶�� ��� ���� ����
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
// 				// ���� �߽ɿ��� �浹 ���������� ����
// 				Vector3D AtoContactPoint = contactPoints[i] - A->GetPosition();
// 				Vector3D BtoContactPoint = contactPoints[i] - B->GetPosition();
// 
// 				// ���ӵ�
// 				Vector3D Av = A->GetVelocity() + Cross(A->GetAngularVelocity(), AtoContactPoint);
// 				Vector3D Bv = B->GetVelocity() + Cross(B->GetAngularVelocity(), BtoContactPoint);
// 				Vector3D Sv = Bv - Av;
// 
// 				// �浹 �������� �븻 ���������� ��� �ӵ�
// 				float Cv = Sv.Dot(normal);
// 
// 				if (Cv > 0.f)
// 				{
// 					return;
// 				}
// 
// 				/// ���޽� ������ �и� �κ���.
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
// 				/// ����
// 				Av = A->GetVelocity() + Cross(A->GetAngularVelocity(), AtoContactPoint);
// 				Bv = B->GetVelocity() + Cross(B->GetAngularVelocity(), BtoContactPoint);
// 				Sv = Bv - Av;
// 
// 				// �븻 ������ ���ӵ��� ���ؼ� ���ӵ����� ���� �׿� ������ ���Ͱ� ����
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