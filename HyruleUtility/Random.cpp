#include "Random.h"

namespace Hyrule
{
	Random::Random() noexcept :
		rd{}, mersenne{ rd()}
	{}

	float Random::GetRandom(float _low, float _high)
	{
		return static_cast<float>(std::uniform_real_distribution<>(_low, _high)(mersenne));
	}

	int Random::GetRandom(int _low, int _high)
	{
		return static_cast<int>(std::uniform_int_distribution<>(_low, _high)(mersenne));
	}
}