#pragma once

#include <map>
#include <list>
#include "Manager.h"
#include "Manifold.h"
#include "Simplex.h"

namespace Hyrule
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
		struct BoxCollider;
		struct PlaneCollider;
		struct SphereCollider;
		struct ConvexCollider;

		typedef bool (CollisionFunc)(Collider*, Collider*, Manifold&);
		typedef bool (RaycastFunc)(const Ray&, Collider*);

		class CollisionSystem
		{
		public:
			static void DetectionFuncInitialize();

			/// <summary>
			/// GJK 충돌 감지
			/// </summary>
			static bool GJK(Collider*, Collider*, Manifold&);
			
			/// <summary>
			/// EPA 침투 깊이 계산
			/// </summary>
			static void EPA(Manifold&);


			static Vector3D FindSupportPoint(Collider*, Collider*, const Vector3D&);

			static void FindContactPoint(Manifold&);

		private:
			static bool Raycast(const Ray&, Collider*);
			static bool RaycastToSphere(const Ray&, Collider*);
			static bool RaycastToBox(const Ray&, Collider*);
			static bool RaycastToCapsule(const Ray&, Collider*);
			static bool RaycastToPlane(const Ray&, Collider*);
			static bool RaycastToConvex(const Ray&, Collider*);

			static bool SphereToSphere(Collider*, Collider*, Manifold&);
			static bool SphereToBox(Collider*, Collider*, Manifold&);
			static bool SphereToCapsule(Collider*, Collider*, Manifold&);
			static bool SphereToConvex(Collider*, Collider*, Manifold&);
			
			static bool BoxToBox(Collider*, Collider*, Manifold&);
			static bool BoxToCapsule(Collider*, Collider*, Manifold&);
			static bool BoxToConvex(Collider*, Collider*, Manifold&);

			static bool CapsuleToCapsule(Collider*, Collider*, Manifold&);
			static bool CapsuleToConvex(Collider*, Collider*, Manifold&);
			
			static bool ConvexToConvex(Collider*, Collider*, Manifold&);

			static float PointToSegmentDistance(const Vector3D p, const  Vector3D L1, const  Vector3D L2);


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
		/// 충돌 대응 부분.
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
충돌을 관리하는 시스템

*/