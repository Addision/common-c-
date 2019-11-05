#pragma once

#include <time.h>
#include <string>


bool IsFloatEqual(float a, float b);
std::string StringFormat(const char* fmt, ...);

std::string TimeToDate(time_t t);
time_t DateToTime(const std::string &date);
int GetDigitDate(time_t t);
time_t GetTimeSeconds();
time_t GetTimeMs();
time_t GetTimeMMs();

std::string &StringTrim(std::string &s);