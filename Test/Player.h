#pragma once
#include "MonoBehaviour.h"
#include "FSM.h"

namespace Hyrule
{
	enum class PlayerState : int
	{
		IDLE,
		MOVE,
		DASH,
		ATTACK,
		BLOCK,
		PARRY,
	};

	class Player : public MonoBehaviour
	{
	public:
		Player(GameObject*);
		virtual ~Player() = default;

	private:
		float HP;
		float damage;
		float speed;

	private:
		FSM<Player, PlayerState> fsm;

	public:
		void Update();

	public:
		PlayerState Move();
		PlayerState Dash();

		PlayerState Attack();
		PlayerState Block();
		PlayerState Parry();
	};
}

