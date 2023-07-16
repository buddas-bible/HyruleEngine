#include "CoreSystem.h"

#include "SceneManager.h"
#include "PhysicsSystem.h"
#include "RendererSystem.h"

namespace Hyrule
{
	bool CoreSystem::GameProcess()
	{
		switch (state)
		{
			case INITIALIZAION:
			{
				SceneManager::GetInstance().Awake();
				SceneManager::GetInstance().OnEnable();
				SceneManager::GetInstance().Start();
				break;
			}
			case PHYSICS:
			{
				SceneManager::GetInstance().FixedUpdate();
				PhysicsSystem::GetInstance().CollisionDetection();
				// 이쯤 어딘가에서 Manifold 가지고 뭔가를 해야함.
				PhysicsSystem::GetInstance().CollisionResponse(0.008f);

				// 시간이 남으면 물리 연산을 더 돌고,
				// 아니면 렌더링도 넘기는 방식...으로?
				break;
			}
			case INPUT:
			{
				// 인풋 관련 함수?
				break;
			}
			case GAME_LOGIC:
			{
				SceneManager::GetInstance().Update();
				SceneManager::GetInstance().LateUpdate();
				break;
			}
			case RENDERING:
			{
				// RendererSystem::GetInstance().PreRender();
				RendererSystem::GetInstance().Render();
				// RendererSystem::GetInstance().PostRender();
				break;
			}
			case 7:
			{
				RendererSystem::GetInstance().DebugRender();
				break;
			}
			case DESTROY:
			{
				SceneManager::GetInstance().OnDestroy();
				break;
			}
			default:
				break;
		}


	}
}