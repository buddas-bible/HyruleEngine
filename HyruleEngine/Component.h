#pragma once


namespace Hyrule
{
	class GameObject;

	class Component abstract
	{
	public:
		Component() = default;
		virtual ~Component() = default;

	private:
		GameObject* m_pGameObject;

	public:
		GameObject* GetGameObject();
	};
}


/*
������, ���� ���� ������Ʈ���� ��� �� ���ΰ�..
������ ���̺귯���� �����س��´ٸ�
������ ���� ����ü ���� �� ��� �� ���ΰ�..
������ ���̴� ����ü�� �������̽��� ���� ������ AddForce��簡.. ������
���� ���� �Լ��� �����ϴ� ������� �ؾ��ϳ�..




*/