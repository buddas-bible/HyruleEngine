#pragma once
#include <vector>

namespace hyrule
{
	namespace Physics
	{
		class RigidBody;
		class Manifold;

		// ���ڰ� �ִ� ��ü���� ����
		// �� 
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