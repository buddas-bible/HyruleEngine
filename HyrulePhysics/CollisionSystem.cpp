#include "CollisionSystem.h"

#include <vector>
#include <set>
#include "HyruleMath.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Face.h"
#include "Edge.h"

constexpr size_t GJK_MAX = 50;
constexpr size_t EPA_MAX = 50;

namespace Hyrule
{
	namespace Physics
	{
		/// <summary>
		/// Casey's GJK
		/// </summary>
		bool CollisionSystem::GJKCollisionDetection(Collider* _colliderA, Collider* _colliderB, Manifold& _manifold)
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
					// detectionInfo.insert(std::make_pair(_manifold, simplex));
					_manifold.SetSimplex(simplex);
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
		void CollisionSystem::EPAComputePenetrationDepth(Manifold& _manifold)
		{
			// ���÷����� ���� �ϴ� ������
			Simplex polytope{ _manifold.GetSimplex() };
			polytope.SetFace();

			size_t count{};

			while (count < EPA_MAX && polytope.faceMap.size() < 64)
			{
				// ������ �븻�� �Ÿ��� ����� �� ����.
 				Vector3D normal{ polytope.faceMap.begin()->second.normal };
				Vector3D support{ FindSupportPoint(
					_manifold.GetColliderA(),
					_manifold.GetColliderB(),
					normal) 
				};

				float faceDist{ polytope.faceMap.begin()->first };
				float supportDist{ support.Dot(normal) };

				auto itr = 
					std::find(
					polytope.points.begin(), 
					polytope.points.end(),
					support
					);

				if (itr != polytope.points.end())
				{
					float depth{ faceDist };
					Vector3D detectNormal{ normal };
					return;
				}
				
				// ���� dist�� ���ؼ� ���� ª�� ��� ����Ʈ ����Ʈ�� �Ÿ��� ����
				if (std::fabs(supportDist - faceDist) <= Epsilon)
				{
					// �����ϸ� �ش� ���̿� �븻�� ��ȯ
					float depth{ faceDist };
					Vector3D detectNormal{ normal };
					_manifold.SetDepth(depth + Epsilon);
					_manifold.SetNormal(detectNormal);
					return;
				}
				else
				{
					std::list<Edge> edges;

					// ���� ����Ʈ ����Ʈ�� ���ϸ鼭 Ȯ�� ���ɼ��� ����.
					for (auto itr = polytope.faceMap.begin(); itr != polytope.faceMap.end(); itr++)
					{
						float faceDist = itr->first;
						Face f = itr->second;

						float supportDist = f.normal.Dot(support);

						// ����Ʈ ����Ʈ �Ÿ� - �� �Ÿ� > ������������ ũ�ٸ� Ȯ�� ���ɼ��� ����.
						if (f.normal.Dot(support.Normalized()) > 0.f)
						{
							itr = polytope.faceMap.erase(itr);

							// ��ġ�� ���� �ִٸ� �� �� �̻��� ���ӵ� ���̱� ������ ���� ��.
							for (auto& edge : f.edge)
							{
								auto fIter = std::find(edges.begin(), edges.end(), edge);
							
								if (fIter != edges.end())
								{
									edges.erase(fIter);
								}
								else
								{
									edges.push_back(edge);
								}
							}
						}

						if (itr == polytope.faceMap.end())
						{
							break;
						}
					}

					polytope.push_back(support);

					for (auto& edge : edges)
					{
						polytope.AddFace(edge.index1, edge.index2, polytope.size() - 1);
					}
				}
				count++;
			}

			float depth{ polytope.faceMap.begin()->first };
			Vector3D detectNormal{ polytope.faceMap.begin()->second.normal };
			return;
		}

		/// <summary>
		/// �� �ݶ��̴��� ��������Ű ������ ���� ������ ����Ʈ ����Ʈ�� ����
		/// </summary>
		Vector3D CollisionSystem::FindSupportPoint(Collider* _colliderA, Collider* _colliderB, const Vector3D& _direction)
		{
			return _colliderA->FindFarthestPoint(_direction) - _colliderB->FindFarthestPoint(-_direction);
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
			Vector3D CBA = CB.Cross(CA).Normalized();
			
			// ABC �ﰢ���� �븻 ���͸� ���ϰ�
			// �ﰢ�� ��� ���⿡ ������ �ִ��� �Ǵ�.

			// CA ������ ������ �����ϴ��� üũ
			if ((CBA.Cross(CA).Normalized()).Dot(CO) > 0.f)
			{
				// CA ������ ������ �����Ѵٸ�
				// ��� ���� �ٽ� �������.
				// DoSimplex2�� ����� �ൿ
				if (CA.Dot(CO) > 0.f)
				{
					// CA �������� �ٽ� Ž��
					_simplex = { A, C };
					_direction = CA.Cross(CO).Cross(CA).Normalized();
				}
				else
				{
					// CB �������� �ٽ� Ž��
					_simplex = { B, C };
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
				// CB ������ ������ �����ϴ��� üũ
				if ((CB.Cross(CBA).Normalized()).Dot(CO) > 0.f)
				{
					// CB ������ ������ �����Ѵٸ�
					// ��� ���� �ٽ� �������.
					_simplex = { B, C };
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
					// �� CBA �븻 ���⿡ ������ �����ϴ°�?
					if (CBA.Dot(CO) > 0.f)
					{
						// CBA �븻 �������� �� D�� Ž��
						_simplex = { A, B, C };
						_direction = CBA;
					}
					else
					{
						// CBA ���� �ȿ� ������ ������
						// ������ �ݴ��
						// CBA -�븻 �������� �� D�� Ž��
						_simplex = { B, A, C };
						_direction = -CBA;
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
			Vector3D DBA{ DB.Cross(DA).Normalized() };
			Vector3D DAC{ DA.Cross(DC).Normalized() };
			Vector3D DCB{ DC.Cross(DB).Normalized() };
			Vector3D DO{ -D.Normalized() };

			// ���ü�� �̷�� �� ���� �븻 ���Ϳ�
			// ������ �������� ���ü�� ������ �����ϰ� �ִ����� �Ǵ���.
			if (DBA.Dot(DO) > 0.f)
			{
				// �븻 ���⿡ ������ �����Ѵٸ�...
				// DAB �����ȿ� ������ ����
				_simplex = { A, B, D };
				_direction = DBA;
				return false;
			}

			if (DAC.Dot(DO) > 0.f)
			{
				_simplex = { A, C, D };
				_direction = DAC;
				return false;
			}

			if (DCB.Dot(DO) > 0.f)
			{
				_simplex = { B, C, D };
				_direction = DCB;
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

		void CollisionSystem::ComputeImpulse(Manifold& _manifold)
		{
			// �� ��ü���� ������ �ִ� �ӷ����� ��ݷ��� �����

			RigidBody* A{ _manifold.GetColliderA()->GetRigidBody() };
			RigidBody* B{ _manifold.GetColliderB()->GetRigidBody() };

			float systemMass{ A->GetInvMass() + B->GetInvMass() };

			if (systemMass <= Epsilon)
			{
				return;
			}

			float sfriction = ComputeFriction(A->GetStaticFriction(), B->GetStaticFriction());
			float dfriction = ComputeFriction(A->GetDynamicFriction(), B->GetDynamicFriction());
			float restitution = A->GetRestitution() < B->GetRestitution() ? B->GetRestitution() : A->GetRestitution();

			for (size_t i = 0; i < _manifold.GetContactPoints().size(); i++)
			{
				/// ���޽� ��� ���� ��
				// ���� �߽ɿ��� �浹 ���������� ����
				Vector3D r_1 = _manifold.GetContactPoints()[i]/* - A->GetPosition()*/;
				Vector3D r_2 = _manifold.GetContactPoints()[i]/* - B->GetPosition()*/;

				// ���ӵ�
				Vector3D v_p1 = A->GetVelocity() + A->GetAngularVelocity().Cross(r_1);
				Vector3D v_p2 = B->GetVelocity() + B->GetAngularVelocity().Cross(r_2);
				Vector3D v_r = v_p2 - v_p1;

				// �浹 �������� �븻 ���������� ��� �ӵ�
				float contactVelocity = v_r.Dot(_manifold.GetNormal());

				if (contactVelocity > 0.f)
				{
					return;
				}

				/// ���޽� ������ �и� �κ�.
				Vector3D inertiaA = (r_1.Cross(_manifold.GetNormal()) * A->GetInvInertia()).Cross(r_1);
				Vector3D inertiaB = (r_2.Cross(_manifold.GetNormal()) * B->GetInvInertia()).Cross(r_2);
				float numerator = systemMass + (inertiaA + inertiaB).Dot(_manifold.GetNormal());

				// ���޽� ũ��
				float j = -(1.f + restitution) * contactVelocity;
				j /= numerator;

				// ���޽� ����
				Vector3D impulse = _manifold.GetNormal() * j;
				A->ApplyImpulse(-impulse, r_1);
				B->ApplyImpulse(impulse, r_2);


				/// ���޽� ��� ���� ��
				// ���� ���޽� ����.
				// �� ������ contactVelocity != 0 �� �� ����Ǵ� ����
				Vector3D tangent = v_r - (_manifold.GetNormal() * contactVelocity);

				if (tangent == Vector3D::Zero())
				{
					return;
				}

				tangent.Normalize();

				// ���޽� ũ��
				// contactVelocity�� ���ߴ� v_r Dot normal�� ��������� ������ ���� ���� �ٸ�.
				float j_t = -v_r.Dot(tangent);

				// ����� �Ǵ� ���� ���޽� ũ�⸦ ���ϴ°Ÿ�
				j_t /= numerator;

				//���޽� ����
				Vector3D frictionImpulse;

				// ������ = �����׷� * �������
				// ���� ���� ���� �������� �Ѿ�ٸ� ���� ���������� �����
				// m * Dot (v_r, t) <= j_s 
				if (std::abs(j_t) < j * sfriction)
				{
					// j_f = - (m * Dot(v_r, t) * t 
					frictionImpulse = tangent * j_t;
				}
				else
				{
					// j_f = - j_d * t
					frictionImpulse = tangent * -j * dfriction;
				}

				A->ApplyImpulse(-frictionImpulse, r_1);
				B->ApplyImpulse(frictionImpulse, r_2);
			}
		}

		void CollisionSystem::ResolveCollision(Manifold& _manifold)
		{
			RigidBody* A{ _manifold.GetColliderA()->GetRigidBody() };
			RigidBody* B{ _manifold.GetColliderB()->GetRigidBody() };
			
			float invMass{ A->GetInvMass() + B->GetInvMass() };

			if (invMass <= Epsilon)
			{
				return;
			}

			Vector3D resolve;
			float dist;
			
			if ((_manifold.GetDepth() - 0.05f) > Epsilon)
			{
				dist = _manifold.GetDepth() - 0.05f;
			}
			else
			{
				dist = 0.f;
			}

			resolve = _manifold.GetNormal() * dist / invMass;

			Vector3D Adist = -resolve * A->GetInvMass();
			Vector3D Bdist = resolve * B->GetInvMass();
		}

		float CollisionSystem::ComputeFriction(float _a, float _b)
		{
			return std::powf(_a * _b, 0.5f);
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