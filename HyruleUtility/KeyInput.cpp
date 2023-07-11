#include "KeyInput.h"
#include "framework.h"

namespace Hyrule
{
	void KeyInput::Update() noexcept
	{
		for (int i = 0; i < 0xFF; i++)
		{
			key[i] = GetAsyncKeyState(i);
		}
	}

	bool KeyInput::KeyPress(int _key) noexcept
	{
		return key[_key] & 0x8001;
	}

	bool KeyInput::KeyPressedNow(int _key) noexcept
	{
		return key[_key] & 0x8000;
	}

	bool KeyInput::KeyRelease(int _key) noexcept
	{
		return key[_key] & 0x0000;
	}

	bool KeyInput::KeyReleasedNow(int _key) noexcept
	{
		return key[_key] & 0x0001;
	}
}