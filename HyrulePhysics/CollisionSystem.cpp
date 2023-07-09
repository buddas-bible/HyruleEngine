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
			// 임의의 방향 벡터
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
						// 서포트 포인트 A를 구함
						Vector3D support; // = FindSupport(A, B, direction);
						// simplex.push_back(support);

						// 방향 벡터로부터 서포트를 구했는데 완전 엉뚱한 애가 나오면 충돌 안함.
						if (support.Dot(direction) < 0)
						{
							return false;
						}

						direction = -direction;
					}
					break;

					case 1:
					{
						// 서포트 포인트 B를 구함
						Vector3D OA = simplex[0].Normalized();
						Vector3D AO = -OA;
						// Vector3D support = FindSupport(A, B, direction);
						// simplex.push_back(support);

						Vector3D OB = simplex[1].Normalized();

						// 서포트 포인트 B가 원점 너머에 있지 않으면 충돌하지 않음
						if (OB.Dot(AO) < 0)
						{
							return false;
						}
					}
					break;

					// 선
					case 2:
					{
						// 원점을 향한 방향 벡터를 구하기 위해서 삼중곱을 함
						Vector3D AB = simplex[1] - simplex[0];
						Vector3D AO = -simplex[0];
						direction = AB.Cross(AO).Cross(AB).Normalized();

						// AB 위에 원점이 있을 경우
						// if (directionVec == Vector3D::Zero())
						// {
						// 	directionVec = Vector3D(-AB.y, AB.x, 0.f).Normalized();
						// }

						// 서포트 포인트 C를 구함
						// Vector3D support = FindSupport(A, B, direction);
						// simplex.push_back(support);

						Vector3D OC = simplex[2].Normalized();

						// 서포트 포인트 C가 원점 너머에 있지 않으면 충돌하지 않음
						if (OC.Dot(direction) <= 0)
						{
							// collided = false;
							return false;
						}
					}
					break;

					// 삼각형
					case 3:
					{
						// 점이 중복된다면 리턴
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
							// collided = true;
							return true;
						}

						if (nBC.Dot(CO) > 0)
						{
							// BC 영역 안에 원점이 존재함.
							direction = nBC;

							trash = simplex[0];
							// 점 A 삭제 및 배열을 당김
							simplex.erase(simplex.begin() + 0);
							count++;
							break;
						}
						else if (nAC.Dot(CO) > 0)
						{
							// AC 영역 안에 원점이 존재함.
							direction = nAC;

							trash = simplex[1];
							// 점 B 삭제 및 배열을 당김
							simplex.erase(simplex.begin() + 1);
							count++;
							break;
						}
					}
					break;

					// 사면체
					case 4:
					{
						// 사면체 내부에 점이 있는가 판단.

						// 사면체 내부에 없다면 방향을 찾고
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
// 			// 가까운 변을 찾는다.
// 			MinkowskiEdge edge = GetSupportEdge(m_Simplex);
// 
// 			// 가장 가까운 변의 노말 벡터를 방향벡터로 삼아 서포트 포인트를 구한다.
// 			Vector2D p = GetSupportPoint(A, B, edge.normal);
// 
// 			// 서포트 포인트를 노말벡터에 투영해서 거리를 구한다.
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
// 			// 서포트 포인트를 노말벡터에 투영한 값이
// 			// 찾은 변의 정보와 유사하다면?
// 			if ((dist - edge.dist) < 0.01f)
// 			{
// 				// 반복 충돌을 방지하기 위해 아주 작은 값은 더해서 반환
// 				/// 벡터는 구했지만 어느 점에서 어느 변을 향한 벡터인지는 모른다.
// 				manifold.Clear();
// 				manifold.normalVector = edge.normal;
// 				manifold.depth = edge.dist;
// 				return (edge.normal * (edge.dist + 0.001f));
// 			}
// 			else
// 			{
// 				// 찾은 점을 심플렉스에 넣고 다시 탐색
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
		3D GJK 메모
		2D에서는 삼각형을 만들면서 원점을 포함하고 있는지를 판단했다면
		3D에서는 사면체를 만들면서 원점을 포함하고 있는지를 판단해야 한다.

		첫 방향 벡터로 서포트 A와 반대 방향으로 서포트 B를 찾고
		OA 벡터와 AB 벡터로 B가 이루는 각도가 90도가 넘는가로 원점 너머에 있는지 판단한다.
		(원점 너머에 없으면 충돌 하지 않음)

		AB

		
		*/

	}
}

/*
* 서포트 포인트
*
서포터 포인트는 해당 방향으로부터 가장 먼 점을 찾는 것인데
콜라이더의 점 개수만큼 내적해서 찾아야한다는 점이 매우 비효율적일듯 싶어 방법을 조금만 바꿔보기로 했다.
메모리는 조금 잡아 먹겠지만 점과 인덱스를 가지고 Face를 미리 연산을 해둔다.
노말 방향으로부터 가장 먼 Face의 중점을 찾는다. (Face의 개수만큼 탐색은 할 것이다.)
그 Face를 이루는 세 점 중에서 가장 먼 점을 찾으면
모든 점을 탐색하는 것보단 빨라지지 않을까?
*/

/*
* 민코프스키 차와 EPA
*
EPA에 대해서 한가지 착각을 하고 있던 점이 있었지만
초천재 킹범준이 바로 잡아주어서 어떻게 해결이 될 수도 있을 것같다.
*/

/*
* 충돌지점 찾기
*
물리에서 복수의 충돌 지점 찾는 것이 매우 중요하다.
힘의 분산도 그러하고 지터링을 완화를 시킬 수 있기 때문이다
(이번에 기회가 된다면 Sleep도 넣어보려고 한다.)

EPA에서 얻은 노말(방향) 벡터로부터 두 도형의 Face를 우선 찾는다.
EPA에서 얻은 벡터는 특정 면의 수직이기 때문에 내적을 해서 1에 가장 가까운 면을 찾으면 될 것이다.
충돌과 방향은 알았지만 누가 침투했는지 형상은 모르기에 그것을 해결하기 위해서
수직인 면을 가진 오브젝트가 침투 당한(?) 오브젝트라 생각하여
*/