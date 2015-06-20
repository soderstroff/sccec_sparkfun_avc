#include "common.h"
#include "telemetry.h"

#include "motion.h"
#include "pid.h"
#include "nav.h"

errParams headingParams, throttleParams;

/* Forward Declarations */
void setThrottlePID(char*, char*);
void setHeadingPID(char*, char*);

void initMotion()
{
	setErrParams(&headingParams, 3.f, 2.f, 0.1f, .1f); /* Heading PID values. */

	/* Event Handlers */
	addTelemetryEventHandler(setHeadingPID);
	addTelemetryEventHandler(setThrottlePID);
}

void updateMotion()
{
	motionData* MotionData = getMotionData();
	float adjustedHeading = pidAdjust(MotionData->heading, &headingParams);
}

/* Event handlers */

void setHeadingPID(char *key, char *paramsString)
{	/* Event handler for the "setHeadingPID" key. */

 	if ( strcmp(key, "setHeadingPID") == 0 )
	{
		float* params = parseToArray(paramsString, 4);
		setErrParams( &headingParams, params[0], params[1], params[2], params[3] );
		free(params);
	}
}

void setThrottlePID(char *key, char *paramsString)
{	/* Event handler for the "setMotionPID" key. */

	if ( strcmp(key, "setThrottlePID") == 0 )
	{
		float* params = parseToArray(paramsString, 4);
		setErrParams( &throttleParams, params[0], params[1], params[2], params[3] );
		free(params);
	}
}
