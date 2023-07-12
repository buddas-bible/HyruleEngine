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
		public:
			bool CollisionCheck(Collider*, Collider*);
			bool Velocity();
			
			Manifold* ComputePenetrationDepth(Collider*, Collider*, Simplex*);
			Vector3D FindSupportPoint(Collider*, Collider*, const Vector3D&);
			void FindSupportEdge(Simplex*);
			void FindSupportFace();
			void FindContactPoint(Collider*, Collider*);

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
		};
	}
}


/*
충돌을 관리하는 시스템

*/