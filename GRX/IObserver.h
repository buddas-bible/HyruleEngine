#pragma once
#include <functional>
#include <exception>

namespace GRX
{
	template <typename T>
	class IObserver
	{
	public:
		virtual ~IObserver()
		{

		}
	public:
		virtual void OnNext(T) abstract;
		virtual void OnComplete() abstract;
		virtual void OnError(std::exception) abstract;
	};
}