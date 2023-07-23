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

		class CollisionSystem
		{
		public:
			/// <summary>
			/// GJK 충돌 감지
			/// </summary>
			static bool GJKCollisionDetection(Collider*, Collider*, Manifold&);
			// bool CollisionCheck2(Collider*, Collider*);
			
			/// <summary>
			/// EPA 침투 깊이 계산
			/// </summary>
			static void EPAComputePenetrationDepth(Manifold& _manifold);


			static Vector3D FindSupportPoint(Collider*, Collider*, const Vector3D&);
			static void FindContactPoint(Manifold*, const Vector3D&);

		private:
			enum GJK : size_t
			{
				LINE = 2,
				TRIANGLE = 3,
				TETRAHEDRON = 4,
			};

			static bool DoSimplex(Simplex&, Vector3D&);
			static bool DoSimplex2(Simplex&, Vector3D&);
			static bool DoSimplex3(Simplex&, Vector3D&);
			static bool DoSimplex4(Simplex&, Vector3D&);

			static void FaceClip(Face& _incident, const Edge& _refEdge, const Vector3D& _refNormal);
			static void EdgeClip(Edge&, const Vector3D&, const Vector3D&, bool);

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