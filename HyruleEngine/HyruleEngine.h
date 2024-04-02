#pragma once
#include "framework.h"
#include <string>


namespace Hyrule
{
	class HyruleEngine
	{
		HyruleEngine();
		~HyruleEngine() = default;
		HyruleEngine(const HyruleEngine&) = delete;
		HyruleEngine(HyruleEngine&&) = delete;
		HyruleEngine& operator=(const HyruleEngine&) = delete;
		HyruleEngine& operator=(HyruleEngine&&) = delete;

	public:
		static HyruleEngine& GetInstance();
		
		void Initialize(HINSTANCE hInstance, const std::wstring& _name);
		void Run();
		void Finalize();

		void LoadGraphicsDLL(const std::wstring&);
		void LoadPhysicsDLL(const std::wstring&);

		static bool focus;

	private:
		long OnResize();

		long CreateEngineWindow(HINSTANCE& hInstance, const std::wstring& _name);

	private:
		HWND hwnd;
		bool isRunning;

		static LRESULT CALLBACK WndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);
	};
}

/*
*/

/*
저번 3쿼터때 수학 함수를 만들다가 벽을 조금 느낀 적이 있음
*/