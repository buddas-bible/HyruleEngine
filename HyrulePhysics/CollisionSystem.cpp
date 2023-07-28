#include "CollisionSystem.h"

#include <vector>
#include <set>
#include "HyruleMath.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Face.h"
#include "Edge.h"

#include <iostream>

constexpr size_t GJK_MAX = 50;
constexpr size_t EPA_MAX = 50;

namespace Hyrule
{
	namespace Physics
	{
		/// <summary>
		/// Casey's GJK
		/// </summary>
		bool CollisionSystem::GJKCollisionDetection(Collider* _colliderA, Collider* _colliderB, Manifold* _manifold)
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
					break;
				}

				// ����Ʈ �����Ͱ� ���������� ���÷����� �ִ´�.
				simplex->push_back(support);

				if (DoSimplex(*simplex, direction))
				{
					// ���÷��� �ȿ� ������ �����Ѵٸ� �浹��.
					// detectionInfo.insert(std::make_pair(_manifold, simplex));
					_manifold->SetSimplex(simplex);
					return true;
				}

				if (direction == Vector3D::Zero())
				{
					break;
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
		void CollisionSystem::EPAComputePenetrationDepth(Manifold* _manifold)
		{
			// ���÷����� ���� �ϴ� ������
			Simplex polytope{ _manifold->GetSimplex() };
			polytope.SetFace();

			size_t count{};

			while (count < EPA_MAX)
			{
				// ������ �븻�� �Ÿ��� ����� �� ����.
 				Vector3D normal{ polytope.faceMap.begin()->second.normal };
				Vector3D support{ FindSupportPoint(
					_manifold->GetColliderA(),
					_manifold->GetColliderB(),
					normal) 
				};

				// ����� �Ÿ��� 0�� ���� �ִ�.
				// ������ ���������� �� ���� �ִٸ� ����� �Ÿ��� 0�� �� �� �ִ�.
				// ���� �� ���� �ִٸ� �Ÿ��� 0�� ���� 2���� ���� ���̴�.

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
					break;
				}

				// �븻�������� ����Ʈ ����Ʈ�� ã�Ҵµ�
				// �װ� �̹� ã�Ҵ� ���̶��
// 				if (polytope.faceMap.begin()->second.vec[0] == support ||
// 					polytope.faceMap.begin()->second.vec[1] == support ||
// 					polytope.faceMap.begin()->second.vec[2] == support)
// 				{
// 					break;
// 				}

				// �븻 �������� ����Ʈ ����Ʈ�� ã�Ҵµ� �Ÿ��� 0�� �����ٸ�...
				if (supportDist <= Epsilon)
				{
					break;
				}
				
				// ���� dist�� ���ؼ� ���� ª�� ��� ����Ʈ ����Ʈ�� �Ÿ��� ����
				if (std::fabs(supportDist - faceDist) <= Epsilon)
				{
					break;
				}

				std::list<Edge> edges;

				for (auto& e : polytope.faceMap.begin()->second.edge)
				{
					edges.push_back(e);
				}

				polytope.faceMap.erase(polytope.faceMap.begin());

				// ���� ����Ʈ ����Ʈ�� ���ϸ鼭 Ȯ�� ���ɼ��� ����.
				for (auto itr = polytope.faceMap.begin(); itr != polytope.faceMap.end(); itr++)
				{
					// float faceDist = itr->first;
					Face f = itr->second;

					// float supportDist = f.normal.Dot(support);

					float radian{ f.normal.Dot(support.Normalized()) };
						
					// ����Ʈ ����Ʈ�� ���̽� �븻�� ���� �����ΰ�?
					if (radian <= 0.f)
					{
						continue;
					}

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

					if (itr == polytope.faceMap.end())
					{
						break;
					}
				}

				if (edges.empty())
				{
					float depth{ polytope.faceMap.begin()->first };
					Vector3D detectNormal{ polytope.faceMap.begin()->second.normal };
					_manifold->SetDepth(depth + 0.0001f);
					_manifold->SetNormal(detectNormal);
					return;
				}

				polytope.push_back(support);

				for (auto& edge : edges)
				{
					polytope.AddFace(edge.index1, edge.index2, polytope.size() - 1);
				}

				count++;
			}

			float depth{ polytope.faceMap.begin()->first };
			Vector3D detectNormal{ polytope.faceMap.begin()->second.normal };
			_manifold->SetDepth(depth + 0.0001f );
			_manifold->SetNormal(detectNormal);
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
		void CollisionSystem::FindContactPoint(Manifold* _manifold)
		{
			Vector3D direction = _manifold->GetNormal();

			Collider* _cA{ _manifold->GetColliderA() };
			Collider* _cB{ _manifold->GetColliderB() };

			// �浹�� ������ ���� ã�Ƴ�
			Face A = _manifold->GetColliderA()->FindSupportFace(direction);
			Face B = _manifold->GetColliderB()->FindSupportFace(-direction);

			Face* reference = &A;
			Face* incident = &B;

			float aPerpendicular = std::fabs(reference->normal.Dot(direction));
			float bPerpendicular = std::fabs(incident->normal.Dot(direction));

			// 1�� ���� ����� ���� ���ظ����� ����
			if (aPerpendicular < bPerpendicular)
			{
				_manifold->SetColliderA(_cB);
				_manifold->SetColliderB(_cA);
				_manifold->SetNormal(-direction);
				reference = &B;
				incident = &A;
				direction = -direction;
			}
			
			// ���̽��� �븻 ���Ϳ� ���� ���͸� �����ؼ� ���� ������ ���� ���͸� ���س�
			// incident ���� ������ ���ؼ� �Ѵ� ģ������ �߶󳻱� ������.
			for (auto& edge : reference->edge)
			{
				for (auto i = 0; i < incident->vec.size(); i++)
				{
					auto j = (i + 1) % incident->vec.size();

					// ��� ģ������ �ٸ��� ó�� ����
					EdgeClip(incident->vec[i], incident->vec[j], edge.vectorA, edge.normal, false);
				}
			}

			// ���۷��� ���̽��� �븻 �������� �߶�
			for (auto i = 0; i < incident->vec.size(); i++)
			{
				auto j = (i + 1) % incident->vec.size();

				EdgeClip(incident->vec[i], incident->vec[j], reference->vec[0], -reference->normal, true);
			}

			for (auto i = 0; i < incident->vec.size(); i++)
			{
				auto itr = std::find(_manifold->GetContactPoints().begin(), _manifold->GetContactPoints().end(), incident->vec[i]);

				if (itr == _manifold->GetContactPoints().end())
				{
					_manifold->AddContactPoint(incident->vec[i]);
				}
			}
		}

		bool CollisionSystem::SphereToSphere(Collider* _colliderA, Collider* _colliderB, Manifold* _manifold)
		{
			Vector3D AB{ _colliderB->GetPosition() - _colliderA->GetPosition() };

			float total{ _colliderA->GetLength() + _colliderB->GetLength() };
			float gap{ AB.Length() };

			if (total >= gap)
			{
				_manifold->SetDepth(total - gap);
				_manifold->SetNormal(AB.Normalized());
				return true;
			}

			return false;
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
			float dot{ BA.Dot(BO) };

			if (dot > 0.f)
			{
				_direction = BA.Cross(BO).Cross(BA).Normalized();
			}
			else if (dot < 0.f)
			{
				_direction = Vector3D::Zero();
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
			Vector3D CBA = CB.Cross(CA).Normalized();
			Vector3D CO = -C.Normalized();

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
					_direction = CB.Cross(CO).Cross(CB).Normalized();
					// return DoSimplex2(_simplex, CO);
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
					_direction = CB.Cross(CO).Cross(CB).Normalized();
					// return DoSimplex2(_simplex, CO);
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

		void CollisionSystem::FaceClip(Face& _incident, const Edge& _refEdge, const Vector3D& _refFaceNormal)
		{
			// ������ �븻�� ���� ���̽��� �߶����.
			// ��� �߶󳻳�?
			// �����ִ� ģ���� �߶󳻰�, ��� ģ���� ���ְ� 
			for (auto i = 0; i < _incident.vec.size(); i++)
			{
				auto j = ( i + 1 ) % _incident.vec.size();

				// ��� ģ������ �ٸ��� ó�� ����
				EdgeClip(_incident.vec[i], _incident.vec[j], _refEdge.vectorA, _refEdge.normal, false);
			}

			// ���۷��� ���̽��� �븻 �������� �߶�
			for (auto i = 0; i < _incident.vec.size(); i++)
			{
				auto j = (i + 1) % _incident.vec.size();

				EdgeClip(_incident.vec[i], _incident.vec[j], _refEdge.vectorA, -_refFaceNormal, true);
			}
		}

		void CollisionSystem::EdgeClip(Vector3D& edgeA, Vector3D& edgeB, const Vector3D& _point, const Vector3D& _direction, bool _remove)
		{
			// ���۷��� ������ �� ���� Ŭ������ ������ �� ���� ���͸� ���ϰ�
			// �𷺼� ���Ϳ� �����ؼ� ���̸� ����
			float dA = (edgeA - _point).Dot(_direction);
			float dB = (edgeB - _point).Dot(_direction);

			Vector3D A{ edgeA };
			Vector3D B{ edgeB };

			// �븻 �������� ���̰� �� �� ������ ��쿣 �ڸ��� ����
			if (dA <= 0.f && dB <= 0.f)
			{
				return;
			}

			// �븻 �������� �Ѵ� ����� ��쿣 �ϴ� �ѱ���..
			if (!_remove && dA > 0.f && dB > 0.f)
			{

				// �ٸ� ó���� ���ٷ� ������
				// ���ؽ� ������ �̹� ������ ���̽� ������
				// �׳� ������� ������� ���� ó���ϱ�� ��.
				// ���� ���·δ� ���� ���ؽ��ε� �ٸ��� ó���ϴ� ��찡 ����ϱ�..

				return;
			}

			if (dA > 0.f)
			{
				if (_remove)
				{
					edgeA = B;
				}
				else
				{
					edgeA = A + (B - A) * ( dA / (std::fabs(dA) + std::fabs(dB)) );
				}
			}
			if (dB > 0.f)
			{
				if (_remove)
				{
					edgeB = A;
				}
				else
				{
					edgeB = B + (A - B) * ( dB / (std::fabs(dA) + std::fabs(dB)) );
				}
			}
		}

		void CollisionSystem::ComputeImpulse(Manifold* _manifold)
		{
			// �� ��ü���� ������ �ִ� �ӷ����� ��ݷ��� �����
			RigidBody* A{ _manifold->RigidBodyA() };
			RigidBody* B{ _manifold->RigidBodyB() };

			float systemMass{ A->GetInvMass() + B->GetInvMass() };

			if (systemMass <= Epsilon)
			{
				return;
			}

			float sfriction = ComputeFriction(A->GetStaticFriction(), B->GetStaticFriction());
			float dfriction = ComputeFriction(A->GetDynamicFriction(), B->GetDynamicFriction());
			float restitution = std::min(A->GetRestitution(), B->GetRestitution());

			Vector3D P_a{ _manifold->GetColliderA()->GetPosition() };
			Vector3D P_b{ _manifold->GetColliderB()->GetPosition() };

			Vector3D V_a{ A->GetVelocity() };
			Vector3D V_b{ B->GetVelocity() };

			Vector3D W_a{ A->GetAngularVelocity() };
			Vector3D W_b{ B->GetAngularVelocity() };

			Vector3D Normal{ _manifold->GetNormal() };

			const auto& contactPoints{ _manifold->GetContactPoints() };
			for (const auto& contactPoint : contactPoints)
			{							
				/// ���޽� ��� ���� ��
				// ���� �߽ɿ��� �浹 ���������� ����
				Vector3D r_1 = contactPoint - P_a;
				Vector3D r_2 = contactPoint - P_b;

				// ���ӵ�
				Vector3D v_p1 = V_a + W_a.Cross(r_1);
				Vector3D v_p2 = V_b + W_b.Cross(r_2);
				Vector3D v_r = v_p2 - v_p1;

				// �浹 �������� �븻 ���������� ��� �ӵ�
				float contactVelocity = v_r.Dot(Normal);

				if (contactVelocity > 0.f)
				{
					return;
				}

				Matrix3x3 inertiaTMA = A->GetInvInertia();
				Matrix3x3 inertiaTMB = B->GetInvInertia();

				/// ���޽� ������ �и� �κ�.
				Vector3D inertiaA = (r_1.Cross(Normal) * inertiaTMA).Cross(r_1);
				Vector3D inertiaB = (r_2.Cross(Normal) * inertiaTMB).Cross(r_2);
				float numerator = systemMass + (inertiaA + inertiaB).Dot(Normal);

				// ���޽� ũ��
				float j = -(1.f + restitution) * contactVelocity;
				j /= numerator;
				j /= (float)contactPoints.size();

				// ���޽� ����
				Vector3D impulse = Normal * j;
				A->ApplyImpulse(-impulse, r_1);
				B->ApplyImpulse(impulse, r_2);


				/// ���޽� ��� ���� ��
				// ���� ���޽� ����.
				// �� ������ contactVelocity != 0 �� �� ����Ǵ� ����
				Vector3D tangent = (v_r - (Normal * contactVelocity)).Normalized();

				// ���޽� ũ��
				// contactVelocity�� ���ߴ� v_r Dot normal�� ��������� ������ ���� ���� �ٸ�.
				float j_t = -v_r.Dot(tangent);
				j_t /= numerator;
				j_t /= (float)contactPoints.size();

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

		void CollisionSystem::ResolveCollision(Manifold* _manifold)
		{
			RigidBody* A{ _manifold->RigidBodyA() };
			RigidBody* B{ _manifold->RigidBodyB() };
			
			float InvMassA = (A == nullptr) ? 0.f : A->GetInvMass();
			float InvMassB = (B == nullptr) ? 0.f : B->GetInvMass();
			
			float systemMass{ InvMassA + InvMassB };

			if (systemMass <= Epsilon)
			{
				return;
			}

			float depth{ _manifold->GetDepth() };
			Vector3D normal{ _manifold->GetNormal() };
			
			float dist;
			Vector3D resolve;

			if ((depth - 0.01f) > Epsilon)
			{
				dist = depth - 0.01f;
			}
			else
			{
				dist = 0.f;
			}
			// dist = depth + 0.01f;

			resolve = normal * (dist / systemMass) * 0.5f;

			Vector3D Adist = -resolve * InvMassA;
			A->SetPosition(A->GetPosition() + Adist);

			Vector3D Bdist = resolve * InvMassB;
			B->SetPosition(B->GetPosition() + Bdist);
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