#include "RenderWindow.h"
#include "Texture2DGL.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ImageSprite.h"
#include "Button.h"

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
namespace Platform
{
	static Kurumi::Button*button;
	void RenderWindow::Init()
	{
		NTWindow::Init();
		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nVersion = 1;
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_TYPE_RGBA;
		pfd.iLayerType = PFD_MAIN_PLANE;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;
		int pixelFormatID = ChoosePixelFormat(mDC, &pfd);
		SetPixelFormat(mDC, pixelFormatID, &pfd);

		HGLRC rc = wglCreateContext(mDC);
		wglMakeCurrent(mDC, rc);

		glClearColor(0, 0, 0, 1.0f);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-400, 400, -300, 300);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glColor3b(100, 100, 100);

		Kurumi::Texture2DGL::Load("test.bmp");
		button = new Kurumi::Button;
		button->mImageSprite=new Kurumi::ImageSprite;
		button->mImageSprite->mTexture= Kurumi::Texture2DGL::Load("test.bmp");
		button->Init(0, 0, 100, 100);
	}

	void RenderWindow::RenderOnFrame()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		button->Draw();
		SwapBuffers(mDC);
	}

	void RenderWindow::OnLButtonDown(WPARAM wParam, LPARAM lParam)
	{
		int x=LOWORD(lParam) - mWidth / 2;
		int y = mHeight / 2 - HIWORD(lParam);
		if (button->HitTest(x,y))
		{
			button->mbPressed = true;
		}
	}

	void RenderWindow::OnLButtonUp(WPARAM wParam, LPARAM lParam)
	{
		button->mbPressed = false;
	}
}