#include "Thread.h"

void Thread::Start()
{
	Init();
	m_oThread = std::thread(std::bind(&Thread::ThreadFunc, this));
	m_bActive = true;
}

void Thread::Join()
{
	if(m_oThread.joinable())
	{
		m_oThread.join();
	}
}

