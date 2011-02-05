#ifndef DISPLAYWRAPPER_H
#define DISPLAYWRAPPER_H

#include <string>
#include <vector>

#include "WPILib.h"

/**
 * This wraps around the LCD Display.
 */
class DisplayWrapper
{
public:
	DisplayWrapper();
	
	void Clear();
	void Output();
	void Printf(const char* format, ...);
	void PrintfLine(unsigned line, const char* format, ...);
	void SetScrollLocation(float location);
	void SetBufferSize(unsigned size);
	
private:
	std::vector<std::string> buffer;
	unsigned bufferSize;
	unsigned bufferLocation;
	unsigned outputLocation;
	DriverStationLCD* display;
	
	void Shift();
};

#endif // DISPLAY
