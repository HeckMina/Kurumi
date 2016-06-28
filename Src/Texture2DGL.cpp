#include "Texture2DGL.h"
#include "FileSystem.h"
#include "SOIL.h"

#pragma comment(lib,"SOIL.lib")

namespace Kurumi
{
	const char* Extension(const char*path)
	{
		int nlen = strlen(path);
		for (int i=nlen-1;i>0;--i)
		{
			if (path[i]=='.')
			{
				return path+i;
			}
		}
		return path;
	}
	std::map<std::string, Texture2DGL*> Texture2DGL::mCachedTextures;
	Texture2DGL*Texture2DGL::Load(const char*path)
	{
		auto iter = mCachedTextures.find(path);
		if (iter!=mCachedTextures.end())
		{
			return iter->second;
		}
		if (strcmp(Extension(path),".png")==0)
		{
			Texture2DGL*texture = new Texture2DGL;
			texture->mBPP = 32;
			texture->mTextureID = SOIL_load_OGL_texture(path, 0, 0, SOIL_FLAG_POWER_OF_TWO| SOIL_FLAG_INVERT_Y);
			mCachedTextures.insert(std::pair<std::string, Texture2DGL*>(path, texture));
			return texture;
		}
		Data data;
		FileSystem::LoadData(path, data);
		BITMAPFILEHEADER bfh;
		memcpy(&bfh, data.mContent, sizeof(BITMAPFILEHEADER));
		if (bfh.bfType == 0x4D42)
		{
			Texture2DGL*texture = new Texture2DGL;
			BITMAPINFOHEADER bih;
			memcpy(&bih, data.mContent+sizeof(BITMAPFILEHEADER), sizeof(BITMAPINFOHEADER));
			texture->mWidth = bih.biWidth;
			texture->mHeight = bih.biHeight;
			texture->mBPP = 24;
			unsigned char*imageData = data.mContent + bfh.bfOffBits;
			unsigned char temp;
			int pixelCount = texture->mWidth*texture->mHeight*3;
			for (int i = 0; i < pixelCount; i += 3)
			{
				temp = imageData[i + 2];
				imageData[i + 2] = imageData[i];
				imageData[i] = temp;
			}
			GLuint mainTexture;
			glGenTextures(1, &mainTexture);
			glBindTexture(GL_TEXTURE_2D, mainTexture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->mWidth, texture->mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
			glBindTexture(GL_TEXTURE_2D, 0);
			texture->mTextureID = mainTexture;
			mCachedTextures.insert(std::pair<std::string, Texture2DGL*>(path,texture));
			return texture;
		}
		return nullptr;
	}
}