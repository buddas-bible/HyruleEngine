#pragma once

namespace Hyrule
{
	class IRenderer;
	class IPhysics;

	class HyruleEngine
	{
	public:
		HyruleEngine();
		~HyruleEngine();

	public:
		void Initialize();
		void Finalize();
		void Update();
		void PhysicsUpdate();
		void Render();

	private:
		IRenderer* renderer;
		IPhysics* physics;
	};
}

/*
�� Ŭ������ ���� ����� �ϴ� �������̽��� �����ִ� ������.

IRenderer�� �׷��Ƚ� ������ �������̽���
�̰ɷ� �׸��� �׸��� ����� �� ����.

IPhysics�� ���� ������ �������̽���
���⿡ ���� ó�� �� RigidBody�� �Ѱ��ָ� ó���ϵ��� �� ����.
RigidBody�� Collider�� ������ �浹 ó���� �� ����.
*/

/*
���� 3���Ͷ� ���� �Լ��� ����ٰ� ���� ���� ���� ���� ����
���߿��� 
*/