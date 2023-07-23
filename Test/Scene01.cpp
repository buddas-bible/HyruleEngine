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
		box->GetTransform()->SetLocalScale(Vector3D(5.f, 5.f, 5.f));
		box->AddComponent<BoxCollider>();



		GameObject* box02 = CreateGameObject(L"Box02");
		box02->AddComponent<CubeRenderer>();
		box02->GetTransform()->SetLocalPosition(Vector3D(100.f, 10.f, 100.f));
		box02->GetTransform()->SetLocalScale(Vector3D(5.f, 5.f, 5.f));
		box02->AddComponent<BoxCollider>();

		GameObject* box03 = CreateGameObject(L"Box03");
		box03->AddComponent<CubeRenderer>();
		box03->GetTransform()->SetLocalPosition(Vector3D(-100.f, 10.f, 100.f));
		box03->GetTransform()->SetLocalScale(Vector3D(5.f, 5.f, 5.f));
		box03->AddComponent<BoxCollider>();

		GameObject* box04 = CreateGameObject(L"Box04");
		box04->AddComponent<CubeRenderer>();
		box04->GetTransform()->SetLocalPosition(Vector3D(100.f, -10.f, -100.f));
		box04->GetTransform()->SetLocalScale(Vector3D(5.f, 5.f, 5.f));
		box04->AddComponent<BoxCollider>();

		GameObject* box05 = CreateGameObject(L"Box05");
		box05->AddComponent<CubeRenderer>();
		box05->GetTransform()->SetLocalPosition(Vector3D(-100.f, 10.f, -100.f));
		box05->GetTransform()->SetLocalScale(Vector3D(5.f, 5.f, 5.f));
		box05->AddComponent<BoxCollider>();



		GameObject* sphere = CreateGameObject(L"Sphere01");
		sphere->AddComponent<SphereRenderer>();
		sphere->GetTransform()->SetLocalScale(Vector3D(5.f, 5.f, 5.f));
		sphere->AddComponent<SphereCollider>();
	


		GameObject* controller = CreateGameObject(L"Controller");
		Controller* con = controller->AddComponent<Controller>();
		con->AddControllableObject(VK_F1, box);
		con->AddControllableObject(VK_F2, sphere);
		con->AddControllableObject(VK_F3, mainCamera->gameObject);
	}

}