#include "Enemy.h"

#include "HyruleMath.h"
#include "HEntity.h"
#include "HTransform.h"

namespace hyrule
{
#define DELTATIME_ 0.016f

	Enemy::Enemy(GameObject* _gameObject) : 
		Component(_gameObject)
	{
		fsm.Add(EnemyState::IDLE,
			std::bind(&Enemy::Idle, this)
		);
		fsm.Add(EnemyState::MOVE,
			std::bind(&Enemy::Move, this)
		);
		fsm.Add(EnemyState::TRUN,
			std::bind(&Enemy::Trun, this)
		);		
		fsm.Add(EnemyState::RETURN,
			std::bind(&Enemy::Retrun, this)
		);

		fsm.Add(EnemyState::DETACT,
			std::bind(&Enemy::Detact, this)
		);
		fsm.Add(EnemyState::CHASE,
			std::bind(&Enemy::Chase, this)
		);

		fsm.Add(EnemyState::ATTACK,
			std::bind(&Enemy::Attack, this)
		);
		fsm.Add(EnemyState::DAMAGED,
			std::bind(&Enemy::Damaged, this)
		);
		fsm.Add(EnemyState::DEATH,
			std::bind(&Enemy::Death, this)
		);
	}

	void Enemy::Update()
	{
		if (detact)
		{
			detactTime += DELTATIME_;
		}
		else
		{
			detactTime = 0.f;
		}

		statetime += DELTATIME_;
		fsm.Excute();
	}

	EnemyState Enemy::Idle()
	{
		// PATROL 상태에서 언제든지 플레이어가 범위에 1초 이상 있으면 Detact 상태로 넘어감
		if (detactTime >= 1.f)
		{
			detactTime = 0.f;
			statetime = 0.f;
			return EnemyState::DETACT;
		}

		// 0.5초간 멈춰있음
		if (statetime >= 0.5f)
		{
			statetime = 0.f;
			return EnemyState::MOVE;
		}
		else
		{
			return EnemyState::IDLE;
		}
	}

	EnemyState Enemy::Move()
	{
		// PATROL 상태에서 언제든지 플레이어가 범위에 1초 이상 있으면 Detact 상태로 넘어감
		if (detactTime >= 1.f)
		{
			detactTime = 0.f;
			statetime = 0.f;
			return EnemyState::DETACT;
		}

		// 3초간 전방으로 이동함
		auto transfrom = gameObject->GetTransform();
		auto position = transfrom->GetLocalPosition();

		auto dL = transfrom->GetForward() * this->speed * DELTATIME_;
		transfrom->SetLocalPosition(position + dL);

		if (statetime >= 3.f)
		{
			// 델타타임 때문에 과하게 이동하거나 돌아가는 경우가 있을 수 있음
			// 이부분에 대해서는 고민을 해보자
			statetime = 0.f;
			return EnemyState::IDLE;
		}
		else
		{
			return EnemyState::MOVE;
		}
	}

	EnemyState Enemy::Trun()
	{
		// PATROL 상태에서 언제든지 플레이어가 범위에 1초 이상 있으면 Detact 상태로 넘어감
		if (detactTime >= 1.f)
		{
			detactTime = 0.f;
			statetime = 0.f;
			return EnemyState::DETACT;
		}

		// 180도 회전을 1초간 해야함.
		auto transfrom = gameObject->GetTransform();
		auto rotation = transfrom->GetLocalQuaternion();

		// *** 수정해야함.
		// 이대로라면 1초간 180도를 회전하는게 아닌
		// 매 프레임 180도 씩 회전함.
		auto theta = ToQuaternion(Vector3D::Up(), ToRadian(180.f * DELTATIME_));
		transfrom->SetLocalQuaternion(rotation * theta);

		if (statetime >= 1.f)
		{
			// 델타타임 때문에 과하게 이동하거나 돌아가는 경우가 있을 수 있음
			// 이부분에 대해서는 고민을 해보자
			statetime = 0.f;
			return EnemyState::IDLE;
		}
		else
		{
			return EnemyState::TRUN;
		}
	}

	EnemyState Enemy::Retrun()
	{
		detactTime = 0.f;
		statetime = 0.f;

		// 돌아갈 때, 체력이 회복하는 그런게 있을까?
		if (isReturn())
		{
			// 제자리로 돌아갔으면 PATROL 다시 시작함
			return EnemyState::IDLE;
		}
		else
		{
			// 원래 자리로 돌아가는 행동
			return EnemyState::RETURN;
		}
	}

	EnemyState Enemy::Detact()
	{
		if (!detact)
		{
			detactTime = 0.f;
			statetime = 0.f;
			return EnemyState::RETURN;
		}

		if (detactTime > 1.f)
		{
			detactTime = 0.f;
			statetime = 0.f;
			return EnemyState::CHASE;
		}
		else
		{
			return EnemyState::DETACT;
		}
	}

	EnemyState Enemy::Chase()
	{
		if (!detact)
		{
			// 감지 범위를 벗어나면 순찰함.
			// 원래 있던 위치로 이동할 수도 있지 않을까?
			return EnemyState::RETURN;
		}
		else if (detact)
		{
			// 공격 범위 안에 들어오면 공격함
			return EnemyState::ATTACK;
		}
		else
		{
			// 그렇지 않다면 추격 모드를 유지함
			return EnemyState::CHASE;
		}
	}

	EnemyState Enemy::Attack()
	{
		return EnemyState::CHASE;
	}

	EnemyState Enemy::Damaged()
	{
		return EnemyState::CHASE;
	}

	EnemyState Enemy::Death()
	{
		return EnemyState::CHASE;
	}

	bool Enemy::isReturn()
	{
		return false;
	}

	void Enemy::OnCollisionEnter(Collider* _collision)
	{
		// 플레이어가 감지됨
		// if (_collision->GetName() == L"Player")
		// {
			detact = true;
		// }
	}

	void Enemy::OnCollisionStay(Collider* _collision)
	{

	}

	void Enemy::OnCollisionExit(Collider* _collision)
	{
		// if (_collision->GetName() == L"Player")
		// {
			detact = false;
		// }
	}
}