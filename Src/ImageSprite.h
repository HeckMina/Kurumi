#pragma once
#include "Object.h"
#include "SmartPtr.h"
#include "Texture2DGL.h"

namespace Kurumi
{
	class ImageSprite :public Object
	{
	public:
		ImageSprite();
		float mVertex[12];
		SmartPtr<Texture2DGL> mTexture;
		void Draw();
		void Init(float x,float y,float width,float height);
	};
}