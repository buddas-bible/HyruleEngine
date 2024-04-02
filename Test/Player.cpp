#include "Player.h"

namespace Hyrule
{

	Player::Player(GameObject* _gameObject) :
		MonoBehaviour(_gameObject)
	{
		fsm.Add(
			PlayerState::MOVE,
			std::bind(&Player::Move, this)
		);
		fsm.Add(
			PlayerState::DASH,
			std::bind(&Player::Dash, this)
		);
		fsm.Add(
			PlayerState::ATTACK, 
			std::bind(&Player::Attack, this)
		);
		fsm.Add(
			PlayerState::BLOCK, 
			std::bind(&Player::Block, this)
		);
		fsm.Add(
			PlayerState::PARRY, 
			std::bind(&Player::Parry, this)
		);
	}


	void Player::Update()
	{
		fsm.Excute();
	}

	PlayerState Player::Move()
	{
		// WASD 이동

		return PlayerState::MOVE;
	}

	PlayerState Player::Dash()
	{
		// 스페이스바 누르면 대시

		return PlayerState::MOVE;
	}

	PlayerState Player::Attack()
	{
		// 마우스 좌클릭을 하면 기본 공격

		return PlayerState::MOVE;
	}

	PlayerState Player::Block()
	{
		// 마우스 우클릭을 하면 방어 (타이밍이 맞으면 패링)

		return PlayerState::MOVE;
	}

	PlayerState Player::Parry()
	{
		// 타이밍 맞게 마우스 우클릭을 하면 패링

		return PlayerState::MOVE;
	}
}