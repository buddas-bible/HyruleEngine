#pragma once
#include <exception>
#include <functional>
#include <list>
#include "IDisposable.h"

namespace GRX
{
	template <typename T>
	class IObservable
	{

	public:
		virtual void Subscribe(std::function<void(T)>) abstract;
		virtual void Subscribe(std::function<void(T)>, std::function<void()>) abstract;
		virtual void Subscribe(std::function<void(T)>, std::function<void()>, std::function<void(std::exception)>) abstract;

	};
}