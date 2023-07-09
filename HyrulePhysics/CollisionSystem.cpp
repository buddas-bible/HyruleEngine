#include "CollisionSystem.h"

#include "HyruleMath.h"
#include <vector>

constexpr size_t GJK_MAX = 50;

namespace Hyrule
{
	namespace Physics
	{
		bool CollisionSystem::CollisionCheck(Collider* _A, Collider* _B, Manifold* _manifold)
		{
			// ������ ���� ����
			Vector3D direction{ Vector3D::Right() };
			Vector3D trash{};

			std::vector<Vector3D> simplex;

			size_t count = 0;

			while (count < GJK_MAX)
			{
				switch (simplex.size())
				{
					case 0:
					{
						// ����Ʈ ����Ʈ A�� ����
						Vector3D support; // = FindSupport(A, B, direction);
						// simplex.push_back(support);

						// ���� ���ͷκ��� ����Ʈ�� ���ߴµ� ���� ������ �ְ� ������ �浹 ����.
						if (support.Dot(direction) < 0)
						{
							return false;
						}

						direction = -direction;
					}
					break;

					case 1:
					{
						// ����Ʈ ����Ʈ B�� ����
						Vector3D OA = simplex[0].Normalized();
						Vector3D AO = -OA;
						// Vector3D support = FindSupport(A, B, direction);
						// simplex.push_back(support);

						Vector3D OB = simplex[1].Normalized();

						// ����Ʈ ����Ʈ B�� ���� �ʸӿ� ���� ������ �浹���� ����
						if (OB.Dot(AO) < 0)
						{
							return false;
						}
					}
					break;

					// ��
					case 2:
					{
						// ������ ���� ���� ���͸� ���ϱ� ���ؼ� ���߰��� ��
						Vector3D AB = simplex[1] - simplex[0];
						Vector3D AO = -simplex[0];
						direction = AB.Cross(AO).Cross(AB).Normalized();

						// AB ���� ������ ���� ���
						// if (directionVec == Vector3D::Zero())
						// {
						// 	directionVec = Vector3D(-AB.y, AB.x, 0.f).Normalized();
						// }

						// ����Ʈ ����Ʈ C�� ����
						// Vector3D support = FindSupport(A, B, direction);
						// simplex.push_back(support);

						Vector3D OC = simplex[2].Normalized();

						// ����Ʈ ����Ʈ C�� ���� �ʸӿ� ���� ������ �浹���� ����
						if (OC.Dot(direction) <= 0)
						{
							// collided = false;
							return false;
						}
					}
					break;

					// �ﰢ��
					case 3:
					{
						// ���� �ߺ��ȴٸ� ����
						if (
							(simplex[0] == simplex[1]) || 
							(simplex[0] == simplex[2]) || 
							(simplex[0] == simplex[3]) || 
							(simplex[1] == simplex[2]) ||
							(simplex[1] == simplex[3]) ||
							(simplex[2] == simplex[3]))
						{
							// collided = false;
							return false;
						}

						Vector3D CA{ simplex[0] - simplex[2] };
						Vector3D CB{ simplex[1] - simplex[2] };
						Vector3D CO{ -simplex[2].Normalized() };

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
							// collided = true;
							return true;
						}

						if (nBC.Dot(CO) > 0)
						{
							// BC ���� �ȿ� ������ ������.
							direction = nBC;

							trash = simplex[0];
							// �� A ���� �� �迭�� ���
							simplex.erase(simplex.begin() + 0);
							count++;
							break;
						}
						else if (nAC.Dot(CO) > 0)
						{
							// AC ���� �ȿ� ������ ������.
							direction = nAC;

							trash = simplex[1];
							// �� B ���� �� �迭�� ���
							simplex.erase(simplex.begin() + 1);
							count++;
							break;
						}
					}
					break;

					// ���ü
					case 4:
					{
						// ���ü ���ο� ���� �ִ°� �Ǵ�.

						// ���ü ���ο� ���ٸ� ������ ã��
						// 


					}
					break;

					default:
						break;
				}
			}

			// collided = false;
			return false;
		}

		Manifold* CollisionSystem::ComputePenetrationDepth(Collider*, Collider*, Simplex*)
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

		void CollisionSystem::GetSupportPoint(Collider*, Collider*, const Vector3D&)
		{

		}

		void CollisionSystem::GetSupportEdge(Simplex*)
		{

		}

		void CollisionSystem::GetSupportFace()
		{

		}

		void CollisionSystem::FindContactPoint(Collider*, Collider*)
		{

		}

		/*
		3D GJK �޸�
		2D������ �ﰢ���� ����鼭 ������ �����ϰ� �ִ����� �Ǵ��ߴٸ�
		3D������ ���ü�� ����鼭 ������ �����ϰ� �ִ����� �Ǵ��ؾ� �Ѵ�.

		ù ���� ���ͷ� ����Ʈ A�� �ݴ� �������� ����Ʈ B�� ã��
		OA ���Ϳ� AB ���ͷ� B�� �̷�� ������ 90���� �Ѵ°��� ���� �ʸӿ� �ִ��� �Ǵ��Ѵ�.
		(���� �ʸӿ� ������ �浹 ���� ����)

		AB

		
		*/

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