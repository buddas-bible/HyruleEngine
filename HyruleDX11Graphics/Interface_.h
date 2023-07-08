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
�׷��Ƚ� ���� �ǵ鿩���ٰ�
.�� -> ���� �� ComPtr�� �����ϴ°Ŷ� 
ComPtr ���ο� �ִ� �����Ϳ� �����ϴ°� �޶󺸿��� �ֱ׷��� �ϴٰ�

������ å���� ���� Mixin�̶�°� ���ڱ� ���ö� ����� ��
������ �̷� ���� ���������� �𸣰����� �̰ɷ� ���� �� �� ������ ����.
*/