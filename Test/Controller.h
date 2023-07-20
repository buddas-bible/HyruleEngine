#pragma once
#include "Component.h"

namespace Hyrule
{
	class Controller : public Component
	{
	public:
		Controller() noexcept = default;
		virtual ~Controller() noexcept = default;
	};
}

