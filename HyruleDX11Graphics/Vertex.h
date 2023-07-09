#pragma once
#include "HyruleMath.h"

namespace Hyrule
{
	struct PC
	{
		Vector3D pos;
		Vector4D color;
	};

	struct PUN
	{
		Vector3D pos;
		Vector2D uv;
		Vector3D normal;
	};

	struct PUNT
	{
		Vector3D pos;
		Vector2D uv;
		Vector3D normal;
		Vector3D tangent;
	};
}