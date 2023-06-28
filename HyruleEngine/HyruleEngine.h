#pragma once

namespace Hyrule
{
	class IRenderer;
	class IPhysicsWorld;

	class HyruleEngine
	{
	public:
		HyruleEngine();
		~HyruleEngine();

	public:
		int			Initialize(int _hwnd);
		void		Finalize();

		void		Update();
		void		PhysicsUpdate();
		void		Render();

		int			OnResize();

		bool		IsStop();

	private:
		IRenderer*	renderer;
		IPhysicsWorld*	physics;
	
		bool		isStop;
	};
}

/*
*/

/*
���� 3���Ͷ� ���� �Լ��� ����ٰ� ���� ���� ���� ���� ����
*/