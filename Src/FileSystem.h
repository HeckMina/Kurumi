#pragma once
#include <stdio.h>

namespace Kurumi
{
	class Data
	{
	public:
		Data():mContent(nullptr),mLen(0)
		{

		}
		~Data()
		{
			if (mContent!=nullptr)
			{
				delete mContent;
				mLen = 0;
			}
		}
		unsigned char* mContent;
		int mLen;
	};

	class FileSystem 
	{
	public:
		static bool LoadData(const char*path, Data &data);
	};
}