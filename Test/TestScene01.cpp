#include "TestScene01.h"
#pragma comment(lib, "HyruleMath.lib")

#include "GameObject.h"
#include "Transform.h"

#include "BoxCollider.h"
#include "SphereCollider.h"

#include "CubeRenderer.h"
#include "SphereRenderer.h"

#include "RigidBody.h"

#include "Controller.h"
#include "Player.h"
#include "PlayerController.h"

#include "Camera.h"

namespace Hyrule
{
	TestScene01::TestScene01(const std::wstring& _name) noexcept :
		Scene(_name)
	{}

	void TestScene01::Load() noexcept
	{
		GameObject* ground = CreateGameObject(L"Ground");
		ground->AddComponent<BoxCollider>();
		ground->AddComponent<CubeRenderer>();
		ground->GetTransform()->SetLocalScale(Vector3D(100.f, 0.5f, 100.f));

		GameObject* controller = CreateGameObject(L"Controller");
		Controller* con = controller->AddComponent<Controller>();
		con->AddControllableObject(VK_F1, nullptr);
		con->AddControllableObject(VK_F3, GetMainCamera()->gameObject);

	}
}