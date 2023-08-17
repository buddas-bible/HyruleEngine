#pragma once
#include <functional>
#include <exception>
#include <vector>
#include <set>
#include "IObserver.h"
#include "IObservable.h"
#include "Observable.h"

namespace GRX
{
	template <typename T>
	class DistinctUntilChangedObserver : public Observable<T>, public IObserver<T>
	{
	public:
		DistinctUntilChangedObserver();
		virtual ~DistinctUntilChangedObserver() {};
	public:
		virtual void OnNext(T) override;
		virtual void OnComplete() override;
		virtual void OnError(std::exception) override;

	public:
		std::function<void(T)> onNextCallback;
		std::function<void(T)> onCompleteCallback;
		std::function<void(std::exception)> onErrorCallback;
		T prev;
	};

	template <typename T>
	DistinctUntilChangedObserver<T>::DistinctUntilChangedObserver() {}

	template <typename T>
	void DistinctUntilChangedObserver<T>::OnNext(T data)
	{
		try
		{
			if (data != prev)
			{
				for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
				{
					(*iter)->OnNext(data);
				}
				prev = data;
			}
		}
		catch (std::exception e)
		{
			OnError(e);
		}
	}

	template <typename T>
	void DistinctUntilChangedObserver<T>::OnComplete()
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
	void DistinctUntilChangedObserver<T>::OnError(std::exception e)
	{
		for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
		{
			(*iter)->OnError(e);
		}
		Observable<T>::Dispose();
	}
}