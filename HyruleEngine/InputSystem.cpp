#include "InputSystem.h"

namespace Hyrule
{
	void InputSystem::Update()
	{
		keyInput.Update();
	}

	bool InputSystem::KeyPress(int _input)
	{
		return keyInput.KeyPress(_input);
	}

	bool InputSystem::KeyPressedNow(int _input)
	{
		return keyInput.KeyPressedNow(_input);
	}

	bool InputSystem::KeyRelease(int _input)
	{
		return keyInput.KeyRelease(_input);
	}

	bool InputSystem::KeyReleasedNow(int _input)
	{
		return keyInput.KeyReleasedNow(_input);
	}

}