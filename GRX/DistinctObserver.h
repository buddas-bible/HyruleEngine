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
	class DistinctObserver : public Observable<T>, public IObserver<T>
	{
	public:
		DistinctObserver();
		virtual ~DistinctObserver() {};
	public:
		virtual void OnNext(T) override;
		virtual void OnComplete() override;
		virtual void OnError(std::exception) override;


	public:
		std::function<void(T)> onNextCallback;
		std::function<void(T)> onCompleteCallback;
		std::function<void(std::exception)> onErrorCallback;
		std::set<T> filter;
	};

	template <typename T>
	DistinctObserver<T>::DistinctObserver() {}

	template <typename T>
	void DistinctObserver<T>::OnNext(T data)
	{
		try
		{
			if (filter.find(data) == filter.end())
			{
				for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
				{
					(*iter)->OnNext(data);
				}
				filter.insert(data);
			}
		}
		catch (std::exception e)
		{
			OnError(e);
		}
	}

	template <typename T>
	void DistinctObserver<T>::OnComplete()
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
	void DistinctObserver<T>::OnError(std::exception e)
	{
		for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
		{
			(*iter)->OnError(e);
		}
		Observable<T>::Dispose();
	}
}