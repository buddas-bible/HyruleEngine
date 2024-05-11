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
		// PATROL ���¿��� �������� �÷��̾ ������ 1�� �̻� ������ Detact ���·� �Ѿ
		if (detactTime >= 1.f)
		{
			detactTime = 0.f;
			statetime = 0.f;
			return EnemyState::DETACT;
		}

		// 0.5�ʰ� ��������
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
		// PATROL ���¿��� �������� �÷��̾ ������ 1�� �̻� ������ Detact ���·� �Ѿ
		if (detactTime >= 1.f)
		{
			detactTime = 0.f;
			statetime = 0.f;
			return EnemyState::DETACT;
		}

		// 3�ʰ� �������� �̵���
		auto transfrom = gameObject->GetTransform();
		auto position = transfrom->GetLocalPosition();

		auto dL = transfrom->GetForward() * this->speed * DELTATIME_;
		transfrom->SetLocalPosition(position + dL);

		if (statetime >= 3.f)
		{
			// ��ŸŸ�� ������ ���ϰ� �̵��ϰų� ���ư��� ��찡 ���� �� ����
			// �̺κп� ���ؼ��� ����� �غ���
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
		// PATROL ���¿��� �������� �÷��̾ ������ 1�� �̻� ������ Detact ���·� �Ѿ
		if (detactTime >= 1.f)
		{
			detactTime = 0.f;
			statetime = 0.f;
			return EnemyState::DETACT;
		}

		// 180�� ȸ���� 1�ʰ� �ؾ���.
		auto transfrom = gameObject->GetTransform();
		auto rotation = transfrom->GetLocalQuaternion();

		// *** �����ؾ���.
		// �̴�ζ�� 1�ʰ� 180���� ȸ���ϴ°� �ƴ�
		// �� ������ 180�� �� ȸ����.
		auto theta = ToQuaternion(Vector3D::Up(), ToRadian(180.f * DELTATIME_));
		transfrom->SetLocalQuaternion(rotation * theta);

		if (statetime >= 1.f)
		{
			// ��ŸŸ�� ������ ���ϰ� �̵��ϰų� ���ư��� ��찡 ���� �� ����
			// �̺κп� ���ؼ��� ����� �غ���
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

		// ���ư� ��, ü���� ȸ���ϴ� �׷��� ������?
		if (isReturn())
		{
			// ���ڸ��� ���ư����� PATROL �ٽ� ������
			return EnemyState::IDLE;
		}
		else
		{
			// ���� �ڸ��� ���ư��� �ൿ
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
			// ���� ������ ����� ������.
			// ���� �ִ� ��ġ�� �̵��� ���� ���� ������?
			return EnemyState::RETURN;
		}
		else if (detact)
		{
			// ���� ���� �ȿ� ������ ������
			return EnemyState::ATTACK;
		}
		else
		{
			// �׷��� �ʴٸ� �߰� ��带 ������
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
		// �÷��̾ ������
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