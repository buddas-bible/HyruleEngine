#pragma once
#include <string>
#include <vector>

namespace Hyrule
{
	namespace Physics
	{
		class RigidBody;
		class Collider;
		class Transform;

		struct Object
		{
		public:
			Object() noexcept = delete;
			Object(const std::wstring&) noexcept;
			~Object() noexcept = default;

		public:
			std::wstring name;
			Transform* transform;
			
		public:
			RigidBody* rigidbody;
			std::vector<Collider*> colliders;
		};
	}
}

/*
������Ʈ?
�ݶ��̴�? ��ü? �̰͵��� ������ ������ ������ �ϴµ�...
�̰͵��� ������ �� ������ �Ű������� �ʹ� ����.


���� ������Ʈ �̸�
���� Ʈ������ ���� (��ġ, ȸ��, ������)
���� Ʈ������ ����
���ؽ� ����
�ε��� ����
*/
