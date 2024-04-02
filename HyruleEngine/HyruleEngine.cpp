#include "HyruleEngine.h"

#include "framework.h"
#include "CoreSystem.h"
#include "RendererSystem.h"
#include "PhysicsSystem.h"
#include "TimeSystem.h"

namespace Hyrule
{
	bool HyruleEngine::focus = true;

	HyruleEngine::HyruleEngine() : 
		hwnd(), isRunning(true)
	{
		// m_gameEngine = this;
	}

	/// <summary>
	/// 그냥 싱글턴으로 객체 반환해주는 함수
	/// </summary>
	/// <returns></returns>
	HyruleEngine& HyruleEngine::GetInstance()
	{
		static HyruleEngine gameEngine;

		return gameEngine;
	}

	/// <summary>
	/// 게임 메인 루프
	/// </summary>
	void HyruleEngine::Run()
	{
		MSG msg;
		
		TimeSystem::GetInstance().Tick();
		HyruleEngine::focus = true;

		while (isRunning)
		{
			if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) break;
				DispatchMessage(&msg);
			}
			else
			{
				if (HyruleEngine::focus)
					isRunning = CoreSystem::Instance().GameProcess();
			}
		}
	}

	/// <summary>
	/// 초기화 (윈도우 창 설정)
	/// </summary>
	void HyruleEngine::Initialize(HINSTANCE hInstance, const std::wstring& _name)
	{
		// 윈도우 창 설정
		this->CreateEngineWindow(hInstance, _name);

		CoreSystem::Instance().SetHandle((int)hwnd);
	}

	/// <summary>
	/// 다 할당을 풀어주려고 함.
	/// </summary>
	void HyruleEngine::Finalize()
	{

	}

	/// <summary>
	/// 윈도우 창 생성
	/// </summary>
	long HyruleEngine::CreateEngineWindow(HINSTANCE& hInstance, const std::wstring& _name)
	{
		WNDCLASSEXW wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = Hyrule::HyruleEngine::WndProc; // 프로시저
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 0);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = _name.c_str();
		wcex.hIconSm = NULL;

		RegisterClassExW(&wcex);

		hwnd = CreateWindowW(
			wcex.lpszClassName,
			_name.c_str(),
			WS_OVERLAPPEDWINDOW | WS_BORDER | WS_SYSMENU,
			CW_USEDEFAULT,				// 윈도우 좌측 상단의 x 좌표
			CW_USEDEFAULT,				// 윈도우 좌측 상단의 y 좌표
			0,							// 윈도우 가로 방향 해상도
			0,							// 윈도우 세로 방향 해상도
			NULL,
			NULL,
			hInstance,
			NULL);

		if (!hwnd)
		{
			return S_FALSE;
		}

		float dpi = (float)GetDpiForWindow(hwnd);

		SetWindowPos(
			hwnd,
			NULL,
			NULL,
			NULL,
			static_cast<int>(ceil(1600.f * dpi / 96.f)),
			static_cast<int>(ceil(900.f * dpi / 96.f)),
			SWP_NOMOVE);

		ShowWindow(hwnd, SW_SHOWNORMAL);
		UpdateWindow(hwnd);

		return S_OK;
	}

	/// <summary>
	/// 창 크기 재설정
	/// </summary>
	long HyruleEngine::OnResize()
	{
		HRESULT hr = S_OK;

		hr = (HRESULT)(RendererSystem::Instance().OnResize());

		if (FAILED(hr))
		{
			return hr;
		}

		return hr;
	}

	/// <summary>
	/// Graphics DLL 동적 링킹
	/// </summary>
	void HyruleEngine::LoadGraphicsDLL(const std::wstring& _path)
	{
		auto& renderer = RendererSystem::Instance();

		auto result = renderer.LoadGraphicsDLL(_path, hwnd);
		if (!result)
		{
			isRunning = false;
		}
	}

	/// <summary>
	/// Physics DLL 동적 링킹
	/// </summary>
	void HyruleEngine::LoadPhysicsDLL(const std::wstring& _path)
	{
		auto& physics = PhysicsSystem::Instance();

		auto result = physics.LoadPhysicsDLL(_path, hwnd);
		if (!result)
		{
			isRunning = false;
		}
	}

	/// <summary>
	/// 윈도우 메세지 함수
	/// </summary>
	LRESULT CALLBACK HyruleEngine::WndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
	{
		switch (_msg)
		{
			case WM_SETFOCUS:
			{
				// 윈도우가 포커스 될 때
				// 타임 스케일이 1.f로 게임을 실행시킴
				TimeSystem::GetInstance().Start();
				HyruleEngine::focus = true;
			}
 			break;

			// case WM_GETMINMAXINFO:
			// case WM_MOVE:
			case WM_KILLFOCUS:
			{
				// 윈도우가 비활성화 될 때
				// 타임 스케일이 0.f로 게임을 정지시킴
				TimeSystem::GetInstance().Stop();
				HyruleEngine::focus = false;
			}
			break;

			case WM_SIZE:
			{
				if (_wParam == SIZE_MINIMIZED)
				{
					// 윈도우가 최소화될 때
					// 타임 스케일이 0.f로 게임을 정지시킴
					TimeSystem::GetInstance().Stop();
					HyruleEngine::focus = false;
				}
				else if (_wParam == SIZE_MAXIMIZED || _wParam == SIZE_RESTORED)
				{
					// 윈도우가 최대화될 때
					// 윈도우 크기가 변경될 때
					// if (HyruleEngine::GetInstance() != nullptr)
					// {
						HyruleEngine::GetInstance().OnResize();
					// }
				}
			}
			break;

			case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
			break;
		}

		return DefWindowProc(_hWnd, _msg, _wParam, _lParam);
	}
}