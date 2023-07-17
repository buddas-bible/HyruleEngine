#pragma once
#include "System.h"

namespace Hyrule
{
	class CoreSystem : public System<CoreSystem>
	{
	public:
		CoreSystem() noexcept = default;
		~CoreSystem() noexcept = default;
		CoreSystem(const CoreSystem&) = delete;
		void operator=(const CoreSystem&) = delete;

	public:
		bool GameProcess() noexcept;

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

