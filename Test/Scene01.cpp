#pragma comment(lib, "HyruleMath.lib")

#include "GameObject.h"
#include "Transform.h"

#include "BoxCollider.h"
#include "SphereCollider.h"

#include "CubeRenderer.h"
#include "SphereRenderer.h"

#include "RigidBody.h"

#include "Controller.h"
#include "Camera.h"

#include "Scene01.h"

namespace Hyrule
{
	Scene01::Scene01(const std::wstring& _name) noexcept :
		Scene(_name)
	{}

	void Scene01::Load() noexcept
	{
		GameObject* controller = CreateGameObject(L"Controller");
		Controller* con = controller->AddComponent<Controller>();

		GameObject* box = CreateGameObject(L"Box01");
		box->AddComponent<CubeRenderer>();
		box->GetTransform()->SetLocalPosition(Vector3D(0.f, 0.0f, -0.6f));
		box->GetTransform()->SetLocalScale(Vector3D(10.f, 10.f, 10.f));
		box->AddComponent<BoxCollider>();
		Hyrule::RigidBody* rigidBox01 = box->AddComponent<RigidBody>();
		// rigidBox01->SetVelocity({ 2.f, 0.f, 0.f });
		// rigidBox01->SetMass(0.f);

		// GameObject* sphere = CreateGameObject(L"Sphere01");
		// sphere->AddComponent<SphereRenderer>();
		// sphere->GetTransform()->SetLocalScale(Vector3D(5.f, 5.f, 5.f));
		// sphere->AddComponent<SphereCollider>();
		// sphere->AddComponent<RigidBody>();

		GameObject* box2 = CreateGameObject(L"Box02");
		box2->AddComponent<CubeRenderer>();
		box2->GetTransform()->SetLocalPosition(Vector3D(0.f, 10.f, 0.f));
		box2->GetTransform()->SetLocalScale(Vector3D(10.f, 10.f, 10.f));
		box2->AddComponent<BoxCollider>();
		Hyrule::RigidBody* rigidBox02 = box2->AddComponent<RigidBody>();
		// rigidBox02->SetVelocity(Vector3D{ -2.f, 0.f, 0.f });

		// GetMainCamera()->gameObject->GetTransform()->SetLocalPosition({ 0, 0.5f, 1.f });

		GetMainCamera()->gameObject->SetParent(box2);
		con->AddControllableObject(VK_F1, box);
		con->AddControllableObject(VK_F2, box2);
		con->AddControllableObject(VK_F3, GetMainCamera()->gameObject);
	}
}