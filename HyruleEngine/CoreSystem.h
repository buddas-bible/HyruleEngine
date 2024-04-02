#pragma once
#include "Singleton.h"

namespace Hyrule
{
	class CoreSystem : public Singleton<CoreSystem>
	{
	public:
		bool GameProcess();

		void SetHandle(int);

		float Clamp(float, float, float);

	private:
		bool first = false;
		int state{};

		int hWnd;

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

