#pragma once

namespace Hyrule
{
	class KeyInput
	{
	public:
		constexpr KeyInput() = default;
		~KeyInput() = default;

	private:
		short key[0xFF];

	public:
		void Update();
		bool KeyPress(int);
		bool KeyPressedNow(int);
		bool KeyRelease(int);
		bool KeyReleasedNow(int);
	};
}

