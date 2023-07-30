#include "CollisionSystem.h"

#include <vector>
#include <set>
#include "HyruleMath.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Face.h"
#include "Edge.h"
#include "Object.h"

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
				float dot{ OP.Dot(direction) };
				if (dot < 0.f)
				{
					break;
				}

				// 서포트 포인터가 구해졌으면 심플렉스에 넣는다.
				simplex->push_back(support);

				if (DoSimplex(*simplex, direction))
				{
					// 심플렉스 안에 원점이 존재한다면 충돌함.
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
			Simplex polytope{ _manifold->GetSimplex() };
			polytope.SetFace();

			size_t count{};

			// 노말이 0이 나와서 거리도 0이 나오는 경우가 있다.
			// 노말이 0이 나오는 경우는 삼각형을 이루지 못하고 직선이기 때문인데
			// 사면체를 못만들었다는 


			while (count < EPA_MAX)
			{
				// 면들과의 노말과 거리를 계산할 수 있음.
 				Vector3D normal{ polytope.faceMap.begin()->second.normal };
				Vector3D support{ FindSupportPoint(
					_manifold->GetColliderA(),
					_manifold->GetColliderB(),
					normal) 
				};

				// 면과의 거리가 0일 수도 있다.
				// 원점이 폴리토프의 면 위에 있다면 면과의 거리가 0이 될 수 있다.
				// 만약 변 위에 있다면 거리가 0인 면이 2개가 생길 것이다.

				float faceDist{ polytope.faceMap.begin()->first };
				// Vector3D faceToP{ support - polytope.faceMap.begin()->second.vec[0] };
				// float faceToPDist{ faceToP.Dot(normal) };
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

				// 노말 방향으로 서포트 포인트를 찾았는데 거리가 0에 가깝다면...
				if (std::fabs(supportDist) <= Epsilon)
				{
					break;
				}
				
				// 계산된 dist만 비교해서 가장 짧은 면과 서포트 포인트의 거리를 비교함
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

				// 면들과 서포트 포인트를 비교하면서 확장 가능성을 본다.
				for (auto itr = polytope.faceMap.begin(); itr != polytope.faceMap.end(); itr++)
				{
					Face f = itr->second;

					Vector3D fToSupport{ support - f.vec[0] };

					float radian{ f.normal.Dot(fToSupport) };
						
					// 서포트 포인트가 페이스 노말과 같은 방향인가?
					if (radian <= 0.f)
					{
						continue;
					}

					itr = polytope.faceMap.erase(itr);

					// 겹치는 변이 있다면 두 면 이상이 연속된 것이기 때문에 변을 뺌.
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
					break;
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

			_manifold->SetDepth(depth + Epsilon );
			_manifold->SetNormal(detectNormal);
			return;
		}

		/// <summary>
		/// 두 콜라이더의 민코프스키 차에서 방향 벡터의 서포트 포인트를 구함
		/// </summary>
		Vector3D CollisionSystem::FindSupportPoint(Collider* _colliderA, Collider* _colliderB, const Vector3D& _direction)
		{
			return _colliderA->FindFarthestPoint(_direction) - _colliderB->FindFarthestPoint(-_direction);
		}

		/// <summary>
		/// 접촉점을 찾아냄
		/// 
		/// 최대 6개까지 나올 수 있음
		/// 삼각형끼리의 충돌을 예상하고 만듬.
		/// </summary>
		void CollisionSystem::FindContactPoint(Manifold* _manifold)
		{
			Vector3D direction = _manifold->GetNormal();

			Collider* _cA{ _manifold->GetColliderA() };
			Collider* _cB{ _manifold->GetColliderB() };

			// 충돌에 관여한 면을 찾아냄
			Face A = _manifold->GetColliderA()->FindSupportFace(direction);
			Face B = _manifold->GetColliderB()->FindSupportFace(-direction);

			Face* reference = &A;
			Face* incident = &B;

			float aPerpendicular = std::fabs(reference->normal.Dot(direction));
			float bPerpendicular = std::fabs(incident->normal.Dot(direction));

			// 1에 제일 가까운 면을 기준면으로 삼음
			if (aPerpendicular < bPerpendicular)
			{
				_manifold->SetColliderA(_cB);
				_manifold->SetColliderB(_cA);
				_manifold->SetNormal(-direction);
				reference = &B;
				incident = &A;
				direction = -direction;
			}
			
			std::vector<Vector3D> contactPoint{ incident->vec };

			// 기준 면의 모서리를 순회하면서 면을 잘라냄
			// 모서리 하나에 대해서 잘라내고 나면 face를 반환 받을 것.
			for (auto& edge : reference->edge)
			{
				contactPoint = FaceClip(contactPoint, edge, edge.normal, false);
			}

			// 레퍼런스 페이스의 노말 방향으로 잘라냄

			contactPoint = FaceClip(contactPoint, reference->edge[0], reference->normal, true);

			for (auto i = 0; i < contactPoint.size(); i++)
			{
				_manifold->AddContactPoint(contactPoint[i]);
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

		float CollisionSystem::PointToSegmentDistance(const Vector3D p, const Vector3D L1, const Vector3D L2)
		{
			// 선분이 아닐 때
			const float l2{ (L2 - L1).LengthSquare() };
			if (l2 == 0.f)
			{
				return (p - L1).Length();
			}

			// 
			const float t{ (p - L1).Dot(L2 - L1) / l2 };
			if (t < 0.f)
			{
				return (p - L1).Length();
			}
			else if (t > 1.f)
			{
				return (p - L2).Length();
			}
			const Vector3D proj{ L1 + (L2 - L1) * t };
			
			return (p - proj).Length();
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

			// AB 직선에 원점이 존재하는 경우 충돌 한 것이지만..
			if (BA.Cross(BO) == Vector3D::Zero() || BA == BO)
			{
				_direction = BA.Cross(Vector3D(1.f, 1.f, 1.f).Normalized());
				return false;
			}

			// 서포트 포인트끼리 선을 그어보고 원점과 각도를 비교해본다.
			// 선분과 원점을 향한 벡터가 이루는 각이 90도 보다 작다면
			// 원점을 포함하는 심플렉스를 만들 가능성이 있기 때문에
			// 그의 수직인 방향으로 서포트 포인트를 찾는다.
			float dot{ BA.Dot(BO) };

			if (dot > 0.f)
			{
				_direction = BA.Cross(BO).Cross(BA).Normalized();
			}
			else if (dot < 0.f)
			{
				// B 너머에 원점이 존재함.
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
		/// 삼각형
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

			if (A == C)
			{
				_simplex = { B, C };
				_direction = CB.Cross(Vector3D(1.f, 1.f, 1.f).Normalized());
				return false;
			}
			if (B == C)
			{
				_simplex = { A, C };
				_direction = CA.Cross(Vector3D(1.f, 1.f, 1.f).Normalized());
				return false;
			}

			// ABC 삼각형의 노말 벡터를 구하고
			// 삼각형 어느 방향에 원점이 있는지 판단.

			// CA 공간에 원점이 존재하는지 체크
			if ((CBA.Cross(CA).Normalized()).Dot(CO) > 0.f)
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
					// _direction = CB.Cross(CO).Cross(CB);
					return DoSimplex2(_simplex, CO);
				}
			}
			else
			{
				// CB 공간에 원점이 존재하는지 체크
				if ((CB.Cross(CBA).Normalized()).Dot(CO) > 0.f)
				{
					// CB 공간에 원점이 존재한다면
					// 비버 집을 다시 지어야함.
					_simplex = { B, C };
					// _direction = CB.Cross(CO).Cross(CB);
					return DoSimplex2(_simplex, CO);
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
						// 방향이 반대거나 삼각형 위에 원점이 있는 경우
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

			// 사면체를 만들지 못하는 경우
			if (A == D)
			{
				_simplex = { B, C, D };
				_direction = DCB.Cross(Vector3D(1.f, 1.f, 1.f).Normalized());
				return false;
			}
			else if (B == D)
			{
				_simplex = { A, C, D };
				_direction = DAC.Cross(Vector3D(1.f, 1.f, 1.f).Normalized());
				return false;
			}
			else if (C == D)
			{
				_simplex = { A, B, D };
				_direction = DBA.Cross(Vector3D(1.f, 1.f, 1.f).Normalized());
				return false;
			}


			// 사면체를 이루는 각 면의 노말 벡터와
			// 원점의 방향으로 사면체가 원점을 포함하고 있는지를 판단함.
			if (DBA.Dot(DO) > 0.f)
			{
				// 노말 방향에 원점이 존재한다면...
				// DAB 공간안에 원점이 있음
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

		std::vector<Vector3D> CollisionSystem::FaceClip(const std::vector<Vector3D>& _incident, const Edge& _refEdge, const Vector3D& _refFaceNormal, bool remove)
		{
			// Sutherland-Hodgman 알고리즘으로 페이스를 잘라낼 예정.
			// 잘라야할 페이스 정보를 알고있음, 기준이 되는 페이스 정보도 알고 있음.
			// 기준 면의 모서리 노말 방향에 따라 잘라내는데
			// 음수, 양수면 둘 다 저장
			// 양수, 음수면 잘린 점만 저장 (두 번째 점)
			// 음수, 음수면 잘리지 않은 점만 저장 (두 번째 점)
			// 양수, 양수면 저장하지 않음
			
			std::vector<Vector3D> points{};

			// 기준 면의 한 모서리에 대해서 노말 비교를 하고
			// 모서리를 잘라낸다.
			for (size_t i = 0; i < _incident.size(); i++)
			{
				size_t j = (i + 1) % _incident.size();
				Edge edge{ _incident[i], _incident[j], i, j };
				size_t state = EdgeClip(edge, _refEdge.vectorA, _refFaceNormal, remove);

				switch (state)
				{
					case OutOut:
					{}
						break;
					
					case InOut:
					{
						if (!remove)
						{
							points.push_back(edge.vectorB);
						}
					}
					break;

					case InIn:
					{
						points.push_back(edge.vectorB);
					}
						break;
					
					case OutIn:
					{
						if (!remove)
						{
							points.push_back(edge.vectorA);
						}
						points.push_back(edge.vectorB);
					}
						break;

					default:
						break;
				}
			}

			return points;
		}

		size_t CollisionSystem::EdgeClip(Edge& _edge, const Vector3D& _point, const Vector3D& _direction, bool _remove)
		{
			// 레퍼런스 엣지의 한 점과 클리핑할 엣지의 점 간의 벡터를 구하고
			// 디렉션 벡터에 내적해서 모서리의 길이를 구함
			float dA = (_edge.vectorA - _point).Dot(_direction);
			float dB = (_edge.vectorB - _point).Dot(_direction);

			Vector3D A{ _edge.vectorA };
			Vector3D B{ _edge.vectorB };

			// 노말 방향으로 길이가 둘 다 음수인 경우엔 자르지 않음
			if (dA <= 0.f && dB <= 0.f)
			{
				return InIn;
			}

			// 노말 방향으로 둘다 양수인 경우엔 엣지를 삭제 해야함.
			if (dA > 0.f && dB > 0.f)
			{
				return OutOut;
			}

			if (dA > 0.f)
			{
				if (_remove)
				{
					_edge.vectorA = B;
				}
				else
				{
					_edge.vectorA = A + (B - A) * ( dA / (std::fabs(dA) + std::fabs(dB)) );
				}

				return OutIn;
			}
			if (dB > 0.f)
			{
				if (_remove)
				{
					_edge.vectorB = A;
				}
				else
				{
					_edge.vectorB = B + (A - B) * ( dB / (std::fabs(dA) + std::fabs(dB)) );
				}

				return InOut;
			}
		}

		void CollisionSystem::ComputeImpulse(Manifold* _manifold)
		{
			// 각 물체들이 가지고 있는 속력으로 충격량을 계산함
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

			Vector3D Normal{ _manifold->GetNormal() };

			const auto& contactPoints{ _manifold->GetContactPoints() };
			for (const auto& contactPoint : contactPoints)
			{							
				Vector3D V_a{ A->GetVelocity() };
				Vector3D V_b{ B->GetVelocity() };

				Vector3D W_a{ A->GetAngularVelocity() };
				Vector3D W_b{ B->GetAngularVelocity() };


				/// 임펄스 기반 반응 모델
				// 질량 중심에서 충돌 지점까지의 벡터
				Vector3D r_1 = contactPoint - P_a;
				Vector3D r_2 = contactPoint - P_b;

				// 충돌 지점에서 속도와 상대 속도
				Vector3D v_p1 = V_a + W_a.Cross(r_1);
				Vector3D v_p2 = V_b + W_b.Cross(r_2);
				Vector3D v_r = v_p2 - v_p1;

				// 충돌 지점에서 노말 방향으로의 상대 속도
				float contactVelocity = v_r.Dot(Normal);

				if (contactVelocity > Epsilon)
				{
					continue;
				}

				Matrix3x3 inertiaTMA = A->GetInvInertia();
				Matrix3x3 inertiaTMB = B->GetInvInertia();

				/// 임펄스 공식의 분모 부분.
				Vector3D inertiaA = r_1.Cross(Normal).Cross(r_1) * inertiaTMA;
				Vector3D inertiaB = r_2.Cross(Normal).Cross(r_2) * inertiaTMB;
				float numerator = systemMass + (inertiaA + inertiaB).Dot(Normal);

				// 임펄스 크기
				float j = -(1.f + restitution) * contactVelocity;
				j /= numerator;
				j /= (float)contactPoints.size();

				// 임펄스 벡터
				Vector3D impulse = Normal * j;
				A->ApplyImpulse(-impulse, r_1);
				B->ApplyImpulse(impulse, r_2);


				/// 임펄스 기반 마찰 모델
				// 마찰 임펄스 방향.
				// 이 공식은 contactVelocity != 0 일 때 적용되는 공식
				Vector3D tangent = (v_r - (Normal * contactVelocity)).Normalized();

				// 임펄스 크기
				// contactVelocity를 구했던 v_r Dot normal과 비슷하지만 음수가 붙은 점이 다름.
				float j_t = -v_r.Dot(tangent);
				j_t /= numerator;
				j_t /= (float)contactPoints.size();

				//임펄스 벡터
				Vector3D frictionImpulse;

				// 마찰력 = 수직항력 * 마찰계수
				// 순간 힘이 일정 마찰력을 넘어간다면 동적 마찰력으로 계산함
				// m * Dot (v_r, t) <= j_s 
				if (std::fabs(j_t) < j * sfriction)
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

			Vector3D p_A{ A->GetPosition() };
			Vector3D p_B{ B->GetPosition() };

			const float persent{ 0.8f };
			const float threshold{ 0.00001f };

			float depth{ _manifold->GetDepth() };
			const Vector3D normal{ _manifold->GetNormal() };
			
			const float dist{ std::max(depth - threshold, 0.0f) };
			Vector3D resolve = normal * (dist / systemMass) * persent;

			Vector3D Adist = -resolve * InvMassA;
			A->SetPosition(p_A + Adist);

			Vector3D Bdist = resolve * InvMassB;
			B->SetPosition(p_B + Bdist);
		}

		float CollisionSystem::ComputeFriction(float _a, float _b)
		{
			return std::powf(_a * _b, 0.5f);
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