#pragma once
#include "IPFactory.h"


namespace Hyrule
{
	class PhysicsFactory : public IPFactory
	{
	public:
		PhysicsFactory() noexcept = delete;
		// PhysicsFactory(const PhsicsWorldSetting&) noexcept;
		~PhysicsFactory() noexcept = default;

	friend class HyrulePhysics;

	public:
		// virtual IPhysics* CreatePhysicsWorld(const PhsicsWorldSetting&) override;

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