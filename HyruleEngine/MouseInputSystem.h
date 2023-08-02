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
마우스 클릭에 대해서 고민이 많았다.
마우스 입력으로 레이케스팅을 하고 싶을 땐 어떻게 해야할까.


*/