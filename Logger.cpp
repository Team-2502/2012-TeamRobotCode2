#include <cstdarg>
#include <cstdio>
#include "Timer.h"
#include "Logger.h"

using std::clock;
using std::endl;
using std::string;

Logger::Logger(const string& fileName)
{
	timer.Start();
	this->file.open(fileName.c_str(), std::ios::trunc);
}

Logger::~Logger()
{
	this->file.close();
}

void Logger::Logf(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	char buffer[256];
	vsnprintf(buffer, 255, format, args);
	va_end(args);
	
	//Create a timestamp
	char message[300];
	double time = timer.Get();
	sprintf(message, "[%f] %s", time, buffer);
	
	this->file << message << endl;
}

void Logger::LogVar(const char* name, const char* format, ...)
{
	va_list args;
	va_start(args,format);
	char buffer[256];
	
}

