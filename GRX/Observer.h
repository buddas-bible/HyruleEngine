#pragma once
#include <functional>
#include <exception>
#include <vector>
#include "IObserver.h"

namespace GRX
{
	template <typename T>
	class Observer : public IObserver<T>
	{
	public:
		virtual ~Observer() {};

	public:
		Observer(std::function<void(T)>);
		Observer(std::function<void(T)>, std::function<void()>);
		Observer(std::function<void(T)>, std::function<void()>, std::function<void(std::exception)>);

	public:
		virtual void OnNext(T) override;
		virtual void OnComplete() override;
		virtual void OnError(std::exception) override;

	public:
		std::function<void(T)> onNextCallback;
		std::function<void()> onCompleteCallback;
		std::function<void(std::exception)> onErrorCallback;
	};

	template<typename T>
	Observer<T>::Observer(std::function<void(T)> onNext)
		:onNextCallback(onNext)
	{

	}

	template<typename T>
	Observer<T>::Observer(std::function<void(T)> onNext, std::function<void()> onComplete, std::function<void(std::exception)> onError)
		:onNextCallback(onNext), onCompleteCallback(onComplete), onErrorCallback(onError)
	{

	}

	template<typename T>
	Observer<T>::Observer(std::function<void(T)> onNext, std::function<void()> onComplete)
		:onNextCallback(onNext), onCompleteCallback(onComplete)
	{

	}


	template <typename T>
	void Observer<T>::OnNext(T data)
	{
		if (onNextCallback)
			onNextCallback(data);
	}

	template <typename T>
	void Observer<T>::OnComplete()
	{
		if (onCompleteCallback)
			onCompleteCallback();
	}

	template <typename T>
	void Observer<T>::OnError(std::exception e)
	{
		if (onErrorCallback)
			onErrorCallback(e);
	}
}