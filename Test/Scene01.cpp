#include "Scene01.h"

#pragma comment(lib, "HyruleMath.lib")
#include "GameObject.h"
#include "Transform.h"

#include "BoxCollider.h"
#include "SphereCollider.h"
#include "CubeRenderer.h"
#include "SphereRenderer.h"

#include "Controller.h"
#include "Camera.h"

namespace Hyrule
{
	Scene01::Scene01(const std::wstring& _name) noexcept :
		Scene(_name)
	{}

	void Scene01::Load() noexcept
	{
		GameObject* box = CreateGameObject(L"Box01");
		box->AddComponent<CubeRenderer>();
		box->GetTransform()->SetLocalPosition(Vector3D(3.f, 0.f, 0.f));
		box->AddComponent<BoxCollider>();

		GameObject* sphere = CreateGameObject(L"Sphere01");
		sphere->AddComponent<SphereRenderer>();
		sphere->AddComponent<SphereCollider>();
	
		GameObject* controller = CreateGameObject(L"Controller");
		auto con = controller->AddComponent<Controller>();
		con->AddControllableObject(VK_F1, box);
		con->AddControllableObject(VK_F2, sphere);
		con->AddControllableObject(VK_F3, mainCamera->gameObject);
	}

}