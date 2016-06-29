#include "ImageSprite.h"

namespace Kurumi
{
	ImageSprite::ImageSprite():mTexture(nullptr)
	{
	}

	void ImageSprite::Init(float x, float y, float width, float height)
	{
		float halfWith = width / 2.0f;
		float halfHeight = height / 2.0f;
		//0~3 --> 1
		mVertex[0] = x - halfWith;
		mVertex[1] = y - halfHeight;
		mVertex[2] = -1.0f;
		//2
		mVertex[3] = x + halfWith;
		mVertex[4] = y - halfHeight;
		mVertex[5] = -1.0f;
		//3
		mVertex[6] = x + halfWith;
		mVertex[7] = y + halfHeight;
		mVertex[8] = -1.0f;
		//4
		mVertex[9] = x - halfWith;
		mVertex[10] = y + halfHeight;
		mVertex[11] = -1.0f;
	}

	void ImageSprite::Draw()
	{
		glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D,mTexture->mTextureID);
		glColor4ub(255, 255, 255, 255);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3fv(mVertex);

		glTexCoord2f(1, 0);
		glVertex3fv(mVertex + 3);	
		
		glTexCoord2f(1, 1);
		glVertex3fv(mVertex + 6);	
		
		glTexCoord2f(0, 1);
		glVertex3fv(mVertex + 9);
		glEnd();
		if (mNext!=nullptr)
		{
			Next<ImageSprite>()->Draw();
		}
	}
}