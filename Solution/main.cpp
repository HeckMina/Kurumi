#include <windows.h>
#include "Src/NTWindow.h"
#include "Src/RenderWindow.h"

static Platform::RenderWindow*sRenderWindow = nullptr;

void DrawScene()
{
	sRenderWindow->RenderOnFrame();
}

void MainLoop()
{
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		DrawScene();
	}
}

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	Platform::NTWindow::gAppInstance = hInstance;
	Platform::NTWindow::RegisterWindow(L"NTWindow",CS_HREDRAW|CS_VREDRAW);
	sRenderWindow = Platform::NTWindow::Create<Platform::RenderWindow>(L"NTWindow",WS_OVERLAPPEDWINDOW);
	sRenderWindow->Init();
	sRenderWindow->Show(true);
	MainLoop();
	return 0;
}