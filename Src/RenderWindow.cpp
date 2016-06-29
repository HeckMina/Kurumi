#include "RenderWindow.h"
#include "Texture2DGL.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ImageSprite.h"
#include "Button.h"
#include "Camera.h"
#include "Ground.h"

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
namespace Platform
{
	static Kurumi::Button*button;

	Kurumi::Camera gCamera;

	RenderWindow::RenderWindow():mbMoveLeft(false),mbMoveRight(false),mbMoveBackward(false),mbMoveForward(false)
	{

	}
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

		glClearColor(41.0f / 255.0f, 71.0f / 255.0f, 121.0f / 255.0f, 1.0f);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-400, 400, -300, 300);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glColor4ub(255, 255, 255, 255);

		Kurumi::Texture2DGL::Load("150001.png");
		button = new Kurumi::Button;
		button->mImageSprite=new Kurumi::ImageSprite;
		button->mImageSprite->mTexture= Kurumi::Texture2DGL::Load("150001.png");
		button->Init(-320, 220, 100, 100);
		Kurumi::Ground::Init();
	}

	void RenderWindow::OnKeyDown(WPARAM wParam, LPARAM lParam)
	{
		if (wParam=='W')
		{
			mbMoveForward = true;
		}
		else if (wParam=='S')
		{
			mbMoveBackward = true;
		}
		else if (wParam=='A')
		{
			mbMoveLeft = true;
		}
		else if (wParam=='D')
		{
			mbMoveRight = true;
		}
	}

	void RenderWindow::OnKeyUp(WPARAM wParam, LPARAM lParam)
	{
		if (wParam == 'W')
		{
			mbMoveForward = false;
		}
		else if (wParam == 'S')
		{
			mbMoveBackward = false;
		}
		else if (wParam == 'A')
		{
			mbMoveLeft = false;
		}
		else if (wParam == 'D')
		{
			mbMoveRight = false;
		}
	}

	void RenderWindow::RenderOnFrame()
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (float)mWidth / (float)mHeight, 0.1f, 1000.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		if (mbMoveLeft)
		{
			gCamera.MoveStrafe(-1.0f);
		}
		if (mbMoveRight)
		{
			gCamera.MoveStrafe(1.0f);
		}
		if (mbMoveForward)
		{
			gCamera.MoveForward(1.0f);
		}
		if (mbMoveBackward)
		{
			gCamera.MoveBackward(1.0f);
		}
		gCamera.Update();
		Kurumi::Ground::Draw();

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-mWidth/2, mWidth/2, -mHeight/2, mHeight/2);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

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