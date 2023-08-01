#include "CoreSystem.h"

#include "SceneManager.h"
#include "PhysicsSystem.h"
#include "InputSystem.h"
#include "RendererSystem.h"
#include "TimeSystem.h"

#include <iostream>

namespace Hyrule
{
	bool CoreSystem::GameProcess() noexcept
	{
		static double accumulatedTime = 0.f;
		static const double fixedDeltaTime = 1.f / 60.f;

		auto& input = InputSystem::GetInstance();

		if (!first && input.KeyPressedNow('P'))
		{
			SceneManager::GetInstance().UnloadScene();
			first = true;
			state = DECOMISSIONING;
		}

		switch (state)
		{
			case INITIALIZATION:
			{
				TimeSystem::GetInstance().Tick();

				// 씬에서 Awake, Enable, Start를 호출해야 할 게임 오브젝트를 처리
				SceneManager::GetInstance().Initalization();
				
				state = PHYSICS;
				break;
			}
			case PHYSICS:
			{
				double deltaTime = (double)TimeSystem::GetInstance().GetfDeltaTime();
				// double deltaTime = 0.008f;
				accumulatedTime += deltaTime;

				// 프레임마다 한 번 호출되도록 함.
				while (accumulatedTime >= fixedDeltaTime)
				{
					SceneManager::GetInstance().FixedUpdate();
					
					/// 콜라이더랑 리지드바디만 따로 모아서 관리할 수 있으면 좋을거 같긴 함.
					SceneManager::GetInstance().PrePhysicsUpdate();				// 콜라이더 매트릭스 업데이트
					PhysicsSystem::GetInstance().CollisionDetection();			// 콜라이더 충돌 체크
					SceneManager::GetInstance().PhysicsUpdate();				// 콜라이더 충돌 여부 확인
					PhysicsSystem::GetInstance().CollisionResponse(deltaTime);	// 강체 시뮬레이션
					SceneManager::GetInstance().LatePhysicsUpdate();			// 강체 시뮬레이션 결과 적용

					accumulatedTime -= fixedDeltaTime;

					if (first == true)
					{
						first = false;
						accumulatedTime = 0.f;
						break;
					}
				}

				state = INPUT;
				break;
			}
			case INPUT:
			{
				// 인풋 관련 함수?
				InputSystem::GetInstance().Update();
				
				state = GAME_LOGIC;
				break;
			}
			case GAME_LOGIC:
			{
				SceneManager::GetInstance().Update();
				
				SceneManager::GetInstance().LateUpdate();
				
				state = RENDERING;
				break;
			}
			case RENDERING:
			{
				RendererSystem::GetInstance().Update();
				// RendererSystem::GetInstance().PreRender();
				RendererSystem::GetInstance().Render();
				// RendererSystem::GetInstance().PostRender();
				
				state = DEBUGRENDERING;
				break;
			}
			case DEBUGRENDERING:
			{
				RendererSystem::GetInstance().DebugRender();
				
				state = DECOMISSIONING;
				break;
			}
			case DECOMISSIONING:
			{
				// 씬에서 파괴되거나 비활성화 된 게임 오브젝트를 처리
				SceneManager::GetInstance().Decommissioning();
				PhysicsSystem::GetInstance().ApplyObjectDestroy();
				
				if (TimeSystem::GetInstance().GetfDeltaTime() != 0.f)
				{
					SetWindowText((HWND)hWnd, (L"fps : " + std::to_wstring((int)TimeSystem::GetInstance().GetFPS())).c_str());
				}
				
				state = INITIALIZATION;
				break;
			}
			default:
				break;
		}

		return true;
	}

	void CoreSystem::SetHandle(int _hwnd) noexcept
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