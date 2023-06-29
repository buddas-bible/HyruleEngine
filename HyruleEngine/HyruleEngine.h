#pragma once
#include "framework.h"
#include <string>


namespace Hyrule
{
	class IRenderer;
	class IPhysics;

	class HyruleEngine
	{
		HyruleEngine();
		~HyruleEngine();

	public:
		static HyruleEngine* GetInstance();
		
		void Initialize(HINSTANCE hInstance, const std::wstring& _name);
		void Run();
		void Finalize();

		void LoadGraphicsDLL(const std::wstring&);
		void LoadPhysicsDLL(const std::wstring&);

	private:
		long OnResize();

		long CreateEngineWindow(HINSTANCE& hInstance, const std::wstring& _name);

	private:
		HWND hwnd;
		bool isRunning;

		HyruleEngine* m_gameEngine;
		IRenderer*	rendererEngine;
		IPhysics*	physicsEngine;

		static LRESULT CALLBACK WndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);
	};
}

/*
*/

/*
���� 3���Ͷ� ���� �Լ��� ����ٰ� ���� ���� ���� ���� ����
*/