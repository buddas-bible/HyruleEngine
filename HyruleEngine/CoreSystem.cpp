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

			// ������ Awake, Enable, Start�� ȣ���ؾ� �� ���� ������Ʈ�� ó��
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
				/// �ݶ��̴��� ������ٵ� ���� ��Ƽ� ������ �� ������ ������ ���� ��.
				SceneManager::Instance()->PrePhysicsUpdate();				// �ݶ��̴� ��Ʈ���� ������Ʈ
					
				PhysicsSystem::Instance()->CollisionDetection();			// �ݶ��̴� �浹 üũ
					
				SceneManager::Instance()->PhysicsUpdate();				// �ݶ��̴� �浹 ���� Ȯ��
					
				PhysicsSystem::Instance()->CollisionResponse(deltaTime);	// ��ü �ùķ��̼�
					
				SceneManager::Instance()->LatePhysicsUpdate();			// ��ü �ùķ��̼� ��� ����
			}

			accumulatedTime -= fixedDeltaTime;

			state = INPUT;
		}
		if (state == INPUT)
		{
			// ��ǲ ���� �Լ�?
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
			// ������ �ı��ǰų� ��Ȱ��ȭ �� ���� ������Ʈ�� ó��
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