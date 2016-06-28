#include "FileSystem.h"

namespace Kurumi
{
	bool FileSystem::LoadData(const char*path, Data &data)
	{
		FILE*pFile = fopen(path, "rb");
		if (pFile)
		{
			fseek(pFile,0,SEEK_END);
			data.mLen = ftell(pFile);
			if (data.mLen==0)
			{
				return false;
			}
			rewind(pFile);
			data.mContent = new unsigned char[data.mLen+1];

			fread(data.mContent, 1, data.mLen, pFile);
			data.mContent[data.mLen] = '\0';
			fclose(pFile);
			return true;
		}
		return false;
	}
}