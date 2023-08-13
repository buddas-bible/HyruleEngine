#include "Player.h"

namespace Hyrule
{

	Player::Player(GameObject* _gameObject) noexcept :
		Component(_gameObject)
	{
		fsm.Add((int)PlayerState::ATTACK, &Attack);
	}

	void Player::Move()
	{

	}

	void Player::Dash()
	{

	}

	void Player::Attack()
	{

	}

	void Player::Block()
	{

	}

	void Player::Parry()
	{

	}

}