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

	private:
		FSM fsm;

	public:
		void Move();
		void Dash();

		void Attack();
		void Block();
		void Parry();
	};
}

