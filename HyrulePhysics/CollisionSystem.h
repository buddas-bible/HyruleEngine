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

		class CollisionSystem
		{
		///
		/// </summary>
		public:
			/// <summary>
			/// �浹 ����
			/// </summary>
			/// <param name=""></param>
			/// <param name=""></param>
			/// <returns></returns>
			bool CollisionCheck(Collider*, Collider*);
			
			/// <summary>
			/// 
			/// </summary>
			Manifold* ComputePenetrationDepth(Collider*, Collider*, Simplex*);
			Vector3D FindSupportPoint(Collider*, Collider*, const Vector3D&);
			void FindSupportEdge(Simplex*);
			void FindSupportFace();
			void FindContactPoint(Collider*, Collider*, const Vector3D&);

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

		/// <summary>
		/// �浹 ���� �κ�.
		/// </summary>
		public:
			void CollisionRespone();
		};
	}
}


/*
�浹�� �����ϴ� �ý���

*/