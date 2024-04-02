#pragma once
#include "Component.h"

namespace Hyrule
{
	class Behaviour : public Component
	{
	protected:
		Behaviour() = delete;
		Behaviour(Entity* _gameObject);
		~Behaviour() override = default;

	public:
		bool enabled;
	};
}

