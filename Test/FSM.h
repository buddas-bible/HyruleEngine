#pragma once
#include <map>
#include <functional>

/*
state에 따라서 저장된 함수가 호출 되도록 한다.
*/

namespace hyrule
{
	template <typename Type, typename Enum>
	class FSM
	{
	private:
		friend typename Type;

		// 상태와 함수만 엮어놓음
		std::map<Enum, std::function<Enum()>> stateFunc;
	
	public:
		FSM() : currState() {}

		Enum currState;

		void Add(Enum _state, std::function<Enum()> _func)
		{
			stateFunc.insert(std::make_pair(_state, _func));
		}

		void Excute()
		{
			currState = stateFunc[currState]();
		}
	};
}

