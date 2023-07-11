#pragma once
#include <random>


namespace Hyrule
{
	class Random
	{
	public:
		Random() noexcept;
		~Random() noexcept = default;

	private:
		std::random_device rd;
		std::mt19937 mersenne;

	public:
		float GetRandom(float _low, float _high);

		int GetRandom(int _low, int _high);
	};
}

