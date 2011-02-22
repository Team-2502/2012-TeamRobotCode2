#ifndef ARMCLASS_H
#define ARMCLASS_H

#include "WPILib.h"
#include "JAGPidSource.h"

typedef enum Level {
	sideFirst=29375,
	middleFirst=37275,
	loadingLevel=54600,
	sideSecond=64625,
	middleSecond=72625
};

typedef enum Shape {
	triangle=950,
	square=1000,
	circle=1250
};

class Arm
{
	public:
		static Arm* GetInstance();
		~Arm();
		void setSpeed(float speed);
		void abruptStop();
		
	private:
		Arm();
		PIDController* armPID;
		Jaguar* armJag;
		JagPIDSource* pidSource;
		static Arm* instance;
};

#endif // ARM
