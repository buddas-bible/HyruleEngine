#pragma once
#include "ICollider.h"

#include <vector>
#include "HyruleMath.h"

namespace Hyrule
{
	class Transform;
	class RigidBody;

	class Collider
	{
	public:
		Collider() noexcept = default;
		~Collider() noexcept = default;

	private:
		RigidBody* rigidbody;
		Transform* transform;

		// �޽� ������ ��� �ұ�...
		std::vector<Vector3D> vertex;
		std::vector<int> index;

		void GetWorldTransform();
	};

}


/*
����� �ǳ�
���ؽ�


*/