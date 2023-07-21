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
				// ������ Awake, Enable, Start�� ȣ���ؾ� �� ���� ������Ʈ�� ó��
				SceneManager::GetInstance().Initalization();
				state = PHYSICS;
				break;
			}
			case PHYSICS:
			{
				SceneManager::GetInstance().FixedUpdate();

				PhysicsSystem::GetInstance().CollisionDetection();
				/// ���� ��򰡿��� Manifold ������ ������ �ؾ���.
				PhysicsSystem::GetInstance().CollisionResponse(0.008f);

				// �ð��� ������ ���� ������ �� ����,
				// �ƴϸ� �������� �ѱ�� ���...����?
				state = INPUT;
				break;
			}
			case INPUT:
			{
				// ��ǲ ���� �Լ�?
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
				// ������ �ı��ǰų� ��Ȱ��ȭ �� ���� ������Ʈ�� ó��
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