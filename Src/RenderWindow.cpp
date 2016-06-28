#include "RenderWindow.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
namespace Platform
{
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
	}

	void RenderWindow::RenderOnFrame()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBegin(GL_TRIANGLES);
		glVertex3f(0, 0, -1.0f);
		glVertex3f(100, 0, -1.0f);
		glVertex3f(0, 100, -1.0f);
		glEnd();
		SwapBuffers(mDC);
	}
}