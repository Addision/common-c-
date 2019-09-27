#pragma once

#include <thread>
#include <functional>

class Thread
{
public:
	Thread() {}
	virtual ~Thread(){}
	virtual void Start();
	virtual void Join();
	virtual bool Init(){ return false;}
	virtual void ThreadFunc() = 0;
	std::thread::id GetThreadId() { return m_oThread.get_id();}
	bool IsActive() { return m_bActive;}
private:
	std::thread m_oThread;
	bool m_bActive{false};
};