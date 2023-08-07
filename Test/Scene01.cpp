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

#include <random>
#include <ctime>
#include <cstdlib>

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
		box->GetTransform()->SetLocalPosition(Vector3D(0.f, 0.f, 0.f));
		box->GetTransform()->SetLocalScale(Vector3D(50.f, 5.f, 50.f));
		box->AddComponent<BoxCollider>();
		Hyrule::RigidBody* rigidBox01 = box->AddComponent<RigidBody>();
		// rigidBox01->SetVelocity({ 2.f, 0.f, 0.f });
		rigidBox01->SetMass(0.f);

		for (auto i = 0; i < 1000; i++)
		{
			GameObject* sphere = CreateGameObject(L"Sphere0" + std::to_wstring(i));
			sphere->AddComponent<SphereRenderer>();
			sphere->GetTransform()->SetLocalPosition(
				Vector3D(
					(float)(rand() % 1000) * pow(-1.f, i + rand() % 2),
					10.f + 5.f * i,
					(float)(rand() % 1000) * pow(-1.f, i + rand() % 2)
				)
			);
			sphere->GetTransform()->SetLocalScale(Vector3D(5.f, 5.f, 5.f));
			sphere->AddComponent<SphereCollider>();
			Hyrule::RigidBody* rigidsphere = sphere->AddComponent<RigidBody>();
			rigidsphere->SetMass(10.f);
		}

		std::srand((unsigned int)time(NULL));
		for (auto i = 2; i < 2000; i++)
		{
			GameObject* box4 = CreateGameObject(L"Box0" + std::to_wstring(i));
			box4->AddComponent<CubeRenderer>();
			box4->GetTransform()->SetLocalPosition(
				Vector3D(
					(float)(rand() % 1000) * pow(-1.f, i + rand() % 2),
					10.f + 5.f * i,
					(float)(rand() % 1000) * pow(-1.f, i + rand() % 2)
				)
			);
			box4->GetTransform()->SetLocalScale(Vector3D(1, 1, 1));
			box4->AddComponent<BoxCollider>();
			Hyrule::RigidBody* rigidBox03 = box4->AddComponent<RigidBody>();
			rigidBox03->SetMass(3.f);
		}

		// GetMainCamera()->gameObject->AddComponent<BoxCollider>();
		// GetMainCamera()->gameObject->GetTransform()->SetLocalScale(Vector3D(5.f, 5.f, 5.f));

		// GetMainCamera()->gameObject->GetTransform()->

		// GetMainCamera()->gameObject->SetParent(box);
		
		// GetMainCamera()->gameObject->SetParent(box2);
		con->AddControllableObject(VK_F1, box);
		// con->AddControllableObject(VK_F2, sphere);
		con->AddControllableObject(VK_F3, GetMainCamera()->gameObject);
	}
}