#pragma once
#include <vector>
#include "HyruleMath.h"

namespace Hyrule
{
	namespace Physics
	{
		struct Vertex
		{
			Vector3D point;
			std::vector<size_t> index;		// 인접한 버텍스들의 인덱스
		};

		class HillClimbing
		{
		public:
		};
	}
}

/*
버텍스를 트리로 관리하면

*/