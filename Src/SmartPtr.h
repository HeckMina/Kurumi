#pragma once

template<typename T>
class SmartPtr
{
protected:
	SmartPtr() {}
public:
	T*mPtr;
	SmartPtr(T*ptr) :mPtr(ptr) 
	{
		if (mPtr!=nullptr)
		{
			mPtr->mReferenceCount++;
		}
	}
	~SmartPtr()
	{
		if (mPtr!=nullptr)
		{
			mPtr->mReferenceCount--;
		}
	}
	T*operator->() { return mPtr; }
	void operator=(T*ptr) 
	{
		if (mPtr!=nullptr)
		{
			mPtr->mReferenceCount--;
		}
		mPtr = ptr;
		if (mPtr!=nullptr)
		{
			mPtr->mReferenceCount++;
		}
	}
};