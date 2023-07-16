#include "CollisionSystem.h"

#include "HyruleMath.h"
#include <vector>
#include "Simplex.h"
#include "Collider.h"
#include "Face.h"
#include "Edge.h"
#include "Manifold.h"

constexpr size_t GJK_MAX = 50;
constexpr size_t EPA_MAX = 50;

namespace Hyrule
{
	namespace Physics
	{
		/// <summary>
		/// Casey's GJK
		/// </summary>
		bool CollisionSystem::GJKCollisionDetection(Collider* _colliderA, Collider* _colliderB)
		{
			size_t count{};

			Simplex* simplex = new Simplex;

			// ������ ���� ���ͷ� 
			Vector3D direction{ Vector3D::Right() };
			Vector3D support{ FindSupportPoint(_colliderA, _colliderB, direction) };

			simplex->push_back(support);
			direction = -support.Normalized();

			while (count < GJK_MAX)
			{
				// ���� ���ͷκ��� ����Ʈ �����͸� ���ϴ°� ������
				support = FindSupportPoint(_colliderA, _colliderB, direction);
				Vector3D OP = support.Normalized();

				// ����Ʈ ����Ʈ�� ���⺤���� ������ 90�� �̻��̸� �׳� �浹 ���ϴ� ����
				// (�ش� �������� ������ �Ѵ� ���� ���� ������)
				// (������ �����ϴ� ���÷����� ���� ���� ����)
				if (OP.Dot(direction) < 0.f)
				{
					delete simplex;
					return false;
				}

				// ����Ʈ �����Ͱ� ���������� ���÷����� �ִ´�.
				simplex->push_back(support);

				if (DoSimplex(*simplex, direction))
				{
					// ���÷��� �ȿ� ������ �����Ѵٸ� �浹��.
					Manifold* newManifold = new Manifold(_colliderA, _colliderB);

					detectionInfo.insert(std::make_pair(newManifold, simplex));
					return true;

				}
				count++;
			}

			delete simplex;
			return false;
		}

		//		Chung-Wang �и� ���� �˰���
		//		bool CollisionSystem::CollisionCheck2(Collider*, Collider*)
		//		{
		//			// ������ ���͸� ���� ���� d�� ��Ƽ�
		//			// �� �ݶ��̴��� ����Ʈ �����͸� ����.
		//			// a dot d < b dot -d ��� ����� ������ �浹 ����
		//
		//			// �ƴϸ� ���ο� ���� ���͸� ����
		//			// ���ο� ���⺤�ʹ� d-2(r dot d)r
		//			// ���⼭ r�� (b-a) / (b-a).length()
		//			// 
		//			// ���� ���� ���⺤�ͷ� �ٽ� Ž���� ������
		//			// GJK���� 2�� ���� �浹 ���� �˰���
		//		}

		/// <summary>
		/// EPA
		/// </summary>
		void CollisionSystem::ComputePenetrationDepth(Manifold* _manifold)
		{
			// �Ŵ������� ���÷����� �������� �ε����� ��
			Simplex simplex = *detectionInfo[_manifold];
			simplex.SetIndices();

			size_t count{};

			while (count < EPA_MAX)
			{
				// ���� ����� ���� ã�� �� ��� ������ �Ÿ��� ����
				std::tuple<Face*, float> closestFace = FindClosestFace(&simplex);

				// �븻 �������� ����Ʈ ����Ʈ�� ����
				Vector3D support = FindSupportPoint(_manifold->GetColliderA(), _manifold->GetColliderB(), std::get<0>(closestFace)->normal);

				// ����Ʈ ����Ʈ���� �Ÿ��� �븻 �����
				float dist{ support.Dot(std::get<0>(closestFace)->normal) };
				
				// ���� �븻�� ������ ���� ����� �Ÿ��� �����ϴٸ�
				if (std::fabs(dist - std::get<1>(closestFace)) > Epsilon)
				{
					_manifold->SetDepth(dist);
					_manifold->SetNormal(std::get<0>(closestFace)->normal);
					return;
				}
				// �븻 �������� Ȯ�� ��Ŵ
				else
				{
					// ���÷����� ���� �߰��ϰ� ���� ������Ŵ
					simplex.push_back(support);

					for (size_t i = 0; i < simplex.index.size(); i += 3)
					{
						// ���÷����κ��� ���� �� �����̱� ������ �ε��� ������ ��ġ�� ����
						size_t _i0 = std::get<0>(closestFace)->index[0];
						size_t _i1 = std::get<0>(closestFace)->index[1];
						size_t _i2 = std::get<0>(closestFace)->index[2];
						
						if (simplex.index[i] == _i0 && simplex.index[i + 1] == _i1 && simplex.index[i + 2] == _i2)
						{
							simplex.index.erase(simplex.index.begin() + i);
							simplex.index.erase(simplex.index.begin() + i + 1);
							simplex.index.erase(simplex.index.begin() + i + 2);
						}
					}
				}
			}

			// 		size_t i = 0;
// 
// 		while (i < EPA_MAXCOUNT)
// 		{
// 			// ����� ���� ã�´�.
// 			MinkowskiEdge edge = GetSupportEdge(m_Simplex);
// 
// 			// ���� ����� ���� �븻 ���͸� ���⺤�ͷ� ��� ����Ʈ ����Ʈ�� ���Ѵ�.
// 			Vector2D p = GetSupportPoint(A, B, edge.normal);
// 
// 			// ����Ʈ ����Ʈ�� �븻���Ϳ� �����ؼ� �Ÿ��� ���Ѵ�.
// 			float dist = p.Dot(edge.normal);
// 
// 			if (dist < 0.01f)
// 			{
// 				manifold.Clear();
// 				manifold.A = A->pRigidBody;
// 				manifold.B = B->pRigidBody;
// 				manifold.normalVector = edge.normal;
// 				manifold.depth = edge.dist;
// 				return (edge.normal * (edge.dist + 0.001f));
// 			}
// 
// 			// ����Ʈ ����Ʈ�� �븻���Ϳ� ������ ����
// 			// ã�� ���� ������ �����ϴٸ�?
// 			if ((dist - edge.dist) < 0.01f)
// 			{
// 				// �ݺ� �浹�� �����ϱ� ���� ���� ���� ���� ���ؼ� ��ȯ
// 				/// ���ʹ� �������� ��� ������ ��� ���� ���� ���������� �𸥴�.
// 				manifold.Clear();
// 				manifold.normalVector = edge.normal;
// 				manifold.depth = edge.dist;
// 				return (edge.normal * (edge.dist + 0.001f));
// 			}
// 			else
// 			{
// 				// ã�� ���� ���÷����� �ְ� �ٽ� Ž��
// 				m_Simplex.insert(m_Simplex.begin() + edge.index, p);
// 				i++;
// 			}
// 		}
// 
// 		return Vector2D(0, 0);

			return;
		}

		/// <summary>
		/// �� �ݶ��̴��� ��������Ű ������ ���� ������ ����Ʈ ����Ʈ�� ����
		/// </summary>
		Vector3D CollisionSystem::FindSupportPoint(Collider* _colliderA, Collider* _colliderB, const Vector3D& _direction)
		{
			return _colliderA->FindFarthestPoint(_direction) - _colliderB->FindFarthestPoint(-_direction);
		}

		std::pair<Edge*, float> CollisionSystem::FindClosestEdge(Simplex* _simplex)
		{
			return std::pair<Edge*, float>();
		}

		std::pair<Face*, float> CollisionSystem::FindClosestFace(Simplex* _simplex)
		{
			return std::pair<Face*, float>();
		}

		/// <summary>
		/// �������� ã�Ƴ�
		/// 
		/// �ִ� 6������ ���� �� ����
		/// �ﰢ�������� �浹�� �����ϰ� ����.
		/// </summary>
		void CollisionSystem::FindContactPoint(Manifold* _manifold, const Vector3D& _direction)
		{
			Vector3D direction = _direction;

			// �浹�� ������ ���� ã�Ƴ�
			Face A = _manifold->GetColliderA()->FindSupportFace(_direction);
			Face B = _manifold->GetColliderA()->FindSupportFace(-_direction);

			Face* reference = &A;
			Face* incident = &B;

			float aPerpendicular = std::fabs(reference->normal.Dot(_direction));
			float bPerpendicular = std::fabs(incident->normal.Dot(_direction));

			// 0�� ���� ����� ���� ���ظ����� ����
			if (aPerpendicular > bPerpendicular)
			{
				Face* temp = reference;
				reference = incident;
				incident = reference;
				direction = -direction;
			}
			
			// ���̽��� �븻 ���Ϳ� ���� ���͸� �����ؼ� ���� ������ ���� ���͸� ���س�
			// incident ���� ������ ���ؼ� �Ѵ� ģ������ �߶󳻱� ������.
			for (auto& edge : reference->edge)
			{
				FaceClip(*incident, edge, reference->normal);
				// FaceClip(*incident, reference->edge[0], reference->normal);
				// FaceClip(*incident, reference->edge[1], reference->normal);
				// FaceClip(*incident, reference->edge[2], reference->normal);
			}

			Vector3D contactPoint;
			size_t count{};

			for (auto& e : incident->edge)
			{
				if (e.GetLengthSquare() <= Epsilon)
				{
					++count;
					contactPoint = e.vectorA;
				}
				else
				{
					++count;
					++count;
					contactPoint = e.vectorA + e.vectorB;
				}
			}

			contactPoint /= count;

			delete reference;
			delete incident;
		}

		/// <summary>
		/// ���÷������� �� ������ ���� �Լ��� ȣ������
		/// </summary>
		bool CollisionSystem::DoSimplex(Simplex& _simplex, Vector3D& _direction)
		{
			switch (_simplex.size())
			{
				case LINE:
				{
					return DoSimplex2(_simplex, _direction);
				}
				break;

				case TRIANGLE:
				{
					return DoSimplex3(_simplex, _direction);
				}
				break;

				case TETRAHEDRON:
				{
					return DoSimplex4(_simplex, _direction);
				}
				break;
			}
			return false;
		}

		/// <summary>
		/// ����
		/// </summary>
		bool CollisionSystem::DoSimplex2(Simplex& _simplex, Vector3D& _direction)
		{
			Vector3D A = _simplex[0];
			Vector3D B = _simplex[1];
			Vector3D BA = (A - B).Normalized();
			Vector3D BO = -B.Normalized();

			// ����Ʈ ����Ʈ���� ���� �׾�� ������ ������ ���غ���.
			// ���а� ������ ���� ���Ͱ� �̷�� ���� 90�� ���� �۴ٸ�
			// ������ �����ϴ� ���÷����� ���� ���ɼ��� �ֱ� ������
			// ���� ������ �������� ����Ʈ ����Ʈ�� ã�´�.
			if (BA.Dot(BO) > 0.f)
			{
				_direction = BA.Cross(BO).Cross(BA).Normalized();
			}
			else
			{
				_simplex = { B };
				_direction = BO;
			}

			return false;
		}

		/// <summary>
		/// �ﰢ��
		/// </summary>
		bool CollisionSystem::DoSimplex3(Simplex& _simplex, Vector3D& _direction)
		{
			Vector3D A = _simplex[0];
			Vector3D B = _simplex[1];
			Vector3D C = _simplex[2];
			Vector3D CA = (A - C).Normalized();
			Vector3D CB = (B - C).Normalized();
			Vector3D CO = -C.Normalized();
			Vector3D CAB = CA.Cross(CB).Normalized();
			
			// ABC �ﰢ���� �븻 ���͸� ���ϰ�
			// �ﰢ�� ��� ���⿡ ������ �ִ��� �Ǵ�.

			// CB ������ ������ �����ϴ��� üũ
			if (CAB.Cross(CB).Normalized().Dot(CO) > 0.f)
			{
				// CB ������ ������ �����Ѵٸ�
				// ��� ���� �ٽ� �������.
				// DoSimplex2�� ����� �ൿ
				if (CB.Dot(CO) > 0.f)
				{
					// CB �������� �ٽ� Ž��
					_simplex = { B, C };
					_direction = CB.Cross(CO).Cross(CB).Normalized();
				}
				else
				{
					// CA �������� �ٽ� Ž��
					_simplex = { A, C };
					return DoSimplex2(_simplex, CO);
// 					// DoSimplex2�� ����� �ൿ
// 					// CA�� ������ ������ �Ǵ�
// 					if (CA.Dot(CO) > 0.f)
// 					{
// 						_simplex = { B, C };
// 						_direction = CA.Cross(CO).Cross(CA);
// 					}
// 
// 					// �������� ã�� ���� �ְ� �ٽ� DoSimplex...
// 					else
// 					{
// 						_simplex = { C };
// 						_direction = CO;
// 					}
				}
			}
			else
			{
				// CA ������ ������ �����ϴ��� üũ
				if (CA.Cross(CAB).Normalized().Dot(CO) > 0.f)
				{
					// CA ������ ������ �����Ѵٸ�
					// ��� ���� �ٽ� �������.
					_simplex = { A, C };
					return DoSimplex2(_simplex, CO);
// 					// DoSimplex2�� ����� �ൿ
// 					// CA�� ������ ���踦 �Ǵ�
// 					if (CA.Dot(CO) > 0.f)
// 					{
// 						_simplex = { A, C };
// 						_direction = CA.Cross(CO).Cross(CA);
// 					}
// 					else
// 					{
// 						_simplex = { C };
// 						_direction = CO;
// 					}
				}
				
				// CA, CB ������ ������ �������� �ʴ´ٸ�
				else
				{
					// �� CAB �븻 ���⿡ ������ �����ϴ°�?
					if (CAB.Dot(CO) > 0.f)
					{
						// CBA �븻 �������� �� D�� Ž��
						_simplex = { A, B, C };
						_direction = CAB;
					}
					else
					{
						// CBA ���� �ȿ� ������ ������
						// ������ �ݴ��
						// CBA -�븻 �������� �� D�� Ž��
						_simplex = { B, A, C };
						_direction = -CAB;
					}
				}
			}
			return false;
		}

		/// <summary>
		/// ���ü
		/// </summary>
		bool CollisionSystem::DoSimplex4(Simplex& _simplex, Vector3D& _direction)
		{
			Vector3D A{ _simplex[0] };
			Vector3D B{ _simplex[1] };
			Vector3D C{ _simplex[2] };
			Vector3D D{ _simplex[3] };
			Vector3D DA{ (A - D).Normalized() };
			Vector3D DB{ (B - D).Normalized() };
			Vector3D DC{ (C - D).Normalized() };
			Vector3D DAB{ DA.Cross(DB).Normalized() };
			Vector3D DCA{ DC.Cross(DA).Normalized() };
			Vector3D DBC{ DB.Cross(DC).Normalized() };
			Vector3D DO{ -D.Normalized() };

			// ���ü�� �̷�� �� ���� �븻 ���Ϳ�
			// ������ �������� ���ü�� ������ �����ϰ� �ִ����� �Ǵ���.
			if (DAB.Dot(DO) > 0.f)
			{
				// �븻 ���⿡ ������ �����Ѵٸ�...
				// DAB �����ȿ� ������ ����
				// �ش� ���� 
				_simplex = { A, B, D };
				_direction = DO;
				return false;
			}

			if (DCA.Dot(DO) > 0.f)
			{
				_simplex = { A, C, D };
				_direction = DO;
				return false;
			}

			if (DBC.Dot(DO) > 0.f)
			{
				_simplex = { B, C, D };
				_direction = DO;
				return false;
			}

			return true;
		}

		void CollisionSystem::FaceClip(Face& _incident, const Edge& _refEdge, const Vector3D& _refNormal)
		{
			for (auto& edge : _incident.edge)
			{
				EdgeClip(edge, _refEdge.vectorA, _refEdge.normal, false);
				EdgeClip(edge, _refEdge.vectorA, -_refNormal, true);
			}
		}

		void CollisionSystem::EdgeClip(Edge& _edge, const Vector3D& _point, const Vector3D& _direction, bool _remove)
		{
			float dA = (_edge.vectorA - _point).Dot(_direction);
			float dB = (_edge.vectorB - _point).Dot(_direction);

			Vector3D& _A = _edge.vectorA;
			Vector3D& _B = _edge.vectorB;

			// �븻 �������� �� �� ������ ��쿣 �ڸ��� ����
			if (dA <= 0.f && dB <= 0.f)
			{
				return;
			}

			// �븻 �������� �Ѵ� ����� ��쿣 �ٸ��� ó�� ����� ��...
			if (dA > 0.f && dB > 0.f)
			{
				// ���� �븻�� �߶󳻱� ������...
				_edge.vectorA = _A + (-_direction) * dA;
				_edge.vectorB = _B + (-_direction) * dB;

				// ���� ���� ���ͷ� �ٽ� �� �� �ڸ� �ʿ䰡 ������ ������

				return;
			}

			if (dA > 0.f)
			{
				if (_remove)
				{
					_edge.vectorA = _B;
				}
				else
				{
					_edge.vectorA = _A + (_B - _A) * ( dA / (std::fabs(dA) + std::fabs(dB)) );
				}
			}
			if (dB > 0.f)
			{
				if (_remove)
				{
					_edge.vectorB = _A;
				}
				else
				{
					_edge.vectorB = _B + (_A - _B) * ( dB / (std::fabs(dA) + std::fabs(dB)) );
				}
			}
		}

		void CollisionSystem::CollisionRespone(float)
		{
			// �ӷ� ������Ʈ
			// �浹 ����
			// ��ġ ������Ʈ
			// �о
			// �� �ʱ�ȭ


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
		}
	}
}

/*
* ����Ʈ ����Ʈ
*
������ ����Ʈ�� �ش� �������κ��� ���� �� ���� ã�� ���ε�
�ݶ��̴��� �� ������ŭ �����ؼ� ã�ƾ��Ѵٴ� ���� �ſ� ��ȿ�����ϵ� �;� ����� ���ݸ� �ٲ㺸��� �ߴ�.
�޸𸮴� ���� ��� �԰����� ���� �ε����� ������ Face�� �̸� ������ �صд�.
�븻 �������κ��� ���� �� Face�� ������ ã�´�. (Face�� ������ŭ Ž���� �� ���̴�.)
�� Face�� �̷�� �� �� �߿��� ���� �� ���� ã����
��� ���� Ž���ϴ� �ͺ��� �������� ������?
*/

/*
* ��������Ű ���� EPA
*
EPA�� ���ؼ� �Ѱ��� ������ �ϰ� �ִ� ���� �־�����
��õ�� ŷ������ �ٷ� ����־ ��� �ذ��� �� ���� ���� �Ͱ���.
*/

/*
* �浹���� ã��
*
�������� ������ �浹 ���� ã�� ���� �ſ� �߿��ϴ�.
���� �л굵 �׷��ϰ� ���͸��� ��ȭ�� ��ų �� �ֱ� �����̴�
(�̹��� ��ȸ�� �ȴٸ� Sleep�� �־���� �Ѵ�.)

EPA���� ���� �븻(����) ���ͷκ��� �� ������ Face�� �켱 ã�´�.
EPA���� ���� ���ʹ� Ư�� ���� �����̱� ������ ������ �ؼ� 1�� ���� ����� ���� ã���� �� ���̴�.
�浹�� ������ �˾����� ���� ħ���ߴ��� ������ �𸣱⿡ �װ��� �ذ��ϱ� ���ؼ�
������ ���� ���� ������Ʈ�� ħ�� ����(?) ������Ʈ�� �����Ͽ�
*/