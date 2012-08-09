#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

#include <WPILib.h>

/**
 * A logger for diagnostic purposes.
 */
class Logger
{
public:
	/**
	 * Constructor.
	 * 
	 * \param fileName the name of the file to log output to.
	 */
	Logger(const std::string& fileName);
	
	/**
	 * Destructor.
	 */
	~Logger();
	
	/**
	 * Log a formatted string to the log.
	 * 
	 * \param format the format string.
	 */
	void Logf(const char* format, ...);
	void LogVar(const char* name, const char* format, ...);
	
private:
	Timer timer;
	std::ofstream file;
};

#endif // LOGGER_H
