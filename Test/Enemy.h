#pragma once
#include "MonoBehaviour.h"
#include "FSM.h"

namespace hyrule
{
	enum class EnemyState : int
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

	class Enemy : public MonoBehaviour
	{
	public:
		Enemy() = delete;
		Enemy(GameObject*);
		virtual ~Enemy() = default;

	protected:
		int		HP;				// 체력
		int		speed;			// 이동속도
		int		attackRange;	// 공격 범위
		int		detactRange;	// 감지 범위
		int		attackType;		// 공격 타입
		float	chargeTime;		// 준비 시간
		float	castTime;		// 시전 시간
		int		damage;			// 데미지

	protected:
		float statetime;
		float detactTime;

		bool detact;			// 감지 여부
		bool attackAble;		// 공격 가능 여부

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

