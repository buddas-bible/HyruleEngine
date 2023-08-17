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
	class BufferCountObserver : public Observable<std::vector<T> >, public IObserver<T>
	{
	public:
		BufferCountObserver(int bundle, int skip = 0);
		virtual ~BufferCountObserver() {};
	public:
		virtual void OnNext(T) override;
		virtual void OnComplete() override;
		virtual void OnError(std::exception) override;

	public:
		std::function<void(T)> onNextCallback;
		std::function<void(T)> onCompleteCallback;
		std::function<void(std::exception)> onErrorCallback;
		int bundle;
		int count;
		int skip;
		bool pass;
		std::vector<T> tmp;
	};

	template <typename T>
	BufferCountObserver<T>::BufferCountObserver(int bundle, int skip) :
		bundle(bundle), skip(skip), count(0), pass(false) {}

	template <typename T>
	void BufferCountObserver<T>::OnNext(T data)
	{
		try
		{
			if (pass && skip > count)
			{
				pass = false;
			}
			else if (pass)
			{
				count++;
			}

			if (!pass && tmp.size() < bundle)
			{
				tmp.push_back(data);
			}

			if (!pass && tmp.size() == bundle)
			{
				for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
				{
					(*iter)->OnNext(tmp);
				}
				tmp.clear();
				pass == true;
			}



		}
		catch (std::exception e)
		{
			OnError(e);
		}
	}

	template <typename T>
	void BufferCountObserver<T>::OnComplete()
	{
		try
		{
			for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
			{
				(*iter)->OnComplete();
			}
			Observable<std::vector<T> >::Dispose();
		}
		catch (std::exception e)
		{
			OnError(e);
		}
	}

	template <typename T>
	void BufferCountObserver<T>::OnError(std::exception e)
	{
		for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
		{
			(*iter)->OnError(e);
		}
		Observable<std::vector<T> >::Dispose();
	}
}