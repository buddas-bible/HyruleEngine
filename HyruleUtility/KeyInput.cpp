#include "KeyInput.h"
#include "framework.h"

namespace hyrule
{
	void KeyInput::Update()
	{
		for (int i = 0; i < 0xFF; i++)
		{
			key[i] = GetAsyncKeyState(i);
		}
	}

	bool KeyInput::KeyPress(int _key)
	{
		return key[_key] & 0x8001;
	}

	bool KeyInput::KeyPressedNow(int _key)
	{
		return key[_key] & 0x8000;
	}

	bool KeyInput::KeyRelease(int _key)
	{
		return key[_key] & 0x0000;
	}

	bool KeyInput::KeyReleasedNow(int _key)
	{
		return key[_key] & 0x0001;
	}
}