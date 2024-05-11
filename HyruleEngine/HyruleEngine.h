#pragma once
#include "framework.h"
#include <string>
#include "Singleton.h"

namespace hyrule
{
	class HyruleEngine : public Singleton<HyruleEngine>
	{
	public:
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
���� 3���Ͷ� ���� �Լ��� ����ٰ� ���� ���� ���� ���� ����
*/