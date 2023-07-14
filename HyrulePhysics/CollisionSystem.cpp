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

			// 임의의 방향 벡터로 
			Vector3D direction{ Vector3D::Right() };
			Vector3D support{ FindSupportPoint(_colliderA, _colliderB, direction) };

			simplex->push_back(support);
			direction = -support.Normalized();

			while (count < GJK_MAX)
			{
				// 방향 벡터로부터 서포트 포인터를 구하는건 공통임
				support = FindSupportPoint(_colliderA, _colliderB, direction);
				Vector3D OP = support.Normalized();

				// 서포트 포인트와 방향벡터의 각도가 90도 이상이면 그냥 충돌 안하는 거임
				// (해당 방향으로 원점을 넘는 점이 없기 때문에)
				// (원점을 포함하는 심플렉스를 만들 수가 없음)
				if (OP.Dot(direction) < 0.f)
				{
					return false;
				}

				// 서포트 포인터가 구해졌으면 심플렉스에 넣는다.
				simplex->push_back(support);

				if (DoSimplex(*simplex, direction))
				{
					// 심플렉스 안에 원점이 존재한다면 충돌함.
					return true;
				}

				count++;
			}
		}


		//		bool CollisionSystem::CollisionCheck2(Collider*, Collider*)
		//		{
		//			// 임의의 벡터를 방향 벡터 d로 삼아서
		//			// 두 콜라이더의 서포트 포인터를 구함.
		//			// a dot d < b dot -d 라는 결과가 나오면 충돌 안함
		//
		//			// 아니면 새로운 방향 벡터를 구함
		//			// 새로운 방향벡터는 d-2(r dot d)r
		//			// 여기서 r은 (b-a) / (b-a).length()
		//			// 
		//			// 새로 얻은 방향벡터로 다시 탐색을 시작함
		//			// GJK보다 2배 빠른 충돌 감지 알고리즘
		//		}

		Manifold* CollisionSystem::ComputePenetrationDepth(Collider* _colliderA, Collider* _colliderB, Simplex* _simplex)
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
			// // 충돌에 관여한 면을 찾아냄
			// Face* reference = _colliderA->FindSupportFace(_direction);
			// Face* incident = _colliderA->FindSupportFace(-_direction);
			// 
			// // Face* reference;
			// // Face* incident;
			// 
			// float aPerpendicular = std::fabs(reference->normal.Dot(_direction));
			// float bPerpendicular = std::fabs(incident->normal.Dot(_direction));
			// 
			// // 0에 제일 가까운 면을 기준면으로 삼음
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
		/// 선분
		/// </summary>
		bool CollisionSystem::DoSimplex2(Simplex& _simplex, Vector3D& _direction)
		{
			Vector3D A = _simplex[0];
			Vector3D B = _simplex[1];
			Vector3D BA = (A - B).Normalized();
			Vector3D BO = -B.Normalized();

			// 서포트 포인트끼리 선을 그어보고 원점과 각도를 비교해본다.
			// 선분과 원점을 향한 벡터가 이루는 각이 90도 보다 작다면
			// 원점을 포함하는 심플렉스를 만들 가능성이 있기 때문에
			// 그의 수직인 방향으로 서포트 포인트를 찾는다.
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
		/// 삼각형
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
			
			// ABC 삼각형의 노말 벡터를 구하고
			// 삼각형 어느 방향에 원점이 있는지 판단.

			// CB 공간에 원점이 존재하는지 체크
			if (CAB.Cross(CB).Dot(CO) > 0.f)
			{
				// CB 공간에 원점이 존재한다면
				// 비버 집을 다시 지어야함.
				// DoSimplex2와 비슷한 행동
				if (CB.Dot(CO) > 0.f)
				{
					// CB 공간에서 다시 탐색
					_simplex = { B, C };
					_direction = CB.Cross(CO).Cross(CB);
				}
				else
				{
					// CA 공간에서 다시 탐색
					_simplex = { A, C };
					return DoSimplex2(_simplex, CO);
// 					// DoSimplex2와 비슷한 행동
// 					// CA와 원점의 방향을 판단
// 					if (CA.Dot(CO) > 0.f)
// 					{
// 						_simplex = { B, C };
// 						_direction = CA.Cross(CO).Cross(CA);
// 					}
// 
// 					// 마지막에 찾은 점을 넣고 다시 DoSimplex...
// 					else
// 					{
// 						_simplex = { C };
// 						_direction = CO;
// 					}
				}
			}
			else
			{
				// CA 공간에 원점이 존재하는지 체크
				if (CA.Cross(CAB).Dot(CO) > 0.f)
				{
					// CA 공간에 원점이 존재한다면
					// 비버 집을 다시 지어야함.
					_simplex = { A, C };
					return DoSimplex2(_simplex, CO);
// 					// DoSimplex2와 비슷한 행동
// 					// CA와 원점의 관계를 판단
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
				
				// CA, CB 공간에 원점이 존재하지 않는다면
				else
				{
					// 면 CAB 노말 방향에 원점이 존재하는가?
					if (CAB.Dot(CO) > 0.f)
					{
						// CBA 노말 방향으로 점 D를 탐색
						_simplex = { A, B, C };
						_direction = CAB;
					}
					else
					{
						// CBA 공간 안에 원점은 있으나
						// 방향은 반대라서
						// CBA -노말 방향으로 점 D를 탐색
						_simplex = { B, A, C };
						_direction = -CAB;
					}
				}
			}
			return false;
		}

		/// <summary>
		/// 사면체
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

			// 사면체를 이루는 각 면의 노말 벡터와
			// 원점의 방향으로 사면체가 원점을 포함하고 있는지를 판단함.
			if (DAB.Dot(DO) > 0.f)
			{
				// 노말 방향에 원점이 존재한다면...
				// DAB 공간안에 원점이 있음
				// 해당 면의 
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