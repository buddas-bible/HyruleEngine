#pragma once
#include "Component.h"
#include "FSM.h"

namespace Hyrule
{
	enum class EnemyState
	{
		IDLE,			// PATROL
		MOVE,			// PATROL
		TRUN,			// PATROL
		
		RETURN,

		DETACT,
		CHASE,

		ATTACK,
		DAMAGED,
		DEATH,
	};

	class Enemy : public Component
	{
	public:
		Enemy() = delete;
		Enemy(GameObject*) noexcept;
		virtual ~Enemy() noexcept = default;

	protected:
		int HP;				// 체력
		int speed;			// 이동속도
		int attackRange;	// 공격 범위
		int detactRange;	// 감지 범위
		int attackType;		// 공격 타입
		float chargeTime;	// 준비 시간
		float castTime;		// 시전 시간
		int damage;			// 데미지

	protected:
		float statetime;
		float detactTime;

		bool detact;

	protected:
		FSM<Enemy, EnemyState> fsm;

	public:
		virtual EnemyState Idle();
		virtual EnemyState Move();
		virtual EnemyState Trun();
		virtual EnemyState Retrun();

		virtual EnemyState Detact();
		virtual EnemyState Chase();

		virtual EnemyState Attack();
		virtual EnemyState Damaged();
		virtual EnemyState Death();

	public:
		bool isReturn();

	public:
		virtual void Update();
		virtual void OnCollisionEnter(Collider*);
		virtual void OnCollisionStay(Collider*);
		virtual void OnCollisionExit(Collider*);
	};
}

