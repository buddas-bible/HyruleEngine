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
		// WASD �̵�

		return PlayerState::MOVE;
	}

	PlayerState Player::Dash()
	{
		// �����̽��� ������ ���

		return PlayerState::MOVE;
	}

	PlayerState Player::Attack()
	{
		// ���콺 ��Ŭ���� �ϸ� �⺻ ����

		return PlayerState::MOVE;
	}

	PlayerState Player::Block()
	{
		// ���콺 ��Ŭ���� �ϸ� ��� (Ÿ�̹��� ������ �и�)

		return PlayerState::MOVE;
	}

	PlayerState Player::Parry()
	{
		// Ÿ�̹� �°� ���콺 ��Ŭ���� �ϸ� �и�

		return PlayerState::MOVE;
	}
}