#pragma once

namespace Hyrule
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