#pragma once

namespace hyrule
{
	namespace Physics
	{
		class RigidBody;

		class SpringJoint
		{
		public:
			RigidBody* A;
			RigidBody* A;

			float damping;			// ����
			float distance;			// ����
		};
	}
}