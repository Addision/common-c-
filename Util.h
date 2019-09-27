#pragma once

#include <time.h>
#include <string>

std::string TimeToDate(time_t t);
time_t DateToTime(const std::string& date);
bool IsFloatEqual(float a, float b);

std::string StringFormat(const char* fmt, ...);