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

		void OnResize();

		bool IsStop();

	private:
		IRenderer* renderer;
		IPhysics* physics;
	
		bool isStop;
	};
}

/*
*/

/*
���� 3���Ͷ� ���� �Լ��� ����ٰ� ���� ���� ���� ���� ����
*/