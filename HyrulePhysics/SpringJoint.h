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

			float damping;			// ∞®ºË
			float distance;			// ±Ê¿Ã
		};
	}
}