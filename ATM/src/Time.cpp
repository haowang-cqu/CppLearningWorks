#include "Time.h"
std::string Time::getTime()
{
	time_t tt = time(NULL);
	tm *t = localtime(&tt);
	std::string time_now;
	std::string temp;
	std::stringstream ss;
	ss << t->tm_year + 1900 << "/";
	ss << t->tm_mon + 1 << "/";
	ss << t->tm_mday;
	ss >> temp;
	time_now.append(temp + "  ");
	std::stringstream sss;
	sss << t->tm_hour << ":";
	sss << t->tm_min << ":";
	sss << t->tm_sec;
	sss >> temp;
	time_now.append(temp);
	return time_now;
}
