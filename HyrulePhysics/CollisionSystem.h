#pragma once

#include <map>

namespace Hyrule
{
	namespace Physics
	{
		class Collider;
		class Manifold;
		class Simplex;

		class CollisionSystem
		{
		public:
			bool CollisionCheck(Collider*, Collider*, Manifold*);
			void CollisionCheck(Collider*, Collider*);

		private:
			std::map<Manifold*, Simplex*> detectionInfo;
		};
	}
}


/*
�浹�� �����ϴ� �ý���

*/