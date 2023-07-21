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
		bool KeyPress(int);
		bool KeyPressedNow(int);
		bool KeyRelease(int);
		bool KeyReleasedNow(int);
	};
}

