#pragma once
#include <vector>

namespace hyrule
{
	namespace Physics
	{
		class RigidBody;
		class Manifold;

		// 잠자고 있는 강체들의 집합
		// 섬 
		class Island
		{
		public:
			void Add(RigidBody*);
			void Add(Manifold*);

			std::vector<RigidBody*> bodies;
			std::vector<Manifold*> contacts;
		};
	}
}