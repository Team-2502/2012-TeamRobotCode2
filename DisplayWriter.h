#ifndef DISPLAYWRITER_H
#define DISPLAYWRITER_H

#include <cstdarg>

/**
 * This wraps around the LCD Display for the driver station.
 */
class DisplayWriter
{
public:
	DisplayWriter();
	~DisplayWriter();

	/**
	 * Clear the display buffer.
	 */
	void Clear();

	/**
	 * specify the number of lines to reserve for this writer
	 * the lines are on a first-come-first-served basis
	 */
	void Reserve(int size);

	/**
	 * Printf to the next line in the display, this "scrolls".
	 */
	int Printf(const char* format, ...);

	/**
	 * Printf at a specific line.
	 */
	int PrintfLine(int line, const char* format, ...);

private:
	int startingLine;
	int reservedSize;
	int nextPrintfLine;
};

#endif // DISPLAYWRITER_H
