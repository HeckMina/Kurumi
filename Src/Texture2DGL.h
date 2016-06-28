#pragma once
#include <windows.h>
#include <gl/GL.h>
#include <map>
#include "Object.h"

namespace Kurumi
{
	class Texture2DGL :public Object
	{
	public:
		int mWidth;
		int mHeight;
		int mBPP;
		GLuint mTextureID;
	public:
		static Texture2DGL* Load(const char*path);
		static std::map<std::string, Texture2DGL*> mCachedTextures;
	};
}