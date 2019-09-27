#pragma once

#include <string>
#include <memory>
#include "ThreadPool.h"


class Log
{
public:
	enum eLogLevel{
		TRACE = 1,
		DEBUG = 2,
		INFO = 3,
		WARN = 4,
		ERROR = 5,
		FATAL = 6,
	};
	void InitLog(char* path = "/var/log/mylog");
	void WriteLog(const char* file, const char* func, int nLine, int nLogLevel, const char* fmt, ...);
	void ThreadLog(const std::string& strLog);
private:
	char* m_logpath{nullptr};
	int m_nLogLevel{1};
	ThreadPool m_oThreadPool;
};

extern std::unique_ptr<Log> gPtr_Log;

#define LOGTRACE(...) gPtr_Log->WriteLog(__FILE__,__FUNCTION__, __LINE__, Log::eLogLevel::TRACE, __VA_ARGS__);
#define LOGDEBUG(...) gPtr_Log->WriteLog(__FILE__,__FUNCTION__, __LINE__, Log::eLogLevel::DEBUG, __VA_ARGS__)
#define LOGINFO(...) gPtr_Log->WriteLog(__FILE__,__FUNCTION__, __LINE__, Log::eLogLevel::INFO, __VA_ARGS__)
#define LOGWARN(...) gPtr_Log->WriteLog(__FILE__,__FUNCTION__, __LINE__, Log::eLogLevel::WARN, __VA_ARGS__)
#define LOGERROR(...) gPtr_Log->WriteLog(__FILE__,__FUNCTION__, __LINE__, Log::eLogLevel::ERROR, __VA_ARGS__)
#define LOGFATAL(...) gPtr_Log->WriteLog(__FILE__,__FUNCTION__, __LINE__, Log::eLogLevel::FATAL, __VA_ARGS__)



