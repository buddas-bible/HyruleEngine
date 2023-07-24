#include "Scene01.h"

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

namespace Hyrule
{
	Scene01::Scene01(const std::wstring& _name) noexcept :
		Scene(_name)
	{}

	void Scene01::Load() noexcept
	{
		GameObject* controller = CreateGameObject(L"Controller");
		Controller* con = controller->AddComponent<Controller>();

		float x = 1.f;
		float y = 1.f;
		float z = 1.f;

		for (auto i = 0; i < 10; i++)
		{
			if (i & 1)
			{
				x *= -1.f;
			}
			if (i & 2)
			{
				y *= -1.f;
			}
			if (i & 4)
			{
				z *= -1.f;
			}

			GameObject* box = CreateGameObject(L"Box0" + std::to_wstring(i));
			box->AddComponent<CubeRenderer>();
			box->GetTransform()->SetLocalPosition(Vector3D(0.f + 5.f * x * i, 0.f + 5.f * y * i, 0.f + 5.f * z * i));
			box->GetTransform()->SetLocalScale(Vector3D(5.f, 5.f, 5.f));
			box->AddComponent<BoxCollider>();

			con->AddControllableObject(VK_F1, box);
		}

		GameObject* sphere = CreateGameObject(L"Sphere01");
		sphere->AddComponent<SphereRenderer>();
		sphere->GetTransform()->SetLocalScale(Vector3D(5.f, 5.f, 5.f));
		sphere->AddComponent<SphereCollider>();
		sphere->AddComponent<RigidBody>();

		con->AddControllableObject(VK_F2, sphere);
		con->AddControllableObject(VK_F1, mainCamera->gameObject);
	}
}