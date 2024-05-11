#include "CollisionSystem.h"

#include <vector>
#include <set>
#include "HyruleMath.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Face.h"
#include "Edge.h"
#include "Object.h"

#include "Ray.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "PlaneCollider.h"

#include <iostream>

constexpr size_t GJK_MAX = 50;
constexpr size_t EPA_MAX = 50;

namespace hyrule
{
	namespace Physics
	{
		std::function<bool(Collider*, Collider*, Manifold&)> CollisionSystem::DetectionFunc[4][4] =
		{
			// sphere			box				capsule			convex
			TestSphereSphere,	TestSphereOBB,	NULL,			TestSphereConvex,		// sphere
			NULL,				GJK,			NULL,			GJK,				// box
			NULL,				NULL,			NULL,			NULL,				// capsule
			NULL,				NULL,			NULL,			GJK					// convex
		};

		std::function<void(Manifold&)> CollisionSystem::FindContactFunc[4][4] =
		{
			// sphere			box				capsule			convex
			CPSphereToSphere,	CPSphereToBox,	NULL,			CPSphereToConvex,	// sphere
			NULL,				CPPolyToPoly,	NULL,			CPPolyToPoly,		// box
			NULL,				NULL,			NULL,			NULL,				// capsule,
			NULL,				NULL,			NULL,			CPPolyToPoly		// convex
		};

		std::function<bool(const Ray&, Collider*)> CollisionSystem::RaycastFunc[4] =
		{
			RaycastToSphere, RaycastToBox, NULL, RaycastToConvex
		};

		bool CollisionSystem::CollisionDetection(Collider* _colliderA, Collider* _colliderB, Manifold& _manifold)
		{
			size_t typeA = (size_t)_colliderA->GetType();
			size_t typeB = (size_t)_colliderB->GetType();
			
			if (typeA > typeB)
			{
				auto temp = _manifold.GetColliderA();
				auto B = _manifold.GetColliderB();

				_manifold.SetColliderA(B);
				_manifold.SetColliderB(temp);
			}

			size_t min = std::min(typeA, typeB);
			size_t max = std::max(typeA, typeB);

			return DetectionFunc[min][max](_manifold.GetColliderA(), _manifold.GetColliderB(), _manifold);
		}

		void CollisionSystem::FindContactPoint(Manifold& _manifold)
		{
			const size_t typeA = (size_t)_manifold.GetColliderA()->GetType();
			const size_t typeB = (size_t)_manifold.GetColliderB()->GetType();

			if (typeA > typeB)
			{
				auto temp = _manifold.GetColliderA();
				auto B = _manifold.GetColliderB();

				_manifold.SetColliderA(B);
				_manifold.SetColliderB(temp);
			}

			size_t min = std::min(typeA, typeB);
			size_t max = std::max(typeA, typeB);

			FindContactFunc[min][max](_manifold);
		}
		
		Vector3D CollisionSystem::FindSupportPoint(Collider* _colliderA, Collider* _colliderB, const Vector3D& _direction)
		{
			return _colliderA->FindFarthestPoint(_direction) - _colliderB->FindFarthestPoint(-_direction);
		}

		bool CollisionSystem::GJK(Collider* _colliderA, Collider* _colliderB, Manifold& _manifold)
		{
			size_t count{};

			Simplex simplex;

			// ������ ���� ���ͷ� 
			Vector3D direction{ Vector3D::Right() };
			Vector3D support{ FindSupportPoint(_colliderA, _colliderB, direction) };

			simplex.push_back(support);
			direction = -support.Normalized();

			while (count < GJK_MAX)
			{
				// ���� ���ͷκ��� ����Ʈ �����͸� ���ϴ°� ������
				support = FindSupportPoint(_colliderA, _colliderB, direction);
				Vector3D OP = support.Normalized();

				// ����Ʈ ����Ʈ�� ���⺤���� ������ 90�� �̻��̸� �׳� �浹 ���ϴ� ����
				// (�ش� �������� ������ �Ѵ� ���� ���� ������)
				// (������ �����ϴ� ���÷����� ���� ���� ����)
				float dot{ OP.Dot(direction) };
				if (dot < 0.f)
				{
					break;
				}

				// ����Ʈ �����Ͱ� ���������� ���÷����� �ִ´�.
				simplex.push_back(support);

				if (DoSimplex(simplex, direction))
				{
					// ���÷��� �ȿ� ������ �����Ѵٸ� �浹��.
					_manifold.SetSimplex(std::move(simplex));
					return true;
				}

				if (direction == Vector3D::Zero())
				{
					break;
				}
				count++;
			}

			return false;
		}

		void CollisionSystem::EPA(Manifold& _manifold)
		{
			// ���÷����� ���� �ϴ� ������
			Simplex polytope{ _manifold.GetSimplex() };
			polytope.SetFace();

			size_t count{};

			// �븻�� 0�� ���ͼ� �Ÿ��� 0�� ������ ��찡 �ִ�.
			// �븻�� 0�� ������ ���� �ﰢ���� �̷��� ���ϰ� �����̱� �����ε�
			// ���ü�� ��������ٴ� 

			while (count < EPA_MAX)
			{
				// ������ �븻�� �Ÿ��� ����� �� ����.
 				Vector3D normal{ polytope.faceMap.begin()->second.normal };
				Vector3D support{ FindSupportPoint(
					_manifold.GetColliderA(),
					_manifold.GetColliderB(),
					normal) 
				};

				// ����� �Ÿ��� 0�� ���� �ִ�.
				// ������ ���������� �� ���� �ִٸ� ����� �Ÿ��� 0�� �� �� �ִ�.
				// ���� �� ���� �ִٸ� �Ÿ��� 0�� ���� 2���� ���� ���̴�.

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

				// �븻 �������� ����Ʈ ����Ʈ�� ã�Ҵµ� �Ÿ��� 0�� �����ٸ�...
				if (std::fabs(supportDist) <= Epsilon)
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
					Face f = itr->second;

					Vector3D fToSupport{ support - f.vec[0] };

					float radian{ f.normal.Dot(fToSupport) };
						
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

			_manifold.SetDepth(depth );
			_manifold.SetNormal(detectNormal);
			return;
		}


		Vector3D CollisionSystem::ClosestPointToAABB(const Vector3D& _point, Collider* _collider)
		{
			const Vector3D AABBScale{ _collider->GetScale() * 0.5f };
			const Vector3D AABBMin{ _collider->GetPosition() - AABBScale };
			const Vector3D AANNMax{ _collider->GetPosition() + AABBScale };

			Vector3D result;

			for (int i = 0; i < 3; i++)
			{
				float v = _point.e[i];

				if (v < AABBMin.e[i])
				{
					v = AABBMin.e[i];
				}
				else if (v > AANNMax.e[i])
				{
					v = AANNMax.e[i];
				}

				result.e[i] = v;
			}

			return result;
		}

		Vector3D CollisionSystem::ClosestPointToOBB(const Vector3D& _point, Collider* _collider)
		{
			Vector3D pos = _collider->GetPosition();
			Matrix3x3 rotate = ToMatrix3(_collider->GetRotation());
			Vector3D scale = _collider->GetScale() * 0.5f;

			Vector3D d = (_point - pos) * rotate.Inverse();

			Vector3D Axis[3]
			{
				Vector3D(1.f, 0.f, 0.f),
				Vector3D(0.f, 1.f, 0.f),
				Vector3D(0.f, 0.f, 1.f),
			};

			Vector3D result;
			for (int i = 0; i < 3; i++)
			{
				float dist = d.Dot(Axis[i]);

				if (dist < -scale.e[i])
				{
					dist = -scale.e[i];
				}
				else if (dist > scale.e[i])
				{
					dist = scale.e[i];
				}

				result += Axis[i] * dist;
			}

			return result * rotate + pos;
		}

		Vector3D CollisionSystem::ClosestPointToConvex(const Vector3D&, Collider*)
		{
			return Vector3D();
		}


		void CollisionSystem::CPSphereToSphere(Manifold& _manifold)
		{
			Collider* A = _manifold.GetColliderA();
			Collider* B = _manifold.GetColliderB();

			if (A->hasRigidBody() && B->hasRigidBody())
			{
				_manifold.Apply();
			}
		}

		void CollisionSystem::CPSphereToBox(Manifold& _manifold)
		{
			Collider* sphere{ _manifold.GetColliderA() }; // A�� ��ü�� ����
			Collider* box{ _manifold.GetColliderB() };

			Vector3D sphereScale{ sphere->GetScale() };
			float Radius{ 0.5f * sphereScale.x };

			Vector3D sphereCenter{ sphere->GetPosition() };
			Vector3D closestPoint{ ClosestPointToOBB(sphereCenter, box) };

			Vector3D v{ closestPoint - sphereCenter };

			Vector3D normal{ v.Normalized() };
			float penetrationDepth{ Radius - v.Length() };

			_manifold.SetNormal(normal);
			_manifold.AddContactPoint(closestPoint);

			if (sphere->hasRigidBody() && box->hasRigidBody())
			{
				_manifold.SetDepth(penetrationDepth);
				_manifold.Apply();
			}
		}

		void CollisionSystem::CPSphereToConvex(Manifold& _manifold)
		{
			Collider* sphere{ _manifold.GetColliderA() };
			Collider* convex{ _manifold.GetColliderB() };

			Vector3D sphereCenter{ sphere->GetPosition() };

			Vector3D sphereScale{ sphere->GetScale() };
			float sphereRadius{ 0.5f * sphereScale.x };
			
			Vector3D closestPointOnConvex{ ClosestPointToConvex(sphereCenter, convex) };

			Vector3D normal{ (closestPointOnConvex - sphereCenter).Normalized() };
			float penetrationDepth{ sphereRadius - (closestPointOnConvex - sphereCenter).Length() };

			// �Ŵ������� ��� �� ������ ����
			_manifold.SetNormal(normal);
			_manifold.SetDepth(penetrationDepth);

			if (sphere->hasRigidBody() && convex->hasRigidBody())
			{
				_manifold.AddContactPoint(closestPointOnConvex);
				_manifold.Apply();
			}
		}

		void CollisionSystem::CPPolyToPoly(Manifold& _manifold)
		{
			EPA(_manifold);

			Collider* _cA{ _manifold.GetColliderA() };
			Collider* _cB{ _manifold.GetColliderB() };

				Vector3D direction = _manifold.GetNormal();

				// �浹�� ������ ���� ã�Ƴ�
				Face A = _manifold.GetColliderA()->FindSupportFace(direction);
				Face B = _manifold.GetColliderB()->FindSupportFace(-direction);

				Face* reference = &A;
				Face* incident = &B;

				float aPerpendicular = std::fabs(reference->normal.Dot(direction));
				float bPerpendicular = std::fabs(incident->normal.Dot(direction));

				// 1�� ���� ����� ���� ���ظ����� ����
				if (aPerpendicular < bPerpendicular)
				{
					_manifold.SetColliderA(_cB);
					_manifold.SetColliderB(_cA);
					_manifold.SetNormal(-direction);
					reference = &B;
					incident = &A;
					direction = -direction;
				}

				std::vector<Vector3D> contactPoint{ incident->vec };

				// ���� ���� �𼭸��� ��ȸ�ϸ鼭 ���� �߶�
				// �𼭸� �ϳ��� ���ؼ� �߶󳻰� ���� face�� ��ȯ ���� ��.
				for (auto& edge : reference->edge)
				{
					contactPoint = FaceClip(contactPoint, edge, edge.normal, false);
				}

				// ���۷��� ���̽��� �븻 �������� �߶�

				contactPoint = FaceClip(contactPoint, reference->edge[0], reference->normal, true);

				for (auto i = 0; i < contactPoint.size(); i++)
				{
					_manifold.AddContactPoint(contactPoint[i]);
				}

				if (_cA->hasRigidBody() && _cB->hasRigidBody())
				{
				_manifold.Apply();
			}
		}


		bool CollisionSystem::Raycast(const Ray& _ray, Collider* _collider)
		{
			size_t type = (size_t)_collider->GetType();

			return RaycastFunc[type](_ray, _collider);
		}

		bool CollisionSystem::RaycastToSphere(const Ray& _ray, Collider* _collider)
		{
			// ���Ǿ� - ���� ����
			Vector3D sphereToOrigin{ _ray.from - _collider->GetPosition() };

			// ���Ǿ������ �Ÿ��� ���Ǿ��� �������� �� ��
			float c{ sphereToOrigin.Dot(sphereToOrigin) - 
				_collider->GetLength() * _collider->GetLength() 
			};

			// �Ÿ��� ª�ٸ� �浹
			if (c <= 0.f)
			{
				return true;
			}

			// 
			float b{ sphereToOrigin.Dot(_ray.direction) };

			if (b > 0.f)
			{
				return false;
			}

			float disc{ b * b - c };
			if (disc < 0.f)
			{
				return false;
			}

			return true;
		}

		bool CollisionSystem::RaycastToBox(const Ray& _ray, Collider* _collider)
		{
			// Ray = t * to + from �� ǥ���� �� �ִµ�
// 

			// Vector3D boxPosition{ _collider->GetPosition() };
			// Quaternion boxQuaternion{ _collider->GetRotation() };
			// Matrix3x3 boxRotationTranspose{ ToMatrix3(boxQuaternion).Transpose() };
			// Vector3D boxScale{ _collider->GetScale() };
			// 
			// // ���̸� BOX ���÷� ������
			// // Vector3D rayPos{ (_ray.position - boxPosition) * boxRotationTranspose };
			// Vector3D rayDirection{ _ray.direction * boxRotationTranspose };
			// 
			// // _t = 0.0f;
			// float tmax = FLT_MAX;
			// 
			// Vector3D min{ -boxScale * 0.5f };
			// Vector3D max{ boxScale * 0.5f };
			// 
			// for (int i = 0; i < 3; i++)
			// {
			// 	if (std::abs(rayDirection.e[i]) < Epsilon)
			// 	{
			// 		if (rayPos.e[i] < min.e[i] || rayPos.e[i] > max.e[i])
			// 		{
			// 			return 0;
			// 		}
			// 	}
			// 	else
			// 	{
			// 		float ood = 1.0f / rayDirection.e[i];
			// 		float t1 = (min.e[i] - rayPos.e[i]) * ood;
			// 		float t2 = (max.e[i] - rayPos.e[i]) * ood;
			// 		if (t1 > t2)
			// 		{
			// 			std::swap(t1, t2);
			// 		}
			// 		if (t1 > _t)
			// 		{
			// 			_t = t1;
			// 		}
			// 		if (t2 > tmax)
			// 		{
			// 			tmax = t2;
			// 		}
			// 		if (_t > tmax)
			// 		{
			// 			// ������ ����
			// 			return false;
			// 		}
			// 	}
			// }

			// _contact = _ray.position + _ray.direction * _t;
			return true;
		}

		bool CollisionSystem::RaycastToConvex(const Ray& _ray, Collider* _collider)
		{
			return false;
		}


		bool CollisionSystem::TestSphereSphere(Collider* _colliderA, Collider* _colliderB, Manifold& _manifold)
		{
			Vector3D Apos{ _colliderA->GetPosition() };
			Vector3D Bpos{ _colliderB->GetPosition() };

			Vector3D AB{ Bpos - Apos };

			Vector3D sphereScaleA = _colliderA->GetScale();
			Vector3D sphereScaleB = _colliderB->GetScale();
			
			float radiusA{ 0.5f * sphereScaleA.x };
			float radiusB{ 0.5f * sphereScaleB.x };

			float total{ radiusA + radiusB };
			float distanceBetweenCenters{ AB.Length() };
			Vector3D normal{ AB.Normalized() };

			float penetrationDepth = (radiusA + radiusB) - distanceBetweenCenters;

			Vector3D contactPoint = Apos + normal * radiusA;

			if (total >= distanceBetweenCenters)
			{
				_manifold.SetNormal(normal);
				_manifold.SetDepth(penetrationDepth);
				_manifold.AddContactPoint(contactPoint);
				return true;
			}

			return false;
		}

		bool CollisionSystem::TestSphereAABB(Collider* _colliderA, Collider* _colliderB, Manifold& _manifold)
		{
			Vector3D p = ClosestPointToAABB(_colliderA->GetPosition(), _colliderB);

			Vector3D v{ p - _colliderA->GetPosition() };
			Vector3D scl{ _colliderA->GetScale() };

			float r{ 0.5f * scl.x };

			return v.Dot(v) <= r * r;
		}

		bool CollisionSystem::TestSphereOBB(Collider* _colliderA, Collider* _colliderB, Manifold& _manifold)
		{
			Vector3D p = ClosestPointToOBB(_colliderA->GetPosition(), _colliderB);

			Vector3D v{ p - _colliderA->GetPosition() };
			Vector3D scl{ _colliderA->GetScale() };

			float r{ 0.5f * scl.x };

			return v.Dot(v) <= r * r;
		}

		bool CollisionSystem::TestSphereConvex(Collider*, Collider*, Manifold&)
		{
			return false;
		}

		float CollisionSystem::PointToSegmentDistance(const Vector3D p, const Vector3D L1, const Vector3D L2)
		{
			// ������ �ƴ� ��
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

			// AB ������ ������ �����ϴ� ��� �浹 �� ��������..
			if (BA.Cross(BO) == Vector3D::Zero() || BA == BO)
			{
				_direction = BA.Cross(Vector3D(1.f, 1.f, 1.f).Normalized());
				return false;
			}

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
				// B �ʸӿ� ������ ������.
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
					// _direction = CB.Cross(CO).Cross(CB);
					return DoSimplex2(_simplex, CO);
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
					// _direction = CB.Cross(CO).Cross(CB);
					return DoSimplex2(_simplex, CO);
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
						// ������ �ݴ�ų� �ﰢ�� ���� ������ �ִ� ���
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

			// ���ü�� ������ ���ϴ� ���
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

		std::vector<Vector3D> CollisionSystem::FaceClip(const std::vector<Vector3D>& _incident, const Edge& _refEdge, const Vector3D& _refFaceNormal, bool remove)
		{
			// Sutherland-Hodgman �˰������� ���̽��� �߶� ����.
			// �߶���� ���̽� ������ �˰�����, ������ �Ǵ� ���̽� ������ �˰� ����.
			// ���� ���� �𼭸� �븻 ���⿡ ���� �߶󳻴µ�
			// ����, ����� �� �� ����
			// ���, ������ �߸� ���� ���� (�� ��° ��)
			// ����, ������ �߸��� ���� ���� ���� (�� ��° ��)
			// ���, ����� �������� ����
			
			std::vector<Vector3D> points{};

			// ���� ���� �� �𼭸��� ���ؼ� �븻 �񱳸� �ϰ�
			// �𼭸��� �߶󳽴�.
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
			// ���۷��� ������ �� ���� Ŭ������ ������ �� ���� ���͸� ���ϰ�
			// �𷺼� ���Ϳ� �����ؼ� �𼭸��� ���̸� ����
			float dA = (_edge.vectorA - _point).Dot(_direction);
			float dB = (_edge.vectorB - _point).Dot(_direction);

			Vector3D A{ _edge.vectorA };
			Vector3D B{ _edge.vectorB };

			// �븻 �������� ���̰� �� �� ������ ��쿣 �ڸ��� ����
			if (dA <= 0.f && dB <= 0.f)
			{
				return InIn;
			}

			// �븻 �������� �Ѵ� ����� ��쿣 ������ ���� �ؾ���.
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

		void CollisionSystem::ComputeImpulse(Manifold& _manifold)
		{
			// �� ��ü���� ������ �ִ� �ӷ����� ��ݷ��� �����
			RigidBody* A{ _manifold.RigidBodyA() };
			RigidBody* B{ _manifold.RigidBodyB() };

			float systemMass{ A->GetInvMass() + B->GetInvMass() };

			if (systemMass == 0.f)
			{
				return;
			}

			float sfriction = ComputeFriction(A->GetStaticFriction(), B->GetStaticFriction());
			float dfriction = ComputeFriction(A->GetDynamicFriction(), B->GetDynamicFriction());
			float restitution = std::min(A->GetRestitution(), B->GetRestitution());

			Vector3D P_a{ _manifold.GetColliderA()->GetPosition() };
			Vector3D P_b{ _manifold.GetColliderB()->GetPosition() };

			Vector3D Normal{ _manifold.GetNormal() };

			const auto& contactPoints{ _manifold.GetContactPoints() };

			for (const auto& contactPoint : contactPoints)
			{			
				Vector3D V_a{ A->GetVelocity() };
				Vector3D V_b{ B->GetVelocity() };

				Vector3D W_a{ A->GetAngularVelocity() };
				Vector3D W_b{ B->GetAngularVelocity() };

				/// ���޽� ��� ���� ��
				// ���� �߽ɿ��� �浹 ���������� ����
				Vector3D r_1{ contactPoint - P_a };
				Vector3D r_2{ contactPoint - P_b };

				// �浹 �������� �ӵ��� ��� �ӵ�
				Vector3D v_p1{ V_a + W_a.Cross(r_1) };
				Vector3D v_p2{ V_b + W_b.Cross(r_2) };
				Vector3D v_r{ v_p2 - v_p1 };

				// �浹 �������� �븻 ���������� ��� �ӵ�
				float contactVelocity{ v_r.Dot(Normal) };

				if (contactVelocity > 0.f)
				{
					return;
				}

				Matrix3x3 inertiaTMA{ A->GetInvInertia() };
				Matrix3x3 inertiaTMB{ B->GetInvInertia() };

				/// ���޽� ������ �и� �κ�.
				Vector3D inertiaA{ r_1.Cross(Normal).Cross(r_1) * inertiaTMA };
				Vector3D inertiaB{ r_2.Cross(Normal).Cross(r_2) * inertiaTMB };
				float numerator{ systemMass + (inertiaA + inertiaB).Dot(Normal) };

				// ���޽� ũ��
				float j{ -(1.f + restitution) * contactVelocity };
				j /= numerator;
				j /= (float)contactPoints.size();

				// ���޽� ����
				Vector3D impulse = Normal * j;
				// _manifold.AddImpulse(impulse);
				A->ApplyImpulse(-impulse, r_1);
				B->ApplyImpulse(impulse, r_2);


				/// ���޽� ��� ���� ��
				// ���� ���޽� ����.
				// �� ������ contactVelocity != 0 �� �� ����Ǵ� ����
				Vector3D tangent{ (v_r - (Normal * contactVelocity)).Normalized() };

				if (tangent == Vector3D::Zero())
				{
					return;
				}

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

		void CollisionSystem::ResolveCollision(Manifold& _manifold)
		{
			RigidBody* A{ _manifold.RigidBodyA() };
			RigidBody* B{ _manifold.RigidBodyB() };
			
			if (A->IsAwake() == false || B->IsAwake() == false)
			{
				return;
			}

			float InvMassA = (A == nullptr) ? 0.f : A->GetInvMass();
			float InvMassB = (B == nullptr) ? 0.f : B->GetInvMass();
			
			float systemMass{ InvMassA + InvMassB };

			if (systemMass == 0.f)
			{
				return;
			}

			Vector3D p_A{ A->GetPosition() };
			Vector3D p_B{ B->GetPosition() };

			const float persent{ 0.8f };
			const float threshold{ 0.00001f };

			float depth{ _manifold.GetDepth() };
			const Vector3D normal{ _manifold.GetNormal() };
			
			const float dist{ std::max(depth - threshold, 0.0f) };
			Vector3D resolve = normal * (dist / systemMass) * persent;

			Vector3D Adist = -resolve * InvMassA;
			A->SetPosition(p_A + Adist);

			Vector3D Bdist = resolve * InvMassB;
			B->SetPosition(p_B + Bdist);
		}

		float CollisionSystem::ComputeFriction(float _a, float _b)
		{
			return std::sqrtf(_a * _b);
		}
	}
}