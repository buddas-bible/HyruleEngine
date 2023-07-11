#pragma once


namespace Hyrule
{
	class KeyInput
	{
	public:
		constexpr KeyInput() noexcept = default;
		~KeyInput() noexcept = default;

	private:
		short key[0xFF];

	public:
		void Update() noexcept;
		bool KeyPress(int) noexcept;
		bool KeyPressedNow(int) noexcept;
		bool KeyRelease(int) noexcept;
		bool KeyReleasedNow(int) noexcept;
	};
}

