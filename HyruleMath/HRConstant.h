#pragma once

// #define ToDegree(x) x * (180.0f / PI<float>)
// #define ToRadian(x) x * (PI<float> / 180.f)

namespace Hyrule
{
	template <typename T>
	constexpr T PI = T(3.14159265358979323846);

	constexpr float Epsilon = 1.192092896e-07F;
}