#pragma once
#include <windows.h>

namespace Platform
{
	class NTWindow
	{
	protected:
		HWND mHwnd;
		HDC mDC;
		bool mbVisiable;
	protected:
		virtual void OnClose(WPARAM wParam, LPARAM lParam);
		virtual void OnLButtonDown(WPARAM wParam, LPARAM lParam);
		virtual void OnLButtonUp(WPARAM wParam, LPARAM lParam);
		virtual void OnRButtonDown(WPARAM wParam, LPARAM lParam);
		virtual void OnRButtonUp(WPARAM wParam, LPARAM lParam);
	public:
		NTWindow();
		virtual void Init();
		HDC DC() { return mDC; }
		void Show(bool bShow);
	public:
		template<typename T>
		static T* Create(LPCTSTR className,DWORD style)
		{
			HWND hwnd = CreateWindowEx(NULL, className, L"OpenGL Render Window", style, 200, 200, 800, 600, NULL, NULL, gAppInstance, NULL);
			T*window = new T;
			window->mHwnd = hwnd;
			SetWindowLongPtr(hwnd, GWL_USERDATA, (LONG_PTR)window);
			return window;
		}
		static ATOM RegisterWindow(LPCTSTR className, DWORD style);
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
		static HINSTANCE gAppInstance;
	};
}