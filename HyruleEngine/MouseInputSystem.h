#pragma once
#include "System.h"

namespace Hyrule
{
	class MouseInputSystem : public System<MouseInputSystem>
	{
	public:
		MouseInputSystem() noexcept = default;
		virtual ~MouseInputSystem() noexcept = default;

	public:
		void MouseEvent();

	};
}

/*
���콺 Ŭ���� ���ؼ� ����� ���Ҵ�.
���콺 �Է����� �����ɽ����� �ϰ� ���� �� ��� �ؾ��ұ�.


*/