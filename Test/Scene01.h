#pragma once
#include "Scene.h"

namespace Hyrule
{
	struct Vector3D;

	class Scene01 : public Scene
	{
	public:
		Scene01(const std::wstring&);
		virtual ~Scene01() = default;

		virtual void Load() override;
	};
}
