/*
 * SteeringProcess.h
 *
 *  Created on: August 18, 2026
 *      Author: pinuela.loic
 */

#ifndef INC_STEERINGPROCESS_H_
#define INC_STEERINGPROCESS_H_

#include "Project_Defines.h"
#include <math.h>

int16_t count;

bool steeringProcess(Event* ev);

void initialisation_steering();
void target_position(int32_t target);


#endif /* INC_STEERINGPROCESS_H_ */
