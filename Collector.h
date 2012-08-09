#ifndef COLLECTOR_H
#define COLLECTOR_H

#include <WPILib.h>
#include "Constants.h"
#include "SharpIR.h"
#include "DisplayWriter.h"

/**
 * The state that the Collector is in.
 */
enum CollectorState 
{
	OFF, /**< The Collector is not doing anything. */
	LOOKING_FOR_BALLS, /**< Collector is looking for balls to collect. */
	STAGE1, /**< The collector is moving the bottom belt. */
	STAGE2, /**< The collector is moving the top belt. */
	PREPARE_TO_SHOOT, /**< The collector is holding the ball, waiting for the shooter. */
	SHOOTING, /**< The collector is feeding balls into the shooter. */
	EJECTING /**< The collector is ejecting the balls from where they came in. */
};

/**
 * The state of the ramp manipulator.
 */
enum RampState 
{
	RAMP_OFF, /**< Not moving. */
	UP, /**< Moving up. */
	DOWN /**< Moving down. */
};

/**
 * The part of the Robot that collects the balls from the field for storage.
 */
class Collector
{
public:
	Collector();
	~Collector();
	
	/**
	 * Shoot balls that have been collected.
	 * 
	 * \return if a ball shot.
	 */
	bool Shoot();
	
	/**
	 * Use the ramp manipulator.
	 */
	void ManipulateRamp(RampState state);
	
	/**
	 * Stop the Collector from running.
	 */
	void Stop();
	
	/**
	 * Eject all balls in the collector.
	 */
	void Eject();
	
	/**
	 * Start running the collector.
	 */
	void Start();
	
	/**
	 * Set the internal count of the number balls stored.
	 * 
	 * \param balls the number of balls that are currently stored.
	 */
	static void SetBallCount( int balls );
	
	/**
	 * Prepare to feed a ball to the shooter.
	 */
	void PrepareToShoot();
	
	/**
	 * Modify the ball count.
	 * 
	 * \param c the change in the ball count.
	 */
	void ChangeBallCountBy(int c);
	
	/**
	 * Get the number of balls that are currently stored in the Collector.
	 */
	int GetBalls();

	void reservePrimaryLines();
	void reserveSecondaryLines();
	
	DisplayWriter primaryDisplay;
	DisplayWriter secondaryDisplay;

private:
	static unsigned balls;
	static Victor *grabber;
	static Victor *lifter;
	static SharpIR *frontIR;
	static SharpIR *frontMiddleIR;
	static SharpIR *middleIR;
	static SharpIR *topIR;
	Task *collectorTask;
	//Relay *strike1;
	Victor* rampVictor;
	Relay *rampStrike;
	static CollectorState collectorState;
	static Timer* prepTimer;
	static void ThreadLoop();
	static void RejectBall();
};

#endif
