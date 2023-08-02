#pragma once
#include "System.h"
#pragma comment(lib, "HyruleUtility.lib")
#include "../HyruleUtility/KeyInput.h"

namespace Hyrule
{
	class InputSystem : public System<InputSystem>
	{
	private:
		KeyInput keyInput;

	public:
		void Update();
		bool KeyDown(int);
		bool KeyDownNow(int);
		bool KeyUp(int);
		bool KeyUpStay(int);
	};
}

