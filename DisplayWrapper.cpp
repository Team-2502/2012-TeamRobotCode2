#include <cmath>
#include <cstdio>
#include <cstdarg>

#include "DisplayWrapper.h"

#include "DriverStationLCD.h"


DisplayWrapper* DisplayWrapper::Instance = NULL;

DisplayWrapper::DisplayWrapper()
{
	bufferSize = 0;
	outputLocation = 0;
	setBufferSize(0);
	display = DriverStationLCD::GetInstance();
	displayDirty = true;
}

DisplayWrapper::~DisplayWrapper()
{
	Instance = NULL;
}

bool DisplayWrapper::isLineVisible(unsigned line)
{
	return (outputLocation <= line && line < outputLocation + 6);
}

void DisplayWrapper::clear(unsigned start, unsigned count)
{
	for (unsigned i = 0; i < count; i++)
	{
		buffer[start+i].clear();
		if (isLineVisible(start+i))
			displayDirty = true;
	}
}

void DisplayWrapper::clear()
{
	clear(0, bufferSize);
	bufferLocation = 0;
}

DisplayWrapper* DisplayWrapper::GetInstance()
{
	if (!Instance)
		Instance = new DisplayWrapper();
	return Instance;
}

void DisplayWrapper::Output()
{
	if (false == displayDirty)
		return;

	displayDirty = false;
	for (unsigned i = outputLocation; i < outputLocation + 6; i++)
	{
		if (i >= bufferSize)
			break;
		else
		{
			switch(i - outputLocation)
			{
			case 0:
				display->PrintfLine(DriverStationLCD::kUser_Line1, buffer[i].c_str());
				break;
			case 1:
				display->PrintfLine(DriverStationLCD::kUser_Line2, buffer[i].c_str());
				break;
			case 2:
				display->PrintfLine(DriverStationLCD::kUser_Line3, buffer[i].c_str());
				break;
			case 3:
				display->PrintfLine(DriverStationLCD::kUser_Line4, buffer[i].c_str());
				break;
			case 4:
				display->PrintfLine(DriverStationLCD::kUser_Line5, buffer[i].c_str());
				break;
			case 5:
				display->PrintfLine(DriverStationLCD::kUser_Line6, buffer[i].c_str());
				break;
			}
		}
	}
	display->UpdateLCD();
}

void DisplayWrapper::puts(unsigned int line, const char* buf)
{
	buffer[line] = buf;
	if (isLineVisible(line))
		displayDirty = true;
}

void DisplayWrapper::setBufferSize(unsigned size)
{
	clear();
	bufferSize = size;
	buffer.clear();
	buffer.resize(size);
}

unsigned DisplayWrapper::growBufferSize(unsigned count)
{
	unsigned priorSize = bufferSize;
	bufferSize += count;
	buffer.resize(bufferSize);
	return priorSize;
}

void DisplayWrapper::SetScrollLocation(float location)
{
	outputLocation = (unsigned)std::floor(((location + 1.0) / 2.0) * (float)(bufferSize - 7));
}

void DisplayWrapper::shift(unsigned int start, unsigned int count)
{
	for (unsigned i = start; i < count - 1; i++)
	{
		buffer[i] = buffer[i + 1];
		if (isLineVisible(i))
			displayDirty = true;
	}
	buffer[count - 1].clear();
	if (isLineVisible(count - 1))
		displayDirty = true;
}

void DisplayWrapper::shift()
{
	shift(0, bufferSize);
	bufferLocation--;
}

