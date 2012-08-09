
#include "Singleton.h"
#include "DisplayWriter.h"
#include "DisplayWrapper.h"

DisplayWriter::DisplayWriter()
	: startingLine(-1)	// BEWARE - this is a half-baked object
	, reservedSize(0)
	, nextPrintfLine(0)
{
}

DisplayWriter::~DisplayWriter()
{
}

void DisplayWriter::Clear()
{
	if (reservedSize <= 0)
		return;

	if (startingLine >= 0)
	{
		DisplayWrapper::GetInstance()->clear(startingLine, reservedSize);
		nextPrintfLine = 0;
	}
}

void DisplayWriter::Reserve(int size)
{
	if (reservedSize == 0)	// do not allow re-reserving ... ignore such requests
	{
		reservedSize = size;
		startingLine = DisplayWrapper::GetInstance()->growBufferSize(size);
	}
}

int DisplayWriter::Printf(const char* format, ...)
{
	if (reservedSize <= 0)
		return 0;

	char buf[256];
	va_list args;
	va_start(args, format);
	int retlen = vsnprintf(buf, sizeof(buf), format, args);
	va_end(args);

	if (nextPrintfLine >= reservedSize)
		DisplayWrapper::GetInstance()->shift(startingLine, reservedSize);
	DisplayWrapper::GetInstance()->puts(startingLine + nextPrintfLine, buf);
	nextPrintfLine++;

	return retlen;
}

int DisplayWriter::PrintfLine(int line, const char* format, ...)
{
	if (reservedSize <= 0)
		return 0;

	char buf[256];
	va_list args;
	va_start(args, format);
	int retlen = vsnprintf(buf, sizeof(buf), format, args);
	va_end(args);

	if (line < reservedSize)
		DisplayWrapper::GetInstance()->puts(startingLine + line, buf);
	else
		Printf("DisplayWriter line exceeds reservation: %s\n", buf);

	return retlen;
}

