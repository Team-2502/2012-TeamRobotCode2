#ifndef MINIBOT_H
#define MINIBOT_H

#include "WPILib.h"

class Minibot
{
public:
	Minibot();
	~Minibot();
	
	void Deploy();
	void StopDeploy();
	void ToggleDeploy();
private:
	bool deployed;
	Servo* servo1;
	Servo* servo2;
	Servo* servo3;
};

#endif // MINIBOT
