#pragma once
#include "Component.h"
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

	class Player : public Component
	{
	public:
		Player(GameObject*) noexcept;
		virtual ~Player() noexcept = default;

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

