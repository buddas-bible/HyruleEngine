#include "CoreSystem.h"

#include "SceneManager.h"
#include "PhysicsSystem.h"
#include "InputSystem.h"
#include "RendererSystem.h"
#include "TimeSystem.h"

#include <iostream>

// https://github.com/ocornut/imgui

namespace hyrule
{
	bool CoreSystem::GameProcess()
	{
		static double accumulatedTime = 0.f;
		static const double fixedDeltaTime = 1.f / 60.f;

		auto input = InputSystem::Instance();

		if (input->KeyDownNow('P'))
		{
			first = true;
		}

		if (state == INITIALIZATION)
		{
			TimeSystem::Instance()->Tick();

			// 씬에서 Awake, Enable, Start를 호출해야 할 게임 오브젝트를 처리
			SceneManager::Instance()->Initalization();
				
			state = PHYSICS;
		}
		if (state == PHYSICS)
		{
			double deltaTime = (double)TimeSystem::Instance()->GetfDeltaTime();
			// double deltaTime = fixedDeltaTime;
			accumulatedTime += deltaTime;

			SceneManager::Instance()->FixedUpdate();

			if (first)
			{
				/// 콜라이더랑 리지드바디만 따로 모아서 관리할 수 있으면 좋을거 같긴 함.
				SceneManager::Instance()->PrePhysicsUpdate();				// 콜라이더 매트릭스 업데이트
					
				PhysicsSystem::Instance()->CollisionDetection();			// 콜라이더 충돌 체크
					
				SceneManager::Instance()->PhysicsUpdate();				// 콜라이더 충돌 여부 확인
					
				PhysicsSystem::Instance()->CollisionResponse(deltaTime);	// 강체 시뮬레이션
					
				SceneManager::Instance()->LatePhysicsUpdate();			// 강체 시뮬레이션 결과 적용
			}

			accumulatedTime -= fixedDeltaTime;

			state = INPUT;
		}
		if (state == INPUT)
		{
			// 인풋 관련 함수?
			InputSystem::Instance()->Update();
				
			state = GAME_LOGIC;
		}
		if (state == GAME_LOGIC)
		{
			SceneManager::Instance()->Update();
			SceneManager::Instance()->LateUpdate();

			state = RENDERING;
		}
		if (state == RENDERING)
		{
			RendererSystem::Instance()->Update();

			RendererSystem::Instance()->PreRender();
			RendererSystem::Instance()->Render();
			RendererSystem::Instance()->PostRender();
#if _DEBUG
			state = DEBUGRENDERING;
#endif
		}
#if _DEBUG
		if (state == DEBUGRENDERING)
		{
			RendererSystem::Instance()->DebugRender();

			state = DECOMISSIONING;
		}
#endif
		if (state == DECOMISSIONING)
		{
			// 씬에서 파괴되거나 비활성화 된 게임 오브젝트를 처리
			SceneManager::Instance()->Decommissioning();
			PhysicsSystem::Instance()->ApplyObjectDestroy();
				
			if (TimeSystem::Instance()->GetfDeltaTime() != 0.f)
			{
				static int currFPS = 0;
				static float count = 0;
				static int minFPS = FLT_MAX;
				static int maxFPS = FLT_MIN;

				minFPS = min(minFPS, currFPS);
				maxFPS = max(maxFPS, currFPS);

				currFPS = (int)TimeSystem::Instance()->GetFPS();
				count += TimeSystem::Instance()->GetfDeltaTime();

				if (count > 1.f)
				{
					SetWindowText((HWND)hWnd,
						(
							L"fps : " + std::to_wstring(currFPS) +
							L", min : " + std::to_wstring(minFPS) +
							L", max : " + std::to_wstring(maxFPS)
							).c_str()
						);
						
					count -= 1.f;
				}
			}
				
			state = INITIALIZATION;
		}

		return true;
	}

	void CoreSystem::SetHandle(int _hwnd)
	{
		this->hWnd = _hwnd;
	}

	float CoreSystem::Clamp(float _min, float _max, float a)
	{
		if (a < _min)
		{
			return _min;
		}
		if (a > _max)
		{
			return _max;
		}

		return a;
	}
}