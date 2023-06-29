#pragma once
#include <string>
#include <vector>

namespace Hyrule
{
	struct Matrix4x4;

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

		private:
			std::wstring name;
			Transform* transform;
			
		public:
			RigidBody* rigidbody;
			std::vector<Collider*> colliders;

			Matrix4x4 GetWorldTM();
		};
	}
}

/*
������Ʈ?
�ݶ��̴�? ��ü? �̰͵��� ������ ������ ������ �ϴµ�...
�̰͵��� ������ �� ������ �Ű������� �ʹ� ����.


���� ������Ʈ �̸�
���� Ʈ������ ���� (��ġ, ȸ��, ������)
���� Ʈ������ ���� (��Ʈ����)
���ؽ� ����
�ε��� ����

�� �θ��ڽ� ���踦 ������ �ִ� ��쵵 ������ ������Ʈ������ �˰� �־�� �� ���̴�.

*/
