#include "Player.h"

namespace Hyrule
{

	Player::Player(GameObject* _gameObject) noexcept :
		Component(_gameObject)
	{
		fsm.Add(PlayerState::MOVE, [this]() -> PlayerState { return this->Move(); });
		fsm.Add(PlayerState::DASH, [this]() -> PlayerState { return this->Dash(); });
		fsm.Add(PlayerState::ATTACK, [this]() -> PlayerState { return this->Attack(); });
		fsm.Add(PlayerState::BLOCK, [this]() -> PlayerState { return this->Block(); });
		fsm.Add(PlayerState::PARRY, [this]() -> PlayerState { return this->Parry(); });
	}


	void Player::Update()
	{
		fsm.Excute();
	}

	PlayerState Player::Move()
	{
		return PlayerState::MOVE;
	}

	PlayerState Player::Dash()
	{
		return PlayerState::MOVE;
	}

	PlayerState Player::Attack()
	{
		return PlayerState::MOVE;
	}

	PlayerState Player::Block()
	{
		return PlayerState::MOVE;
	}

	PlayerState Player::Parry()
	{
		return PlayerState::MOVE;
	}
}