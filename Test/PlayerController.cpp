#include "PlayerController.h"

#include "Entity.h"
#include "RigidBody.h"
#include "InputSystem.h"

namespace Hyrule
{
	PlayerController::PlayerController(GameObject* _gameObject) :
		Component(_gameObject)
	{

	}

	void Hyrule::PlayerController::Awake()
	{

	}

	void Hyrule::PlayerController::Start()
	{

	}

	void Hyrule::PlayerController::FixedUpdate()
	{

	}

	void Hyrule::PlayerController::Update()
	{
		auto& input = InputSystem::GetInstance();

		if (input.KeyDown('W'))
		{
			Move(Vector3D::Forward() * speed);
		}
		if (input.KeyDown('S'))
		{
			Move(Vector3D::Forward() * -speed);
		}
		if (input.KeyDown('A'))
		{
			Move(Vector3D::Right() * -speed);
		}
		if (input.KeyDown('D'))
		{
			Move(Vector3D::Right() * speed);
		}
	}

	void Hyrule::PlayerController::LateUpdate()
	{

	}

	void PlayerController::Move(Vector3D _force)
	{
		gameObject->GetComponent<Hyrule::RigidBody>()->AddForce(_force);
	}

}