#include "CollisionSystem.h"

#include "HyruleMath.h"
#include <vector>
#include "Simplex.h"
#include "Collider.h"

constexpr size_t GJK_MAX = 50;

namespace Hyrule
{
	namespace Physics
	{
		/// <summary>
		/// Casey's GJK
		/// </summary>
		bool CollisionSystem::CollisionCheck(Collider* _colliderA, Collider* _colliderB)
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
					return false;
				}

				// ����Ʈ �����Ͱ� ���������� ���÷����� �ִ´�.
				simplex->push_back(support);

				if (DoSimplex(*simplex, direction))
				{
					// ���÷��� �ȿ� ������ �����Ѵٸ� �浹��.
					return true;
				}

				count++;
			}
		}


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

		Manifold* CollisionSystem::ComputePenetrationDepth(Collider* _colliderA, Collider* _colliderB, Simplex* _simplex)
		{
			
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
			return nullptr;
		}

		/// <summary>
		/// 
		/// </summary>
		Vector3D CollisionSystem::FindSupportPoint(Collider* _colliderA, Collider* _colliderB, const Vector3D& _direction)
		{
			return _colliderA->FindFarthestPoint(_direction) - _colliderB->FindFarthestPoint(-_direction);
		}

		void CollisionSystem::FindSupportEdge(Simplex* _simplex)
		{

		}

		void CollisionSystem::FindSupportFace()
		{

		}

		void CollisionSystem::FindContactPoint(Collider* _colliderA, Collider* _colliderB, const Vector3D& _direction)
		{
			// Vector3D direction = _direction;
			// 
			// // �浹�� ������ ���� ã�Ƴ�
			// Face* reference = _colliderA->FindSupportFace(_direction);
			// Face* incident = _colliderA->FindSupportFace(-_direction);
			// 
			// // Face* reference;
			// // Face* incident;
			// 
			// float aPerpendicular = std::fabs(reference->normal.Dot(_direction));
			// float bPerpendicular = std::fabs(incident->normal.Dot(_direction));
			// 
			// // 0�� ���� ����� ���� ���ظ����� ����
			// if (aPerpendicular > bPerpendicular)
			// {
			// 	auto temp = reference;
			// 	reference = incident;
			// 	incident = reference;
			// 	direction = -direction;
			// }

			// FaceClip(incident, );
			// FaceClip(incident, );
			// FaceClip(incident, );
		}

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
				_direction = BA.Cross(BO).Cross(BA);
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
			Vector3D CAB = CA.Cross(CB);
			
			// ABC �ﰢ���� �븻 ���͸� ���ϰ�
			// �ﰢ�� ��� ���⿡ ������ �ִ��� �Ǵ�.

			// CB ������ ������ �����ϴ��� üũ
			if (CAB.Cross(CB).Dot(CO) > 0.f)
			{
				// CB ������ ������ �����Ѵٸ�
				// ��� ���� �ٽ� �������.
				// DoSimplex2�� ����� �ൿ
				if (CB.Dot(CO) > 0.f)
				{
					// CB �������� �ٽ� Ž��
					_simplex = { B, C };
					_direction = CB.Cross(CO).Cross(CB);
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
				if (CA.Cross(CAB).Dot(CO) > 0.f)
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
			Vector3D DAB{ DA.Cross(DB) };
			Vector3D DCA{ DC.Cross(DA) };
			Vector3D DBC{ DB.Cross(DC) };
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