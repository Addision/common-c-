
#include "Util.h"
#include <vector>
#include <stdarg.h>
#include <math.h>
#include <string.h>

std::string TimeToDate(time_t t)
{
	struct tm* ptm = localtime(&t);
	char buf[32];
	memset(buf, '\0', sizeof(buf));
	strftime(buf, sizeof(buf), "%Y/%m/%d %H:%M:%S", ptm);
	std::string str = buf;
	return str;
}

time_t DateToTime(const std::string& date)
{
	struct tm stm;
	int year, month, day, hour, minute, second;
	sscanf(date.c_str(), "%d/%d/%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
	stm.tm_year = year - 1900;
	stm.tm_mon = month - 1;
	stm.tm_mday = day;
	stm.tm_hour = hour;
	stm.tm_min = minute;
	stm.tm_sec = second;
	stm.tm_isdst = 0;

	time_t t = mktime(&stm);
	return t;
}

bool IsFloatEqual(float a, float b)
{
	return ::fabs(a - b) < 0.0001;
}

std::string StringFormat(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	int nSize = std::vsnprintf(nullptr, 0, fmt, ap);
	std::vector<char> buff(nSize + 1, '\0');
	va_start(ap, fmt);
	std::vsnprintf(buff.data(), buff.size(), fmt, ap);
	va_end(ap);
	return buff.data();
}