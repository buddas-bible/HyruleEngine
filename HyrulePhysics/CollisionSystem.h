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
			bool CollisionCheck(Collider*, Collider*, Manifold*);
			
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

			void Simplex2(Simplex*, const Vector3D&);
			void Simplex3(Simplex*, const Vector3D&);
			void Simplex4(Simplex*, const Vector3D&);
		};
	}
}


/*
충돌을 관리하는 시스템

*/