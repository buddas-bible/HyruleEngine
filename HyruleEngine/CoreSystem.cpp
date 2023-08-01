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

				// ������ Awake, Enable, Start�� ȣ���ؾ� �� ���� ������Ʈ�� ó��
				SceneManager::GetInstance().Initalization();
				
				state = PHYSICS;
				break;
			}
			case PHYSICS:
			{
				double deltaTime = (double)TimeSystem::GetInstance().GetfDeltaTime();
				// double deltaTime = 0.008f;
				accumulatedTime += deltaTime;

				// �����Ӹ��� �� �� ȣ��ǵ��� ��.
				while (accumulatedTime >= fixedDeltaTime)
				{
					SceneManager::GetInstance().FixedUpdate();
					
					/// �ݶ��̴��� ������ٵ� ���� ��Ƽ� ������ �� ������ ������ ���� ��.
					SceneManager::GetInstance().PrePhysicsUpdate();				// �ݶ��̴� ��Ʈ���� ������Ʈ
					PhysicsSystem::GetInstance().CollisionDetection();			// �ݶ��̴� �浹 üũ
					SceneManager::GetInstance().PhysicsUpdate();				// �ݶ��̴� �浹 ���� Ȯ��
					PhysicsSystem::GetInstance().CollisionResponse(deltaTime);	// ��ü �ùķ��̼�
					SceneManager::GetInstance().LatePhysicsUpdate();			// ��ü �ùķ��̼� ��� ����

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