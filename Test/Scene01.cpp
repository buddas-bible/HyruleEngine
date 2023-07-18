#include "Scene01.h"

#include "GameObject.h"
#include "BoxCollider.h"
#include "CubeRenderer.h"

namespace Hyrule
{
	Scene01::Scene01(const std::wstring& _name) noexcept :
		Scene(_name)
	{}

	void Scene01::Load() noexcept
	{
		GameObject* box = CreateGameObject(L"Box01");
		box->AddComponent<CubeRenderer>();
		// box->AddComponent<BoxCollider>();
	}

}