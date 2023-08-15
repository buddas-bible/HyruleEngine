#pragma once
#include "Enemy.h"

namespace Hyrule
{
	class RangeEnemy : public Enemy
	{
	public:
		RangeEnemy() = delete;
		RangeEnemy(GameObject*) noexcept;
		virtual ~RangeEnemy() noexcept = default;

	public:
		void Initialize();
		
		virtual EnemyState Attack();
		virtual EnemyState Damaged();
		virtual EnemyState Death();
	};
}

