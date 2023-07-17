#pragma once

#include <map>

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
		///
		/// </summary>
		public:
			/// <summary>
			/// GJK �浹 ����
			/// </summary>
			bool GJKCollisionDetection(Collider*, Collider*);
			// bool CollisionCheck2(Collider*, Collider*);
			
			/// <summary>
			/// EPA ħ�� ���� ���
			/// </summary>
			void ComputePenetrationDepth(Manifold* _manifold);
			Vector3D FindSupportPoint(Collider*, Collider*, const Vector3D&);
			std::pair<Edge*, float> FindClosestEdge(Simplex*);
			std::pair<Face*, float> FindClosestFace(Simplex*);
			void FindContactPoint(Manifold*, const Vector3D&);

		private:
			enum GJK : size_t
			{
				LINE = 2,
				TRIANGLE = 3,
				TETRAHEDRON = 4,
			};

			std::map<Manifold*, Simplex*> detectionInfo;

			bool DoSimplex(Simplex&, Vector3D&);
			bool DoSimplex2(Simplex&, Vector3D&);
			bool DoSimplex3(Simplex&, Vector3D&);
			bool DoSimplex4(Simplex&, Vector3D&);

			void FaceClip(Face& _incident, const Edge& _refEdge, const Vector3D& _refNormal);
			void EdgeClip(Edge&, const Vector3D&, const Vector3D&, bool);

		/// <summary>
		/// �浹 ���� �κ�.
		/// </summary>
		public:
			void CollisionRespone(float);
			void ComputeVelocity();
			void ComputeImpulse();
			void ComputePosition();
			void ResolveCollision();
		};
	}
}


/*
�浹�� �����ϴ� �ý���

*/