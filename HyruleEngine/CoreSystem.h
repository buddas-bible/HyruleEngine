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
			INITIALIZAION	= 0,
			PHYSICS			= 10,
			INPUT			= 20,
			GAME_LOGIC		= 30,
			RENDERING		= 40,
			DESTROY			= 50,
			DEBUGRENDERING	= 60,
		};
	};
}

