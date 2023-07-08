#pragma once


template <typename T>
class Interface_ : T
{
public:
	Interface_() = default;
	virtual ~Interface_()
	{
		this->Release();
	}

	void Release()
	{
		if (_interface == nullptr)
		{
			return;
		}

		_interface->Release();
		delete _interface;
	}

	T* Get()
	{
		return _interface;
	}

	T** GetAdress()
	{
		return &_interface;
	}

	void operator=(const Interface_<T>& other)
	{
		this->_interface = other._interface;
	}

	void operator=(Interface_<T>&& other)
	{
		if (this != &other)
		{
			this->_interface = other._interface;
			other._interface = nullptr;
		}
	}

	T* operator&(int)
	{
		return _interface;
	}

private:
	T* _interface;
};


/*
그래픽스 조금 건들여보다가
.과 -> 했을 때 ComPtr에 접근하는거랑 
ComPtr 내부에 있는 포인터에 접근하는게 달라보여서 왜그럴까 하다가

디자인 책에서 보던 Mixin이라는게 갑자기 떠올라서 만들어 봄
실제로 이런 식의 구성인지는 모르겠지만 이걸로 뭔가 할 수 있을것 같음.
*/