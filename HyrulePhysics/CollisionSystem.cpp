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
					delete simplex;
					return false;
				}

				// 서포트 포인터가 구해졌으면 심플렉스에 넣는다.
				simplex->push_back(support);

				if (DoSimplex(*simplex, direction))
				{
					// 심플렉스 안에 원점이 존재한다면 충돌함.
					Manifold* newManifold = new Manifold(_colliderA, _colliderB);

					detectionInfo.insert(std::make_pair(newManifold, simplex));
					return true;

				}
				count++;
			}

			delete simplex;
			return false;
		}

		//		Chung-Wang 분리 벡터 알고리즘
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

		/// <summary>
		/// EPA
		/// </summary>
		void CollisionSystem::EPAComputePenetrationDepth(Manifold* _manifold)
		{
			// 심플렉스의 면을 일단 구분함
			Simplex simplex{ *detectionInfo[_manifold] };
			simplex.SetFace();

			size_t count{};

			while (count < EPA_MAX)
			{
				// 면들과의 노말과 거리를 계산할 수 있음.
				Vector3D normal{ simplex.faceMap.begin()->second->normal };
				Vector3D support{ FindSupportPoint(
					_manifold->GetColliderA(),
					_manifold->GetColliderB(),
					normal) 
				};
				float dist{ simplex.faceMap.begin()->first };
				// 계산된 dist만 비교해서 가장 짧은 면과 서포트 포인트의 거리를 비교함
				if (std::fabs(dist - support.Dot(normal)) < Epsilon)
				{
					// 유사하면 해당 깊이와 노말만 반환
					_manifold->SetDepth(dist);
					_manifold->SetNormal(normal);
					return;
				}
				else
				{
					// 아니라면 심플렉스에 점을 추가하고
					simplex.push_back(support);
					size_t index[3]
					{
						simplex.faceMap.begin()->second->index[0],
						simplex.faceMap.begin()->second->index[1],
						simplex.faceMap.begin()->second->index[2],
					};
					simplex.faceMap.erase(simplex.faceMap.begin());

					// 면을 추가하고 각 면과 거리를 계산해둠.
					simplex.AddFace(index[0], index[1], simplex.points.size());
					simplex.AddFace(index[0], simplex.points.size(), index[2]);
					simplex.AddFace(index[1], index[2], simplex.points.size());
				}
			}
			return;
		}

		/// <summary>
		/// 두 콜라이더의 민코프스키 차에서 방향 벡터의 서포트 포인트를 구함
		/// </summary>
		Vector3D CollisionSystem::FindSupportPoint(Collider* _colliderA, Collider* _colliderB, const Vector3D& _direction)
		{
			return _colliderA->FindFarthestPoint(_direction) - _colliderB->FindFarthestPoint(-_direction);
		}

		// 		std::pair<Edge*, float> CollisionSystem::FindClosestEdge(Simplex* _simplex)
		// 		{
		// 			return std::pair<Edge*, float>();
		// 		}
		// 
		// 		std::tuple<Face*, float, std::list<size_t[3]>::iterator> CollisionSystem::FindClosestFace(Simplex* _simplex)
		// 		{
		// 			Face* closestFace{};
		// 			float mindist{ FLT_MAX };
		// 			std::list<size_t[3]>::iterator pos{};
		// 
		// 			for (auto itr = _simplex->index.begin(); itr != _simplex->index.end(); itr++ )
		// 			{
		// 				size_t i0{ (*itr)[0] };
		// 				size_t i1{ (*itr)[1] };
		// 				size_t i2{ (*itr)[2] };
		// 
		// 				Face* newFace = new Face((*_simplex)[i0], (*_simplex)[i1], (*_simplex)[i2], i0, i1, i2);
		// 				float dist{ (*_simplex)[i0].Dot(newFace->normal) };
		// 
		// 				if (mindist > dist)
		// 				{
		// 					mindist = dist;
		// 					delete closestFace;
		// 					closestFace = newFace;
		// 					pos = itr;
		// 				}
		// 				else
		// 				{
		// 					delete newFace;
		// 				}
		// 			}
		// 
		// 			return std::make_tuple(closestFace, mindist, pos);
		// 		}

		/// <summary>
		/// 접촉점을 찾아냄
		/// 
		/// 최대 6개까지 나올 수 있음
		/// 삼각형끼리의 충돌을 예상하고 만듬.
		/// </summary>
		void CollisionSystem::FindContactPoint(Manifold* _manifold, const Vector3D& _direction)
		{
			Vector3D direction = _direction;

			// 충돌에 관여한 면을 찾아냄
			Face A = _manifold->GetColliderA()->FindSupportFace(_direction);
			Face B = _manifold->GetColliderA()->FindSupportFace(-_direction);

			Face* reference = &A;
			Face* incident = &B;

			float aPerpendicular = std::fabs(reference->normal.Dot(_direction));
			float bPerpendicular = std::fabs(incident->normal.Dot(_direction));

			// 0에 제일 가까운 면을 기준면으로 삼음
			if (aPerpendicular > bPerpendicular)
			{
				Face* temp = reference;
				reference = incident;
				incident = reference;
				direction = -direction;
			}
			
			// 페이스의 노말 벡터와 변의 벡터를 외적해서 변과 수직인 방향 벡터를 구해냄
			// incident 면의 변들을 비교해서 넘는 친구들을 잘라내기 시작함.
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
		/// 심플렉스가에 점 개수를 보고 함수를 호출해줌
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
			Vector3D CBA = CB.Cross(CA).Normalized();
			
			// ABC 삼각형의 노말 벡터를 구하고
			// 삼각형 어느 방향에 원점이 있는지 판단.

			// CA 공간에 원점이 존재하는지 체크
			if (CBA.Cross(CA).Normalized().Dot(CO) > 0.f)
			{
				// CA 공간에 원점이 존재한다면
				// 비버 집을 다시 지어야함.
				// DoSimplex2와 비슷한 행동
				if (CA.Dot(CO) > 0.f)
				{
					// CA 공간에서 다시 탐색
					_simplex = { A, C };
					_direction = CA.Cross(CO).Cross(CA).Normalized();
				}
				else
				{
					// CB 공간에서 다시 탐색
					_simplex = { B, C };
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
				if (CB.Cross(CBA).Normalized().Dot(CO) > 0.f)
				{
					// CA 공간에 원점이 존재한다면
					// 비버 집을 다시 지어야함.
					_simplex = { B, C };
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
					// 면 CBA 노말 방향에 원점이 존재하는가?
					if (CBA.Dot(CO) > 0.f)
					{
						// CBA 노말 방향으로 점 D를 탐색
						_simplex = { A, B, C };
						_direction = CBA;
					}
					else
					{
						// CBA 공간 안에 원점은 있으나
						// 방향은 반대라서
						// CBA -노말 방향으로 점 D를 탐색
						_simplex = { B, A, C };
						_direction = -CBA;
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
			Vector3D DBA{ DB.Cross(DA).Normalized() };
			Vector3D DAC{ DA.Cross(DC).Normalized() };
			Vector3D DCB{ DC.Cross(DB).Normalized() };
			Vector3D DO{ -D.Normalized() };

			// 사면체를 이루는 각 면의 노말 벡터와
			// 원점의 방향으로 사면체가 원점을 포함하고 있는지를 판단함.
			if (DBA.Dot(DO) > 0.f)
			{
				// 노말 방향에 원점이 존재한다면...
				// DAB 공간안에 원점이 있음
				// 해당 면의 
				_simplex = { A, B, D };
				_direction = DO;
				return false;
			}

			if (DAC.Dot(DO) > 0.f)
			{
				_simplex = { A, C, D };
				_direction = DO;
				return false;
			}

			if (DCB.Dot(DO) > 0.f)
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

			// 노말 방향으로 둘 다 음수인 경우엔 자르지 않음
			if (dA <= 0.f && dB <= 0.f)
			{
				return;
			}

			// 노말 방향으로 둘다 양수인 경우엔 다르게 처리 해줘야 함...
			if (dA > 0.f && dB > 0.f)
			{
				// 변의 노말로 잘라내긴 했지만...
				_edge.vectorA = _A + (-_direction) * dA;
				_edge.vectorB = _B + (-_direction) * dB;

				// 변의 방향 벡터로 다시 한 번 자를 필요가 있을거 같은데

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
			// 속력 업데이트
			ComputeVelocity();
			// 충돌 대응
			ComputeImpulse();
			// 위치 업데이트
			ComputePosition();
			// 밀어냄
			ResolveCollision();
			// 힘 초기화

		}

		void CollisionSystem::ComputeVelocity()
		{

		}

		void CollisionSystem::ComputeImpulse()
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
		}

		void CollisionSystem::ComputePosition()
		{

		}


		void CollisionSystem::ResolveCollision()
		{

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