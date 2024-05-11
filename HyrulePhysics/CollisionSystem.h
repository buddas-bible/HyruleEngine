#pragma once

#include <map>
#include <list>
#include "Manager.h"
#include "Manifold.h"
#include "Simplex.h"
#include <functional>
namespace hyrule
{
	struct Vector3D;

	namespace Physics
	{
		class Collider;
		class Manifold;
		class Simplex;
		struct Face;
		struct Edge;
		struct Ray;


		class CollisionSystem
		{
		public:
			static bool CollisionDetection(Collider*, Collider*, Manifold&);
			static void FindContactPoint(Manifold&);

			static bool Raycast(const Ray&, Collider*);

		private:
			static Vector3D FindSupportPoint(Collider*, Collider*, const Vector3D&);
			
			// ����� ��
			static Vector3D ClosestPointToAABB(const Vector3D&, Collider*);
			static Vector3D ClosestPointToOBB(const Vector3D&, Collider*);
			static Vector3D ClosestPointToConvex(const Vector3D&, Collider*);

#pragma region ������
			// �븻 ã��
			static void EPA(Manifold&);

			// ������ ã��
			static void CPSphereToSphere(Manifold&);
			static void CPSphereToBox(Manifold&);
			static void CPSphereToConvex(Manifold&);
			static void CPPolyToPoly(Manifold&);
#pragma endregion ������

#pragma region �����ɽ�Ʈ
			static bool RaycastToSphere(const Ray&, Collider*);
			static bool RaycastToBox(const Ray&, Collider*);
			static bool RaycastToConvex(const Ray&, Collider*);
#pragma endregion �����ɽ�Ʈ

#pragma region �浹 ����
			// �浹 ����
			static bool GJK(Collider*, Collider*, Manifold&);
			
			// �浹 ����
			static bool TestSphereSphere(Collider*, Collider*, Manifold&);
			static bool TestSphereAABB(Collider*, Collider*, Manifold&);
			static bool TestSphereOBB(Collider*, Collider*, Manifold&);
			static bool TestSphereConvex(Collider*, Collider*, Manifold&);
#pragma endregion �浹 ����
			// ���� ���� ���� �Ÿ�
			static float PointToSegmentDistance(const Vector3D p, const  Vector3D L1, const  Vector3D L2);

		public:
			static std::function<bool(Collider*, Collider*, Manifold&)> DetectionFunc[4][4];
			static std::function<void(Manifold&)> FindContactFunc[4][4];
			static std::function<bool(const Ray&, Collider*)> RaycastFunc[4];

		private:
			enum GJK_State : size_t
			{
				LINE = 2,
				TRIANGLE = 3,
				TETRAHEDRON = 4,
			};

			enum Cliping : size_t
			{
				OutOut = 0,
				InOut = 1,
				OutIn = 2,
				InIn = 3,
			};

			static bool DoSimplex(Simplex&, Vector3D&);
			static bool DoSimplex2(Simplex&, Vector3D&);
			static bool DoSimplex3(Simplex&, Vector3D&);
			static bool DoSimplex4(Simplex&, Vector3D&);

			static std::vector<Vector3D> FaceClip(
				const std::vector<Vector3D>& _incident, 
				const Edge& _refEdge, 
				const Vector3D& _refNormal, 
				bool remove);

			static size_t EdgeClip(
				Edge& edge, 
				const Vector3D& _refP, 
				const Vector3D& _d, 
				bool _remove);



		/// <summary>
		/// �浹 ���� �κ�.
		/// </summary>
		public:
			static void ComputeImpulse(Manifold&);
			static void ResolveCollision(Manifold&);

		private:
			static float ComputeFriction(float, float);
		};
	}
}


/*
�浹�� �����ϴ� �ý���

*/