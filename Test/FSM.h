#pragma once
#include <map>
#include <functional>

/*
state에 따라서 저장된 함수가 호출 되도록 한다.
*/

namespace Hyrule
{
	class FSM
	{
	private:
		int currState;
		int prevState;

		std::map<int, std::function<void()>> stateFunc;
	
	public:
		void Add(int, std::function<void()>);

	public:
	};
}

