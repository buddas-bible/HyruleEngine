#include "CoreSystem.h"

#include "SceneManager.h"
#include "PhysicsSystem.h"
#include "InputSystem.h"
#include "RendererSystem.h"
#include "TimeSystem.h"

namespace Hyrule
{
	bool CoreSystem::GameProcess() noexcept
	{
		TimeSystem::GetInstance().Tick();

		switch (state)
		{
			case INITIALIZATION:
			{
				// 씬에서 Awake, Enable, Start를 호출해야 할 게임 오브젝트를 처리
				SceneManager::GetInstance().Initalization();
				state = PHYSICS;
				break;
			}
			case PHYSICS:
			{
				SceneManager::GetInstance().FixedUpdate();

				PhysicsSystem::GetInstance().CollisionDetection();
				/// 이쯤 어딘가에서 Manifold 가지고 뭔가를 해야함.
				PhysicsSystem::GetInstance().CollisionResponse(0.008f);

				// 시간이 남으면 물리 연산을 더 돌고,
				// 아니면 렌더링도 넘기는 방식...으로?
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
				state = INITIALIZATION;
				break;
			}
			default:
				break;
		}

		return true;
	}
}