#include <cmath>
#include <cstdio>
#include <cstdarg>

#include "DisplayWrapper.h"

DisplayWrapper* DisplayWrapper::instance = new DisplayWrapper();

DisplayWrapper::DisplayWrapper()
{
	this->bufferSize = 0;
	this->outputLocation = 0;
	this->display = DriverStationLCD::GetInstance();
	SetBufferSize(12);
}

void DisplayWrapper::Clear()
{
	for(unsigned i = 0; i < this->bufferSize; i++)
	{
		this->buffer[i].clear();
	}
	this->bufferLocation = 0;
}

DisplayWrapper* DisplayWrapper::GetInstance()
{
	return instance;
}

void DisplayWrapper::Output()
{
	for(unsigned i = this->outputLocation; i < this->outputLocation + 6; i++)
	{
		if(i >= this->bufferSize)
			break;
		else
		{
			switch(i - this->outputLocation)
			{
			case 0:
				this->display->PrintfLine(DriverStationLCD::kUser_Line1, this->buffer[i].c_str());
				break;
			case 1:
				this->display->PrintfLine(DriverStationLCD::kUser_Line2, this->buffer[i].c_str());
				break;
			case 2:
				this->display->PrintfLine(DriverStationLCD::kUser_Line3, this->buffer[i].c_str());
				break;
			case 3:
				this->display->PrintfLine(DriverStationLCD::kUser_Line4, this->buffer[i].c_str());
				break;
			case 4:
				this->display->PrintfLine(DriverStationLCD::kUser_Line5, this->buffer[i].c_str());
				break;
			case 5:
				this->display->PrintfLine(DriverStationLCD::kUser_Line6, this->buffer[i].c_str());
				break;
			}
		}
	}
	this->display->UpdateLCD();
}

void DisplayWrapper::Printf(const char* format, ...)
{
	char buf[256];
	va_list args;
	va_start (args, format);
	vsnprintf ( buf, 256, format, args );
	va_end (args);
	this->buffer[this->bufferLocation] = buf;
	this->bufferLocation++;
	if(this->bufferLocation >= this->bufferSize)
		Shift();
}

void DisplayWrapper::PrintfLine(unsigned int line, const char* format, ...)
{
	if(line < this->bufferSize)
	{
		char buf[256];
		va_list args;
		va_start (args, format);
		vsnprintf ( buf, 256, format, args);
		va_end (args);
		this->buffer[line] = buf;
	}
}

void DisplayWrapper::SetBufferSize(unsigned size)
{
	Clear();
	this->bufferSize = size;
	this->buffer.clear();
	this->buffer.resize(size);
}

void DisplayWrapper::SetScrollLocation(float location)
{
	this->outputLocation = (unsigned)std::floor(((location + 1.0) / 2.0) * (float)(this->bufferSize - 7));
}

void DisplayWrapper::Shift()
{
	for(unsigned i = 0; i < this->bufferSize - 1; i++)
	{
		this->buffer[i] = this->buffer[i + 1];
	}
	this->buffer[this->bufferSize - 1].clear();
	this->bufferLocation--;
}
