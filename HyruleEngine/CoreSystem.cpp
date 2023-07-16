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
				// ���� ��򰡿��� Manifold ������ ������ �ؾ���.
				PhysicsSystem::GetInstance().CollisionResponse(0.008f);

				// �ð��� ������ ���� ������ �� ����,
				// �ƴϸ� �������� �ѱ�� ���...����?
				break;
			}
			case INPUT:
			{
				// ��ǲ ���� �Լ�?
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