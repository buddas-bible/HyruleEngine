#pragma once


namespace Hyrule
{
	class GameObject;

	class Component abstract
	{
	public:
		Component() = default;
		virtual ~Component() = default;

	protected:
		GameObject* gameObject;

	public:
		virtual GameObject* GetGameObject();
	};
}


/*
������, ���� ���� ������Ʈ���� ��� �� ���ΰ�..
������ ���̺귯���� �����س��´ٸ�
������ ���� ����ü ���� �� ��� �� ���ΰ�..
������ ���̴� ����ü�� �������̽��� ���� ������ AddForce��簡.. ������
���� ���� �Լ��� �����ϴ� ������� �ؾ��ϳ�..




*/