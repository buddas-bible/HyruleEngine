#pragma once
#include "Scene.h"

namespace Hyrule
{
	class Scene01 : public Scene
	{
	public:
		Scene01(const std::wstring&) noexcept;
		virtual ~Scene01() noexcept = default;

		virtual void Load() noexcept override;
	};
}
