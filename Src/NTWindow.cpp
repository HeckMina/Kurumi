#include "NTWindow.h"
#include <stdio.h>

namespace Platform
{
	HINSTANCE NTWindow::gAppInstance = nullptr;

	NTWindow::NTWindow():mbVisiable(false)
	{

	}

	void NTWindow::OnClose(WPARAM wParam, LPARAM lParam)
	{
		PostQuitMessage(0);
	}

	void NTWindow::OnLButtonDown(WPARAM wParam, LPARAM lParam)
	{
		printf("OnLButtonDown\n");
	}

	void NTWindow::OnLButtonUp(WPARAM wParam, LPARAM lParam)
	{

		printf("OnLButtonUp\n");
	}

	void NTWindow::OnRButtonDown(WPARAM wParam, LPARAM lParam)
	{

	}

	void NTWindow::OnRButtonUp(WPARAM wParam, LPARAM lParam)
	{

	}

	void NTWindow::OnKeyDown(WPARAM wParam, LPARAM lParam)
	{

	}

	void NTWindow::OnKeyUp(WPARAM wParam, LPARAM lParam)
	{

	}

	void NTWindow::Show(bool bShow)
	{
		mbVisiable = bShow;
		ShowWindow(mHwnd, mbVisiable ? SW_SHOW : SW_HIDE);
		mbVisiable && UpdateWindow(mHwnd);
	}

	void NTWindow::Init()
	{
		mDC = GetDC(mHwnd);
		RECT rect;
		GetClientRect(mHwnd, &rect);
		mWidth = rect.right - rect.left;
		mHeight = rect.bottom - rect.top;
	}

	ATOM NTWindow::RegisterWindow(LPCTSTR className,DWORD style)
	{
		WNDCLASSEX wndClass;
		memset(&wndClass, 0, sizeof(WNDCLASSEX));
		wndClass.cbSize = sizeof(WNDCLASSEX);
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hbrBackground = NULL;
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.hIcon = NULL;
		wndClass.hIconSm = NULL;
		wndClass.hInstance = gAppInstance;
		wndClass.lpfnWndProc = WindowProc;
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = className;
		wndClass.style = style;

		ATOM atom = RegisterClassEx(&wndClass);
		return atom;
	}

	LRESULT CALLBACK NTWindow::WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		NTWindow*self = (NTWindow*)GetWindowLongPtr(hwnd, GWL_USERDATA);
		if (self ==nullptr)
		{
			return DefWindowProc(hwnd, message, wParam, lParam);
		}

		switch (message)
		{
		case WM_CLOSE:
			self->OnClose(wParam, lParam);
			break;
		case WM_LBUTTONDOWN:
			self->OnLButtonDown(wParam, lParam);
			break;
		case WM_LBUTTONUP:
			self->OnLButtonUp(wParam, lParam);
			break;
		case WM_RBUTTONDOWN:
			self->OnRButtonDown(wParam, lParam);
			break;
		case WM_RBUTTONUP:
			self->OnRButtonUp(wParam, lParam);
			break;
		case WM_KEYDOWN:
			self->OnKeyDown(wParam, lParam);
			break;
		case WM_KEYUP:
			self->OnKeyUp(wParam, lParam);
			break;
		}
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}