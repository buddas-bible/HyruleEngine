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
			void GetSupportPoint(Collider*, Collider*, const Vector3D&);
			void GetSupportEdge(Simplex*);
			void GetSupportFace();
			void FindContactPoint(Collider*, Collider*);

		private:
			std::map<Manifold*, Simplex*> detectionInfo;
		};
	}
}


/*
충돌을 관리하는 시스템

*/