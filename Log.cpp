#include "Log.h"
#include <fstream>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include "lexical_cast.h"
#include <iostream>

std::unique_ptr<Log> gPtr_Log = nullptr;

void Log::WriteLog(const char* file, const char* func, int nLine, int nLogLevel, const char* fmt, ...)
{
	if(nLogLevel < m_nLogLevel)
		return;
	char timestr[50];
	memset(timestr, '\0', sizeof timestr);
	time_t now = time(0);
	strftime(timestr, sizeof timestr, "%Y-%m-%d %H:%M:%S", localtime(&now));

	std::string strLog = timestr;
	strLog.append(":");
	strLog.append(file);
	strLog.append(":");
	strLog.append(func);
	strLog.append(":");
	strLog.append(lexical_cast<std::string>(nLine));
	strLog.append(":");
	char content[500];
	memset(content, '\0', sizeof content);
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(content, sizeof(content)-1, fmt, ap);
	va_end(ap);
	strLog.append(content);
	m_oThreadPool.Run(std::bind(&Log::ThreadLog, this, strLog));
}


void Log::InitLog(char* path)
{
	m_logpath = path;
	m_nLogLevel = 1;
	m_oThreadPool.SetQueueMaxSize(10);
	m_oThreadPool.Start(2);
}


void Log::ThreadLog(const std::string& strLog)
{
	if(m_logpath == nullptr || strlen(m_logpath) == 0)
		return;

	std::string sLogPath = m_logpath;
	std::string::size_type find = sLogPath.find_last_of('/');
	std::string path = "";
	std::string sLogName = "";
	if(find != std::string::npos)
	{
		path = sLogPath.substr(0, find+1);
		sLogName = sLogPath.substr(find+1);
		char timestr[50];
		memset(timestr, '\0', sizeof timestr);
		time_t now = time(0);
		strftime(timestr, sizeof timestr, "%Y%m%d", localtime(&now));
		sLogName = timestr+sLogName;
	}
	sLogName = path+sLogName;
	const char* logpath = sLogName.c_str();
	//std::cout << "name==="<<sLogName << endl;
	fstream file;
	file.open(logpath, ios::out | ios::app);
	if(!file)
	{
		return;
	}
	const char* logbuf = strLog.c_str();
	file << logbuf;
	file << std::endl;
	file.flush();
	file.close();
}