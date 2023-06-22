#include "Matrix3x3.h"

namespace Hyrule
{

	Matrix3x3::Matrix3x3(
		float e00, float e01, float e02, 
		float e10, float e11, float e12, 
		float e20, float e21, float e22) noexcept
		:
		e{e00, e01, e02, e10, e11, e12, e20, e21, e22}
	{

	}
}
