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
		int HP;				// ü��
		int speed;			// �̵��ӵ�
		int attackRange;	// ���� ����
		int detactRange;	// ���� ����
		int attackType;		// ���� Ÿ��
		float chargeTime;	// �غ� �ð�
		float castTime;		// ���� �ð�
		int damage;			// ������

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

