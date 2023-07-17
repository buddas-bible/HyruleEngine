#pragma once
#include "Scene.h"

class Scene01 : public Hyrule::Scene
{
public:
	Scene01(const std::wstring&) noexcept;
	virtual ~Scene01() noexcept = default;

	virtual void Load() noexcept override;
};

