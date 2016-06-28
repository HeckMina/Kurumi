#pragma once
#include "NTWindow.h"

namespace Platform
{
	class RenderWindow:public NTWindow
	{
	protected:
		HGLRC mRC;
	public:
		virtual void Init();
		void RenderOnFrame();
	};
}