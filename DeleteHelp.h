#pragma once

template<class T>
class DeleteHelp
{
public:
	DeleteHelp(T* t):m_pT(t){}
	~DeleteHelp()
	{
		if(m_pT)
		{
			delete m_pT;
			m_pT = nullptr;
		}
	}
private:
	T* m_pT;
};