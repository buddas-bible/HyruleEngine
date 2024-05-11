#pragma once
#include "HComponent.h"

namespace hyrule
{
	class Behaviour : public HComponent
	{
	protected:
		Behaviour() = delete;
		Behaviour(HEntity* _entity);
		~Behaviour() override = default;

	public:
		bool enabled;
	};
}

