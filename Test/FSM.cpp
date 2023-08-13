#include "FSM.h"


namespace Hyrule
{
	void FSM::Add(int _state, std::function<void()> _func)
	{
		stateFunc.insert(std::make_pair(_state, _func));
	}
}