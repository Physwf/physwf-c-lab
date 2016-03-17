#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <windows.h>

namespace Toy3D {

	const bool FULLSCREEN = false;
	static bool bExit = false;

	class System 
	{
	public:
		System();
		System(const System&) = delete;
		System& operator=(const System&) = delete;
		System(System&&) = delete;
		System& operator=(System&&) = delete;
		~System();

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
	};

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	static System* ApplicationHandle = nullptr;
}
#endif