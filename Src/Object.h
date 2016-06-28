#pragma once
#include "LinkList.h"

namespace Kurumi
{
	class Object:public LinkedList
	{
	public:
		Object();
		int mReferenceCount;
	};
}