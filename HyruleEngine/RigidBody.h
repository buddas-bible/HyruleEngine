#pragma once
#include "Component.h"

namespace Hyrule
{
	class RigidBody : public Component
	{
	public:
		RigidBody() = default;
		virtual ~RigidBody() = default;
	};
}


/*
�ݶ��̴��� ���� ������Ʈ�� �浹 �̺�Ʈ�� �����Ŵ.
��ü�� ���� ������ �浹 ������ �� �� �߰����� ������ ���� ����.
*/