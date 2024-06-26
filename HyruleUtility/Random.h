#pragma once
#include <random>


namespace hyrule
{
	class Random
	{
	public:
		Random();
		~Random() = default;

	private:
		std::random_device rd;
		std::mt19937 mersenne;

	public:
		float GetRandom(float _low, float _high);
		int GetRandom(int _low, int _high);
	};
}

