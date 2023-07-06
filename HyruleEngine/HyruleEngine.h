#pragma once
#include "framework.h"
#include <string>


namespace Hyrule
{
	class HyruleEngine
	{
		HyruleEngine() noexcept;
		~HyruleEngine() noexcept;

	public:
		static HyruleEngine* GetInstance() noexcept;
		
		void Initialize(HINSTANCE hInstance, const std::wstring& _name) noexcept;
		void Run() noexcept;
		void Finalize() noexcept;

		void LoadGraphicsDLL(const std::wstring&) noexcept;
		void LoadPhysicsDLL(const std::wstring&) noexcept;

	private:
		long OnResize() noexcept;

		long CreateEngineWindow(HINSTANCE& hInstance, const std::wstring& _name) noexcept;

	private:
		HWND hwnd;
		bool isRunning;

		static LRESULT CALLBACK WndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam) noexcept;
	};
}

/*
*/

/*
저번 3쿼터때 수학 함수를 만들다가 벽을 조금 느낀 적이 있음
*/