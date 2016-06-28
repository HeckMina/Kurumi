#pragma once
#include "NTWindow.h"

namespace Platform
{
	class RenderWindow:public NTWindow
	{
	protected:
		HGLRC mRC;
	protected:
		virtual void OnLButtonDown(WPARAM wParam, LPARAM lParam);
		virtual void OnLButtonUp(WPARAM wParam, LPARAM lParam);
	public:
		virtual void Init();
		void RenderOnFrame();
	};
}