#include "Button.h"

namespace Kurumi
{
	Button::Button():mbPressed(false)
	{

	}

	void Button::Init(float x, float y, float width, float height)
	{
		mX = x;
		mY = y;
		mWidth = width;
		mHeight = height;
		mImageSprite->Init(x, y, width, height);
	}

	bool Button::HitTest(int x, int y)
	{
		if (x>mX-mWidth/2.0f&&
			x<mX+mWidth/2.0f)
		{
			if (y>mY-mHeight/2.0f&&
				y<mY+mHeight/2.0f)
			{
				mImageSprite->FadeIn(0.5f);
				return true;
			}
		}
		return false;
	}

	void Button::Draw()
	{
		glPushMatrix();
		if (mbPressed)
		{
			glTranslatef(0, -4.0f, 0);
		}
		mImageSprite->Draw();
		glPopMatrix();
	}
}