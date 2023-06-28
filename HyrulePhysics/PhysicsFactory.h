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

Window 창 생성

Graphics 엔진 생성

Physics 엔진 생성

///// 만약에 파일을 읽어온다면 이쯤이지 않을까?

Scene 로드

Scene 내에 있는 게임 오브젝트 Start 함수 실행
	게임 오브젝트의 컴포넌트 리스트 순회하면서 Start 실행

** 루프 **
Scene 내에 있는 게임 오브젝트의 Update 함수 실행 
	게임 오브젝트의 컴포넌트 리스트 순회하면서 Update 실행

*/