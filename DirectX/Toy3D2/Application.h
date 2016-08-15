#pragma once

#include <memory>
#include <windows.h>

namespace Toy3D {

	const bool FULLSCREEN = false;
	static bool bExit = false;

	class Application
	{
	public:
		Application();
		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator=(Application&&) = delete;
		~Application();

	public:
		bool Initialize();
		void Shutdown();
		void Run();

		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
	private:
		bool Frame();
		void InitializeWindows(int&, int&);
		void ShutdownWindows();

		LPCTSTR m_ApplicationName;
		HINSTANCE m_hInstance;
		HWND m_hwnd;

	};

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wParam, LPARAM lParam);
	static Application* ApplicationHandle = nullptr;
}