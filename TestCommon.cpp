#include "Random.h"
#include "Config.h"
#include "lexical_cast.h"
#include "BlockQueue.h"
#include "Singleton.h"
#include "Thread.h"
#include "ObjPool.h"
#include "ThreadPool.h"
#include "Log.h"
#include <iostream>
#include <time.h>
#include <unistd.h>
using namespace std;

void test_lexical_cast()
{
   cout<<lexical_cast<int>(1)<<endl;
   cout << lexical_cast<int>("1") << endl;
   cout << lexical_cast<long>("1") << endl;
   cout << lexical_cast<string>(1) << endl;
   cout << lexical_cast<bool>(1) << endl;
   cout << lexical_cast<double>("1.2") << endl;
   cout << lexical_cast<float>("1.2") << endl;
   string s = "true";
   cout << lexical_cast<bool>(s) << endl;
   char* p = "false";
   cout << lexical_cast<bool>(p) << endl;
   const char* q = "false";
   cout << lexical_cast<bool>(q) << endl;
   cout << lexical_cast<bool>("false") << endl;
}

class Single : public Singleton<Single>
{
public:

};

class TestThread :public Thread
{
public:
	void PrintTid()
	{
		cout << GetThreadId() << endl;
	}
	virtual bool Init()
	{
		cout << "init ..." << endl;
		return true;
	}
	virtual void ThreadFunc()
	{
		while(1)
		{
			cout << "thread ..." << endl;
			sleep(1);
		}
	}
};

class TestObj
{
public:
	TestObj(){}
	~TestObj(){}
	void Clear(){}
	void SetObjPoolId(int32_t nObjPoolId)
	{
		m_nObjPoolId = nObjPoolId;
	}
	int32_t GetObjPoolId(){ return m_nObjPoolId;}
private:
	int32_t m_nObjPoolId{0};

};

void TestPoolPrintWithParam(const std::string& str)
{
	cout << "this is thread pool running" << endl;
	if(str.size()>0)
	{
		cout << str << endl;
	}
}

void TestPoolPrint()
{
	cout << "this is thread pool running" << endl;
}

int main(int argc, char const *argv[])
{
	cout << "test random" << endl;
	auto Rand = Random::Instance();
	int nResult = Rand.rand<int>(10, 20);
	cout << nResult << endl;
	unsigned int unResult = Rand.rand<unsigned int>(10, 20);
	cout << unResult << endl;
	float fResult = Rand.randf<float>(10.0f, 20.0f);
	cout << fResult << endl;
	double dResult = Rand.randf<double>(10.0f, 20.0f);
	cout << dResult << endl;
	cout << "test config json" << endl;
	gPtr_Config.reset(new Config);
	gPtr_Config->LoadJson("config.json");
	rapidjson::Value& v = gPtr_Config->GetDom()["TestConfig"]["ServerIp"];
	cout << v.GetString() << endl;
	cout << "test lexical_cast" << endl;
	test_lexical_cast();

	cout << "test blockqueue" << endl;
	BlockQueue<std::string> blockQueue;
	blockQueue.Put("AAAAAA");
	blockQueue.Put("BBB");
	blockQueue.Put("BBBCCC");
	std::string str = blockQueue.Take();
	cout << str << endl;
	str = blockQueue.Take();
	cout << str << endl;
	str = blockQueue.Take();
	cout << str << endl;

	cout << "test singleton" << endl;
	Single& s1 = Single::Instance();
	Single& s2 = Single::Instance();
	cout << static_cast<void *>(&s1) << endl;
	cout << static_cast<void *>(&s2) << endl;

	cout << "test thread" << endl;
	// TestThread thread;
	// thread.Start();
	// while(1)
	// {
	// 	sleep(1);
	// }

	cout << "test creat obj by objpool" << endl;
	ObjPool<TestObj>::Instance().InitObjPool(10);
	TestObj* pObj = ObjPool<TestObj>::Instance().NewObj();
	cout << pObj->GetObjPoolId() << endl;
	pObj = ObjPool<TestObj>::Instance().NewObj();
	cout << pObj->GetObjPoolId() << endl;
	pObj = ObjPool<TestObj>::Instance().NewObj();
	cout << pObj->GetObjPoolId() << endl;
	ObjPool<TestObj>::Instance().ReleaseObj(pObj);
	cout << pObj->GetObjPoolId() << endl;
	cout << ObjPool<TestObj>::Instance().GetObjNum() << endl;
	cout << ObjPool<TestObj>::Instance().GetFreeObjNum() << endl;

	cout << "test thread pool" << endl;
	// ThreadPool threadPool;
	// threadPool.SetQueueMaxSize(5);
	// threadPool.Start(3);
	// threadPool.Run(TestPoolPrint);
	// threadPool.Run(TestPoolPrint);
	// for (int i = 0; i < 100; ++i)
	// {
	// 	char buf[32];
	// 	snprintf(buf, sizeof buf, "task %d", i);
	// 	threadPool.Run(std::bind(TestPoolPrintWithParam, std::string(buf)));
	// }
	// sleep(3);
	// threadPool.Stop();
	cout << "test log" <<endl;
	gPtr_Log.reset(new Log);
	gPtr_Log->InitLog("/var/log/testlog");
	LOGTRACE("test log trace %d", 100);

	while(1)
	{
		sleep(1);
	}
	return 0;


}