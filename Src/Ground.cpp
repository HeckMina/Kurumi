#include "Ground.h"
#include <windows.h>
#include <gl/GL.h>

namespace Kurumi
{
	static GLuint ground;
	void Ground::Init()
	{
		ground=glGenLists(1);
		glNewList(ground, GL_COMPILE);
		glBegin(GL_QUADS);
		for (int i = 0; i < 20; i++)
		{
			float zStart = 100.0f - i * 10.0f;
			for (int j = 0; j < 20; ++j)
			{
				float xStart = j * 10.0f - 100.0f;
				if ((i % 2) ^ (j % 2))
				{
					glColor4ub(41, 41, 41, 255);
				}
				else
				{
					glColor4ub(200, 200, 200, 255);
				}
				glVertex3f(xStart, -2.0f, zStart);
				glVertex3f(xStart + 10.0f, -2.0f, zStart);
				glVertex3f(xStart + 10.0f, -2.0f, zStart - 10.0f);
				glVertex3f(xStart, -2.0f, zStart - 10.0f);
			}
		}
		glEnd();
		glEndList();
	}

	void Ground::Draw()
	{
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
		glCallList(ground);
		glPopMatrix();
	}
}