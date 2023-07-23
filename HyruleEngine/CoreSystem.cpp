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
		static const double fixedDeltaTime = 1.f / 120.f;

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
				accumulatedTime += deltaTime;

				// 프레임마다 한 번 호출되도록 함.
				while (accumulatedTime >= fixedDeltaTime)
				{
					SceneManager::GetInstance().FixedUpdate();
					PhysicsSystem::GetInstance().CollisionDetection();

					/// 이쯤 어딘가에서 Manifold 가지고 뭔가를 해야함.

					PhysicsSystem::GetInstance().CollisionResponse(TimeSystem::GetInstance().GetfDeltaTime());

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