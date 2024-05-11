#pragma once
#include "Singleton.h"
#pragma comment(lib, "HyruleUtility.lib")
#include "../HyruleUtility/KeyInput.h"

namespace hyrule
{
	class InputSystem : public Singleton<InputSystem>
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

