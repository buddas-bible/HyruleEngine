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
							return;
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
							return;
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
							return;
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
			return;
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

		void CollisionSystem::CollisionCheck(Collider* _A, Collider* _B)
		{

		}
	}
}
