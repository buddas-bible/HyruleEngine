#pragma once
#include "Scene.h"

namespace Hyrule
{
	struct Vector3D;

	class TestScene01 : public Scene
	{
	public:
		TestScene01(const std::wstring&) noexcept;
		virtual ~TestScene01() noexcept = default;

		virtual void Load() noexcept override;
	};
}
