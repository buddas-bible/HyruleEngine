#pragma once
#include "Component.h"

namespace Hyrule
{
	class GameObject;
	class IRigidBody;

	class RigidBody : public Component
	{
	public:
		RigidBody() = delete;
		RigidBody(GameObject*) noexcept;
		virtual ~RigidBody() = default;

		/// ���� �������������� ��ü�� �̺�Ʈ�� �������ִ� ����.
		/// ��ü�� �̺�Ʈ��... �ִ���...?
		IRigidBody* rigidbody;
	};
}


/*
�ݶ��̴��� ���� ������Ʈ�� �浹 �̺�Ʈ�� �����Ŵ.
��ü�� ���� ������ �浹 ������ �� �� �߰����� ������ ���� ����.
*/