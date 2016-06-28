#pragma once
#include "NTWindow.h"

namespace Platform
{
	class RenderWindow:public NTWindow
	{
	protected:
		HGLRC mRC;
		bool mbMoveLeft, mbMoveRight, mbMoveForward, mbMoveBackward;
	protected:
		virtual void OnLButtonDown(WPARAM wParam, LPARAM lParam);
		virtual void OnLButtonUp(WPARAM wParam, LPARAM lParam);
		virtual void OnKeyDown(WPARAM wParam, LPARAM lParam);
		virtual void OnKeyUp(WPARAM wParam, LPARAM lParam);
	public:
		RenderWindow();
		virtual void Init();
		void RenderOnFrame();
	};
}