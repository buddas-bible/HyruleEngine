#pragma once
#include "System.h"

namespace Hyrule
{
	class CoreSystem : System<CoreSystem>
	{
	public:
		bool GameProcess();

	private:
		int state{};

		enum EventFunction : int
		{
			INITIALIZATION	= 0,
			PHYSICS			= 10,
			INPUT			= 20,
			GAME_LOGIC		= 30,
			RENDERING		= 40,
			DECOMISSIONING	= 50,
			DEBUGRENDERING	= 60,
		};
	};
}

