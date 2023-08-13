#pragma once
#include <map>
#include <functional>

/*
state�� ���� ����� �Լ��� ȣ�� �ǵ��� �Ѵ�.
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

