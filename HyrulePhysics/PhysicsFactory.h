#pragma once
#include "IPFactory.h"


namespace Hyrule
{
	class PhysicsFactory : public IPFactory
	{
	public:
		PhysicsFactory() noexcept = delete;
		~PhysicsFactory() noexcept = default;

	friend class HyrulePhysics;

	public:

	};
}




/*
RUN

Window â ����

Graphics ���� ����

Physics ���� ����

///// ���࿡ ������ �о�´ٸ� �������� ������?

Scene �ε�

Scene ���� �ִ� ���� ������Ʈ Start �Լ� ����
	���� ������Ʈ�� ������Ʈ ����Ʈ ��ȸ�ϸ鼭 Start ����

** ���� **
Scene ���� �ִ� ���� ������Ʈ�� Update �Լ� ���� 
	���� ������Ʈ�� ������Ʈ ����Ʈ ��ȸ�ϸ鼭 Update ����

*/