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
이 클래스는 세부 기능을 하는 인터페이스를 돌려주는 역할임.

IRenderer는 그래픽스 엔진의 인터페이스임
이걸로 그림을 그리는 기능을 할 것임.

IPhysics는 물리 엔진의 인터페이스임
여기에 물리 처리 할 RigidBody를 넘겨주면 처리하도록 할 것임.
RigidBody는 Collider를 가지면 충돌 처리가 될 것임.
*/

/*
저번 3쿼터때 수학 함수를 만들다가 벽을 조금 느낀 적이 있음
나중에는 
*/