#pragma once
#include <map>
#include <functional>

/*
state�� ���� ����� �Լ��� ȣ�� �ǵ��� �Ѵ�.
*/

namespace hyrule
{
	template <typename Type, typename Enum>
	class FSM
	{
	private:
		friend typename Type;

		// ���¿� �Լ��� �������
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

