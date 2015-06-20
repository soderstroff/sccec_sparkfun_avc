/*
 * Sierra College Computer Engineering Club: Sparkfun AVC
 * Navigation Subsystem
 * Authors: Kristoffer Semelka
 */
 
#include <stdlib.h>
#include <math.h>

#include "common.h"
#include "telemetry.h"
#include "sensors.h"
#include "nav.h"
#include "bezier.h"

motionData MotionData;
const float magneticDeclination;

/* Forward declarations */
float findCorrection(float, float);

void initNav()
{
	initMap(map); /* Map is defined in common.h */
}

void updateNav()
{
	/*
	  This function:
	  - gets the navigation data from sensors (heading, position)
	  - gets desired values from Bezier Curves (position, velocity)
	  - finds difference between desired position and real position
	  to obtain desired heading;
	  - find difference between desired heading and real heading
	  - creates instructions for motion module;
	  - and pushes instructions to MotionData
	  on every update.
	*/
	navData* NavData;
	float desiredHeading, headingDiff, adjustedHeading;

	NavData = getNavData();
	desiredHeading = getDesiredHeading(NavData->position);
	headingDiff = findCorrection(NavData->heading, desiredHeading);
	MotionData.heading = headingDiff;
  
}

motionData* getMotionData()
{
	return &MotionData;
}

float findCorrection(float current, float desired)
{
	/*
	  Takes the current heading and desired heading, and
	  finds the (shortest, signed) difference between the two.
	*/

	float correction = desired - current;

	if ( fabs(correction) > 180)
		{ /* Angle too large? Use the other angle, in the other direction */

			if ( correction > 0)
				/* Were we going left (positive theta)? Go right instead. */
				{ correction -= 360.f; }
			else
				/* Were we going right (negative theta)? Go left instead. */
				{ correction += 360.f; }
		}

	return correction;
}


