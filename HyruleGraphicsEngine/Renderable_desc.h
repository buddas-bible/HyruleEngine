#pragma once
#include <string>

namespace Hyrule
{
	enum MESH_TYPE : int
	{
		CUBE		= 0,
		PLANE		= 10,
		SPHERE		= 20,
		CAPSULE		= 30,
		그외무언가	= 40,
	};

	struct RENDERABLE_DESC
	{
		int meshType;
		std::wstring meshName;
	};
}