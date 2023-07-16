#pragma once
#pragma comment(lib, "HyruleEngine.lib")
#include "Scene.h"

class Scene01 : public Hyrule::Scene<Scene01>
{
public:
	Scene01(const std::wstring&) noexcept;
	virtual ~Scene01() noexcept = default;

public:
	virtual void Load() noexcept override;
};

