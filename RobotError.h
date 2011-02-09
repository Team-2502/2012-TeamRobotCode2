#ifndef ROBOTERROR
#define ROBOTERROR

#include <string>

enum ErrorLevel { None, Warning, Critical, Fatal }; 
//Warning  | something went wrong that was then recovered.
//Critical | something went wrong that can not be recovered.
//Fatal    | something went wrong that needs the robot stopped.
//           For example: The motors have stopped responding, endangering people.

class RobotError
{
public:
	RobotError(ErrorLevel lvl, string message)
	{
		this->lvl = lvl;
		msg = message;
	}
	
	ErrorLevel getErrorLevel()             { return lvl; }
	void       setErrorLevel(ErrorLevel l) { lvl = l;    }
	string     getErrorMessage()           { return msg; }
	void       setErrorMessage(string str) { msg = str;  }
	
	static RobotError* NoError() { return new RobotError(None, "No errors have occurred."); }
	
private:
	ErrorLevel lvl;
	string msg;
};

#endif
