#include "HyruleEngine.h"

#include "framework.h"

#include "IRenderer.h"
// #include "IPhysics.h"

// #include <functional>

namespace Hyrule
{
	HyruleEngine::HyruleEngine() : hwnd(), isRunning(true), rendererEngine(), physicsEngine()
	{
		m_gameEngine = this;
	}

	HyruleEngine::~HyruleEngine()
	{

	}

	/// <summary>
	/// 그냥 싱글턴으로 객체 반환해주는 함수
	/// </summary>
	/// <returns></returns>
	HyruleEngine* HyruleEngine::GetInstance()
	{
		static HyruleEngine* gameEngine = nullptr;

		if (!gameEngine)
		{
			gameEngine = new HyruleEngine;
		}

		return gameEngine;
	}

	/// <summary>
	/// 게임 메인 루프
	/// </summary>
	void HyruleEngine::Run()
	{
		MSG msg;

		while (isRunning)
		{
			if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) break;
				DispatchMessage(&msg);
			}
			else
			{
				/// 여기가 Core를 실행시킬 곳일까?
				rendererEngine->Render();
				// m_engine->PhysicsUpdate();
				// engine->Render();
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

		// 여기서 아마 시스템 관련 친구들을 생성 및 초기화 하지 않을까?
	}

	/// <summary>
	/// 다 할당을 풀어주려고 함.
	/// </summary>
	void HyruleEngine::Finalize()
	{
		if (rendererEngine != nullptr)
		{
			// renderer->Finalize();
			rendererEngine = nullptr;
		}
		if (physicsEngine != nullptr)
		{
			// physics->Finalize();
			physicsEngine = nullptr;
		}
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

		if (rendererEngine == nullptr)
		{
			return S_FALSE;
		}

		hr = rendererEngine->OnResize();

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
		HMODULE graphicsDLL{ LoadLibrary(_path.c_str()) };
		if (graphicsDLL == nullptr)
		{
			MessageBox(hwnd, L"해당 경로에 Graphics DLL 파일이 존재하지 않습니다.", L"DLL 오류", NULL);
			isRunning = false;
			return;
		}

		using ImportFunction = IRenderer* (*) ();
		// std::function function{ (ImportFunction)GetProcAddress(graphicsDLL, "CreateRenderer") };
		ImportFunction CreateInstance{ (ImportFunction)GetProcAddress(graphicsDLL, "CreateRenderer") };

		if (CreateInstance == nullptr)
		{
			MessageBox(hwnd, L"Graphics DLL에서 함수 포인터를 받아오지 못했습니다.", L"DLL 오류", NULL);
			isRunning = false;
			return;
		}

		rendererEngine = CreateInstance();

		if (rendererEngine == nullptr)
		{
			MessageBox(hwnd, L"Graphics Engine 객체 생성 실패", L"DLL 오류", NULL);
			isRunning = false;
			return;
		}

		if (FAILED(rendererEngine->Initialize((int)hwnd)))
		{
			isRunning = false;
		}
	}

	/// <summary>
	/// Physics DLL 동적 링킹
	/// </summary>
	void HyruleEngine::LoadPhysicsDLL(const std::wstring& _path)
	{
		// HMODULE physicsDLL{ LoadLibrary(_path.c_str()) };
		// if (!physicsDLL)
		// {
		// 	MessageBox(hwnd, L"해당 경로에 Physics DLL 파일이 존재하지 않습니다.", L"DLL 오류", MB_OK | MB_ICONWARNING);
		// 	isRunning = false;
		// 	return;
		// }
		// 
		// using ImportFunction = IPhysics* (*) ();
		// ImportFunction CreateInstance{ (ImportFunction)GetProcAddress(physicsDLL, "CreatePhysicsWorld") };
		// 
		// if (!CreateInstance)
		// {
		// 	MessageBox(hwnd, L"Physics DLL에서 함수 포인터를 받아오지 못했습니다.", L"DLL 오류", MB_OK | MB_ICONWARNING);
		// 	isRunning = false;
		// 	return;
		// }
		// 
		// 	if (rendererEngine == nullptr)
		// {
		// 	MessageBox(hwnd, L"Graphics Engine 객체 생성 실패", L"DLL 오류", NULL);
		// 	isRunning = false;
		// 	return;
		// }
		// 
		// physicsEngine = CreateInstance();
	}

	/// <summary>
	/// 윈도우 메세지 함수
	/// </summary>
	LRESULT CALLBACK HyruleEngine::WndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
	{
		switch (_msg)
		{
			case WM_ACTIVATE:
			{
				// 윈도우가 활성화 될 때
				// 타임 스케일이 1.f로 게임을 시작함
			}
			break;

			case WA_INACTIVE:
			{
				// 윈도우가 비활성화 될 때
				// 타임 스케일이 0.f로 게임을 정지시킴
			}
			break;

			case WM_SIZE:
			{
				if (_wParam == SIZE_MINIMIZED)
				{
					// 윈도우가 최소화될 때
					// 타임 스케일이 0.f로 게임을 정지시킴
				}
				else if (_wParam == SIZE_MAXIMIZED || _wParam == SIZE_RESTORED)
				{
					// 윈도우가 최대화될 때
					// 윈도우 크기가 변경될 때
					if (HyruleEngine::GetInstance() != nullptr)
					{
						HyruleEngine::GetInstance()->OnResize();
					}
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