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
			std::vector<size_t> index;		// ������ ���ؽ����� �ε���
		};

		class HillClimbing
		{
		public:
		};
	}
}

/*
���ؽ��� Ʈ���� �����ϸ�

*/