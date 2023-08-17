#pragma once
#include <functional>
#include <exception>
#include <vector>
#include "IObserver.h"
#include "IObservable.h"
#include "Observable.h"

namespace GRX
{
	template <typename T>
	class SkipWhileObserver : public Observable<T>, public IObserver<T>
	{
	public:
		SkipWhileObserver(std::function<bool(T)>);
		virtual ~SkipWhileObserver() {};
	public:
		virtual void OnNext(T) override;
		virtual void OnComplete() override;
		virtual void OnError(std::exception) override;

	public:
		std::function<void(T)> onNextCallback;
		std::function<void(T)> onCompleteCallback;
		std::function<void(std::exception)> onErrorCallback;
		std::function<bool(T)> predicate;
		bool skip;
	};

	template <typename T>
	SkipWhileObserver<T>::SkipWhileObserver(std::function<bool(T)> predicate) :
		predicate(predicate), skip(true) {}

	template <typename T>
	void SkipWhileObserver<T>::OnNext(T data)
	{
		try
		{
			if (!predicate(data))
			{
				skip = false;
			}
			if (!skip)
			{
				for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
				{
					(*iter)->OnNext(data);
				}
			}
		}
		catch (std::exception e)
		{
			OnError(e);
		}
	}

	template <typename T>
	void SkipWhileObserver<T>::OnComplete()
	{
		try
		{
			for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
			{
				(*iter)->OnComplete();
			}
			Observable<T>::Dispose();
		}
		catch (std::exception e)
		{
			OnError(e);
		}
	}

	template <typename T>
	void SkipWhileObserver<T>::OnError(std::exception e)
	{
		for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
		{
			(*iter)->OnError(e);
		}
		Observable<T>::Dispose();
	}
}