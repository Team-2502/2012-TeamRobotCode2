#ifndef OUTPUT_H
#define OUTPUT_H

#include "WPILib.h"
#include <Dashboard.h>
using std::string;

inline string boolToString(bool in) { return ((in)?"Yes":"No"); }

class Output
{
public:
	Output();
	static void errorCode(int error);
	static void setAutocompressing(bool a){autoCompressing=a; print();}
	static void setCompressing(bool a){compressing=a; print();}
	static void setFullyPressurized(bool a){fullyPressurized=a; print();}
	static void setKicking(bool a){kicking=a; print();}
private:
	static DriverStationLCD *driverStationLCD;
	static bool autoCompressing;
	static bool compressing;
	static bool fullyPressurized;
	static bool kicking;
	
	static void print();
	static void clear();
};

#endif
