#pragma once

#include "Lock.h"
#include <deque>

template<class T>
class BlockQueue
{
public:
	BlockQueue():mMutex(),mCond(),mQueue(){}
	~BlockQueue(){mQueue.clear();}
	void Put(const T& x)
	{
		AutoLock Lock(mMutex);
		mQueue.push_back(x);
		mCond.notify_all();
	}
	void Put(T&& x)
	{
		AutoLock Lock(mMutex);
		mQueue.push_back(std::move(x));
		mCond.notify_all();
	}

	T Take()
	{
		AutoLock Lock(mMutex);
		while(mQueue.empty())
		{
			mCond.wait(Lock);
		}
		T x = mQueue.front();
		mQueue.pop_front();
		return x;
	}

	size_t Size()
	{
		AutoLock Lock(mMutex);
		return mQueue.size();
	}
private:
	Mutex mMutex;
	Condition mCond;
	std::deque<T> mQueue;
};