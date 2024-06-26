#pragma comment(lib, "HyruleMath.lib")

#include "HEntity.h"
#include "HTransform.h"

#include "HBoxCollider.h"
#include "HSphereCollider.h"

#include "CubeRenderer.h"
#include "SphereRenderer.h"

#include "HRigidBody.h"

#include "Controller.h"
#include "HCamera.h"

#include "Scene01.h"

#include <random>
#include <ctime>
#include <cstdlib>

namespace hyrule
{
	Scene01::Scene01(const std::wstring& _name) :
		Scene(_name)
	{}

	void Scene01::Load()
	{
		GameObject* controller = CreateGameObject(L"Controller");
		Controller* con = controller->AddComponent<Controller>();

		GameObject* box = CreateGameObject(L"Box01");
		box->AddComponent<CubeRenderer>();
		box->GetTransform()->SetLocalPosition(Vector3D(0.f, 0.f, 0.f));
		box->GetTransform()->SetLocalScale(Vector3D(150.f, 5.f, 150.f));
		hyrule::BoxCollider* colliderBox01 = box->AddComponent<BoxCollider>();
		// hyrule::RigidBody* rigidBox01 = box->AddComponent<RigidBody>();
		// rigidBox01->SetMass(0.f);

		std::srand((unsigned int)time(NULL));
		for (auto i = 0; i < 10; i++)
		{
			GameObject* sphere = CreateGameObject(L"Sphere0" + std::to_wstring(i));
			sphere->AddComponent<CubeRenderer>();
			sphere->GetTransform()->SetLocalPosition(
				Vector3D(
					// (float)(rand() % 40) * pow(-1.f, i + rand() % 2),
					0.f,
					// (float)(rand() % 2000) * pow(-1.f, i + rand() % 2),
					10.f + 5.f * i,
					0.f
					// (float)(rand() % 40) * pow(-1.f, i + rand() % 2)
				)
			);
			sphere->GetTransform()->SetLocalScale(Vector3D(5.f, 5.f, 5.f));
			sphere->AddComponent<BoxCollider>();
			hyrule::RigidBody* rigidsphere = sphere->AddComponent<RigidBody>();
			rigidsphere->SetMass(3000.f);
		}

		// for (auto i = 2; i < 10; i++)
		// {
		// 	GameObject* box4 = CreateGameObject(L"Box0" + std::to_wstring(i));
		// 	box4->AddComponent<CubeRenderer>();
		// 	box4->GetTransform()->SetLocalPosition(
		// 		Vector3D(
		// 			(float)(rand() % 500) * pow(-1.f, i + rand() % 2),
		// 			(float)(rand() % 500) * pow(-1.f, i + rand() % 2),
		// 			// 10.f + 5.f * i,
		// 			(float)(rand() % 500) * pow(-1.f, i + rand() % 2)
		// 		)
		// 	);
		// 	box4->GetTransform()->SetLocalScale(Vector3D(50.f, 50.f, 50.f));
		// 	hyrule::BoxCollider* colliderBox02 = box4->AddComponent<BoxCollider>();
		// 	hyrule::RigidBody* rigidBox03 = box4->AddComponent<RigidBody>();
		// 	rigidBox03->SetMass(30.f);
		// }

		// GetMainCamera()->gameObject->AddComponent<BoxCollider>();
		// GetMainCamera()->gameObject->GetTransform()->SetLocalScale(Vector3D(5.f, 5.f, 5.f));

		// GetMainCamera()->gameObject->GetTransform()->

		// GetMainCamera()->gameObject->SetParent(box);
		
		// GetMainCamera()->gameObject->SetParent(box2);
		con->AddControllableObject(VK_F1, box);
		// con->AddControllableObject(VK_F2, sphere1);
		con->AddControllableObject(VK_F3, GetMainCamera()->gameObject);
	}
}