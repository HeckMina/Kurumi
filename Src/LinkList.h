#pragma once

class LinkedList
{
public:
	LinkedList():mNext(nullptr)
	{

	}
	void *mNext;
	void PushBack(LinkedList*node)
	{
		if (mNext==nullptr)
		{
			mNext = node;
		}
		else
		{
			Next<LinkedList>()->PushBack(node);
		}
	}
	template<typename T>
	T*Next()
	{
		return (T*)mNext;
	}
};

class DoubleLinkedList
{
public:
	DoubleLinkedList() :mPrev(nullptr), mNext(nullptr)
	{

	}

	void*mPrev;
	void*mNext;

	void PushBack(DoubleLinkedList*node)
	{
		if (mNext == nullptr)
		{
			mNext = node;
			node->mPrev = this;
		}
		else
		{
			Next<DoubleLinkedList>()->PushBack(node);
		}
	}

	void InsertBefore(DoubleLinkedList*node)
	{

	}

	void InsertAfter(DoubleLinkedList*node)
	{

	}

	void LeaveList()
	{
		if (mNext!=nullptr)
		{
			Next<DoubleLinkedList>()->mPrev = mPrev;
			mNext = nullptr;
		}
		if (mPrev!=nullptr)
		{
			Prev<DoubleLinkedList>()->mNext=mNext;
			mPrev = nullptr;
		}
	}

	template<typename T>
	T*Next()
	{
		return (T*)mNext;
	}

	template<typename T>
	T*Prev()
	{
		return (T*)mPrev;
	}
};