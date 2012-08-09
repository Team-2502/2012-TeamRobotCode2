#ifndef DISPLAYWRAPPER_H
#define DISPLAYWRAPPER_H

#include <cstdarg>
#include <string>
#include <vector>

class DriverStationLCD;

/**
 * This wraps around the LCD Display for the driver station.
 * The only class that should call this is the DriverWriter.
 */
class DisplayWrapper
{
public:
	DisplayWrapper();
	~DisplayWrapper();
	
	/**
	 * Get the instance of the display wrapper.
	 */
	static DisplayWrapper* GetInstance();
	
	/**
	 * Set the scroll location of the buffer to display.
	 * 0.0 is the top and 1.0 is the bottom.
	 */
	void SetScrollLocation(float location);
	
	/**
	 * Send changes to the display
	 */
	void Output();
	
	/****************************************************************************/
	// Only the DisplayWriter should be using the following methods

	/**
	 * Clear part of the display buffer
	 */
	void clear(unsigned start, unsigned size);

	/**
	 * Clear ALL of the display buffer
	 */
	void clear();
	
	/**
	 * Write buffer to the display.
	 */
	void puts(unsigned line, const char* buffer);
	
	/**
	 * Set the size of the buffer (in lines).
	 */
	void setBufferSize(unsigned size);
	
	/**
	 * Grow the size of the buffer (in lines).
	 */
	unsigned growBufferSize(unsigned size);
	
	/**
	 * shift a section of the lines up
	 */
	void shift(unsigned start, unsigned size);

	/**
	 * answers true if the specified line is displayed on the LCD screen
	 */
	bool isLineVisible(unsigned line);

private:
	void shift();

	std::vector<std::string> buffer;
	unsigned bufferSize;
	unsigned bufferLocation;
	unsigned outputLocation;
	DriverStationLCD* display;
	bool displayDirty;

	static DisplayWrapper* Instance;
};

#endif // DISPLAY
