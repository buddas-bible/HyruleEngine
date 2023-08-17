#pragma once
#include <functional>
#include <exception>
#include <vector>
#include "IObserver.h"
#include "IObservable.h"
#include "Observable.h"

namespace GRX
{
	template <typename T, typename U>
	class SelectObserver : public Observable<U>, public IObserver<T>
	{
	public:
		SelectObserver(std::function<U(T)>);
		virtual ~SelectObserver() {};

	public:
		virtual void OnNext(T) override;
		virtual void OnComplete() override;
		virtual void OnError(std::exception) override;


	public:
		std::function<void(T)> onNextCallback;
		std::function<void(T)> onCompleteCallback;
		std::function<void(std::exception)> onErrorCallback;
		std::function<U(T)> query;
	};

	template <typename T, typename U>
	SelectObserver<T, U>::SelectObserver(std::function<U(T)> query) :
		query(query) {}

	template <typename T, typename U>
	void SelectObserver<T, U>::OnNext(T data)
	{
		try
		{
			for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
			{
				(*iter)->OnNext(query(data));
			}

		}
		catch (std::exception e)
		{
			OnError(e);
		}
	}

	template <typename T, typename U>
	void SelectObserver<T, U>::OnComplete()
	{
		try
		{
			for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
			{
				(*iter)->OnComplete();
			}
			Observable<U>::Dispose();
		}
		catch (std::exception e)
		{
			OnError(e);
		}
	}

	template <typename T, typename U>
	void SelectObserver<T, U>::OnError(std::exception e)
	{
		for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
		{
			(*iter)->OnError(e);
		}
		Observable<U>::Dispose();
	}
}