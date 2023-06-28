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
저번 3쿼터때 수학 함수를 만들다가 벽을 조금 느낀 적이 있음
*/