#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <memory>

#include <windows.h>
#include "Input.h"
#include "Scene.h"

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
		void InitialzeWindows(int&, int&);
		void ShutdownWindows();

		LPCTSTR m_ApplicationName;
		HINSTANCE m_hInstance;
		HWND m_hwnd;
		std::shared_ptr<Input> m_spInput{ nullptr };
		std::shared_ptr<Scene> m_spScene{ nullptr };
	};

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	static Application* ApplicationHandle = nullptr;
}
#endif