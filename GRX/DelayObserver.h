#pragma once
#include <functional>
#include <exception>
#include <vector>
#include "IObserver.h"
#include "IObservable.h"
#include "Observable.h"

template <typename T>
class DelayObserver : public Observable<T>, public IObserver<T>
{
public:
	DelayObserver(std::function<bool(T)>);
	virtual ~WhereObserver() {}

public:
	virtual void OnNext(T) override;
	virtual void OnComplete() override;
	virtual void OnError(std::exception) override;

public:
	std::function<void(T)> onNextCallback;
	std::function<void(T)> onCompleteCallback;
	std::function<void(std::exception)> onErrorCallback;
	std::function<bool(T)> predicate;
};

template <typename T>
DelayObserver<T>::DelayObserver(std::function<bool(T)> predicate) :
	predicate(predicate) {}

template <typename T>
void DelayObserver<T>::OnNext(T data)
{
	try
	{
		if (predicate(data))
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
void DelayObserver<T>::OnComplete()
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
void DelayObserver<T>::OnError(std::exception e)
{
	for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
	{
		(*iter)->OnError(e);
	}
	Observable<T>::Dispose();
}