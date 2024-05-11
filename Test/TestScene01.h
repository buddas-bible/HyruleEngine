#pragma once
#include "Scene.h"

namespace hyrule
{
	struct Vector3D;

	class TestScene01 : public Scene
	{
	public:
		TestScene01(const std::wstring&);
		virtual ~TestScene01() = default;

		virtual void Load() override;
	};
}
