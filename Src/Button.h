#pragma once
#include "ImageSprite.h"

namespace Kurumi
{
	class Button 
	{
	public:
		Button();
		float mX, mY, mWidth, mHeight;
		bool mbPressed;
		void Init(float x, float y, float width, float height);
		bool HitTest(int x,int y);
		ImageSprite*mImageSprite;
		void Draw();
	};
}