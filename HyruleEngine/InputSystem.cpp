#include "InputSystem.h"

namespace hyrule
{
	void InputSystem::Update()
	{
		keyInput.Update();
	}

	bool InputSystem::KeyDown(int _input)
	{
		return keyInput.KeyPress(_input);
	}

	bool InputSystem::KeyDownNow(int _input)
	{
		return keyInput.KeyPressedNow(_input);
	}

	bool InputSystem::KeyUpStay(int _input)
	{
		return keyInput.KeyRelease(_input);
	}

	bool InputSystem::KeyUp(int _input)
	{
		return keyInput.KeyReleasedNow(_input);
	}
}