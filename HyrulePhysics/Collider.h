#pragma once
#include "ICollider.h"

#include <vector>
#include "HyruleMath.h"

namespace Hyrule
{
	namespace Physics
	{
		class Object;

		class Collider : public ICollider
		{
		public:
			Collider() noexcept = default;
			~Collider() noexcept = default;

		private:
			Object* object;

			// �޽� ������ ��� �ұ�...
			std::vector<Hyrule::Vector3D> vertex;
			std::vector<int> index;
		};
	}
}


/*
����� �ǳ�
���ؽ�


*/